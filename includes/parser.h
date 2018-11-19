/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:31:26 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/17 16:48:57 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define REDIRECT_LEFT			1
# define REDIRECT_RIGHT			2
# define REDIRECT_APPEND_RIGHT	3

typedef struct					s_redirect
{
	char						type;
	int							fd;
	char						*path;
	struct s_redirect			*next;
}								t_redirect;

typedef struct					s_assign
{
	char			*value;
	struct s_assign	*next;
}								t_assign;

# define T_CMD					1
# define T_PIPE					2
# define T_AND					3
# define T_OR					4
# define T_SEMI					5

typedef struct					s_cmd
{
	t_redirect					*redirects;
	t_assign					*assign;
	char						**argv;
	int							return_status;
}								t_cmd;

typedef struct					s_tree
{
	char						type;
	struct s_tree				*left;
	struct s_tree				*right;
	struct s_tree				*parent;
	struct s_cmd				*data;
}								t_tree;

#endif
