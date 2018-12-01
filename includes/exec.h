/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 17:52:34 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/30 18:12:21 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include <ft_sh.h>
# include <sys/stat.h>
# define CREAT_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IRUSR)
# define NUM_PATH_SLOTS 100

typedef struct	s_table
{
	char	type;
	int		(*f)();
}				t_table;

/*
**	assignments.c
*/
int				split_assignment(char *str, char **key, char **value);

/*
**	expand.c
*/

/*
**	redirects.c
*/

int				init_redirects(t_redirect *redirect);
int				reset_redirects(t_redirect *redirect);
int				init_heredoc(t_redirect *redirect);

/*
**	exec_cmd.c
*/
char			*search_cmd(char *argv);
int				exec_cmd(t_tree *tree, int use_current_process);

/*
**	exec_tree.c
*/
int				exec_node(t_tree *tree, int use_current_process);
int				exec_pipe(t_tree *tree, int use_current_process);

/*
**	exec_semi_and_or.c
*/
int				exec_and(t_tree *tree, int use_current_process);
int				exec_or(t_tree *tree, int use_current_process);
int				exec_semi(t_tree *tree, int use_current_process);

/*
**	back_ticks.c
*/
int				exec_backticks(char **dst, char *str);


/*
**	back_ticks_comp.c
*/
char	*create_res_str(char *init_str, char *new_str);
char	*build_str_from_pipe(int fd);
t_tree	*parse_backticks(char *input);

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
int				path_init(void);
char			*path_search(char *executable_name, char *exists);
void			path_teardown(void);

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

#endif
