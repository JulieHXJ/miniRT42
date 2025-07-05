#
#
CC = cc
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
	@echo "\033[33mCompilating $(NAME) static library...\033[0m"
	ar rcs $(NAME) $(OBJS)
	@echo "$(NAME) created \033[32msuccessful\033[0m!"

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
