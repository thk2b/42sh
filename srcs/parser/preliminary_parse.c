/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preliminary_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 13:34:40 by ale-goff          #+#    #+#             */
/*   Updated: 2018/12/02 18:38:24 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int					interpret_token(t_token_lst **head, const char *input,
									int *p, int errors)
{
	int					tmp;
	static t_token		info;

	init_token_info(&info);
	tmp = *p;
	info.type = classify_token(input[tmp]);
	if (info.type == T_COMMENT)
	{
		info.status = skip_to_end_of_line(input, &tmp);
	}
	else if (info.type == T_AND || info.type == T_PIPE ||  info.type == T_SEMI)
	{
		if ((info.status = pull_operator(head, input, &tmp, errors)) == -1)
			return (-1);
	}
	else
	{
		if ((info.status = pull_token(head, input, &tmp, errors)) == -1)
			return (-1);
	}
	*p = tmp;
	return (info.status);
}

t_token_lst			*interpret_input(const char *input,
					int *token_completion, int errors)
{
	int					p;
	t_token_lst			*arguments;

	p = 0;
	arguments = NULL;
	while (input[p])
	{
		if (IS_SPACE(input[p]))
			p = skip_whitespace(input, p);
		else
			*token_completion = interpret_token(&arguments, input, &p, errors);
		if (*token_completion == -1)
			return (NULL);
	}
	if (*token_completion == SEEKING_END)
	{
		if (arguments)
			free_list(arguments);
		arguments = NULL;
	}
	return (arguments);
}

t_token_lst			*split_args(char *input, int activate_errors)
{
	t_token_lst			*arguments;
	int					token_completion;

	arguments = interpret_input(input, &token_completion, activate_errors);
	return (arguments);
}

void				remove_back_slash(char *input)
{
	int			i;

	i = 0;
	while (input[i])
	{
		if (i > 0 && input[i - 1] == '\\' && input[i] == '\n')
		{
			ft_memmove(input + i, input + i + 1, ft_strlen(input) - i);
			return ;
		}
		i++;
	}
}

t_tree				*parse(char *input)
{
	t_token_lst			*arguments;
	t_nodes				*traverse;
	t_tree				*ast;

	remove_back_slash(input);
	if (check_input(input))
		return (NULL);
	arguments = split_args(input, 1);
	if (arguments == NULL)
		return (NULL);
	if (expand_tokens(&arguments, 1))
		return (NULL);
	traverse = arguments->head;
	ast = build_tree(traverse);
	if (arguments)
		free_list(arguments);
	return (ast);
}
