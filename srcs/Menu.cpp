#include "Menu.hpp" 

//Constructors
Menu::Menu()
{
	Log log("Menu", "Constructor", CRITICAL);
}


Menu::Menu(const Menu &obj)
{
	Log log("Menu", "Copy Constructor", CRITICAL);
}

Menu::~Menu()
{
	Log log("Menu", "Deconstructor", CRITICAL);
}

Menu &Menu::operator =(const Menu &obj)
{ 
	Log log("Menu", "= Operator", CRITICAL);
	return *this; 
}

// Setters

// Getters

// Methods
void	Menu::drawMenu(SpriteBatch &spriteBatch)
{
		glm::vec4						uv(0.0f, 0.0f, 1.0f, 1.0f);
		static gameEngine::GLTexture	texture;
		gameEngine::Colour				colour;
		glm::vect4						posAndSize;
	
		// Change the path to match the relative path.
		texture = gameEngine::ResourceManager::getTexture("main_menu.png");
		colour.r = colour.g = colour.b = 255;
		colour.a = 255;
		posAndSize = glm::vect4(10, 10, 100, 100);//play around with
	
		spriteBatch.draw(posAndSize, uv, texture.id, 0.0f, colour);
}

menuCode	Menu::show(SpriteBatch &spriteBatch, gameEngine::Window window)
{
		menuCode	retCode = menuCodeContinue;
		double		xpos, ypos;
	
		this->drawMenu(spriteBatch);
	
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);
	
		while (1) {
			glfwWaitEvents();
			
			if (glfwGetKey(window, GLFW_KEY_ESC) = GLFW_PRESS)
				break ;
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
				glfwGetCursorPos(window, &xpos, &ypos);
				if (this->clickedExit(xpos, ypos)) {
					retCode = menuCodeExit;
					break;
				}
				else if (this->clickedRestart(xpos, ypos)) {
					retCode = menuCodeRestart;
					break;
				}
				else if (this->clickedContinue(xpos, ypos)) {
					retCode = menuCodeContinue;
					break;
				}
			}
		}
	
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		return (retCode);
}

bool	Menu::clickedExit(double x, double y)
{
		// play around to get exact position
		return (20 < x && x < 100 && 20 < y && y < 100);
}

bool	Menu::clickedRestart(double x, double y)
{
		// play around to get exact position
		return (20 < x && x < 100 && 20 < y && y < 100);
}

bool	Menu::clickedContinue(double x, double y)
{
		// play around to get exact position
		return (20 < x && x < 100 && 20 < y && y < 100);
}
