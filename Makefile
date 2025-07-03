#
#
CC = gcc
MAKEFLAGS += -s
CFLAGS = -Wall -Wextra -Werror -Ofast -flto -march=native -Wunreachable-code -I$(MLXDIR)/inc -I$(GNLDIR)/inc -I./inc
MLX_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit -ldl -lglfw
# MLX_FLAGS = -ldl -lglfw

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
		$(SRCDIR)/render/hook_camera.c \
		$(SRCDIR)/render/hook.c \
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
	@echo "🚀 \033[33m$(NAME)\033[0m compiled \033[32msuccessfully\033[0m!"


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(GNL):
	$(MAKE) -C $(GNLDIR) LIBFTDIR=../libft

$(MLX): $(MLXDIR)
	@printf "[.]   📦 Compiling \033[33mMLX42\033[0m...\r"
	@cmake $(MLXDIR) -B $(MLXDIR)/build > /dev/null 2>&1 && \
	$(MAKE) -s -C $(MLXDIR)/build -j4 > /dev/null 2>&1 && \
	printf "[✅]  📦 Compiled \033[33mMLX42\033[0m!    \n"

gitclone:
	@if [ ! -d "$(MLXDIR)" ]; then \
		printf "[.]   ⚙️ Cloning \033[33mMLX42\033[0m...\r"; \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLXDIR) > /dev/null 2>&1; \
		printf "[✅]  ⚙️ Cloned \033[33mMLX42\033[0m!   \n"; \
	fi

libmlx: $(MLXDIR)/build/libmlx42.a

libft:
	@printf "[.]   📦 Compiling \033[33mlibft\033[0m...\r"
	@$(MAKE) -s -C $(LIBFTDIR) > /dev/null && \
	printf "[✅]  📦 Compiled \033[33mlibft\033[0m!    \n"

gnl:
	@printf "[.]   📦 Compiling \033[33mgetnextline\033[0m...\r"
	@$(MAKE) -C $(GNLDIR) > /dev/null && \
	printf "[✅]  📦 Compiled \033[33mgetnextline\033[0m!    \n"

clean:
	@$(MAKE) clean -C $(GNLDIR)
	@$(RM) $(OBJS) $(BONUS_OBJS)
	@rm -rf $(OBJDIR) $(MLXDIR)

fclean: clean
	@printf "[.]   💀 Removing \033[33m$(NAME)\033[0m build...\r"
	@$(RM) $(NAME)
	printf "[✅]  💀 Removed \033[33m$(NAME)\033[0m build!    \n"

re: fclean all 

# # # # # # # # # # # # # # # # # # # # # # # # # # # #
#						BONUS						  #
# # # # # # # # # # # # # # # # # # # # # # # # # # # #

BONUSDIR = ./bonus
BONUS_SRCDIR = $(BONUSDIR)/src
BONUS_SRCS := $(BONUSDIR)/$(SRCDIR)/cone.c		 
BONUSINC = -I$(BONUSDIR)/inc
BONUS_OBJS = $(BONUS_SRCS:$(BONUS_SRCDIR)/%.c=$(OBJDIR)/%.bonus.o)

$(OBJDIR)/%.bonus.o: $(BONUS_SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(BONUSINC) -c $< -o $@

bonus: gitclone libmlx libft gnl $(OBJS) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(BONUS_OBJS) -o $(NAME) $(MLX) $(MLX_FLAGS) -L$(GNLDIR) -lgnl -L$(LIBFTDIR) -lft -lm
	@echo "🚀 \033[33m$(NAME) (bonus)\033[0m compiled \033[32msuccessfully\033[0m!"


.PHONY: all clean fclean re libft libmlx gitclone bonus