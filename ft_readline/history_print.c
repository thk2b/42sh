/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 17:38:47 by pdeguing          #+#    #+#             */
/*   Updated: 2018/11/27 15:23:45 by pdeguing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	history_print(int fd, int to_print)
{
	t_dlist	*head;
	int		i;

	head = g_history;
	i = 0;
	while (head && head->next)
	{
		head = head->next;
		i++;
		if (to_print && i >= to_print - 1)
			break ;
	}
	while (head)
	{
		ft_dprintf(fd, "%5d %s\n", g_history_size - i, head->line);
		head = head->prev;
		i--;
	}
}
