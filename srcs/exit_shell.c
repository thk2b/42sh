/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 09:06:35 by pdeguing          #+#    #+#             */
/*   Updated: 2018/11/30 09:07:11 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

void	teardown_shell(void)
{
	extern char	**environ;

	history_file_write(NULL);
	delete_path_map();
	ft_strvdel(environ);
}
