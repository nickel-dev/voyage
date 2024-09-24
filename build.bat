@echo off

if not exist build mkdir build

set LIBS=-lgdi32 -luser32 -lshell32 -lopengl32.lib -lkernel32
set OPTIONS=-fuse-ld=lld -g -O0 -femit-all-decls -Wl,/subsystem:console -Wno-pointer-sign -Wno-format
set OUT=%cd%\build\voyage.exe

pushd build
clang -o%OUT% %OPTIONS% ..\source\build.c %LIBS%
popd