NAME		= 42sh

LIB			= libft.a
LIB_DIR		= libft
LIB_PATH	= $(LIB_DIR)/$(LIB)

CC			= gcc
FLAGS		= -Wall -Wextra -Werror -g -fsanitize=address
INCLUDES	= -I ./libft/includes -I ./includes
COMPILE		= $(CC) $(FLAGS) $(INCLUDES)

SRCS		= $(addprefix srcs/, main.c errors.c \
	$(addprefix builtins/, b_cd.c b_echo.c b_env.c b_setenv.c b_unsetenv.c builtin.c\
				b_exit.c b_export.c b_unset.c)\
	$(addprefix exec/, assignments.c exec_cmd.c exec_tree.c expand.c path.c redirects.c)\
	$(addprefix get_line/, )\
	$(addprefix parser/, parse_tokens.c preliminary_parse.c tree2.c)\
	$(addprefix tokenizer/, )\
	$(addprefix local_var/, local_var.c)\
)
OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(COMPILE) $(OBJS) $(LIB_PATH) -o $(NAME)

%.o: %.c
	$(COMPILE) -c $< -o $@

$(LIB):
	make -C $(LIB_DIR)

clean:
	make clean -C $(LIB_DIR)
	rm -rf $(OBJS)

fclean: clean
	make fclean -C $(LIB_DIR)
	rm -rf $(NAME)

re: fclean all
