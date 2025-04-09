# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junjun <junjun@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/08 18:48:42 by junjun            #+#    #+#              #
#    Updated: 2025/04/09 12:50:09 by junjun           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minirt

CC = gcc

# CFLAGS = -Wall -Wextra -Werror -Imlx -g libmlx42.a -Iinclude -lglfw
CFLAGS = -Wall -Wextra -Werror -Wunreachable-code -Ofast -g

HEADERS = -I. -I $(LIBMLX)/include

SRCS = $(wildcard *.c src/*.c src/*/*.c)

SRCOBJ = $(SRCS:%.c=%.o) 

LIBMLX = ./lib/MLX42

LIBFT = ./lib/libft

LIB = $(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

RM = rm -f

all: gitclone libmlx libft $(NAME)

gitclone:	
	@if [ ! -d "$(LIBMLX)" ]; then \
		echo "Cloning MLX42..."; \
		git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX); \
	fi

libmlx: $(LIBMLX)/build/libmlx42.a

$(LIBMLX)/build/libmlx42.a: $(LIBMLX)
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft: 
	@make -C $(LIBFT)

$(NAME):	$(SRCOBJ) 
	$(CC) $(CFLAGS) $(SRCOBJ) $(LIB) $(HEADERS) -o $(NAME)
	@echo "Executable $(NAME) has been created."

%.o:	%.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) 

clean:	
	$(RM) $(SRCOBJ) 
	make clean -C $(LIBFT)
	@echo "Object files have been deleted."

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT)
	@echo "Library has been deleted."

re: fclean all 

bonus:


.PHONY: all clean fclean re libft libmlx gitclone 