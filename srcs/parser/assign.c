/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:40:37 by ale-goff          #+#    #+#             */
/*   Updated: 2018/11/28 18:55:00 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void					push_back(t_assign **head, char *value)
{
	t_assign			*new;
	t_assign			*traverse;

	new = malloc(sizeof(*new));
	new->value = ft_strdup(value);
	new->next = NULL;
	if (!(*head))
	{
		*head = new;
		return ;
	}
	traverse = *head;
	while (traverse && traverse->next)
		traverse = traverse->next;
	traverse->next = new;
}

int						pull_assignment(char *assignment, t_cmd **cmd)
{
	int					p;

	p = 0;
	if ((*cmd)->argv == NULL)
		push_back(&(*cmd)->assign, assignment);
	else
		append_word_argv(assignment, cmd);
	return (0);
}
