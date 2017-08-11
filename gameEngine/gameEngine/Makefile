# OBJS specifies which files to compile as part of the project
OBJS = 	main.cpp  \
		mainGame.cpp \
		Timing.cpp \
		Logger.cpp \
		Log.cpp \
		SpriteBatch.cpp \
		Window.cpp \
		Camera2D.cpp \
		gameEngine.cpp \
		Sprite.cpp \
		GLSLProgram.cpp \
		IOManager.cpp \
		ImageLoader.cpp \
		picoPNG.cpp \
		Vertex.cpp \
		ResourceManager.cpp \
		TextureCache.cpp \
		InputManager.cpp \
		Bullet.cpp \
		Bomb.cpp

# CC specifies which compiler we're using
CC = g++

# INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I ~/.brew/Cellar/glfw/3.2.1/include -I ~/.brew/Cellar/glew/2.0.0/include
INCLUDE_PATHS += -I ~/.brew/Cellar/glm/0.9.8.4/include
# LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L ~/.brew/Cellar/glfw/3.2.1/lib -L ~/.brew/Cellar/glew/2.0.0/lib

# COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w -std=c++11 -stdlib=libc++

# LINKER_FLAGS specifies the libraries we're linking against
# Cocoa, IOKit, and CoreVideo are needed for static GLFW3.
LINKER_FLAGS = -framework SDL2 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreFoundation -framework CoreVideo -framework Carbon -lglfw -lGLEW

# OBJ_NAME specifies the name of our exectuable
OBJ_NAME = game

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
