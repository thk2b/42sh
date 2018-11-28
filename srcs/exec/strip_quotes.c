// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   strip_quotes.c                                     :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2018/11/27 14:47:31 by tkobb             #+#    #+#             */
// /*   Updated: 2018/11/27 15:52:13 by tkobb            ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include <ft_sh.h>

// static int		strip_squote(int quote, char *str, int *i)
// {
// 	if (!(quote & (Q_BSLASH | Q_DQUOTE)))
// 	{
// 		ft_strcpy(str, str + 1);
// 		quote ^= Q_SQUOTE;
// 	}
// 	else
// 	{
// 		quote &= ~Q_BSLASH;
// 		*i = *i + 1;
// 	}
// 	return (quote);
// }

// static int		strip_dquote(int quote, char *str, int *i)
// {
// 	if (!(quote & (Q_BSLASH | Q_SQUOTE)))
// 	{
// 		ft_strcpy(str, str + 1);
// 		quote ^= Q_DQUOTE;
// 	}
// 	else
// 	{
// 		quote &= ~Q_BSLASH;
// 		*i = *i + 1;
// 	}
// 	return (quote);
// }

// static int		strip_bslash(int quote, char *str, int *i)
// {
// 	if ((!(quote & (Q_BSLASH | Q_SQUOTE))
// 				|| ((quote & Q_DQUOTE) && ft_strchr("\\\"\n", *str + 1))))
// 	{
// 		ft_strcpy(str, str + 1);
// 		quote |= Q_BSLASH;
// 	}
// 	else
// 	{
// 		quote &= ~Q_BSLASH;
// 		*i = *i + 1;
// 	}
// 	return (quote);
// }

// // static int		strip_str_quotes(char *str)
// int		strip_quotes(char *str)
// {
// 	int		i;
// 	int		quote;
// 	int		l;

// 	i = 0;
// 	quote = 0;
// 	l = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'')
// 			quote = strip_squote(quote, str + i, &i);
// 		else if (str[i] == '\"')
// 			quote = strip_dquote(quote, str + i, &i);
// 		else if (str[i] == '\\')
// 			quote = strip_bslash(quote, str + i, &i);
// 		else
// 			i++;
// 	}
// 	return (quote & Q_SQUOTE);
// }

// // int				strip_quotes(char **argv)
// // {
// // 	size_t	i;

// // 	i = 0;
// // 	while (argv[i])
// // 	{
// // 		strip_str_quotes(argv[i]);
// // 		i++;
// // 	}
// // 	return (0);
// // }
