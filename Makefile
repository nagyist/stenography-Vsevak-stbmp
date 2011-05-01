CC= g++
PARAMS= -O3 -static -lpthread
all:
	$(CC) ./stbmp.cpp -o ./stbmp $(PARAMS)
debug: PARAMS += -DDEBUG -g
debug: 
	$(CC) ./stbmp.cpp -o ./Debug/stbmp $(PARAMS)
stbmp: stbmp.o
	$(CC) ./stbmp.o -o ./stbmp $(PARAMS)
stbmp.o:
	$(CC) ./stbmp.cpp -c -o ./stbmp.o $(PARAMS)
clean:
	rm -f ./*.o
