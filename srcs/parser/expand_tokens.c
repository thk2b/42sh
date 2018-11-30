/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <acakste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 14::51 by acakste           #+#    #+#             */
/*   Updated: 2018/11/28 19:23:35 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

void			print_tokens(t_nodes *token)
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

void			if_sub_lst(t_nodes **cur, t_token_lst *sub_lst, t_token_lst **arguments)
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
	// ft_strdel(&(*cur)->content); attempting double free ?
	free((*cur));
	*cur = sub_lst->head;
	*cur = (*cur)->next;
	free(sub_lst);
}

int				check_token(t_nodes **cur, t_token_lst **arguments)
{
	char		*expanded_str;
	t_token_lst		*sub_lst;
	t_nodes		*tmp;
	static int	times = 0;

	token_expand(&expanded_str, (*cur)->content);
	sub_lst = split_args(expanded_str, 0);
	//strip quotes of sub_lst. Only outer most!
	if (sub_lst)
	{
		if_sub_lst(cur, sub_lst, arguments);
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
	}
	times++;
	return (0);
}

int				expand_tokens(t_token_lst **arguments)
{
	t_nodes		*cur;
	static int	times = 0;

	cur = (*arguments)->head;
	while (cur)
	{
		check_token(&cur, arguments);
		times++;
	}
	return (0);
}
