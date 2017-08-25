BOMBERMAN = /home/cameron/Projects/Bomberman/cdebruyn

NAME = bomberman

SRCS_NAME = Window.class.cpp MainComponent.class.cpp main.cpp

HEADER_NAMES = Window.class.hpp MainComponent.class.hpp

SHARED =	./shared/Coord.cpp \
			./shared/Direction.cpp

ifeq ($(shell uname -s), Darwin)
SYS = OSX
else
SYS = LINUX
endif

CC = g++

COMPILER_FLAGS = -Wall -Werror -Wextra

OPENGL = ./src/Window.class.cpp

ifeq ($(SYS), OSX)

INCLUDE_PATHS = -I ~/.brew/Cellar/glfw/3.2.1/include \
				-I ~/.brew/Cellar/glew/2.0.0/include \
				-I ~/.brew/Cellar/glew/2.1.0/include \
				-I ~/.brew/Cellar/glm/0.9.8.4/include

LIBRARY_PATHS = -L ~/.brew/Cellar/glfw/3.2.1/lib \
				-L ~/.brew/Cellar/glew/2.0.0/lib \
				-L ~/.brew/Cellar/glew/2.1.0/lib

COMPILER_FLAGS += -w -std=c++11 -stdlib=libc++

LINKER_FLAGS =	-framework SDL2 -framework Cocoa -framework OpenGL \
				-framework IOKit -framework CoreFoundation \
				-framework CoreVideo -framework Carbon -lglfw -lGLEW

else

INCLUDE_PATHS = -I /usr/include/GLFW -I /usr/include/GL \
				-I /usr/include/X11 -I /usr/include/glm

LIBRARY_PATHS = -L /usr/lib/x86_64-linux-gnu/libGLU.so \
				-L /usr/lib/x86_64-linux-gnu/libGL.so \
				-L /usr/lib/x86_64-linux-gnu/libGLESv2.so \
				-L /usr/lib/x86_64-linux-gnu/libglfw.so

COMPILER_FLAGS += -w -std=c++11

LINKER_FLAGS = -lglfw -lGLU -lGLEW -lGL -lGLESv2 -lm `sdl2-config --cflags --libs`

endif

INCL_PATH = $(BOMBERMAN)/include/
INCL = -I $(BOMBERMAN)/include/

SRCS_PATH = $(BOMBERMAN)/src/

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS_PATH = $(BOMBERMAN)/obj/

OBJS_NAME = $(SRCS_NAME:.cpp=.o)

OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))

HEADER = $(addprefix $(INCL_PATH), $(HEADER_NAMES))

all: qme odir $(NAME)

ifeq ($(shell uname -s), Linux)
	END_FLAGS = -ldl
endif

$(NAME): $(OBJS)
	bash ./lib/install.sh
	$(CC) $(COMPILER_FLAGS) -shared -fPIC $(SHARED) -I ./shared/ -o Shared.so
ifeq ($(SYS), OSX)
	$(CC) $(COMPILER_FLAGS) -shared -fPIC $(LINKER_FLAGS) Shared.so -o OpenGL.so \
	$(OPENGL)
	$(CC) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) \
	-o $(NAME) $^ $(INCL) Shared.so $(END_FLAGS) -I ~/.brew/include/ 

$(OBJS_PATH)%.o: $(SRCS_PATH)%.cpp
	$(CC) $(COMPILER_FLAGS) $(INCL) -o $@ -c $< -I$(INCL_PATH) $(END_FLAGS) \
	-I ~/.brew/include/

else
	$(CC) $(COMPILER_FLAGS) -shared -fPIC $(LINKER_FLAGS) Shared.so -o OpenGL.so \
	$(OPENGL)
	$(CC) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) \
	-o $(NAME) $^ $(INCL) Shared.so $(END_FLAGS) 

$(OBJS_PATH)%.o: $(SRCS_PATH)%.cpp
	$(CC) $(COMPILER_FLAGS) $(INCL) -o $@ -c $< -I$(INCL_PATH) $(END_FLAGS)

endif

odir:
	@mkdir -p $(OBJS_PATH)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME)

qre:
	rm -f $(OBJS)
	rm -f $(NAME)
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
