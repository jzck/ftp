# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wescande <wescande@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/29 21:32:58 by wescande          #+#    #+#              #
#    Updated: 2017/04/03 18:19:23 by jhalford         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL		:=	bash

NAME		=	server client

CC			=	gcc
W_FLAGS		=	-Wall -Wextra -Werror
D_FLAGS		=
FLAGS		=	$(W_FLAGS) $(D_FLAGS)

LEN_NAME	=	`printf "%s" $(NAME) |wc -c`
DELTA		=	$$(echo "$$(tput cols)-31-$(LEN_NAME)"|bc)

LIBFT_DIR	=	libft/
LIBFT_LIB	=	$(LIBFT_DIR)libft.a
LIBFT_INC	=	$(LIBFT_DIR)includes/

SRC_DIR		=	srcs/
INC_DIR		=	includes/
OBJ_DIR		=	objs/

SERVER_OBJ	=	$(OBJ_DIR)server.o
CLIENT_OBJ	=	$(OBJ_DIR)client.o $(OBJ_DIR)cli_do_help.o

SRC_BASE	=	\
cli_do_debug.c\
cli_do_get.c\
cli_do_help.c\
cli_do_local.c\
cli_output.c\
client.c\
console_msg.c\
req_init.c\
serv_do_get.c\
server.c

SRCS		=	$(addprefix $(SRC_DIR), $(SRC_BASE))
OBJS		=	$(addprefix $(OBJ_DIR), $(SRC_BASE:.c=.o))
OBJS		:=	$(filter-out $(SERVER_OBJ) $(CLIENT_OBJ), $(OBJS))
NB			=	$(words $(SRC_BASE))
INDEX		=	0

all :
	@make -C $(LIBFT_DIR)
	@make -j $(NAME)

server:		$(LIBFT_LIB) $(OBJ_DIR) $(OBJS) $(SERVER_OBJ)
	@$(CC) $(FLAGS) $(OBJS) -o $@ \
		-I $(INC_DIR) \
		-I $(LIBFT_INC) \
		$(SERVER_OBJ) $(LIBFT_LIB)
	@printf "\r\033[38;5;117m✓ MAKE $@ \033[0m\033[K\n"

client:		$(LIBFT_LIB) $(OBJ_DIR) $(OBJS) $(CLIENT_OBJ)
	@$(CC) $(FLAAGS) $(OBJS) -o $@ \
		-I $(INC_DIR) \
		-I $(LIBFT_INC) \
		$(CLIENT_OBJ) $(LIBFT_LIB) \
		-lreadline
	@printf "\r\033[38;5;117m✓ MAKE $@ \033[0m\033[K\n"

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o :	$(SRC_DIR)%.c | $(OBJ_DIR)
	@$(eval DONE=$(shell echo $$(($(INDEX)*20/$(NB)))))
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(eval TO_DO=$(shell echo $$((20-$(INDEX)*20/$(NB) - 1))))
	@$(eval COLOR=$(shell list=(160 196 202 208 215 221 226 227 190 154 118 82 46); index=$$(($(PERCENT) * $${#list[@]} / 100)); echo "$${list[$$index]}"))
	@printf "\r\033[38;5;%dm⌛ [%s]: %2d%% `printf '█%.0s' {0..$(DONE)}`%*s❙%*.*s\033[0m\033[K" $(COLOR) ft_p $(PERCENT) $(TO_DO) "" $(DELTA) $(DELTA) "$(shell echo "$@" | sed 's/^.*\///')"
	@$(CC) $(FLAGS) $(OBJ_FLAG) -MMD -c $< -o $@\
		-I $(INC_DIR)\
		-I $(LIBFT_INC)
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

clean:			cleanlib
	@if [ -e $(OBJ_DIR) ]; then \
		rm -rf $(OBJ_DIR); \
		printf "\r\033[38;5;202m✗ clean $(NAME) \033[0m\033[K\n"; \
	fi;

cleanlib:
	@make -C $(LIBFT_DIR) clean

fclean:			clean fcleanlib
	@for file in $(NAME); do \
		if [ -e $$file ]; then \
			rm -f $$file ; \
			printf "\r\033[38;5;196m✗ fclean $$file\033[0m\033[K\n"; \
		fi; \
	done;

fcleanlib:		cleanlib
	@make -C $(LIBFT_DIR) fclean

re:				fclean all

relib:			fcleanlib $(LIBFT_LIB)

.PHONY :		fclean clean re relib cleanlib fcleanlib

-include $(OBJS:.o=.d)
