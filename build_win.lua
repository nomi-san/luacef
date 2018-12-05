local win32 = package.config:sub(1,1) == '\\' and true or false

function scandir(d)
    local i, t, p = 0, {}, io.popen('dir "'..d..'" /b ') -- "ls -a" for linux/sh
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
	if win32 then
		file = string.gsub(file, '/', '\\')
		os.execute('del /S /Q '..file)
	else
		os.execute('rm '..file)
	end
end

function mkdir(dir)
	if win32 then dir = string.gsub(dir, '/', '\\') end
	os.execute('mkdir '..dir)
end

function rmdir(dir)
	if win32 then dir = string.gsub(dir, '/', '\\') end
	os.execute('rmdir '..dir)
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
    exec(cc .. ' -shared -w -D_MSC_VER -DBUILD_AS_DLL -D_WIN32 -D_NDEBUG -Ideps/lua/src -Ideps/cef -c -o ./build/obj/' .. l[m] .. '.o '.. c[m])
    print('    ' .. l[m] .. '.c -> ' .. l[m] .. '.o' )
end

print("# Linking library...")
exec(cc .. ' -shared -o ./build/luacef.dll ./build/obj/*.o -Ldeps/lua -Ldeps/cef -llua53 -llibcef -lole32')
print("    -> luacef.dll")

--exec('del *.o')
print("# Done.\n")
