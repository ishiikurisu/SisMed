EXE = test.exe
LIB = filters.o
flags = -Wall -lm -O2

do: build run clean

build: filters
	g++ test.cpp $(LIB) -o $(EXE) $(flags)

filters:
	g++ -c filters.cpp -Ifilters.h

run:
	./$(EXE)

clean:
	rm $(EXE)
	rm *.o
