/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 17:22:00 by tkobb             #+#    #+#             */
/*   Updated: 2018/12/03 19:16:01 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

int					validate_quotes(char *input)
{
	int		i;
	t_node	*stack;
	int		empty;

	i = -1;
	stack = NULL;
	empty = 0;
	while (input[++i])
	{
		if (input[i] == '`')
		{
			if (i > 0 && input[i - 1] == '\\')
				continue ;
			else
				while (input[i] != '`')
				{
					if (IS_QU(input[i]) && input[i] != '\\' && input[i] != '`')
						push(&stack, input[i]);
					else if (IS_QU(input[i]) && peek(stack) == input[i])
						pop(&stack);
				}
		}
	}
	if (is_empty(stack))
		empty = 1;
	free(stack);
	return (empty);
}
