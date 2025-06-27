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
	$(MAKE) clean -C $(LIBFTDIR)
	@echo "\033[33mRemoving $(NAME) build...\033[0m"
	rm -f $(OBJDIR)/*.o
	rm -rf $(OBJDIR)
	@echo "$(NAME) build removed \033[32msuccessfully\033[0m!"

fclean: clean
	$(MAKE) fclean -C $(LIBFTDIR)
	@echo "\033[33mRemoving $(NAME)...\033[0m"
	rm -f $(NAME)
	@echo "$(NAME) removed \033[32msuccessfully\033[0m!"
	
re: fclean all

.PHONY: all clean fclean re
