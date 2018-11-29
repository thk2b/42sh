/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <dmendelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 10:18:05 by dmendelo          #+#    #+#             */
/*   Updated: 2018/11/28 18:33:16 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void					push_back(t_assign **head, char *value)
{
	t_assign			*new;
	t_assign			*traverse;

	new = malloc(sizeof(*new));
	new->value = ft_strdup(value); // We now copy the value here since token list is freed
	new->next = NULL;
	if (!(*head))
	{
		*head = new;
		return ;
	}
	traverse = *head;
	while (traverse && traverse->next)
		traverse = traverse->next;
	traverse->next = new;
}

int						pull_assignment(char *assignment, t_cmd **cmd)
{
	int					p;

	p = 0;
	if ((*cmd)->argv == NULL)
		push_back(&(*cmd)->assign, assignment);
	else
		append_word_argv(assignment, cmd);
	return (0);
}

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


int					is_aggregation(char *s1, t_nodes *prev)
{
	if (prev)
		if (!ft_strcmp(s1, "&") && !ft_strcmp(prev->content, ">"))
			return (1);
	return (0);
}

void					append_struct(t_nodes *traverse, t_nodes **tokens, t_cmd *command)
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
