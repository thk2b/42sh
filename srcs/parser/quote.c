/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 19:24:14 by ale-goff          #+#    #+#             */
/*   Updated: 2018/11/28 19:37:04 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <ft_sh.h>

int			remove_squote(int quote, char *str, int *i)
{
	if (!(quote & (Q_BSLASH | Q_DQUOTE)))
	{
		ft_strcpy(str, str + 1);
		quote ^= Q_SQUOTE;
	}
	else
	{
		quote &= ~Q_BSLASH;
		*i = *i + 1;
	}
	return (quote);
}

int			remove_dquote(int quote, char *str, int *i)
{
	if (!(quote & (Q_BSLASH | Q_SQUOTE)))
	{
		ft_strcpy(str, str + 1);
		quote ^= Q_DQUOTE;
	}
	else
	{
		quote &= ~Q_BSLASH;
		*i = *i + 1;
	}
	return (quote);
}

int			remove_bslash(int quote, char *str, int *i)
{
	if ((!(quote & (Q_BSLASH | Q_SQUOTE))
				|| ((quote & Q_DQUOTE) && ft_strchr("\\\"\n", *str + 1))))
	{
		ft_strcpy(str, str + 1);
		quote |= Q_BSLASH;
	}
	else
	{
		quote &= ~Q_BSLASH;
		*i = *i + 1;
	}
	return (quote);
}
