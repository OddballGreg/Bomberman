ifeq ($(shell uname -s), Darwin) # Changes rules for MAC and Linux
SYS = OSX
elseif
SYS = LINUX
endif

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

ifeq ($(SYS), OSX) 

# INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I ~/.brew/Cellar/glfw/3.2.1/include -I ~/.brew/Cellar/glew/2.0.0/include -I ~/.brew/Cellar/glew/2.1.0/include/
INCLUDE_PATHS += -I ~/.brew/Cellar/glm/0.9.8.4/include
# LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L ~/.brew/Cellar/glfw/3.2.1/lib -L ~/.brew/Cellar/glew/2.0.0/lib -L ~/.brew/Cellar/glew/2.1.0/lib

# COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w -std=c++11 -stdlib=libc++

# LINKER_FLAGS specifies the libraries we're linking against
# Cocoa, IOKit, and CoreVideo are needed for static GLFW3.
LINKER_FLAGS = -framework SDL2 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreFoundation -framework CoreVideo -framework Carbon -lglfw -lGLEW

else

INCLUDE_PATHS = -I /usr/include/GLFW -I /usr/include/GL \
								-I /usr/include/X11 -I /usr/include/glm
LIBRARY_PATHS = -L /usr/lib/x86_64-linux-gnu/libGLU.so \
								-L /usr/lib/x86_64-linux-gnu/libGL.so \
								-L /usr/lib/x86_64-linux-gnu/libGLESv2.so \
								-L /usr/lib/x86_64-linux-gnu/libglfw.so
COMPILER_FLAGS = -w -std=c++11
LINKER_FLAGS = -lglfw -lGLU -lGLEW -lGL -lGLESv2 -lm `sdl2-config --cflags --libs`

endif


# OBJ_NAME specifies the name of our exectuable
OBJ_NAME = game

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
