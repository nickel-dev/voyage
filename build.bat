@echo off

if not exist build mkdir build

set LIBS=-lgdi32 -luser32 -lshell32 -lopengl32.lib -lkernel32
set OPTIONS=-fuse-ld=lld -g -O0 -femit-all-decls -Wl,/subsystem:console -w -Wno-strict-prototypes -Wno-newline-eof -Wno-unused-function -Wno-format -Wno-unused-parameter
set OUT=%cd%\build\voyage.exe

pushd build
clang -o%OUT% %OPTIONS% ..\source\build.c %LIBS%
popd