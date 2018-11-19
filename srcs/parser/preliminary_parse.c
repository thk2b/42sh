/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preliminary_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 13:34:40 by ale-goff          #+#    #+#             */
/*   Updated: 2018/11/19 14:36:12 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int				is_alpha_numeric(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c == '-')
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

void	free_list(t_list *head)
{
	t_nodes	*tmp;
	t_nodes *free_;

	tmp = head->head;
	while (tmp)
	{
		free_ = tmp;
		free(tmp->content);
		tmp = tmp->next;
		free(free_);
	}
	free(head);
	head = NULL;
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
		while (s1[tmp])
			new[p++] = s1[tmp++];
	if (c)
		new[p++] = c;
	tmp = 0;
	if (s2)
		while (s2[tmp])
			new[p++] = s2[tmp++];
	new[p] = '\0';
	return (new);
}

void			free_append(char **s, char *end)
{
	char			*new;

	new = trip_join(*s, 0, end);
	free(*s);
	*s = new;
}

int					skip_whitespace(const char *input, int p)
{
	while (input[p] && IS_SPACE(input[p]))
	{
		p += 1;
	}
	return (p);
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
	else if (IS_SPACE(c))
		return (T_SPACE);
	else if (c == '#')
		return (T_COMMENT);
	else
		return (0);
}

void				init_token_info(t_token *info)
{
	info->content = NULL;
	info->status = 0;
	info->type = 0;
}

int					pull_quote_content(t_list **head, const char *input, int *p)
{
	WOW();
	int					tmp;
	char				*content;

	tmp = *p;
	tmp += 1;
	while (input[tmp] && classify_token(input[tmp]) != T_QUOTE)
	{
		tmp += 1;
	}
	if (!input[tmp])
	{
		printf("seeking_end\n");
		*p = tmp;
		return (SEEKING_END);
	}
	content = ft_strdup_range(input, *p, tmp++);
	*p = tmp;
	if (*head && (*head)->tail)
		check_errors((*head)->tail->content, content);
	append(head, content);
	return (END);
}

int					pull_operator(t_list **head, const char *input, int *p)
{
	WOW();
	int					tmp;
	int					type;
	int					op_max;
	char				*content;
	
	tmp = *p;
	type = classify_token(input[tmp]);
	op_max = 2;
	while (input[tmp] && type == classify_token(input[tmp]) && op_max--)
		tmp += 1;
	content = ft_strdup_range(input, *p, tmp - 1);
	if (is_op(content) && (!(*head)))
	{
		printf("syntax error\n");
		exit(1);
	}
	check_errors((*head)->tail->content, content);
	append(head, content);
	*p = tmp;
	return (SEEKING_END);
}

int					pull_token(t_list **head, const char *input, int *p)
{
	WOW();
	int					tmp;
	int					type;
	char				*content;

	tmp = *p;
	type = classify_token(input[tmp]);
	while (input[tmp] && type == classify_token(input[tmp]))
		tmp += 1;
	content = ft_strdup_range(input, *p, tmp - 1);
	if ((*head) && (*head)->tail)
		check_errors((*head)->tail->content, content);
	append(head, content);
	*p = tmp;
	return (END);
}

int					skip_to_end_of_line(const char *input, int *p, t_list **head)
{
	while (input[*p] && input[*p] != '\n')
	{
		*p += 1;
	}
	if (is_op((*head)->tail->content))
	{
		return (SEEKING_END);
	}
	return (END);
}

int					interpret_token(t_list **head, const char *input, int *p)
{
	int					tmp;
	static t_token		info;
//	int					begin;

	init_token_info(&info);
	tmp = *p;
	info.type = classify_token(input[tmp]);
	if (info.type == T_COMMENT)
	{
		info.status = skip_to_end_of_line(input, &tmp, head);//do something here
	}
	else if (info.type == T_QUOTE)
	{
		info.status = pull_quote_content(head, input, &tmp);
	}
	else if (info.type == T_AND || info.type == T_PIPE)
	{
		info.status = pull_operator(head, input, &tmp);
	}
	else
	{
		info.status = pull_token(head, input, &tmp);
	}
	*p = tmp;
	return (info.status);
}

t_list				*interpret_input(const char *input, int *token_completion)
{
	WOW();
	int					p;
	t_list				*arguments;

	printf("-------------------------\nto be interpreted -> %s\n---------------------\n", input);
	p = 0;
	arguments = NULL;
	while (input[p])
	{
		printf("p = %d\n", p);
		printf("%s\n", input);
		printf("%*c\n", (int)strlen(input), input[p]);
		if (IS_SPACE(input[p]))
			p = skip_whitespace(input, p);
		else
			*token_completion = interpret_token(&arguments, input, &p);
	}
	if (*token_completion == SEEKING_END)
	{
		free_list(arguments);
		arguments = NULL;
	}
	return (arguments);
}

t_list				*split_args(void)
{
	WOW();
	static char			*input = NULL;
	char				*line;
	t_list				*arguments;
	int					token_completion;

	line = NULL;
	write(1, "->", 2);
	get_next_line(0, &line);
	free_append(&input, line);
	arguments = interpret_input(input, &token_completion);

	if (arguments)
		print_list(arguments);
	if (token_completion == SEEKING_END)
	{
		free_append(&input, "\n");
		free(line);
		printf("--------------------------------\n");
		return (split_args());
	}
	free(input);
	input = NULL;
	free(line);
	return (arguments);
}

t_tree				*parse(void)
{
	WOW();
	t_list				*arguments;
		
	arguments = split_args();
	while (arguments)
	{
		print_command_info(create_cmd(&arguments));
	}
	if (arguments)
		free_list(arguments);
	return (NULL);
}

int					main(void)
{
	parse();
	return (0);
}
