/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 15:38:22 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/23 15:40:45 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>
#include <env.h>
#include <libft.h>

static void	replace(char **dst, char *s)
{
	if (s == NULL)
		return ;
	free(*dst);
	*dst = s;
}

char	*ft_strreplace(char *s, char *start, size_t r_len, char *by)
{
	size_t	s_len;
	size_t	e_len;
	size_t	by_len;
	size_t	n_len;
	char	*n;

	s_len = start - s;
	e_len = ft_strlen(s) - r_len - s_len;
	by_len = ft_strlen(by);
	n_len = s_len + by_len + e_len;
	MCK(n = (char*)malloc(sizeof(char) * (n_len + 1)), NULL);
	n[n_len] = '\0';
	ft_strncpy(n, s, s_len);
	ft_strcpy(n + s_len, by);
	ft_strcpy(n + s_len + by_len, start + r_len);
	return (n);
}

static char	*expand_tilde(char *str)
{
	char	*home_str;

	if ((home_str = ft_getenv("HOME")) == NULL)
		return (ft_strdup("")); // use local variable? store HOME var?
	return (ft_strreplace(str, str, 1, home_str));
}

static char	*find_var_name_end(char *str)
{
	while (*str && ft_isalpha(*str))
		str++;
	return (str);
}

static char	*expand_var(char *str)
{
	char	*start;
	char	*next;
	char	*value;
	size_t	len;
	char	tmp;

	if ((start = ft_strchr(str, '$')) == NULL)
		return (NULL);
	next = find_var_name_end(start + 1);
	len = next ? next - start : ft_strlen(start + 1);
	tmp = str[len];
	str[len] = '\0';
	value = ft_getenv(start + 1);
	if (value == NULL)
		value = get_local_var(start + 1);
	str[len] = tmp;
	if (value == NULL)
		return (ft_strreplace(str, start, len, ""));
	return (ft_strreplace(str, start, len, value));
}

// static int	strip_quotes(char *str)
// {
// 	int		is_single_quote;
// 	size_t	len;

// 	if (ft_strchr("\"'", *str) == NULL)
// 		return (0);
// 	is_single_quote = *str == '\'';
// 	len = ft_strlen(str);
// 	ft_memmove(str, str + 1, len - 1);
// 	str[len - 2] = '\0';
// 	return (is_single_quote);
// }

int			expand_str(char **dst, char *str)
{
	char	*expanded;

	*dst = str;
	// ft_printf("str is %s\n", str);
	if (exec_backticks(dst, str))
		return (0);
	// if (strip_quotes(str))
		// return (0);
	if (*dst[0] == '~' && *dst[1] != '~')
		replace(dst, expand_tilde(*dst));
	while ((expanded = expand_var(*dst)))
		replace(dst, expanded);
	return (0);
}
