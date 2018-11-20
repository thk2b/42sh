/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:31:26 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/20 08:39:18 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <strings.h>
#include <string.h>
#include <libft.h>
#include "grammar.h"
#include "get_next_line.h"

# define IS_SPACE(x) (x == ' ' || x == '\t' || x == '\n')
# define IS_OP(x) (x == '&' || x == '|')
# define IS_SEMI(x) (x == ';')
# define WOW() printf("->%s\n", __func__)
# define REDIRECT_LEFT			1 //rename to heredoc?
# define REDIRECT_RIGHT			2 //rename to redirect?
# define REDIRECT_APPEND_RIGHT	3 //rename to redirect_append? 

# define SEEKING_END 1
# define END 2

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct					s_redirect
{
	char						type;
	int							fd;
	char						*path;
	struct s_redirect			*next;
}								t_redirect;

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

typedef struct			s_nodes
{
	char				*content;
	struct s_nodes		*next;
}						t_nodes;

typedef struct			s_list
{
	t_nodes				*head;
	t_nodes				*tail;
}						t_list;

/*typedef struct					s_list
{
	char						*content;
	struct s_list				*next;
}
t_list;
*/

typedef struct        	         s_assign
{
    char				*value;
    struct s_assign		*next;
}                                t_assign;

typedef struct					s_tree
{
	char						type;
	struct s_tree				*left;
	struct s_tree				*right;
	struct s_cmd				*data;
	struct s_tree				*parent;
}								t_tree;

typedef struct					s_cmd
{
	t_redirect					*redirects;
	t_assign					*assign;
	char						**argv;
	int							return_status;
}								t_cmd;

typedef struct					s_token
{
	int							type;
	int							status;
	char						*content;
}								t_token;

char			*ft_strdup_range(const char *str, int begin, int end);
t_cmd			*create_cmd(t_nodes **tokens);
int				is_op(char *str);
void			print_command_info(t_cmd *cmd);

#endif
