/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 14:32:51 by acakste           #+#    #+#             */
/*   Updated: 2018/11/27 16:07:51 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>


void	print_token_lst(t_nodes *token)
{
	t_nodes	*cur;

	cur = token;
	while (cur)
	{
		printf("%s -> ", cur->content);
		cur = cur->next;
	}
	printf("\n");
}

int		check_token(t_nodes **cur, t_list **arguments)
{
	char	*expanded_str;
	t_list	*sub_lst;
	t_nodes	*tmp;
	static 	int times = 0;

	// print_token_lst((*arguments)->head);
	token_expand(&expanded_str, (*cur)->content);
	sub_lst = split_args(expanded_str, 0);
	if (sub_lst) //don't need to do, if sub_lst inside
	{
		if ((*cur)->prev)
			(*cur)->prev->next = sub_lst->head;
		else
			(*arguments)->head = sub_lst->head;
		sub_lst->head->prev = (*cur)->prev;
		if ((*cur)->next)
			(*cur)->next->prev = sub_lst->tail;
		else
			(*arguments)->tail = sub_lst->tail;
		sub_lst->tail->next = (*cur)->next;
		ft_strdel(&(*cur)->content); // leads to double free on error
		free((*cur));
		*cur = sub_lst->head;
		*cur = (*cur)->next;
		free(sub_lst);
	}
	else
	{
		printf("2.\n");
		tmp = (*cur)->next;
		if ((*cur)->prev)
			(*cur)->prev->next = tmp;
		if (tmp)
			tmp->prev = (*cur)->prev;
		free(*cur);
		*cur = tmp;
		// (*cur)->content = expanded_str;
	}
		// if (times == 2)
		// {
		// 	printf("stopping\n");
		// 	while (1)
		// 		;
		// }
	// if (times == 1)
	// 	while (1)
	// 		;
	times++;
	// ft_strdel(&expanded_str);
	// printf("check_token end\n");
	return (0);
}

int		expand_tokens(t_list **arguments)
{
	t_nodes	*cur;
	static int times = 0;

	cur = (*arguments)->head;
	while (cur)
	{
		check_token(&cur, arguments);
		times++;
	}
	//go through list. check each token.
		//check the word and create, replace or remove token in the list.
	return (0);
}
