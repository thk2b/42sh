/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back_ticks_comp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 11:58:16 by acakste           #+#    #+#             */
/*   Updated: 2018/12/01 11:58:17 by acakste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

char	*create_res_str(char *init_str, char *new_str)
{
	char	*first_tick;
	char	*end_tick;
	char	*full_res;

	if ((first_tick = ft_strchr(init_str, '`')) == NULL)
		return (NULL);
	if ((end_tick = ft_strchr(first_tick + 1, '`')) == NULL)
		return (NULL);
	full_res = ft_strreplace(init_str, first_tick,
						(end_tick + 1) - first_tick, new_str);
	return (full_res);
}

char	*build_str_from_pipe(int fd)
{
	char	*res;
	char	*tmp;
	char	*line;

	res = ft_strdup("");
	while (get_next_line((fd), &line) == 1)
	{
		if ((*res))
		{
			tmp = res;
			res = ft_strjoin(res, " ");
			free(tmp);
		}
		tmp = res;
		res = ft_strjoin(res, line);
		free(tmp);
		free(line);
	}
	return (res);
}

t_tree	*parse_backticks(char *input)
{
	t_token_lst	*arguments;
	t_tree		*ast;
	t_nodes		*traverse;

	if (check_input(input))
		return (NULL);
	arguments = split_args(input, 1);
	if (expand_tokens(&arguments, 1))
		return (NULL);
	traverse = arguments->head;
	ast = build_tree(traverse);
	if (arguments)
		free_list(arguments);
	return (ast);
}
