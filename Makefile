NAME		= 42sh

LIB			= libft.a
LIB_DIR		= libft
LIB_PATH	= $(LIB_DIR)/$(LIB)

CC			= gcc
FLAGS		= -Wall -Wextra -Werror
COMPILE		= $(CC) $(FLAGS)

SRCS		= $(addprefix srcs/,\
	$(addprefix builtins/, )\
	error.c
	$(addprefix exec/, )\
	$(addprefix get_line/, )\
	$(addprefix parser/, )\
	$(addprefix tokenizer/, )\
)
OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(COMPILE) $(OBJS) -o $(NAME)

%.o: %.c
	$(COMPILE) -c $< -o $@

$(LIB):
	make -C $(LIB_DIR)

clean:
	make clean -C $(LIB_DIR)
	rm -rf $(OBJS)

fclean:
	make fclean -C $(LIB_DIR)
	rm -rf $(NAME)
