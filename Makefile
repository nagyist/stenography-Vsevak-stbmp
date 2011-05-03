CC = g++
PARAMS= -O3 -static -lpthread
all:
	$(CC) ./stbmp.cpp -o ./stbmp $(PARAMS)
	strip -s ./stbmp
debug: PARAMS += -DDEBUG -g3
debug: 
	$(CC) ./stbmp.cpp -o ./Debug/stbmp $(PARAMS)
stbmp: stbmp.o
	$(CC) ./stbmp.cpp -o ./stbmp $(PARAMS)
clean:
	rm -f ./*.o
