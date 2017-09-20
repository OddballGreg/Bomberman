#include "../includes/bomberman.hpp"

int main()
{
	Log log("Main", "main", CRITICAL);
	Gamestate gamestate;

	gamestate.run();
}