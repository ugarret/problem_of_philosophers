NAME = philo
FLAGS = -Wall -Wextra -Werror
SRC = main.c	eat_or_die.c	check.c
OBJS = $(SRC:.c=.o)
HEADER = includes
.PHONY: all clean fclean re

all: $(NAME)
	
$(NAME): 	$(OBJS)
			gcc $(FLAGS) -I $(HEADER) $(OBJS) -o $(NAME) 

%.o: %.c $(HEADER)
	gcc $(FLAGS) -I $(HEADER) -o $@ -c $<

clean:
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME)

re: fclean all