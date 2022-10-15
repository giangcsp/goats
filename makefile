
CC=g++
CFLAGS=--std=c++17 -pthread

bin/goats: obj/bridge.o obj/goat.o src/main.cpp
	${CC} ${CFLAGS} -o bin/goats src/main.cpp obj/goat.o obj/bridge.o

obj/goat.o: src/goat.h src/goat.cpp obj/bridge.o
	${CC} ${CFLAGS} -c -o obj/goat.o src/goat.cpp obj/bridge.o

obj/bridge.o: src/bridge.h src/bridge.cpp
	${CC} ${CFLAGS} -c -o obj/bridge.o src/bridge.cpp

run:
	./bin/goats 12 21

clean:
	rm -f obj/*.o
	rm -f bin/goats