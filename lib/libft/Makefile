#
#
CC = cc
CFLAGS = -Wall -Werror -Wextra -I$(INCDIR)

INCDIR = ./inc
SRCDIR = ./src
OBJDIR = ./obj

SRCS = $(SRCDIR)/ft_isalnum.c $(SRCDIR)/ft_isprint.c $(SRCDIR)/ft_strlen.c $(SRCDIR)/ft_toupper.c\
		$(SRCDIR)/ft_tolower.c $(SRCDIR)/ft_isalpha.c $(SRCDIR)/ft_isdigit.c $(SRCDIR)/ft_isascii.c\
		$(SRCDIR)/ft_memset.c $(SRCDIR)/ft_strchr.c $(SRCDIR)/ft_strrchr.c $(SRCDIR)/ft_strlcpy.c\
		$(SRCDIR)/ft_strncmp.c $(SRCDIR)/ft_strlcat.c $(SRCDIR)/ft_atoi.c $(SRCDIR)/ft_bzero.c\
		$(SRCDIR)/ft_memcpy.c $(SRCDIR)/ft_memcmp.c $(SRCDIR)/ft_memmove.c $(SRCDIR)/ft_memchr.c\
		$(SRCDIR)/ft_calloc.c $(SRCDIR)/ft_strdup.c $(SRCDIR)/ft_itoa.c $(SRCDIR)/ft_putchar_fd.c\
		$(SRCDIR)/ft_putendl_fd.c $(SRCDIR)/ft_putnbr_fd.c $(SRCDIR)/ft_putstr_fd.c $(SRCDIR)/ft_substr.c\
		$(SRCDIR)/ft_strjoin.c $(SRCDIR)/ft_striteri.c $(SRCDIR)/ft_strmapi.c $(SRCDIR)/ft_strtrim.c\
		$(SRCDIR)/ft_strnstr.c $(SRCDIR)/ft_split.c $(SRCDIR)/ft_strcmp.c 

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
NAME = libft.a

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -f $(OBJS)
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re