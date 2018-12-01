/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 19:28:26 by ale-goff          #+#    #+#             */
/*   Updated: 2018/11/29 11:41:04 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void			print_token_lst(t_token_lst *lst)
{
	t_nodes			*node;
	int				index;

	node = lst->head;
	index = 0;
	while (node)
	{
		printf("|%s| -> ", node->content);
		node = node->next;
	}
	printf("\n");
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

t_token_lst		*new_list(char *new_data)
{
	t_token_lst	*lst;
	t_nodes		*node;

	node = new_node(new_data);
	lst = (t_token_lst *)malloc(sizeof(t_token_lst));
	lst->head = node;
	lst->tail = node;
	return (lst);
}

void			append(t_token_lst **head_ref, char *new_data)
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

void			free_list(t_token_lst *head)
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
