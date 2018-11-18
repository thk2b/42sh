/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:31:26 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/18 12:58:43 by ale-goff         ###   ########.fr       */
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

# define WOW() printf("->%s\n", __func__)
# define REDIRECT_LEFT			1
# define REDIRECT_RIGHT			2
# define REDIRECT_APPEND_RIGHT	3

# define SEEKING_END 1
# define END 2

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

typedef struct					s_tree
{
	char						type;
	struct s_tree				*left;
	struct s_tree				*right;
	struct s_list				*args;
	//	struct s_cmd				*data;
}								t_tree;

typedef struct					s_cmd
{
	t_redirect					*redirects;
	char						**argv;
	int							return_status;
}								t_cmd;


void			read_line(void);
#endif
