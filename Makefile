# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/22 03:16:02 by joapedr2          #+#    #+#              #
#    Updated: 2024/09/26 14:53:13 by joapedr2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= webserv
CPP		= c++

CFLAGS	= -Wall -Werror -Wextra -std=c++98
HEADERS	= -I./includes -I./srcs/config -I./srcs/utils

SRC_DIR		= ./srcs/
UTILS_DIR	= utils/
CONFIG_DIR	= config/

SRC_LIST	= $(UTILS_DIR)Exceptions.cpp			$(UTILS_DIR)Utils.cpp			\
			  $(UTILS_DIR)ConfigServerUtils.cpp		$(CONFIG_DIR)ConfigServer.cpp	\
			  $(CONFIG_DIR)Config.cpp				$(UTILS_DIR)FileReader.cpp		\
			  Webserv.cpp

SRCS		= $(addprefix $(SRC_DIR), $(SRC_LIST)) 

OBJS_DIR	= ./objects/
OBJS		= $(addprefix $(OBJS_DIR),$(SRC_LIST:%.cpp=%.o))

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	@$(CPP) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)%.o: $(SRC_DIR)%.cpp
	@$(CPP) $(CFLAGS) $(HEADERS) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)$(UTILS_DIR)
	@mkdir -p $(OBJS_DIR)$(CONFIG_DIR)

clean:
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -rf $(NAME)

re:	fclean $(NAME)

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -q ./$(NAME) ./test.conf
	
.PHONY: all clean fclean re valgrind