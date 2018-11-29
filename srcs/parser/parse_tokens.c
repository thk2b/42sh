/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <dmendelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 10:18:05 by dmendelo          #+#    #+#             */
/*   Updated: 2018/11/28 18:54:33 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int						is_number(char *s)
{
	int					p;

	p = -1;
	while (s[++p])
		if (!ft_isdigit(s[p]))
			return (0);
	return (1);
}

int						append_word_argv(char *word, t_cmd **cmd)
{
	char				**argv;
	int					len;
	int					p;

	if ((*cmd)->argv)
		len = get_ptr_len((*cmd)->argv);
	else
		len = 0;
	argv = (char **)malloc(sizeof(*argv) * (len + 2));
	p = 0;
	while ((*cmd)->argv && (*cmd)->argv[p])
	{
		argv[p] = ft_strdup((*cmd)->argv[p]);
		p += 1;
	}
	argv[p++] = ft_strdup(word);
	argv[p] = NULL;
	if ((*cmd)->argv)
		free_2d((*cmd)->argv);
	(*cmd)->argv = argv;
	return (0);
}

void					append_struct(t_nodes *traverse,
						t_nodes **tokens, t_cmd *command)
{
	t_nodes *prev;
	int		aggreg;

	prev = NULL;
	aggreg = 0;
	while (traverse)
	{
		if (is_aggregation(traverse->content, prev))
			aggreg = 1;
		else if (is_op(traverse->content))
			break ;
		else if (is_assignment_word(traverse->content))
			pull_assignment(traverse->content, &command);
		else if (is_redirection(traverse->content))
			pull_redirection(&traverse, prev, &command);
		else if (is_word(traverse->content))
		{
			if (traverse->next && is_red(traverse->next->content) && aggreg)
				;
			else if (prev && ft_strequ(prev->content, "&") && aggreg)
				;
			else
				append_word_argv(traverse->content, &command);
		}
		prev = traverse;
		traverse = traverse->next;
	}
	*tokens = traverse;
}

t_cmd					*create_cmd(t_nodes **tokens)
{
	t_nodes				*traverse;
	t_cmd				*command;
	int					status;
	t_nodes				*prev;

	traverse = *tokens;
	command = init_command();
	status = 0;
	prev = NULL;
	if (traverse && is_op(traverse->content))
	{
		status = append_word_argv(traverse->content, &command);
		*tokens = traverse->next;
		return (command);
	}
	append_struct(traverse, tokens, command);
	print_redirect_info(command->redirects);
	ft_putstrv(command->argv);
	return (command);
}
