objects = main.o partition.o gpt.o
CPPFLAGS += -std=c++11 -Iinclude/

mksysimg: $(addprefix src/, $(objects))
	mkdir -p bin
	g++ $(CPPFLAGS) $(addprefix src/, $(objects)) -lfsutil -o bin/mksysimg

install:
	cp bin/mksysimg /bin
