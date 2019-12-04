CMP = g++
CFLAGS = -std=c++11 -Wall -Isrc

all: mancala test_board test_ai test_game

test: test_board test_ai test_game
	./test_board
	./test_ai
	./test_game

mancala: bin/ src/mancala.cc src/ai.h src/board.h bin/ai.o bin/board.o bin/game.o
	${CMP} -o mancala src/mancala.cc bin/board.o bin/ai.o bin/game.o ${CFLAGS}

test_board: bin/board.o test/test_board.cc
	${CMP} -o test_board test/test_board.cc bin/board.o ${CFLAGS}

test_ai: bin/ai.o bin/board.o test/test_ai.cc
	${CMP} -o test_ai test/test_ai.cc bin/board.o bin/ai.o ${CFLAGS}

test_game: bin/game.o bin/ai.o bin/board.o test/test_game.cc
	${CMP} -o test_game test/test_game.cc bin/board.o bin/ai.o bin/game.o ${CFLAGS}

bin/:
	mkdir bin

bin/board.o: bin/ src/board.cc src/board.h
	${CMP} -c src/board.cc -o bin/board.o ${CFLAGS}

bin/ai.o: bin/ src/ai.cc src/ai.h src/board.h
	${CMP} -c src/ai.cc -o bin/ai.o ${CFLAGS}

bin/game.o: bin/ src/game.cc src/game.h src/ai.h src/board.h
	${CMP} -c src/game.cc -o bin/game.o ${CFLAGS}


clean:
	-rm mancala
	-rm test_game
	-rm test_board
	-rm test_ai
	-rm -r *.dSYM
	-rm -r bin
