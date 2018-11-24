/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 09:01:02 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/23 16:17:14 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

static int	expand_argv(char **argv)
{
	size_t	i;

	i = 0;
	while (argv[i])
	{
		expand_str(argv + i, argv[i]);
		i++;
	}
	return (0);
}

static int	expand_redirects(t_redirect *r)
{
	t_redirect *cur;

	cur = r;
	while (cur)
	{
		expand_str(&cur->path, cur->path);
		cur = cur->next;
	}
	return (0);
}

int			expand(t_cmd *cmd)
{
	if (cmd->argv && expand_argv(cmd->argv))
		return (1);
	if (cmd->redirects && expand_redirects(cmd->redirects))
		return (1);
	return (0);
}
