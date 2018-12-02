/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <dmendelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 10:18:05 by dmendelo          #+#    #+#             */
/*   Updated: 2018/12/01 20:14:36 by ale-goff         ###   ########.fr       */
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

static void				handle_word(t_nodes *traverse, int aggreg, t_cmd **command)
{
	if (aggreg)
		;
	else
		append_word_argv(traverse->content, command);
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
		if (traverse->next && traverse->next->next &&
			is_aggregation(traverse->content,traverse->next->content,
			traverse->next->next->content))
			aggreg = 1;
		if (traverse->type == T_CMD)
			handle_word(traverse, aggreg, &command);
		else if (traverse->type > T_CMD && traverse->type < T_RED)
			break ;
		else if (traverse->type == T_ASS)
			pull_assignment(traverse->content, &command);
		else if (traverse->type == T_RED)
			pull_redirection(&traverse, prev, &command);
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
	if (traverse && traverse->type > T_CMD && traverse->type <= T_SEMI) //is_op(traverse->content))
	{
		status = append_word_argv(traverse->content, &command);
		*tokens = traverse->next;
		return (command);
	}
	append_struct(traverse, tokens, command);
	print_redirect_info(command->redirects);
	return (command);
}
