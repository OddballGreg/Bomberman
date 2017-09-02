BOMBERMAN = $(HOME)/Projects/Bomberman/cdebruyn

NAME = bomberman

SRCS_NAME = MainComponent.class.cpp ReadLib.class.cpp GLFW.class.cpp main.cpp

HEADER_NAMES =  MainComponent.class.hpp ReadLib.class.hpp GLFW.class.hpp main.hpp

ifeq ($(shell uname -s), Darwin)
SYS = OSX
else
SYS = LINUX
endif

CC = g++

COMPILER_FLAGS = -Wall -Werror -Wextra

OPENGL = ./environ/GLFW/GLFW.class.cpp

ifeq ($(SYS), OSX)

INCLUDE_PATHS = -I ~/.brew/Cellar/glfw/3.2.1/include \
				-I ~/.brew/Cellar/glew/2.0.0/include \
				-I ~/.brew/Cellar/glew/2.1.0/include \
				-I ~/.brew/Cellar/glm/0.9.8.4/include

LIBRARY_PATHS = -L ~/.brew/Cellar/glfw/3.2.1/lib \
				-L ~/.brew/Cellar/glew/2.0.0/lib \
				-L ~/.brew/Cellar/glew/2.1.0/lib

COMPILER_FLAGS += -w -std=c++14 -stdlib=libc++

LINKER_FLAGS =	-framework SDL2 -framework Cocoa -framework OpenGL \
				-framework IOKit -framework CoreFoundation \
				-framework CoreVideo -framework Carbon -lglfw -lGLEW

else

INCLUDE_PATHS = -I/usr/include/GL -I/usr/include/GLFW \
				-I/usr/include/X11 -I/usr/include/glm

LIBRARY_PATHS = -L/usr/lib/x86_64-linux-gnu/libGLU.so \
				-L/usr/lib/x86_64-linux-gnu/libGL.so \
				-L/usr/lib/x86_64-linux-gnu/libGLESv2.so \
				-L/usr/lib/x86_64-linux-gnu/libglfw.so

COMPILER_FLAGS += -w -std=c++14

LINKER_FLAGS = -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor

endif

BREW_INCL = -I ~/.brew/include/
INCL_PATH = $(BOMBERMAN)/include/
INCL = -I $(BOMBERMAN)/include/

SRCS_PATH = $(BOMBERMAN)/src/

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS_PATH = $(BOMBERMAN)/obj/

OBJS_NAME = $(SRCS_NAME:.cpp=.o)

OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))

HEADER = $(addprefix $(INCL_PATH), $(HEADER_NAMES))

all: qme odir $(NAME)

$(NAME): $(OBJS)
	bash ./lib/install.sh
ifeq ($(SYS), OSX)
	$(CC) $(COMPILER_FLAGS) -shared -fPIC $(INCLUDE_PATHS) $(LIBRARY_PATHS) \
	$(LINKER_FLAGS) -o OpenGL.so $(OPENGL)
	$(CC) $(COMPILER_FLAGS) -o $(NAME) $^ OpenGL.so $(BREW_INCL)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.cpp
	$(CC) $(COMPILER_FLAGS) $(INCL) -o $@ -c $< -I$(INCL_PATH) $(BREW_INCL)

else
	#$(CC) $(COMPILER_FLAGS) -shared -fPIC $(LINKER_FLAGS) -o OpenGL.so $(OPENGL)
	$(CC) $(COMPILER_FLAGS) -o $(NAME) $^ -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor 

$(OBJS_PATH)%.o: $(SRCS_PATH)%.cpp
	$(CC) $(COMPILER_FLAGS) $(INCL) -o $@ -c $< -I$(INCL_PATH)

endif

odir:
	@mkdir -p $(OBJS_PATH)

clean:
	/bin/rm -rf $(OBJS)
	/bin/rm -rf OpenGL.so

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME)

qre:
	/bin/rm -f $(OBJS)
	/bin/rm -f $(NAME)
	make odir
	make $(NAME)

qme:
	@if [ ! -f author ]; then \
		rm -Rf author; \
		echo bsaunder > author; \
		echo cdebruyn >> author; \
		echo ghavenga >> author; \
		echo ggroener >> author; \
		echo khansman >> author; \
	fi
	
me: qme
	cat -e author

.PHONY: clean fclean re odir
