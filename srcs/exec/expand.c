/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 09:01:02 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/27 15:09:10 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

static int	expand_argv(char **argv)
{
	size_t	i;

	i = 0;
	while (argv[i])
	{
		// if (exec_backticks(&argv, argv[i], i)) // we can essentially have multiple backticks in one arg
			// return (0);
		//echo "`cat author``cat author`" vs echo '`cat author``cat author`'
		// we have to do backticks after theos quote expansions.
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

static int	expand_assignments(t_assign *a)
{
	t_assign *cur;

	cur = a;
	while (cur)
	{
		// printf("Value: %s\n", cur->value);
		expand_str(&cur->value, cur->value);
		// printf("Expanded: %s\n", cur->value);
		cur = cur->next;
	}
	return (0);
}

//Can expand_argv, redirects etc ever fail?
int			expand(t_cmd *cmd)
{
	if (cmd->argv && expand_argv(cmd->argv))
		return (1);
	if (cmd->redirects && expand_redirects(cmd->redirects))
		return (1);
	if (cmd->assign && expand_assignments(cmd->assign))
	{
		// printf("Expand assignemnts\n");
		return (1);
	}
	return (0);
}
