#include "../includes/bomberman.hpp"
#include "../gameEngine"

int main()
{
	Log log("Main", "main", CRITICAL);
	Gamestate gamestate;

	gamestate.run();
}