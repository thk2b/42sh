NAME = parser

INCLUDES = -I includes/ -I./libft/

SRCS = $(addprefix srcs/, preliminary_parse.c)

ASAN = -fsanitize=address -fsanitize=undefined -g

OBJ = $(SRCS:%.c=%.o)

LIBRARY = libft/libft.a

FLAGS = -Wall -Werror -Wextra -g

CC = gcc

all: $(NAME)

%.o: %.c
	gcc $(FLAGS) $(ASAN) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ) $(LIBRARY)
	$(CC) $(FLAGS) $(ASAN) $(INCLUDES) $(SRCS) $(LIBRARY) -o $(NAME)

$(LIBRARY):
	make -C libft/

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
