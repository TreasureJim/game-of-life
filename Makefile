build:
	gcc src/*.c -Iinclude -o game -Wall -lSDL2 -lSDL2_ttf -g

run:
	./game

clean:
	rm game
