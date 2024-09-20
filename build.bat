@echo off

if not exist build mkdir build

set LIBS=-lgdi32.lib -luser32.lib -lshell32 -lopengl32.lib
set OPTIONS=-g -O0 -Wall -Wpedantic -Wno-newline-eof -Wno-unused-function -Wno-format
set OUT=%cd%\build\voyage.exe

pushd build
clang -o%OUT% %OPTIONS% ..\source\build.c %LIBS%
popd