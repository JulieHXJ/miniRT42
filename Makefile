# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/08 18:48:42 by junjun            #+#    #+#              #
#    Updated: 2025/07/02 18:33:20 by dchrysov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
MAKEFLAGS += -s
CFLAGS = -Wall -Wextra -Werror -Ofast -flto -march=native -Wunreachable-code -g -I$(MLXDIR)/inc -I$(GNLDIR)/inc -I./inc -fsanitize=address
MLX_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit -ldl -lglfw -pthread
# MLX_FLAGS = -ldl -lglfw -pthread

OBJDIR = ./obj
SRCDIR = ./src
MLXDIR = ./lib/MLX42
LIBFTDIR = ./lib/libft
GNLDIR = ./lib/getnextline

# remember to change
SRCS := $(SRCDIR)/main.c $(SRCDIR)/utils.c $(SRCDIR)/garbage_collector.c $(SRCDIR)/debugging.c\
		$(SRCDIR)/vector/color.c \
		$(SRCDIR)/vector/math1.c \
		$(SRCDIR)/vector/math2.c \
		$(SRCDIR)/parser/check_name.c \
		$(SRCDIR)/parser/check_range.c \
		$(SRCDIR)/parser/assign_param.c \
		$(SRCDIR)/parser/environment.c \
		$(SRCDIR)/parser/parse.c \
		$(SRCDIR)/parser/objects.c \
		$(SRCDIR)/intersections/ray_trace.c \
		$(SRCDIR)/intersections/sphere_plane.c \
		$(SRCDIR)/intersections/cylinder.c \
		$(SRCDIR)/render/render.c \
		$(SRCDIR)/render/render2.c \
		$(SRCDIR)/render/hook.c \
		$(SRCDIR)/render/hook_camera.c \
		$(SRCDIR)/lighting/calculate.c \
		$(SRCDIR)/lighting/calculate2.c
		 

# OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

RM = rm -f

MLX = $(MLXDIR)/build/libmlx42.a
LIBFT = $(LIBFTDIR)/libft.a
GNL = $(GNLDIR)/libgnl.a
NAME = minirt

all: gitclone libmlx libft gnl $(NAME)

$(NAME): $(OBJS) $(MLX) $(LIBFT) $(GNL)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX) $(MLX_FLAGS) -L$(GNLDIR) -lgnl -L$(LIBFTDIR) -lft -lm
	@echo "$(NAME) compiled \033[32msuccessfully\033[0m!"


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(GNL):
	$(MAKE) -C $(GNLDIR) LIBFTDIR=../libft

$(MLX): $(MLXDIR)
	@cmake $(MLXDIR) -B $(MLXDIR)/build && make -C $(MLXDIR)/build -j4

gitclone:	
	@if [ ! -d "$(MLXDIR)" ]; then \
		echo "Cloning MLX42..."; \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLXDIR); \
	fi

libmlx: $(MLXDIR)/build/libmlx42.a

libft:
	$(MAKE) -C $(LIBFTDIR)

gnl:
	$(MAKE) -C $(GNLDIR)

clean:
	make clean -C $(GNLDIR)
	make clean -C $(LIBFTDIR)
	@echo "\033[33mRemoving $(NAME) build...\033[0m"
	$(RM) $(OBJS)
	rm -rf $(OBJDIR)
	@echo "$(NAME) build removed \033[32msuccessfully\033[0m!"

fclean: clean
	make fclean -C $(GNLDIR)
	make fclean -C $(LIBFTDIR)
	@echo "\033[33mRemoving $(NAME)...\033[0m"
	$(RM) $(NAME)
	rm -rf $(MLXDIR)
	@echo "$(NAME) removed \033[32msuccessfully\033[0m!"

re: fclean all 

.PHONY: all clean fclean re libft libmlx gitclone 