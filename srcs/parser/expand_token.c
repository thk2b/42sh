/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeguing <pdeguing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 08:19:43 by pdeguing          #+#    #+#             */
/*   Updated: 2018/11/28 19:31:26 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

static int	get_lparam(char *str, int start)
{
	int		i;

	i = start;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i - start);
}

static char	*expand_str(char *str, char *param, int start, int lparam)
{
	char	*new;
	char	*expansion;
	char	*prefix;
	char	*suffix;

	expansion = ft_getenv(param);
	if (!expansion)
		expansion = get_local_var(param);
	if (!expansion)
		expansion = ft_strnew(0);
	else
		expansion = ft_strdup(expansion);
	ft_strdel(&param);
	if (start > 0)
	{
		prefix = ft_strsub(str, 0, start - 1);
		new = ft_strfjoin(prefix, expansion);
	}
	else
		new = expansion;
	suffix = ft_strsub(str, lparam + start, ft_strlen(str + lparam + start));
	new = ft_strfjoin(new, suffix);
	ft_strdel(&str);
	return (new);
}

static int	scan_str(char **str, int quote, int i, int l)
{
	int	len;

	while ((*str)[i])
	{
		if ((*str)[i] == '\'')
			quote = remove_squote(quote, *str + i, &i);
		else if ((*str)[i] == '\"')
			quote = remove_dquote(quote, *str + i, &i);
		else if ((*str)[i] == '\\')
			quote = remove_bslash(quote, *str + i, &i);
		else if (NOT_QUOTE && (*str)[i] == '$' && ft_isalnum((*str)[i + 1]))
		{
			l = get_lparam(*str, i + 1);
			*str = expand_str(*str, ft_strsub(*str, i + 1, l), i + 1, l);
		}
		else if (NOT_QUOTE && (*str)[i] == '`')
		{
			if ((len = exec_backticks(str, *str)) == -1)
				return (1);
			i += len;
		}
		else
			i++;
	}
	return (0);
}

char		*expand_param(char *str)
{
	if (scan_str(&str, 0, 0, 0))
		return (NULL);
	return (str);
}

void		token_expand(char **dst, char *str)
{
	char	*str_cpy;

	if (!str)
		return ;
	str_cpy = ft_strdup(str);
	if (*str_cpy == '~' && (*(str_cpy + 1) == '/' || !*(str_cpy + 1)))
		str_cpy = expand_str(str_cpy, ft_strdup("HOME"), 0, 1);
	*dst = expand_param(str_cpy);
	if (!(*dst))
		*dst = ft_strdup("");
}
