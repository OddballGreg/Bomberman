
#include <cstdlib>
#include <iostream>
#include <stdexcept>

# include <boost/program_options.hpp>

#include "../include/GameLogic.hpp"
#include "../include/KeyInput.hpp"
#include "../gameEngine/include/text2D.hpp"
#include "../gameEngine/include/Menu.hpp"
#include "../SoundEngine/SoundEngine.hpp"

#include <GLFW/glfw3.h>

using namespace std;
using namespace Bomberman;
using namespace gameEngine;

const GLuint frameRate = 60;
bool firstMouse = true;
float yaw	=	-90.0f; // yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =	0.0f;
float lastX =	800.0f / 2.0;
float lastY =	600.0 / 2.0;
float fov	=	45.0f;

int			arg_verbosity = 0;
int			arg_width = 0;
int			arg_height = 0;
int			arg_volume = 100;


KeyInput input;


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		input.down = true;
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		input.up = true;
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		input.left = true;
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		input.right = true;
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
		input.enter = true;

	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		input.camUp = true;
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		input.camDown = true;
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		input.camLeft = true;
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
		input.camRight = true;

	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		input.camRotXUp = true;
	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
		input.camRotXDown = true;
	if (key == GLFW_KEY_4 && action == GLFW_PRESS)
		input.camRotYUp = true;
	if (key == GLFW_KEY_5 && action == GLFW_PRESS)
		input.camRotYDown = true;
	if (key == GLFW_KEY_7 && action == GLFW_PRESS)
		input.camRotZUp = true;
	if (key == GLFW_KEY_8 && action == GLFW_PRESS)
		input.camRotZDown = true;

	if (key == GLFW_KEY_D && action == GLFW_PRESS)
		input.camPosXUp = true;
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		input.camPosXDown = true;
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
		input.camPosYUp = true;
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
		input.camPosYDown = true;
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		input.camPosZUp = true;
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		input.camPosZDown = true;

	if (key == GLFW_KEY_D && action == GLFW_RELEASE)
		input.camPosXUp = false;
	if (key == GLFW_KEY_A && action == GLFW_RELEASE)
		input.camPosXDown = false;
	if (key == GLFW_KEY_E && action == GLFW_RELEASE)
		input.camPosYUp = false;
	if (key == GLFW_KEY_Q && action == GLFW_RELEASE)
		input.camPosYDown = false;
	if (key == GLFW_KEY_S && action == GLFW_RELEASE)
		input.camPosZUp = false;
	if (key == GLFW_KEY_W && action == GLFW_RELEASE)
		input.camPosZDown = false;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		input.esc = true;
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		input.space = true;

	if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
		input.down = false;
	if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
		input.up = false;
	if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
		input.left = false;
	if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
		input.right = false;
	if (key == GLFW_KEY_ENTER && action == GLFW_RELEASE)
		input.enter = false;

	if (key == GLFW_KEY_W && action == GLFW_RELEASE)
		input.camUp = false;
	if (key == GLFW_KEY_S && action == GLFW_RELEASE)
		input.camDown = false;
	if (key == GLFW_KEY_A && action == GLFW_RELEASE)
		input.camLeft = false;
	if (key == GLFW_KEY_D && action == GLFW_RELEASE)
		input.camRight = false;

	if (key == GLFW_KEY_1 && action == GLFW_RELEASE)
		input.camRotXUp = false;
	if (key == GLFW_KEY_2 && action == GLFW_RELEASE)
		input.camRotXDown = false;
	if (key == GLFW_KEY_4 && action == GLFW_RELEASE)
		input.camRotYUp = false;
	if (key == GLFW_KEY_5 && action == GLFW_RELEASE)
		input.camRotYDown = false;
	if (key == GLFW_KEY_7 && action == GLFW_RELEASE)
		input.camRotZUp = false;
	if (key == GLFW_KEY_8 && action == GLFW_RELEASE)
		input.camRotZDown = false;

	if (key == GLFW_KEY_Z && action == GLFW_RELEASE)
		input.camPosXUp = false;
	if (key == GLFW_KEY_X && action == GLFW_RELEASE)
		input.camPosXDown = false;
	if (key == GLFW_KEY_C && action == GLFW_RELEASE)
		input.camPosYUp = false;
	if (key == GLFW_KEY_V && action == GLFW_RELEASE)
		input.camPosYDown = false;
	if (key == GLFW_KEY_B && action == GLFW_RELEASE)
		input.camPosZUp = false;
	if (key == GLFW_KEY_N && action == GLFW_RELEASE)
		input.camPosZDown = false;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
		input.esc = false;
	if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
		input.space = false;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	//cameraFront = glm::normalize(front);
}

