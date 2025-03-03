boomer_boy: main.c game.h game.c input.h input.c levels.h Makefile
	gcc -o boomer_boy -g main.c input.c game.c -I ../raylib/include -L ../raylib/lib/ -lraylib -lm

boomer_boy.exe: main.c game.h game.c input.h input.c levels.h Makefile
	x86_64-w64-mingw32-gcc -fPIC -o boomer_boy main.c input.c game.c -I ../raylib/include -L ../raylib-5.5_win64_mingw-w64/lib -lraylib -lm -lwinmm -lgdi32

# Taken from https://github.com/bradmartin333/WSL2RaylibWASM.git
# Build, and then run python3 -m http.server in build. This will create a pass through http server on port 8000. 
build/boomer_boy.html: main.c game.h game.c input.h input.c levels.h Makefile
	emcc -o build/boomer_boy.html main.c game.c input.c -Wall -D_DEFAULT_SOURCE -Wmissing-braces -Wunused-result -Os -I. -I ../raylib_src/src/ -I ../raylib_src/src/external/ -L. -L ../raylib_src/src/ -s USE_GLFW=3 -s ASYNCIFY -s TOTAL_MEMORY=67108864 -s FORCE_FILESYSTEM=1 --shell-file ./build/shell.html ../raylib_src/src/libraylib.a  -DPLATFORM_WEB -s EXPORTED_FUNCTIONS=[\"_free\",\"_malloc\",\"_main\"] -s EXPORTED_RUNTIME_METHODS=ccall

run: boomer_boy 
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../raylib/lib/ ./boomer_boy      

clean:  
	rm boomer_boy; rm boomer_boy.exe; rm boomer_boy.zip

ship: boomer_boy boomer_boy.exe
	zip boomer_boy.zip boomer_boy.exe --encrypt

build_all: boomer_boy boomer_boy.exe build/boomer_boy.html
