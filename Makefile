NAME		= 42sh

LIB			= libft.a
LIB_DIR		= libft
LIB_PATH	= $(LIB_DIR)/$(LIB)

TERMCAP		= -ltermcap
READLINE	= ft_readline/libft_readline.a

CC			= gcc
FLAGS		= -Wall -Wextra -Werror -g #-fsanitize=address
INCLUDES	= -I ./libft/includes -I ./includes
COMPILE		= $(CC) $(FLAGS) $(INCLUDES)

SRCS		= $(addprefix srcs/, main.c errors.c \
	$(addprefix builtins/, b_cd.c b_echo.c b_env.c b_setenv.c b_unsetenv.c builtin.c\
				b_exit.c b_export.c b_unset.c)\
	$(addprefix exec/, assignments.c exec_cmd.c exec_tree.c expand_str.c expand.c path.c redirects.c)\
	$(addprefix parser/, parse_tokens.c preliminary_parse.c tree2.c)\
	$(addprefix tokenizer/, )\
	$(addprefix local_var/, local_var.c)\
)
OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIB) $(READLINE)
	$(COMPILE) $(OBJS) $(LIB_PATH) $(TERMCAP) $(READLINE) -o $(NAME)

%.o: %.c
	$(COMPILE) -c $< -o $@

$(LIB):
	make -C $(LIB_DIR)

$(READLINE):
	make -C ft_readline

clean:
	make clean -C $(LIB_DIR)
	make clean -C ft_readline
	rm -rf $(OBJS)

fclean: clean
	make fclean -C $(LIB_DIR)
	make fclean -C ft_readline
	rm -rf $(NAME)

re: fclean all
