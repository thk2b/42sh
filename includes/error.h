/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 20:27:08 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/18 20:33:09 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# include <errno.h>
# include <string.h>
# include <ft_printf.h>

int		error(char *msg);
int		error_ret(char *msg, int ret);
void	*error_null(char *msg);

#endif
