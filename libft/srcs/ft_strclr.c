/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strclr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 09:57:51 by tkobb             #+#    #+#             */
/*   Updated: 2018/09/13 23:31:39 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_strclr(char *s)
{
	while (*s)
		*s++ = '\0';
}
