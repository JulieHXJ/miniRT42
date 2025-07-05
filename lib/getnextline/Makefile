#
#
CC = cc
MAKEFLAGS += -s
CFLAGS = -g -Wall -Werror -Wextra -I$(INCDIR) -I$(LIBFTDIR)/inc

SRCDIR = ./src
OBJDIR = ./obj
INCDIR = ./inc
LIBFTDIR ?= ../libft

SRCS = $(SRCDIR)/get_next_line.c

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
LIBFT = $(LIBFTDIR)/libft.a
NAME = libgnl.a

all: $(LIBFT) $(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	@printf "[.]   📦 Compiling \033[33mgetnextline\033[0m...\r"
	ar rcs $(NAME) $(OBJS) > /dev/null && \
	printf "[✅]  📦 Compiled \033[33mgetnextline\033[0m...  \n"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

clean:
	@$(MAKE) clean -C $(LIBFTDIR)
	rm -f $(OBJDIR)/*.o
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re
