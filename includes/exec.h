/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 17:52:34 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/17 18:49:09 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "ft_sh.h"

typedef struct	s_table
{
	char	type;
	int		(*f)();
}				t_table;

/*
**	Handle environment
**		getenv, setenv, unsetenv, env, 
*/

/*
**	Exec builtins
*/

/*
**	Path management (make it easy to add hash map)
**		Split path, try each, validate with access
*/

/*
**	Exec tree
**		Redirection
**		Pipes
**		Semi (multiple commands)
**		Logical Operators
**		Simple Command
*/

int		exec_tree(t_tree *tree, int use_current_process);
int		exec_semi(t_tree *tree, int use_current_process);
int		exec_pipe(t_tree *tree, int use_current_process);
int		exec_and(t_tree *tree, int use_current_process);
int		exec_or(t_tree *tree, int use_current_process);
int		exec_cmd(t_tree *tree);

/*
**	Our Bonues
**		Termcaps
**		Local Variables
**		Back Quotes
**		Command History
*/


/*
**	More Bonuses
**		File Descriptors and read
**		Advanced redirectionss
*/

#endif
