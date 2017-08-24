NAME = bomberman

SRCS_NAME = Window.class.cpp MainComponent.class.cpp main.cpp

HEADER_NAMES = Window.class.hpp MainComponent.class.hpp

ifeq ($(shell uname -s), Darwin) # Changes rules for MAC and Linux
SYS = OSX
else
SYS = LINUX
endif

CFLAGS =	-std=c++14 -O3

ifeq ($(SYS), OSX) 
CFLAGS2 = 	-O3 
else
CFLAGS2 =	-O3
endif

CC = g++

INCLUDES_PATH = include/

SRCS_PATH = src/

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS_PATH = obj/

OBJS_NAME = $(SRCS_NAME:.cpp=.o)

OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))

ifeq ($(SYS), OSX)
INCLUDES = -I include/
else
INCLUDES = -I include/
endif

HEADER = $(addprefix $(INCLUDES_PATH), $(HEADER_NAMES))

all: qme odir $(NAME)

define colourecho
	@tput setaf 14
	@echo $1
	@tput sgr0
endef

define colourecho2
	@tput setaf 2
	@echo $1
	@tput sgr0
endef

$(NAME): $(OBJS)
	@$(call colourecho, " - Making $(NAME)")
	@clear
	@$(CC) $(CFLAGS2) -o $(NAME) $^ $(INCLUDES) -I$(INCLUDES_PATH)
	@clear
	@$(call colourecho, "Make Done!")

$(OBJS_PATH)%.o: $(SRCS_PATH)%.cpp
	@$(call colourecho, " - Compiling $<")
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $< -I$(INCLUDES_PATH)
	@$(call colourecho, "Compiling Done!")

odir:
	@mkdir -p $(OBJS_PATH)

clean:
	@$(call colourecho, " - Clearing object files")
	@rm -f $(OBJS)
	@$(call colourecho, "clean done!")

fclean: clean
	@$(call colourecho, "Clearing executable files")
	@rm -f $(NAME)
	@$(call colourecho, "fclean done")

re: fclean all
	@$(call colourecho, "re Done!")

run: $(NAME)
	./$(NAME)

qre:
	@$(call colourecho, " - Clearing object files")
	@rm -f $(OBJS)
	@rm -f $(NAME)
	@$(call colourecho, "clean done!")
	@make odir
	@make $(NAME)

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
