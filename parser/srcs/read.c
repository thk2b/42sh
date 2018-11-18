/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 17:54:05 by ale-goff          #+#    #+#             */
/*   Updated: 2018/11/17 18:52:40 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <strings.h>
#include <string.h>

# define REDIRECT_LEFT			1
# define REDIRECT_RIGHT			2
# define REDIRECT_APPEND_RIGHT	3

typedef struct					s_redirect
{
	char						type;
	int							fd;
	char						*path;
	struct s_redirect			*next;
}								t_redirect;

# define T_CMD					1
# define T_PIPE					2
# define T_AND					3
# define T_OR					4
# define T_SEMI					5
# define T_ALPHANUM				6
# define T_QUOTE				7
# define T_BRACKET				8
# define T_PAREN				9
# define T_BACKTICK				10
# define T_SPACE				11

typedef struct					s_list
{
	char						*content;
	struct s_list				*next;
}								t_list;

typedef struct					s_tree
{
	char						type;
	struct s_tree				*left;
	struct s_tree				*right;
	struct s_list				*args;
	//	struct s_cmd				*data;
}								t_tree;

typedef struct					s_cmd
{
	t_redirect					*redirects;
	char						**argv;
	int							return_status;
}								t_cmd;

int				is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int				skip_whitespace(char *s, int p)
{
	while (s[p] && is_space(s[p]))
		p += 1;
	return (p);
}

int				is_alpha_numeric(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}

int				is_and_operator(char c)
{
	if (c == '&')
		return (1);
	return (0);
}

int				is_pipe_operator(char c)
{
	if (c == '|')
		return (1);
	return (0);
}

int				is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

int				is_bracket(char c)
{
	if (c == '[' || c == ']')
		return (1);
	return (0);
}

int				is_paren(char c)
{
	if (c == '(' || c == ')')
		return (1);
	return (0);
}

char				*ft_strdup_range(const char *str, int begin, int end)
{
	char			*duplicate;
	int				dp;
	int				sp;

	if (begin > end)
		return (NULL);
	duplicate = malloc(sizeof(char) * (end - begin + 2));
	sp = begin;
	dp = 0;
	while (sp <= end)
	{
		duplicate[dp] = str[sp];
		dp += 1;
		sp += 1;
	}
	duplicate[dp] = '\0';
	return (duplicate);
}
int				classify_token(char c)
{
	if (is_alpha_numeric(c))
		return (T_ALPHANUM);
	else if (is_and_operator(c))
		return (T_AND);
	else if (is_pipe_operator(c))
		return (T_PIPE);
	else if (c == ';')
		return (T_SEMI);
	else if (is_quote(c))
		return (T_QUOTE);
	else if (is_bracket(c))
		return (T_BRACKET);
	else if (is_paren(c))
		return (T_PAREN);
	else if (c == '`')
		return (T_BACKTICK);
	else if (is_space(c))
		return (T_SPACE);
	else
		return (0);
}

void			print_list(t_list *head)
{
	t_list			*traverse;

	traverse = head;
	while (traverse)
	{
		printf("%s\n", traverse->content);
		traverse = traverse->next;
	}
}

void			push(t_list **head, char *content)
{
	t_list			*new;

	new = malloc(sizeof(*new));
	new->content = content;
	if (!(*head))
	{
		new->next = NULL;
	}
	else
	{
		new->next = *head;
	}
	*head = new;
}

void			pull_token(t_list **head, char *s, int *p)
{
	int				tmp;
	int				state;
	int				begin;

	tmp = *p;
	state = classify_token(s[tmp]);
	begin = tmp;	
	if (state == T_QUOTE)
	{
		tmp += 1;
		while (s[tmp] && classify_token(s[tmp]) != T_QUOTE)
			tmp += 1;
		push(head, ft_strdup_range(s, begin, tmp++));
	}
	else
	{
		while (s[tmp] && state == classify_token(s[tmp]))
			tmp += 1;
		push(head, ft_strdup_range(s, begin, tmp - 1));
	}
	*p = tmp;
}

void			parse(char *s)
{
	printf("%s\n", s);
	t_list			*args;

	args = NULL;
	for (int p = 0; s[p]; p += 1)
	{
		if (is_space(s[p]))
			p = skip_whitespace(s, p);
		else
			pull_token(&args, s, &p);
	}
	print_list(args);
}

void			read_line(void)
{
	char			buffer[1024];
	int				p = 0;

	bzero(buffer, 1024);
	write(1, "->", 2);
	while (read(0, &buffer[p], 1))
	{
		if (buffer[p] == '\n')
		{
			buffer[p] = '\0';
			break ;
		}
		p += 1;
	}
	parse(strdup(buffer));
}

int				main(void)
{
	read_line();
	return (0);
}
