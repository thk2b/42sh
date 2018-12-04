/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pull_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 20:05:12 by ale-goff          #+#    #+#             */
/*   Updated: 2018/12/03 17:23:12 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void			push_stack_elem(t_node **stack, const char *input, int tmp)
{
	if (input[tmp] == 34)
	{
		if (tmp > 0 && input[tmp - 1] == '\\')
			;
		else
			push(stack, 1);
	}
	else if (input[tmp] == '\'')
	{
		if (tmp > 0 && input[tmp - 1] == '\\')
			;
		else
			push(stack, 2);
	}
	else if (input[tmp] == '`')
	{
		if (tmp > 0 && input[tmp - 1] == '\\')
			;
		else
			push(stack, 3);
	}
}

int					pull_quote_content(const char *input, int *p,
					t_node **stack)
{
	int					tmp;

	tmp = *p;
	tmp += 1;
	while (input[tmp] && !is_empty(*stack))
	{
		if (input[tmp] == '\'' && peek(*stack) == 2)
			pop(stack);
		else if (input[tmp] == '\"' && peek(*stack) == 1)
			pop(stack);
		else if (input[tmp] == '`' && peek(*stack) == 3)
			pop(stack);
		else if (input[tmp] == '`')
		{
			tmp++;
			while (input[tmp] && input[tmp] != '`')
				tmp++;
		}
		tmp += (input[tmp]) ? 1 : 0;
	}
	*p = tmp;
	return (!input[tmp] ? 1 : 0);
}

int					pull_token(t_token_lst **head, const char *input, int *p,
					int errors)
{
	int					tmp;
	char				*content;
	t_node				*stack;

	stack = NULL;
	tmp = *p;
	while (input[tmp] && ((T_ALPHANUM == classify_token(input[tmp]) ||
	classify_token(input[tmp]) == T_QUOTE)))
	{
		if (input[tmp] == 92)
			tmp += 2;
		if (classify_token(input[tmp]) == T_QUOTE)
		{
			push_stack_elem(&stack, input, tmp);
			if (pull_quote_content(input, &tmp, &stack))
				break ;
		}
		else
			tmp += input[tmp] ? 1 : 0;
	}
	content = ft_strdup_range(input, *p, tmp - 1);
	if (content && error_special(content, head) && errors)
		return (-1);
	append(head, content);
	*p = tmp;
	return (END);
}

int					pull_operator(t_token_lst **head, const char *input, int *p,
					int errors)
{
	int					tmp;
	int					type;
	int					op_max;
	char				*content;

	tmp = *p;
	type = classify_token(input[tmp]);
	op_max = 2;
	while (input[tmp] && type == classify_token(input[tmp]) && op_max--)
		tmp += 1;
	content = ft_strdup_range(input, *p, tmp - 1);
	if ((is_op(content) && ((!(*head)))))
	{
		if (errors)
		{
			error_message(content);
			return (-1);
		}
	}
	if (errors && (check_errors((*head)->tail->content, content) ||
		error_special(content, head)))
		return (-1);
	append(head, content);
	*p = tmp;
	return (0);
}
