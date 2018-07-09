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

------------------------------------------------------------

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


ec = os.execute
cc = 'gcc -std=gnu99 '
ec('del luacef.dll')

for i=1, #c do
	print(c[i])
end

--[[
a = cc .. '-shared -I../lua/src -I../cef -o luacef.dll '

for m = 1, #c do
	if l[m] == 'luacef' then 
		ec(cc .. ' -shared -DBUILD_AS_DLL -D_WIN32 -D_NDEBUG -I../lua/src -I../cef -c -o ' .. l[m] .. '.o '.. c[m])
	else
		ec(cc .. ' -D_WIN32 -D_NDEBUG -I../lua/src -I../cef -c -o ' .. l[m] .. '.o '.. c[m])
	end
	a = a .. l[m] .. '.o '
end
--]]

a = cc .. ' -shared -DBUILD_AS_DLL -D_WIN32 -D_NDEBUG -I../lua/src -I../cef -o luacef.dll '
for m = 1, #c do
	a = a .. c[m] .. ' '
end

ec( a .. ' -L../lua -L../cef -llua53 -llibcef -lole32')
--ec('del *.o')
