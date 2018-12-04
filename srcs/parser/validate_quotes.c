/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 17:22:00 by tkobb             #+#    #+#             */
/*   Updated: 2018/12/03 19:53:41 by ale-goff         ###   ########.fr       */
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
	while (input[++i])
	{
		if (input[i] == '`')
		{
			if (!(i > 0 && input[i - 1] == '\\' && IS_QU(input[i])))
				while (input[++i] != '`')
				{
					if (IS_QU(input[i]) && input[i] != '\\' && input[i] != '`')
						push(&stack, input[i]);
					else if (IS_QU(input[i]) && peek(stack) == input[i] &&
						input[i] != '`')
						pop(&stack);
				}
		}
	}
	empty = is_empty(stack) ? 1 : 0;
	free(stack);
	return (empty);
}
