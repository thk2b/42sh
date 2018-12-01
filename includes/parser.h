/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:31:26 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/30 15:55:40 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <strings.h>
# include <string.h>
# include <libft.h>
# include "grammar.h"
# include "get_next_line.h"
# include <errno.h>
# include <ft_printf.h>
# include "stack2.h"

# define IS_SPACE(x) (x == ' ' || x == '\t' || x == '\n')
# define IS_QU(x) (x == '`' || x == '\'' || x == '\"')
# define IS_OP(x) (x == '&' || x == '|')
# define IS_VALID_CHAR(c) (c == '_' || c == '=' || c == '.' || ft_isalnum(c) || c == '/')
# define IS_SEMI(x) (x == ';')
# define IS_RED(x) (x == '<' || x == '>')
# define IS_REDIRECT_LEFT(x) (x == '<')
# define IS_REDIRECT_RIGHT(x) (x == '>')
# define NOT_QUOTE !(quote & (Q_SQUOTE | Q_BSLASH))
# define WOW() printf("->%s\n", __func__)
# define REDIRECT_LEFT			1 //rename to heredoc?
# define REDIRECT_RIGHT			2 //rename to redirect?
# define REDIRECT_APPEND_RIGHT	3 //rename to redirect_append?
# define HEREDOC_DOC			4
# define HEREDOC_STR			5
# define AGGREG_RED				6

# define SEEKING_END 1
# define END 2

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct	s_redirect
{
	char						type;
	int							fd;
	int							fd_dest;
	char						*path;
	int							old_fd;
	int							close;
	struct s_redirect			*next;
}				t_redirect;

# define T_CMD					1
# define T_PIPE					2
# define T_AND					3
# define T_OR					4
# define T_SEMI					5

# define T_ALPHANUM				6
# define T_QUOTE				7
# define T_BRACKET				8
# define T_PAREN				9
# define T_BACKTICK				10
# define T_SPACE				11
# define T_COMMENT				12

typedef struct	s_nodes
{
	char				*content;
	struct s_nodes		*next;
	struct s_nodes		*prev;
}				t_nodes;

typedef struct	s_token_lst
{
	t_nodes				*head;
	t_nodes				*tail;
}				t_token_lst;

typedef struct	s_assign
{
	char			*value;
	struct s_assign	*next;
}				t_assign;

typedef struct	s_tree
{
	char						type;
	struct s_tree				*left;
	struct s_tree				*right;
	struct s_cmd				*data;
	struct s_tree				*parent;
}				t_tree;

typedef struct	s_cmd
{
	t_redirect					*redirects;
	t_assign					*assign;
	char						**argv;
	int							return_status;
}				t_cmd;

typedef struct	s_token
{
	int							type;
	int							status;
	char						*content;
}				t_token;


/*
** error
*/

int				check_semicolon(char *input);
int				check_redirections(char *input);
int				error_special(char *input, t_token_lst **head);
int				check_errors(char *content, char *s);
int				check_input(const char *input);
/*
** lexing
*/

int				is_alpha_numeric(char c);
int				is_and_operator(char c);
int				is_pipe_operator(char c);
int				is_quote(char c);
int				is_bracket(char c);
int				is_paren(char c);
char			*ft_strdup_range(const char *str, int begin, int end);
void			free_list(t_token_lst *head);
void			print_token_lst(t_token_lst *token);
t_nodes			*new_node(char *new_data);
t_token_lst			*new_list(char *new_data);
void			append(t_token_lst **head_ref, char *new_data);
char			*trip_join(const char *s1, const char c, const char *s2);
void			free_append(char **s, char *end);
int				skip_whitespace(const char *input, int p);
int				check_errors(char *content, char *s);
int				classify_token(char c);
void			init_token_info(t_token *info);
int				pull_quote_content(const char *input, int *p, t_node **stack);
int				pull_operator(t_token_lst **head, const char *input,
								int *p, int errors);
int				pull_token(t_token_lst **head, const char *input,
							int *p, int errors);
int				skip_to_end_of_line(const char *input, int *p);
int				interpret_token(t_token_lst **head, const char *input,
								int *p, int errors);
t_token_lst			*interpret_input(const char *input, int *token_completion,
				int errors);
t_token_lst			*split_args(char *input, int activate_errors);
t_tree			*parse(char *input);
int				is_op(char *str);
void			print_list(t_token_lst *lst);

/*
** grammar
*/

int				is_word(char *str);
void			push_back_test(t_redirect **redir, t_redirect *redirect);
t_cmd			*init_command(void);
int				is_reserved_word(char *s);
int				is_valid_name_char(char c);
int				is_assignment_word(char *s);
void			push_back(t_assign **head, char *value);
int				pull_assignment(char *assignment, t_cmd **cmd);
int				is_redirection(char *s);
int				is_number(char *s);
char			determine_redirection_type(char *o);
t_redirect		*new_redirection(char *operator_, int fd,
									int fd_dest, int close);
int				pull_redirection(t_nodes **node, t_nodes *prev, t_cmd **cmd);
int				get_ptr_len(char **s);
void			free_2d(char **s);
int				append_word_argv(char *word, t_cmd **cmd);
t_cmd			*create_cmd(t_nodes **tokens);
void			print_assign_info(t_assign *s);
void			print_redirect_info(t_redirect *r);
void			print_command_info(t_cmd *cmd);
int				is_red(char *input);
void			error_message(char *line);
int				is_aggregation(char *s1, t_nodes *prev);

/*
** AST
*/

t_tree			*build_tree(t_nodes *tokens);
t_tree			*insert(t_tree **root, t_cmd *data, char type);
t_tree			*build_subtree(t_tree **current, t_tree **new_root);
int				compare_precedence(char a, char b);
void			print_tree(t_tree *tree);
char			get_type(char *s);
t_tree			*new_leaf(t_tree *parent, char type, t_cmd *data);

/*
**	expand_tokens.c
*/

int				remove_squote(int quote, char *str, int *i);
int				expand_tokens(t_token_lst **arguments, char not_backticks);
void			token_expand(char **dst, char *str);
int				remove_dquote(int quote, char *str, int *i);
int				remove_bslash(int quote, char *str, int *i);
int				strip_quotes(t_nodes *tokens);
int				strip_str_quotes(char *str);

#endif
