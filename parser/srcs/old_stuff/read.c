/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 17:54:05 by ale-goff          #+#    #+#             */
/*   Updated: 2018/11/18 13:31:48 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

char				*trip_join(const char *s1, const char c, const char *s2)
{
	char			*new;
	int				tmp;
	int				p;
	int				len1;
	int				len2;

	len1 = 0;
	len2 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	new = malloc(sizeof(char) * (len1 + len2 + 2));
	tmp = 0;
	p = 0;
	if (s1)
	{
		while (s1[tmp])
			new[p++] = s1[tmp++];
	}
	if (c)
		new[p++] = c;
	tmp = 0;
	if (s2)
	{
		while (s2[tmp])
			new[p++] = s2[tmp++];
	}
	new[p] = '\0';
	return (new);
}

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

void			print_list(t_list *lst)
{
	t_nodes			*node;
	int				index = 0;

	node = lst->head;
	while (node)
	{
		printf("[%d] %s\n", index++, node->content);
		node = node->next;
	}
}

t_nodes		*new_node(char *new_data)
{
	t_nodes		*node;

	node = (t_nodes *)malloc(sizeof(t_nodes));
	node->content = new_data;
	node->next = NULL;
	return (node);
}

t_list		*new_list(char *new_data)
{
	t_list		*lst;
	t_nodes		*node;

	node = new_node(new_data);
	lst = (t_list *)malloc(sizeof(t_list));
	lst->head = node;
	lst->tail = node;
	return (lst);
}

void		append(t_list **head_ref, char *new_data)
{
    t_nodes		*new;

	if (*head_ref == NULL)
	{
		*head_ref = new_list(new_data);
		return ;
	}
	new = new_node(new_data);
	(*head_ref)->tail->next = new;
	(*head_ref)->tail = new;
}

int		ft_strequ(char const *s1, char const *s2)
{
	if (!s1 || !s2)
		return (0);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (0);
		s1++;
		s2++;
	}
	return (1);
}

int		is_op(char *str)
{
	if (ft_strequ(str, "&")|| ft_strequ(str, "&&") || ft_strequ(str, "||") || ft_strequ(str, "|"))
		return (1);
	return (0);
}
void		check_errors(char *content, char *s)
{
	if (!content || !s)
			return ;
	if (is_op(content) && is_op(s))
	{
		printf("syntax eror\n");
		exit(1);
	}
}

void			pull_operator(t_list **head, char *s, int *tmp, int state)
{
	int				p;
	int				begin;
	char			*ptr;

	begin = *tmp;
	p = 2;
	while (s[*tmp] && state == classify_token(s[*tmp]) && p--)
	{
		*tmp += 1;	
	}
	ptr = ft_strdup_range(s, begin, *tmp - 1);
	if (is_op(ptr) && (!(*head)))
	{
		printf("ERROR\n");
		exit(1);
	}
	check_errors((*head)->tail->content, ptr);
	append(head, ptr);
}

int				pull_token(t_list **head, char *s, int *p)
{
	WOW();
	int				tmp;
	int				state;
	int				begin;
	int				status;
	char			*ptr;

	tmp = *p;
	state = classify_token(s[tmp]);
	begin = tmp;
	ptr = NULL;
	if (state == T_QUOTE)
	{
		tmp += 1;
		while (s[tmp] && classify_token(s[tmp]) != T_QUOTE)
			tmp += 1;
		if (!s[tmp])
		{
			status = SEEKING_END;
		}
		else
			status = END;
		if (status == END)
		{
			ptr = ft_strdup_range(s, begin, tmp++);
			check_errors((*head)->tail->content, ptr);
			append(head, ptr);
		}
	}
	else if (state == T_AND || state == T_OR || state == T_PIPE)
	{
		pull_operator(head, s, &tmp, state);
		status = SEEKING_END;
	}
	else
	{
		while (s[tmp] && state == classify_token(s[tmp]))
			tmp += 1;
		ptr = ft_strdup_range(s, begin, tmp - 1);
		if ((*head) && (*head)->tail)
			check_errors((*head)->tail->content, ptr);
		append(head, ptr);
		status = END;
	}
	*p = tmp;
	if (*head)
		print_list(*head);
	return (status);
}

void			free_append(char **s, char *end)
{
	char			*new;

	new = trip_join(*s, 0, end);
	free(*s);
	*s = new;
}

t_list			*parse(char *s)
{
	WOW();
	printf("%s\n", s);
	static char		*full = NULL;
	t_list			*args;
	int				token_completion;
	int				p;
	static int		end = 3;

	token_completion = 0;
	args = NULL;
	full = trip_join(full, 0, s);
	printf("line to parsed = %s\n", full);
	p = 0;
	while(full[p])
	{
		printf("%c\n", full[p]);
		if (is_space(full[p]))
			p = skip_whitespace(full, p);
		else
			token_completion = pull_token(&args, full, &p);
		printf("p = %d\n", p);
	}
	if (token_completion == SEEKING_END && end--)
	{
		free_append(&full, "\n");
		read_line();
		return (NULL);
	}
	printf("printing split arguments (tokens)\n\n");
	print_list(args);
	printf("\n\nfull lined that was parsed = %s\n", full);
	free(full);
	full = NULL;
	return (args);
}

void			read_line(void)
{
	char			*line;
	t_list			*args;

	line = NULL;
	write(1, "->", 2);
	get_next_line(0, &line);
	args = parse(line);	

}
/*
void			read_line(void)
{
	char			buffer[1024];
	int				p = 0;
	t_list			*args;

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
	args = parse(strdup(buffer));
}
*/
int				main(void)
{
	read_line();
	return (0);
}
