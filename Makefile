NAME		= 42sh

LIB			= libft.a
LIB_DIR		= libft
LIB_PATH	= $(LIB_DIR)/$(LIB)

CC			= gcc
FLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I ./libft/includes -I ./includes
COMPILE		= $(CC) $(FLAGS) $(INCLUDES)

SRCS		= $(addprefix srcs/, main.c\
	$(addprefix builtins/, b_cd.c b_echo.c b_env.c b_setenv.c b_unsetenv.c)\
	errors.c\
	$(addprefix exec/, )\
	$(addprefix get_line/, )\
	$(addprefix parser/, )\
	$(addprefix tokenizer/, )\
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

fclean:
	make fclean -C $(LIB_DIR)
	rm -rf $(NAME)
