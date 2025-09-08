NAME = philo

OBJDIR = build
INCDIR = inc

SRCS = src/print_error.c \
	src/parser.c \
	src/main.c \
	utils/check_int_overflow.c \
	utils/ft_putstr_fd.c \
	utils/ft_strncpy.c \
	utils/check_num.c \
	utils/ft_atoi.c

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -I$(INCDIR)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
