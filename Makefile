
boomer_boy: main.c game.h game.c input.h input.c levels.h Makefile
	gcc -o boomer_boy -g main.c input.c game.c -L raylib/lib/ -lraylib -lm

boomer_boy.exe: main.c game.h game.c input.h input.c levels.h Makefile
	x86_64-w64-mingw32-gcc -fPIC -o boomer_boy main.c input.c game.c -L raylib-5.5_win64_mingw-w64/lib -lraylib -lm -lwinmm -lgdi32

run: boomer_boy 
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:raylib/lib/ ./boomer_boy      

clean:  
	rm boomer_boy; rm boomer_boy.exe; rm boomer_boy.zip

ship: boomer_boy boomer_boy.exe
	zip boomer_boy.zip boomer_boy.exe --encrypt
