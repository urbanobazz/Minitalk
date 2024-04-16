NAME = libft.a
CC = cc
CCAR = ar rcs
CFLAGS = -Wall -Wextra -Werror
HFILE = libft.h
OBJS = ${SRC:.c=.o}
SRC =	ft_atoi.c\
		ft_isdigit.c\
		ft_putstr_fd.c\
		./ft_printf/ft_printf.c\
		./ft_printf/ft_putsth.c\
		./ft_printf/ft_printf_utils.c\

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CCAR) $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
