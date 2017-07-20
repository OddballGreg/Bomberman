# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghavenga <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/28 11:16:22 by ghavenga          #+#    #+#              #
#    Updated: 2016/12/09 16:35:20 by ghavenga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bomberman

SRCS_NAME =		Bomberman.cpp \

HEADER_NAMES =	Bomberman.hpp \

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

INCLUDES_PATH = includes/

SRCS_PATH = srcs/

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS_PATH = objs/

OBJS_NAME = $(SRCS_NAME:.cpp=.o)

OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))

ifeq ($(SYS), OSX)

LIBRARY = 
 
INCLUDES = -I includes/

else

LIBRARY = 

INCLUDES = -I includes/

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
	@$(CC) $(CFLAGS2) -o $(NAME) $^ $(LIBRARY) $(INCLUDES) -I$(INCLUDES_PATH)
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

format: norme me

norme: norm

norm:
	@clear
	@$(call colourecho2, "Norminette:")
	@norminette $(SRCS)
	@norminette $(HEADER)

fnorm: fnorme

fnorme:
	@clear
	@$(call colourecho2, "Norminette:")
	@find ./srcs -name "*.cpp" -maxdepth 1 -type f -exec norminette  {} \;
	@find ./includes -name "*.h" -maxdepth 1 -type f -exec norminette  {} \;

qme:
	@if [ ! -f author ]; then \
		whoami > author; \
	fi
	
me: qme
	cat -e author

submodule:
	git submodule init libft
	git submodule update
	git submodule sync -- libft

.PHONY: clean fclean re odir
