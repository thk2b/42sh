/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 14:32:51 by acakste           #+#    #+#             */
/*   Updated: 2018/11/26 14:32:52 by acakste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

int		check_token(t_nodes **cur, t_list **arguments)
{
	char	*expanded_str;
	t_list	*sub_lst;
	t_nodes	*tmp;

	// printf("check_token start\n");
	//call the expand str on cur_token. returns a string?
	if (expand_str(&expanded_str, (*cur)->content))
		return (1);
	// ft_printf("%s\n", expanded_str);
	//splits the string into a token list. Basically call split_args.
	sub_lst = split_args(expanded_str);
	//add the sub token list into the existing one.
	if (sub_lst)
	{
		// printf("sub lst exists :%s:\n", sub_lst->head->content);
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
		ft_printf("no expansion\n");
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
