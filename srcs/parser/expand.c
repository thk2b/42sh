/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <acakste@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 12:44:52 by acakste           #+#    #+#             */
/*   Updated: 2018/12/01 20:03:15 by ale-goff         ###   ########.fr       */
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

static void		if_sub_lst(t_nodes **cur, t_token_lst *sub_lst,
							t_token_lst **arguments)
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
	free((*cur));
	*cur = sub_lst->head;
	*cur = (*cur)->next;
	free(sub_lst);
}

static void		else_sub_lst(t_nodes **cur, t_token_lst **arguments)
{
	t_nodes	*tmp;

	tmp = (*cur)->next;
	if ((*cur)->prev)
		(*cur)->prev->next = tmp;
	else
		(*arguments)->head = tmp;
	if ((*cur)->next)
		(*cur)->next->prev = (*cur)->prev;
	else
		(*arguments)->tail = tmp;
	free(*cur);
	*cur = tmp;
}

static void		set_type_to_cmd(t_token_lst **sub_lst)
{
	t_nodes *cur;

	if (!sub_lst || !(*sub_lst))
		return ;
	cur = (*sub_lst)->head;
	while (cur)
	{
		cur->type = T_CMD;
		cur = cur->next;
	}
}

int				check_token(t_nodes **cur, t_token_lst **arguments)
{
	char		*expanded_str;
	char		*trimmed_str;
	t_token_lst	*sub_lst;

	token_expand(&expanded_str, (*cur)->content);
	sub_lst = NULL;
	if (ft_strcmp(expanded_str, (*cur)->content))
	{
		free((*cur)->content);
		trimmed_str = ft_strtrim(expanded_str);
		if (check_input(trimmed_str) && (*trimmed_str))
			return (1);
		sub_lst = split_args(trimmed_str, 0);
		set_type_to_cmd(&sub_lst);
		free(trimmed_str);
		if (sub_lst)
			if_sub_lst(cur, sub_lst, arguments);
		else
			else_sub_lst(cur, arguments);
	}
	else
		*cur = (*cur)->next;
	free(expanded_str);
	return (0);
}

int				expand_tokens(t_token_lst **arguments, char not_backtick)
{
	t_nodes		*cur;

	cur = (*arguments)->head;
	while (cur)
	{
		if (check_token(&cur, arguments))
			return (1);
	}
	if (not_backtick)
		strip_quotes(((*arguments)->head));
	return (0);
}
