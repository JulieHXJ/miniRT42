# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/08 18:48:42 by junjun            #+#    #+#              #
#    Updated: 2025/05/06 16:30:59 by dchrysov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
MAKEFLAGS += -s
CFLAGS = -Wall -Wextra -Werror -Wunreachable-code -g -I$(LIBMLX)/inc -I$(GNLDIR)/inc -I./inc -fsanitize=address
MLX_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit -ldl -lglfw -pthread

OBJDIR = ./obj
SRCDIR = ./src
MLXDIR = ./inc/MLX42
LIBFTDIR = ./lib/libft
GNLDIR = ./lib/getnextline

SRCS = $(SRCDIR)/main.c $(SRCDIR)/utils.c $(SRCDIR)/garbage_collector.c \
	\
	$(SRCDIR)/parser/check.c $(SRCDIR)/parser/parse.c $(SRCDIR)/parser/environment.c $(SRCDIR)/parser/objects.c \
	$(SRCDIR)/parser/parse_utils.c

OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

RM = rm -f

MLX = $(MLXDIR)/build/libmlx42.a
LIBFT = $(LIBFTDIR)/libft.a
GNL = $(GNLDIR)/libgnl.a
NAME = minirt

all: gitclone libmlx libft $(NAME)

$(NAME): $(OBJDIR) $(OBJS) $(MLX) $(LIBFT) $(GNL)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX) $(MLX_FLAGS) -L$(LIBFTDIR) -lft -L$(GNLDIR) -lgnl -lm
	@echo "$(NAME) compiled \033[32msuccessfully\033[0m!"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< $(HEADERS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/parser/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< $(HEADERS) -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(GNL):
	$(MAKE) -C $(GNLDIR) LIBFTDIR=../libft

$(MLX): $(MLXDIR)
	@cmake $(MLXDIR) -B $(MLXDIR)/build && make -C $(MLXDIR)/build -j4

libft:
	$(MAKE) -C $(LIBFTDIR)

gitclone:	
	@if [ ! -d "$(MLXDIR)" ]; then \
		echo "Cloning MLX42..."; \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLXDIR); \
	fi

libmlx: $(MLXDIR)/build/libmlx42.a

clean:
	make clean -C $(GNLDIR)
	@echo "\033[33mRemoving $(NAME) build...\033[0m"
	$(RM) $(OBJ)
	rm -rf $(OBJDIR)
	@echo "$(NAME) build removed \033[32msuccessfully\033[0m!"

fclean: clean
	make fclean -C $(GNLDIR)
	@echo "\033[33mRemoving $(NAME)...\033[0m"
	$(RM) $(NAME)
	rm -rf $(MLXDIR)
	@echo "$(NAME) removed \033[32msuccessfully\033[0m!"

re: fclean all 

.PHONY: all clean fclean re libft libmlx gitclone 