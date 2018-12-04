/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 18:02:58 by tkobb             #+#    #+#             */
/*   Updated: 2018/12/03 20:06:36 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH_H
# define FT_SH_H
# include <builtins.h>
# include <sys/ioctl.h>
# include <sys/time.h>
# include <poll.h>
# include <time.h>
# include <get_line.h>
# include <error.h>
# include <parser.h>
# include <exec.h>
# include <local_var.h>
# include <path.h>
# include <builtins.h>
# include <env.h>
# include <ft_printf.h>
# include "../ft_readline/ft_readline.h"
# define NUM_OP 5
# define TRUE 1
# define FALSE 0

typedef	unsigned char	t_bool;

/*
**	init_shell.c
*/
int		init_shell(void);
int		init_environ(void);

/*
**	main.c
*/
void	teardown_shell(void);
void	free_tree(t_tree *root);

/*
**	free_structs.c
*/
void	free_assignments(t_assign *lst);
void	free_redirects(t_redirect *lst);
void	free_tree(t_tree *root);

#endif
