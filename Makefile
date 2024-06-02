build:
	gcc src/*.c -Iinclude -o game -Wall -lSDL2 -g

run:
	./game

clean:
	rm game
