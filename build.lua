local win32 = package.config:sub(1,1) == '\\' and true or false

function path(path)
	if win32 then
		path = string.gsub(path, '/', '\\')
	else
		path = string.gsub(path, '\\', '/')
	end
	return path
end

function scandir(d)
	local i, t, p = 0, {}, io.popen(win32 and ('dir "'..d..'" /b ') or ('ls -a "'..d..'" '))
	for f in p:lines() do
		i = i + 1; t[i] = f
	end
	p:close()
	return t
end

function findLast(s, p)
	local f = s:reverse():find(p:reverse(), nil, true)
	return f and #s - #p - f + 2 or f
end

function exists(file)
   local ok, err, code = os.rename(file, file)
   if not ok then
	  if code == 13 then
		 return true
	  end
   end
   return ok, err
end

function isdir(path)
   return exists(path.."/")
end

function del(file)
	file = path(file)
	if win32 then
		os.execute('del /S /Q '..file)
	else
		os.execute('rm -r '..file)
	end
end

function mkdir(dir)
	os.execute('mkdir '..path(dir))
end

function rmdir(dir)
	os.execute('rmdir '..path(dir))
end

--------------------------------------------------------------
--    src/
--     |--*.c
--     |--*dir/
--     |    |--*.c
--     |    ..
--     ..
--

dir = 'src'
c, d, l = {}, {}, {}

for k, v in pairs(scandir(dir)) do
	if not findLast(v, '.') then
		d[#d+1] = dir..'/'..v
	elseif  findLast(v, '.c') then
		c[#c+1] = dir..'/'..v
		l[#l+1] = v:gsub('%.c', '')
	end
end

for n = 1, #d do
	for k, v in pairs(scandir(d[n])) do
		if findLast(v, '.c') then
			c[#c+1] = d[n]..'/'..v
			l[#l+1] = v:gsub('%.c', '')
		end
	end
end

function exec(cmd)
	local _,__,c = os.execute(cmd)
	if c > 0 then
		print('build error!')
		os.exit()
	end
end

cc = 'gcc -std=gnu99 '

if (isdir('build')) then
	if (isdir('build/obj')) then 
		del('build/obj/*')
		rmdir('build/obj')
	end
	del('build/*')
	rmdir('build')
end

mkdir('build')
mkdir('build/obj')

print("# Generating object...")
for m = 1, #c do
	exec(cc .. ' -std=c99 -w -fPIC -I./deps/lua53/src -I./deps/cef -c -o ./build/obj/' .. l[m] .. '.o '.. c[m])
	print('    ./' .. c[m] .. ' -> ./build/obj/' .. l[m] .. '.o' )
end

print("# Linking library...")
if win32 then
	exec(cc .. ' -shared -o ./build/luacef.dll ./build/obj/*.o -Ldeps/lua53 -Ldeps/cef -llua53 -llibcef -lole32')
	print("    -> ./build/luacef.dll")
else
	cef_dir = 'cef_minimal/Release' -- directoty which included `libcef.so`
	exec(cc .. ' -std=c99 -shared -o ./build/luacef.so ./build/obj/*.o -Wl,-rpath,. -L./ -L./'..cef_dir..' -lcef')
	print("    -> ./build/luacef.so")
end

print("# Done.\n")
