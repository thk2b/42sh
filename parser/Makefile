NAME = parser

INCLUDES = -I ../includes/

SRCS = $(addprefix srcs/, read.c)

OBJ = $(SRCS:*.c=*.o)

FLAGS = -Wall -Werror -Wextra

CC = gcc

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) $(INCLUDES) $(SRCS) -o $(NAME)

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all