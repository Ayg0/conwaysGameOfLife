NAME = cgl

CC = cc 

CFLAGS=  -Werror -Wall -Wextra -g
LFLAGS= -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
SRCS = main.c

OBJS = ${SRCS:.c=.o}

RM = rm -f

all: $(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re