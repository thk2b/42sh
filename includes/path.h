/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 15:44:48 by acakste           #+#    #+#             */
/*   Updated: 2018/11/27 15:44:49 by acakste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

/*
**	hash_path.c
*/
int			create_path_map(void);
char		*get_cmd_path(char *key);
void		delete_path_map(void);

#endif