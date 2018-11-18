NAME = parser

INCLUDES = -I includes/

SRCS = $(addprefix srcs/, read.c)

ASAN = -fsanitize=address -fsanitize=undefined -g

OBJ = $(SRCS:%.c=%.o)

FLAGS = -Wall -Werror -Wextra

CC = gcc

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) $(ASAN) $(INCLUDES) $(SRCS) -o $(NAME)

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
