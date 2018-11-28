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

int		check_token(t_nodes **cur, t_list **arguments)
{
	char	*expanded_str;
	t_list	*sub_lst;
	t_nodes	*tmp;

	token_expand(&expanded_str, (*cur)->content);
	sub_lst = split_args(expanded_str, 0);
	if (sub_lst)
	{
		if ((*cur)->prev)
			(*cur)->prev->next = (sub_lst) ? sub_lst->head : NULL;
		else
			(*arguments)->head = (sub_lst) ? sub_lst->head : NULL;
		if (sub_lst)
			sub_lst->head->prev = (*cur)->prev;
		if ((*cur)->next)
			(*cur)->next->prev = (sub_lst) ? sub_lst->tail : NULL;
		else
			(*arguments)->tail = (sub_lst) ? sub_lst->tail : NULL;
		if (sub_lst)
			sub_lst->tail->next = (*cur)->next;
		free((*cur));
		*cur = (sub_lst) ? sub_lst->head : NULL;
		*cur = (*cur)->next;
	}
	else
	{
		tmp = (*cur)->next;
		if ((*cur)->prev)
			(*cur)->prev->next = tmp;
		if (tmp)
			tmp->prev = (*cur)->prev;
		free(*cur);
		*cur = tmp;
		// (*cur)->content = expanded_str;
	}
	// printf("check_token end\n");
	return (0);
}

int		expand_tokens(t_list **arguments)
{
	t_nodes	*cur;

	cur = (*arguments)->head;
	while (cur)
	{
		check_token(&cur, arguments);
	}
	//go through list. check each token.
		//check the word and create, replace or remove token in the list.
	return (0);
}
