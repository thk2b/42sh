/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 17:55:29 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/19 15:49:56 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct	s_builtin
{
	char		*name;
	int			(*fn)();
}				t_builtin;

int				b_cd(char **av);
int				b_exit(void);
int				b_echo(char **av);
int				b_env(char **av);
int				b_setenv(char **av);
int				b_unsetenv(char **av);

#endif
