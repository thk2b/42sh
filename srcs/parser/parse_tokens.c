/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 10:18:05 by dmendelo          #+#    #+#             */
/*   Updated: 2018/11/20 11:14:40 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int					is_word(char *str)
{
	WOW();
		if (ft_strchr(str, '|') || ft_strchr(str, '&') || ft_strchr(str, '>') || ft_strchr(str, '<'))
		{
			return (0);
		}
		return (1);
}

void				print_redirect_info(t_redirect *r)
{
	WOW();
	if (!r)
		return ;
	printf("-----------redirect---------\n");
	if (r->type == REDIRECT_LEFT)
		printf("<\n");
	else if (r->type == REDIRECT_RIGHT)
		printf(">\n");
	else if (r->type == REDIRECT_APPEND_RIGHT)
		printf(">>\n");
	printf("fd = %d\n", r->fd);
	printf("path = %s\n", r->path);
}

void				print_assign_info(t_assign *s)
{
	WOW();
	t_assign			*traverse;

	traverse = s;
	printf("----------assign_info---------\n");
	while (traverse)
	{
		if (traverse->value)
			printf("value = %s\n", traverse->value);
		traverse = traverse->next;
	}
}

void				print_command_info(t_cmd *cmd)
{
	WOW();
	printf("---------------------------------------------\n");
	if (!cmd)
		return ;
	if (cmd->argv)
	{
		printf("------argv------\n");
		ft_putstrv(cmd->argv);
	}
	if (cmd->redirects)
	{
		print_redirect_info(cmd->redirects);
	}
	if (cmd->assign)
	{
		print_assign_info(cmd->assign);
	}
	printf("---------------------------------------------\n");
}

t_cmd					*init_command(void)
{
	t_cmd				*new;

	new = (t_cmd *)malloc(sizeof(*new));
	new->redirects = NULL;
	new->assign	= NULL;
	new->argv = NULL;
	new->return_status = 0;
	return (new);
}

int						is_reserved_word(char *s)
{
	if (!ft_strcmp(s, RESERVED_IF) || !ft_strcmp(s, RESERVED_THEN) ||
		!ft_strcmp(s, RESERVED_ELSE) || !ft_strcmp(s, RESERVED_ELIF) ||
		!ft_strcmp(s, RESERVED_FI) || !ft_strcmp(s, RESERVED_DO) ||
		!ft_strcmp(s, RESERVED_DONE) || !ft_strcmp(s, RESERVED_CASE) ||
		!ft_strcmp(s, RESERVED_ESAC) || !ft_strcmp(s, RESERVED_WHILE) ||
		!ft_strcmp(s, RESERVED_UNTIL) || !ft_strcmp(s, RESERVED_UNTIL) ||
		!ft_strcmp(s, RESERVED_FOR))
		return (1);
	return (0);
}

int						is_valid_name_char(char c)
{
	if (c == '_' ||  ft_isalnum(c) || c == '=' || c == '.')
	{
		return (1);
	}
	return (0);
}

int						is_assignment_word(char *s)
{
	WOW();
	int					p;
	int					assignment;

	assignment = 0;
	if (s && (s[0] == '=' || ft_isdigit(s[0])))
		return (0);
	p = 0;
	while (s[p])
	{
		if (!is_valid_name_char(s[p]))
			return (0);
		else if (s[p] == '=')
			assignment = 1;
		p += 1;
	}
	if (assignment)
		return (1);
	return (0);
}

void					push_back(t_assign **head, char *value)
{
	WOW();
	t_assign			*new;
	t_assign			*traverse;

	new = malloc(sizeof(*new));
	new->value = value;
	new->next = NULL;
	if (!(*head))
	{
		*head = new;
		return ;
	}
	traverse = *head;
	while (traverse && traverse->next)
	{
		traverse = traverse->next;
	}
	traverse->next = new;
}

int						pull_assignment(char *assignment, t_cmd **cmd)
{
	WOW();
	int					p;
	int					begin;

	p = 0;
	begin = 0;
	while (assignment[p] && assignment[p] != '=')
	{
		p += 1;
	}
	push_back(&(*cmd)->assign, ft_strdup_range(assignment, 0, p - 1));
	p += 1;
	begin = p;
	while (assignment[p])
	{
		p += 1;
	}
	if (p - begin)
	{
		push_back(&(*cmd)->assign, ft_strdup_range(assignment, begin, p));
	}
	return (0);
}

int						is_redirection(char *s)
{
	if (!ft_strcmp(s, ">") || !ft_strcmp(s, ">>") || !ft_strcmp(s, "<") ||
		!ft_strcmp(s, "<<") || !ft_strcmp(s, "|"))
	{
		return (1);
	}
	return (0);
}

int						is_number(char *s)
{
	WOW();
	int					p;

	p = 0;
	while (s[p])
	{
		if (!ft_isdigit(s[p]))
			return (0);
		p += 1;
	}
	return (1);
}

char					determine_redirection_type(char *o)
{
	WOW();
	if (!ft_strcmp(o, "<"))
		return (REDIRECT_LEFT);
	else if (!ft_strcmp(o, ">"))
		return (REDIRECT_RIGHT);
	else if (!ft_strcmp(o, ">>"))
		return (REDIRECT_APPEND_RIGHT);
	else
		return (0);
}

t_redirect				*new_redirection(char *operator_, int fd)
{
	WOW();
	char				type;
	t_redirect			*new;

	new = (t_redirect *)malloc(sizeof(*new));
	type = determine_redirection_type(operator_);
	new->type = type;
	new->fd = fd;
	new->path = NULL;
	new->next = NULL;
	return (new);
}

int						pull_redirection(t_nodes **node, t_nodes *prev, t_cmd **cmd)
{
	WOW();
	t_redirect			*redirection;
	int					fd;

	if (is_number(prev->content))
		fd = ft_atoi(prev->content);
	else
		fd = STDOUT;
	redirection = new_redirection((*node)->content, fd);
	if ((*node)->next)
	{
		redirection->path = (*node)->next->content;
		(*node) = (*node)->next;
	}
	(*cmd)->redirects = redirection;
	return (0);
}

int						get_ptr_len(char **s)
{
	WOW();
	int					p;

	if (!s)
		return (0);
	p = 0;
	while (s[p])
	{
		p += 1;
	}
	return (p);
}

void					free_2d(char **s)
{
	WOW();
	int					p;

	p = 0;
	while (s[p])
	{
		free(s[p]);
		p += 1;
	}
	free(s);
}

int						append_word_argv(char *word, t_cmd **cmd)
{
	WOW();
	char				**argv;
	int					len;
	int					p;

	if ((*cmd)->argv)
		len = get_ptr_len((*cmd)->argv);
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

t_cmd					*create_cmd(t_nodes **tokens)
{
	WOW();
	t_nodes				*traverse;
	t_cmd				*command;
	int					status;
	t_nodes				*prev;

	traverse = *tokens;
	command = init_command();
	status = 0;
	prev = NULL;
	while (traverse && !is_op(traverse->content))
	{
		printf("mid loop\n");
		printf("%s\n", traverse->content);
		if (is_op(traverse->content))
		{
				break ;
		}
		else if (is_reserved_word(traverse->content))
		{
			printf("1\n");
			//bonus reserved word sequences
		}
		else if (is_assignment_word(traverse->content))
		{
			printf("assignment word\n");
			status = pull_assignment(traverse->content, &command);	
		}
		else if (is_redirection(traverse->content))
		{
			printf("redirection\n");
			status = pull_redirection(&traverse, prev, &command);
		}
		else if (is_word(traverse->content))
		{
			printf("is word\n");
			status = append_word_argv(traverse->content, &command);
		}
		prev = traverse;
		traverse = traverse->next;
	}
	*tokens = traverse;
	return (command);
}
