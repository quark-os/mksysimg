objects = main.o partition.o gpt.o
CPPFLAGS += -std=c++11 -lfsutil -Iinclude/

mksysimg: $(addprefix src/, $(objects))
	g++ $(CPPFLAGS) $(addprefix src/, $(objects)) -o bin/mksysimg
