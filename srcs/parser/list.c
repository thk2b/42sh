/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 19:28:26 by ale-goff          #+#    #+#             */
/*   Updated: 2018/11/28 20:08:37 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void			print_list(t_list *lst)
{
	t_nodes			*node;
	int				index;

	node = lst->head;
	index = 0;
	while (node)
	{
		printf("[%d] %s\n", index++, node->content);
		node = node->next;
	}
}

t_nodes			*new_node(char *new_data)
{
	t_nodes		*node;

	node = (t_nodes *)malloc(sizeof(t_nodes));
	node->content = new_data;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_list			*new_list(char *new_data)
{
	t_list		*lst;
	t_nodes		*node;

	node = new_node(new_data);
	lst = (t_list *)malloc(sizeof(t_list));
	lst->head = node;
	lst->tail = node;
	return (lst);
}

void			append(t_list **head_ref, char *new_data)
{
	t_nodes		*new;

	if (*head_ref == NULL)
	{
		*head_ref = new_list(new_data);
		return ;
	}
	new = new_node(new_data);
	new->prev = (*head_ref)->tail;
	(*head_ref)->tail->next = new;
	(*head_ref)->tail = new;
}

void			free_list(t_list *head)
{
	t_nodes	*tmp;
	t_nodes *free_;

	tmp = head->head;
	while (tmp)
	{
		free_ = tmp;
		free(tmp->content);
		tmp = tmp->next;
		free(free_);
	}
	free(head);
	head = NULL;
}
