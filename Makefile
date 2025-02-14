all:
	@make debug

release:
	@gcc -Wall -std=c++23 -lncurses -lstdc++ main.cpp Game.cpp Area.cpp -o ncursed

debug:
	@gcc -g -Wall -Wpedantic -std=c++23 -lncurses -lstdc++ main.cpp Game.cpp Area.cpp -o ncursed

clean:
	@rm ncursed
