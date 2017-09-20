# OBJS specifies which files to compile as part of the project
OBJS = 	main.cpp  \
		mainGame.cpp \
		Level.cpp \
		Agent.cpp \
		Player.cpp \
		Human.cpp \
		Zombie.cpp \
		Bullet.cpp \
		Gun.cpp \
		gameEngine/Timing.cpp \
		gameEngine/Logger.cpp \
		gameEngine/Log.cpp \
		gameEngine/SpriteBatch.cpp \
		gameEngine/Window.cpp \
		gameEngine/Camera2D.cpp \
		gameEngine/gameEngine.cpp \
		gameEngine/Sprite.cpp \
		gameEngine/GLSLProgram.cpp \
		gameEngine/IOManager.cpp \
		gameEngine/ImageLoader.cpp \
		gameEngine/picoPNG.cpp \
		gameEngine/Vertex.cpp \
		gameEngine/ResourceManager.cpp \
		gameEngine/TextureCache.cpp \
		gameEngine/InputManager.cpp \
		gameEngine/Bomb.cpp

# CC specifies which compiler we're using
CC = g++

# INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I ~/.brew/Cellar/glfw/3.2.1/include 
INCLUDE_PATHS += -I ~/.brew/Cellar/sdl2/2.0.5/include
INCLUDE_PATHS += -I ~/.brew/Cellar/glew/2.1.0/include
INCLUDE_PATHS += -I ~/.brew/Cellar/glm/0.9.8.5/include
# LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L ~/.brew/Cellar/glfw/3.2.1/lib 
LIBRARY_PATHS += -L ~/.brew/Cellar/glew/2.1.0/lib
LIBRARY_PATHS += -L ~/.brew/Cellar/sdl2/2.0.5/lib

# COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w -std=c++11 -stdlib=libc++

# LINKER_FLAGS specifies the libraries we're linking against
# Cocoa, IOKit, and CoreVideo are needed for static GLFW3.
LINKER_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreFoundation -framework CoreVideo -framework Carbon -lglfw -lGLEW -lSDL2

# OBJ_NAME specifies the name of our exectuable
OBJ_NAME = bomberman

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
