NAME = 	gameEngine.a

CC = 	g++

SRC = 	Sprite.cpp			\
		GLSLProgram.cpp		\
		IOManager.cpp		\
		ImageLoader.cpp		\
		picoPNG.cpp			\
		Vertex.cpp			\
		ResourceManager.cpp	\
		TextureCache.cpp	
	 

OBJ		= $(SRC:.c=.o)


CFLAGS = -Wall -Wextra -Werror

INCLUDE_PATHS = -I includes -I ~/.brew/Cellar/glfw/3.2.1/include -I ~/.brew/Cellar/glew/2.0.0/include

LIBRARY_PATHS = -L ~/.brew/Cellar/glfw/3.2.1/lib -L ~/.brew/Cellar/glew/2.0.0/lib

COMPILER_FLAGS = -w

LINKER_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreFoundation -framework CoreVideo -framework Carbon -lglfw -lGLEW



all: $(NAME)

$(NAME):
	@clear
	@echo "\x1b[31m-----Compiling Game Engine\x1b[0m"
	@$(CC) -c -w $(CFLAGS) $(SRC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS)
	
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\x1b[34m-----Done Compiling Game Engine\x1b[0m"

clean:
	@rm -f $(OBJ)
	@echo "\x1b[32mCompleted Clean\x1b[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\x1b[32mCompleted Full Clean\x1b[0m"

re: fclean all
