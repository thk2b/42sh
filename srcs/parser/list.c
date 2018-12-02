/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 19:28:26 by ale-goff          #+#    #+#             */
/*   Updated: 2018/12/01 20:01:14 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void			print_token_lst(t_token_lst *lst)
{
	t_nodes			*node;
	int				i;

	node = lst->head;
	i = 0;
	while (node)
	{
		printf("index[%d] = %s\n", i, node->content);
		i++;
		node = node->next;
	}
	printf("\n");
}

t_nodes			*new_node(char *new_data)
{
	t_nodes		*node;

	node = (t_nodes *)malloc(sizeof(t_nodes));
	node->content = new_data;
	node->type = get_type(new_data);
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
