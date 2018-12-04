/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 17:22:00 by tkobb             #+#    #+#             */
/*   Updated: 2018/12/03 17:23:03 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

int					validate_quotes(char *input)
{
	int		i;
	t_node	*stack;

	i = -1;
	stack = NULL;
	while (input[++i])
	{
		if (IS_QU(input[i]) && input[i] != '\\')
		{
			if (i > 0 && input[i - 1] == '\\')
				continue ;
			if (input[i] == peek(stack))
				pop(&stack);
			else
				push(&stack, input[i]);
		}
	}
	return (is_empty(stack));
}
