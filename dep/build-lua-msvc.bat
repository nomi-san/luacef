@echo off

cl >nul 2>&1 && (
    cd lua-5.3.4
    cl /MD /O2 /c /DLUA_BUILD_AS_DLL src/*.c
    ren lua.obj lua.o
    ren luac.obj luac.o
    link /DLL /IMPLIB:lua53.lib /OUT:lua53.dll *.obj 
    link /OUT:lua.exe lua.o lua53.lib 
    lib /OUT:lua53-static.lib *.obj
    link /OUT:luac.exe luac.o lua53-static.lib
    del *.exp *.obj *.o
    cd ..
) || (
    echo cl.exe not found
)
