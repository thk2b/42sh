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
**	exec_tree.c
*/
int		exec_node(t_tree *tree, int use_current_process);
int		exec_semi(t_tree *tree, int use_current_process);
int		exec_pipe(t_tree *tree, int use_current_process);
int		exec_and(t_tree *tree, int use_current_process);
int		exec_or(t_tree *tree, int use_current_process);
int		exec_cmd(t_tree *tree);


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

/*
**	Our Bonues
**		Termcaps
**		Local Variables
**		Command History
*/

/*
**	More Bonuses
**		File Descriptors and read
**		Advanced redirections, output aggregation and heredoc
**		Back Quotes
*/


/*
**	TASKS:
**		Reading and executing the tree. Along with all the operator functions.
**		The "execute basic command", Path Management.
**		Handle Environment, unsetenv, env, getenv
**		Main, loop, simple getline
**		Expansions
**		
**		
**		
*/


#endif
