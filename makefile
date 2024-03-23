NAME = conwaysGameOfLife

CC = cc 

CFLAGS=  -Werror -Wall -Wextra -g
LFLAGS= -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
SRCS_RULE= conwaysRuleFunction.c tahasRuleFunction.c
SRCS = main.c boardUpdate.c inputHandling.c ${SRCS_RULE}

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