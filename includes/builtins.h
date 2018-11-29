/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 17:55:29 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/27 10:19:11 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <parser.h>

typedef struct	s_builtin
{
	char		*name;
	int			(*fn)();
}				t_builtin;

/*
**	srcs/builtins/
*/
int				b_cd(char **av);
int				b_exit(void);
int				b_echo(char **av);
int				b_env(char **av);
int				b_setenv(char **av);
int				b_unsetenv(char **av);
int				b_unset(char **av);
int				b_export(char **av);
int				builtin(t_cmd *cmd, int *return_status);

/*
**	srcs/builtins/
*/
char			*ft_getenv(const char *name);
int				ft_setenv(const char *name, const char *value, int overwrite);
int				ft_putenv(char *str);
int				ft_unsetenv(const char *name);

#endif
