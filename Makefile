# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joapedr2 < joapedr2@student.42sp.org.br    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/22 03:16:02 by joapedr2          #+#    #+#              #
#    Updated: 2024/10/07 11:30:04 by joapedr2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= webserv
CPP		= c++

CFLAGS	= -Wall -Werror -Wextra -std=c++98 
HEADERS	= -I./includes -I./srcs/config -I./srcs/utils -I./srcs/server -I./srcs/service -I./srcs/client

SRC_DIR		= ./srcs/
UTILS_DIR	= utils/
CONFIG_DIR	= config/
SERVER_DIR	= server/
SERVICE_DIR	= service/
CLIENT_DIR	= client/

SRC_LIST	= $(UTILS_DIR)Exceptions.cpp			$(UTILS_DIR)Utils.cpp				\
			  $(UTILS_DIR)FileReader.cpp			$(CONFIG_DIR)ConfigServerUtils.cpp	\
			  $(CONFIG_DIR)ConfigServer.cpp			$(CONFIG_DIR)Config.cpp				\
			  $(SERVER_DIR)Server.cpp													\
			  $(SERVICE_DIR)serviceUtils.cpp		$(SERVICE_DIR)Service.cpp			\
			  main.cpp

SRCS		= $(addprefix $(SRC_DIR), $(SRC_LIST)) 

OBJS_DIR	= ./objects/
OBJS		= $(addprefix $(OBJS_DIR),$(SRC_LIST:%.cpp=%.o))

#colors
GREEN			= \033[0;32m
YELLOW			= \033[0;33m
BLUE			= \033[0;34m
MAGENTA			= \033[0;35m
CYAN			= \033[0;36m
GREY 			= \033[38;5;8m
RESET			= \033[0m

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	@echo "$(GREEN)----------------------------------------------------"
	@$(CPP) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Executable				./$(NAME)"
	@echo "----------------------------------------------------$(RESET)"

$(OBJS_DIR)%.o: $(SRC_DIR)%.cpp
	@echo "$(GREY)Compiling...	$(GREY)$<$(RESET)"
	@$(CPP) $(CFLAGS) $(HEADERS) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(addprefix $(OBJS_DIR)/,$(UTILS_DIR))
	@mkdir -p $(addprefix $(OBJS_DIR)/,$(CONFIG_DIR))
	@mkdir -p $(addprefix $(OBJS_DIR)/,$(SERVER_DIR))
	@mkdir -p $(addprefix $(OBJS_DIR)/,$(SERVICE_DIR))

clean:
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -rf $(NAME)

re:	fclean $(NAME)

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -q ./$(NAME) ./test.conf
	
.PHONY: all clean fclean re valgrind