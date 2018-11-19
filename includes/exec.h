/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 17:52:34 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/19 09:02:05 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include <ft_sh.h>
# include <sys/stat.h>
# define CREAT_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IRUSR)

typedef struct	s_table
{
	char	type;
	int		(*f)();
}				t_table;

/*
**	expand.c
*/

int		expand(char **argv);

/*
**	redirects.c
*/

int		init_redirects(t_redirect *redirect);

/*
**	exec_cmd.c
*/
char	*search_cmd(char *argv);
int		exec_cmd(t_tree *tree);

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
**	path.c
**	Path management (make it easy to add hash map)
**		Split path, try each, validate with access
*/
int		path_init(void);
char	*path_search(char *executable_name, char *exists);
void	path_teardown(void);

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
**		Sub_module with hash function for storing local variables
**		
**		
**		
*/


#endif
