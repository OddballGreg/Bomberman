# OBJS specifies which files to compile as part of the project
OBJS = 	Bomberman/src/main.cpp  \
		Bomberman/src/GameLogic.cpp \
		Bomberman/gameEngine/src/BoundingBoxSet.cpp \
		Bomberman/gameEngine/src/GetTokens.cpp \
		Bomberman/gameEngine/src/Image.cpp \
		Bomberman/gameEngine/src/Logger.cpp \
		Bomberman/gameEngine/src/Model.cpp \
		Bomberman/gameEngine/src/Renderer.cpp \
		Bomberman/gameEngine/src/SceneObject.cpp
		

# CC specifies which compiler we're using
CC = g++

# INCLUDE_PATHS specifies the additional include paths we'll need


# LIBRARY_PATHS specifies the additional library paths we'll need



# INCLUDE_PATHS specifies the additional include paths we'll need
# INCLUDE_PATHS = -I ~/.brew/Cellar/sfml/2.4.2_1/include
# INCLUDE_PATHS += -I ~/.brew/Cellar/freetype/2.8.1/include
# INCLUDE_PATHS += -I ~/.brew/Cellar/freetype/2.8.1/include/freetype2
# INCLUDE_PATHS += -I ~/.brew/Cellar/libpng/1.6.32/include
# INCLUDE_PATHS += -I ~/.brew/Cellar/glfw/3.2.1/include 
# INCLUDE_PATHS += -I ~/.brew/Cellar/sdl2/2.0.5/include
# INCLUDE_PATHS += -I ~/.brew/Cellar/glew/2.1.0/include
# INCLUDE_PATHS += -I ~/.brew/Cellar/glm/0.9.8.5/include
INCLUDE_PATHS += -I ~/.brew/include
INCLUDE_PATHS += -I ~/.brew/include/freetype2

# LIBRARY_PATHS specifies the additional library paths we'll need
# LIBRARY_PATHS = -L ~/.brew/Cellar/glfw/3.2.1/lib 
# LIBRARY_PATHS += -L ~/.brew/Cellar/glew/2.1.0/lib
# LIBRARY_PATHS += -L ~/.brew/Cellar/sdl2/2.0.5/lib
# LIBRARY_PATHS += -L ~/.brew/Cellar/sfml/2.4.2_1/lib
# LIBRARY_PATHS += -L ~/.brew/Cellar/freetype/2.8.1/lib
# LIBRARY_PATHS += -L ~/.brew/Cellar/libpng/1.6.32/lib
LIBRARY_PATHS += -L ~/.brew/lib
# COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w -std=c++11 -stdlib=libc++

# LINKER_FLAGS specifies the libraries we're linking against
# Cocoa, IOKit, and CoreVideo are needed for static GLFW3.
LINKER_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreFoundation -framework CoreVideo -framework Carbon -lfreetype -lpng -lglfw -lGLEW

# OBJ_NAME specifies the name of our exectuable
OBJ_NAME = game

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
