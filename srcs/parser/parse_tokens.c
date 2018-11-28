/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <dmendelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 10:18:05 by dmendelo          #+#    #+#             */
/*   Updated: 2018/11/28 13:45:15 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int					is_word(char *str)
{
	if (ft_strchr(str, '|') || ft_strchr(str, '&') ||
		ft_strchr(str, '>') || ft_strchr(str, '<'))
		return (0);
	return (1);
}

void				print_redirect_info(t_redirect *r)
{
	if (!r)
		return ;
	printf("-----------redirect---------\n");
	if (r->type == REDIRECT_LEFT)
		printf("<\n");
	else if (r->type == REDIRECT_RIGHT)
		printf(">\n");
	else if (r->type == REDIRECT_APPEND_RIGHT)
		printf(">>\n");
	else if (r->type == HEREDOC_DOC)
		printf("<<");
	else if (r->type == HEREDOC_STR)
		printf("<<<");
	printf("fd = %d\n", r->fd);
	printf("fd dest = %d\n", r->fd_dest);
	printf("path = %s\n", r->path);
}

void				print_assign_info(t_assign *s)
{
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
/*
 void				print_command_info(t_cmd *cmd)
 {
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
*/
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
	return (c == '_' || ft_isalnum(c) || c == '=' || c == '.');
}

int						is_assignment_word(char *s)
{
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
	int					begin;

	p = 0;
	begin = 0;
	if ((*cmd)->argv == NULL)
		push_back(&(*cmd)->assign, assignment);
	else
		append_word_argv(assignment, cmd);
	return (0);
}

int						is_redirection(char *s)
{
	if (!ft_strcmp(s, ">") || !ft_strcmp(s, ">>") || !ft_strcmp(s, "<") ||
		!ft_strcmp(s, "<<") || !ft_strcmp(s, "|") || !ft_strcmp(s, "<<<"))
		return (1);
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

char					determine_redirection_type(char *o)
{
	if (!ft_strcmp(o, "<"))
		return (REDIRECT_LEFT);
	else if (!ft_strcmp(o, ">"))
		return (REDIRECT_RIGHT);
	else if (!ft_strcmp(o, ">>"))
		return (REDIRECT_APPEND_RIGHT);
	else if (!ft_strcmp(o, "<<"))
		return (HEREDOC_DOC);
	else if (!ft_strcmp(o, "<<<"))
		return (HEREDOC_STR);
	else
		return (0);
}

t_redirect				*new_redirection(char *operator_, int fd, int fd_dest)
{
	char				type;
	t_redirect			*new;

	new = (t_redirect *)malloc(sizeof(*new));
	type = determine_redirection_type(operator_);
	new->type = type;
	new->fd = fd;
	new->fd_dest = fd_dest;
	new->path = NULL;
	new->next = NULL;
	return (new);
}

void					push_back_test(t_redirect **redir, t_redirect *redirect)
{
	t_redirect *head;

	if (!(*redir))
	{
		*redir = redirect;
		return ;
	}
	head = *redir;
	while (head->next != NULL)
		head = head->next;
	head->next = redirect;
}

t_redirect				*pull_aggregation(t_nodes **node, t_nodes *prev,
						t_cmd **cmd, int fd)
{
	t_redirect *aggreg;
	int			fd_dest;

	(void)prev;
	(void)cmd;
	fd_dest = 0;
	aggreg = NULL;
	if ((*node)->next->next && (*node)->next->next->content)
		if (is_number((*node)->next->next->content))
			fd_dest = ft_atoi((*node)->next->next->content);
	aggreg = new_redirection((*node)->content, fd, fd_dest);
	aggreg->path = NULL;
	return (aggreg);
}

int						pull_redirection(t_nodes **node, t_nodes *prev, t_cmd **cmd)
{
	t_redirect			*redirection;
	int					fd;

	redirection = NULL;
	if (prev && prev->content && is_number(prev->content))
		fd = ft_atoi(prev->content);
	else
		fd = STDOUT;
	if (ft_strequ((*node)->next->content, "&"))
	{
		redirection = pull_aggregation(node, prev, cmd, fd);
	}
	else if ((*node)->next)
	{
		redirection = new_redirection((*node)->content, fd, 0);
		// if (is_op((*node)->next->content))
		// 	printf("SALUT\n");
		redirection->path = ft_strdup((*node)->next->content); // We now copy the value here since token list is freed
		(*node) = (*node)->next;
	}
	push_back_test(&(*cmd)->redirects, redirection);
	return (0);
}

int						get_ptr_len(char **s)
{
	int					p;

	if (!s)
		return (0);
	p = 0;
	while (s[p])
		p++;
	return (p);
}

void					free_2d(char **s)
{
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
	// ft_putstrv((*cmd)->argv);
	return (0);
}

void					append_struct(t_nodes *traverse, t_nodes **tokens, t_cmd *command)
{
	t_nodes *prev;

	prev = NULL;
	while (traverse)
	{
		if (is_op(traverse->content))
			break ;
		else if (is_assignment_word(traverse->content))
			pull_assignment(traverse->content, &command);
		else if (is_redirection(traverse->content))
			pull_redirection(&traverse, prev, &command);
		else if (is_word(traverse->content))
			append_word_argv(traverse->content, &command);
		prev = traverse;
		traverse = traverse->next;
	}
	// print_redirect_info(command->redirects);
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
	// print_redirect_info((command)->redirects);
	ft_putstrv(command->argv);
	return (command);
}
