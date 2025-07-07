# # # # # # # # # # # # # # # # # # # # # # # # # #
#					GENERAL						  #
# # # # # # # # # # # # # # # # # # # # # # # # # #


CC = gcc
MAKEFLAGS += -s
CFLAGS = -Wall -Wextra -Werror -Ofast -flto -march=native -Wunreachable-code -g -I$(MLXDIR)/inc -I$(GNLDIR)/inc -I./inc -fsanitize=address
MLX_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit -ldl -lglfw
# MLX_FLAGS = -ldl -lglfw

OBJDIR = ./obj
MLXDIR = ./lib/MLX42
LIBFTDIR = ./lib/libft
GNLDIR = ./lib/getnextline

MLX = $(MLXDIR)/build/libmlx42.a
LIBFT = $(LIBFTDIR)/libft.a
GNL = $(GNLDIR)/libgnl.a
NAME = minirt

RM = rm -f
.DEFAULT_GOAL := all


# # # # # # # # # # # # # # # # # # # # # # # # # #
#					MANDATORY					  #
# # # # # # # # # # # # # # # # # # # # # # # # # #


SRCDIR = ./src

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
		$(SRCDIR)/render/hook_camera.c \
		$(SRCDIR)/render/hook.c \
		$(SRCDIR)/lighting/calculate.c \
		$(SRCDIR)/lighting/calculate2.c

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)


# # # # # # # # # # # # # # # # # # # # # # # # # #
#					BONUS						  #
# # # # # # # # # # # # # # # # # # # # # # # # # #


SRCBONUSDIR = ./bonus/src

BONUS_SRCS := $(SRCBONUSDIR)/cone.c $(SRCBONUSDIR)/color_disruption.c \
		$(SRCBONUSDIR)/texture.c $(SRCBONUSDIR)/read_texture.c 

BONUS_OBJS = $(BONUS_SRCS:$(SRCBONUSDIR)/%.c=$(OBJDIR)/%.o)


# # # # # # # # # # # # # # # # # # # # # # # # # #
#					COMPILATION					  #
# # # # # # # # # # # # # # # # # # # # # # # # # #


ALL_OBJS = $(OBJS) $(BONUS_OBJS)

$(NAME): $(ALL_OBJS) $(MLX) $(LIBFT) $(GNL)
	$(CC) $(CFLAGS) $(ALL_OBJS) -o $(NAME) $(MLX) $(MLX_FLAGS) -L$(GNLDIR) -lgnl -L$(LIBFTDIR) -lft -lm
	@echo "🚀 \033[33m$(NAME)\033[0m compiled \033[32msuccessfully\033[0m!"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCBONUSDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(GNL):
	$(MAKE) -C $(GNLDIR) LIBFTDIR=../libft

$(MLX): $(MLXDIR)
	@printf "[.]   📦 Compiling \033[33mMLX42\033[0m...\r"
	@cmake $(MLXDIR) -B $(MLXDIR)/build > /dev/null 2>&1 && \
	$(MAKE) -s -C $(MLXDIR)/build -j4 > /dev/null 2>&1 && \
	printf "[✅]  📦 Compiled \033[33mMLX42\033[0m...  \n"


# # # # # # # # # # # # # # # # # # # # # # # # # #
#					RULES						  #
# # # # # # # # # # # # # # # # # # # # # # # # # #


all: gitclone libmlx libft gnl $(NAME)

gitclone:
	@if [ ! -d "$(MLXDIR)" ]; then \
		printf "[.]   🔗 Cloning \033[33mMLX42\033[0m...\r"; \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLXDIR) > /dev/null 2>&1; \
		printf "[✅]  🔗 Cloned \033[33mMLX42\033[0m...\n"; \
	fi

libmlx: $(MLXDIR)/build/libmlx42.a

libft:
	@$(MAKE) -s -C $(LIBFTDIR)

gnl:
	@$(MAKE) -C $(GNLDIR)

clean:
	@$(MAKE) clean -C $(GNLDIR)
	@$(RM) $(OBJS)
	@rm -rf $(OBJDIR)
	@rm -rf $(MLXDIR)

fclean: clean
	@printf "[.]   🧹 Removing \033[33m$(NAME)\033[0m build...\r"
	@$(RM) $(NAME)
	printf "[✅]  🧹 Removed \033[33m$(NAME)\033[0m build...  \n"

re: fclean all 

.PHONY: all clean fclean re libft libmlx gitclone 