void			parseArgs(int ac, char **av) {
	try {
		boost::program_options::options_description	desc("Options");

		desc.add_options()
		("help", "Print out help messages")
		("verbose,v", boost::program_options::value<int>(&arg_verbosity), "runs logs with a verbosity of 0 to 5")
		("height,h", boost::program_options::value<int>(&arg_height), "sets the window height")
		("width,w", boost::program_options::value<int>(&arg_width), "sets the window width")
		("volume,s", boost::program_options::value<int>(&arg_volume), "Set the volume level");
		// ("ai,a", "enables the AI")
		// ("delay,d", boost::program_options::value<unsigned int>(&g_delay), "Sets the timmers delay, default 90000usec")
		// ("verse_ai,b", "allows the player to play against the AI");

		boost::program_options::variables_map	vm;

		try {
			boost::program_options::store(boost::program_options::parse_command_line(ac, av, desc), vm);

			if (vm.count("help")) {
				std::cout << "Nibbler is a version of the classical snake game, which allows for dynamic graphics libraies to be loaded and used as interfaces." << std::endl;
				std::cout << std::endl << desc << std::endl;
				exit(0);
			}

			boost::program_options::notify(vm);

			if (arg_volume < 0 || arg_volume > 200)
				throw boost::program_options::error("volume has to be between 0 and 200%");
			if (arg_height < 0)
				throw boost::program_options::error("Height can not be a negative value");
			if (arg_width < 0)
				throw boost::program_options::error("Width can not be a negative value");
			if (vm.count("height") && !vm.count("width"))
				throw boost::program_options::error("Can't specify height and not width");
			if (!vm.count("height") && vm.count("width"))
				throw boost::program_options::error("Can't specify width and not height");

			// if (g_height < 15 || g_height > 200)
			// 	throw boost::program_options::error("height can not be greater than 200, or less than 15");
			// if (g_width < 15 || g_width > 200)
			// 	throw boost::program_options::error("width can not be greater than 200, or less than 15");

			// if (arg_volume < 0 || arg_volume)

			// logger.setVerbosity(g_verbosity);

			// if (vm.count("ai"))
			// 	g_ai_flag = true;

		}
		catch (boost::program_options::error& e) {
			std::cerr << "ERROR: " << e.what() << std::endl;
			exit(0);
		}
	}
	catch(std::exception& e) {
		std::cerr << "Exception reached when parsing paramiters" << std::endl;
		exit(0);
	}
}

int main(int argc, char **argv) {

	try {
		initLogger();
		Settings *settings = new Settings;
		GameLogic gameLogic(settings);

		parseArgs(argc, argv);

		settings->SCREEN_WIDTH = arg_width;
		settings->SCREEN_HEIGHT = arg_height;
		// settings->VOLUME = arg_volume;

		// MenuScreen menuSetttings;
		// menuSetttings.initializeMenu(800, 800, "testing");

		// seconds, for setting the framerate
		double seconds = glfwGetTime();
		double prevSeconds = seconds;
		double secondsInterval = 1.0 / frameRate;

		GLFWwindow* window = gameLogic.renderer->getWindow();

		glfwSetKeyCallback(window, keyCallback);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);

		// tell GLFW to capture our mouse
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		Sound musicloop;
		if (settings->PLAY_SOUND)
		{
			musicloop.initialize("../SoundEngine/music/loop.wav");
			musicloop.play(true);
		}

		initText2D( "../gameEngine/resources/fonts/Holstein.DDS" );

		while (!glfwWindowShouldClose(window) && !input.esc) {

			glfwPollEvents();

			seconds = glfwGetTime();
			if (seconds - prevSeconds > secondsInterval) {
				gameLogic.process(input);
				prevSeconds = seconds;
				gameLogic.render();
			}
		}
	}
	catch (std::runtime_error &e) {
	LOGERROR(e.what());
	return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
