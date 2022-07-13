# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apigeon <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/30 16:08:04 by apigeon           #+#    #+#              #
#    Updated: 2022/07/13 22:32:40 by apigeon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


### COMPILATION ###
CC		= cc -Ofast
CFLAGS	= -Wall -Werror -Wextra
LFLAGS	= -L$(LIBFT_DIR) -L$(MLX_DIR)
LINKS	= -lft -lmlx -lX11 -lXext -lm

### EXECUTABLE ###
NAME	= fdf
MAP		= maps/42.fdf

### INCLUDES ###
OBJ_DIR		= bin
SRC_DIR		= src
HEADER		= incl
LIBFT_DIR	= libft
MLX_DIR		= libmlx
LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= $(MLX_DIR)/libmlx.a

### SOURCE FILES ###
SRCS	= 	main.c \
			parse.c \
			file.c \
			hooks.c \
			key_handler.c \
			draw.c \
			colors.c \
			render.c \
			point.c \
			translation_zoom.c \
			rotation.c \
			views.c \
			mlx_utils.c \
			map_utils.c \
			math_utils.c \
			errors.c

### OBJECTS ###
OBJS	= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

### COLORS ###
NOC		= \033[0m
BLACK	= \033[1;30m
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
PURPLE	= \033[1;35m
CYAN	= \033[1;36m
WHITE	= \033[1;37m

### RULES ###
all:	$(NAME)

$(MLX):
	@echo "$(GREEN)Creating mlx lib file$(NOC)"
	@make -C $(MLX_DIR)

$(LIBFT):
	@echo "$(GREEN)Creating libft lib file$(NOC)"
	@make addon -C $(LIBFT_DIR)

$(NAME):	$(LIBFT) $(MLX) $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) $(LINKS) -o $(NAME)
	@echo "$(GREEN)Project successfully compiled$(NOC)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(HEADER)/$(NAME).h
	@$(CC) $(CFLAGS) -I$(HEADER) -I$(LIBFT_DIR)/$(HEADER) -I$(MLX_DIR) -c $< -o $@
	@echo "$(BLUE)Creating object file -> $(WHITE)$(notdir $@)... $(GREEN)[Done]$(NOC)"

run: $(NAME)
	@./fdf $(MAP)

val: $(NAME)
	@valgrind --track-origins=yes --leak-check=full ./fdf $(MAP)

clean:
	@echo "$(GREEN)Supressing libraries files$(NOC)"
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	@echo "$(GREEN)Supressing object files$(NOC)"
	@rm -rf $(OBJ_DIR)

fclean:	clean
	@make fclean -C $(LIBFT_DIR)
	@echo "$(GREEN)Supressing program file$(NOC)"
	@rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
