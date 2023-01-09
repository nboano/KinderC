@echo off
set cpath=%1
set wasmpath=%2
shift
shift
clang --target=wasm32 -Wl,--no-entry -Wl,--export-dynamic -Wl,--allow-undefined -Wl,--lto-O3 -Wl,--import-memory -O3 -s -flto -nostdlib -fdeclspec -o %wasmpath% %cpath%
@echo on