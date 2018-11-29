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
# include <local_var.h>
# include <ft_sh.h>

/*
**	hash_path.c
*/
int			store_cmd_path(char *key, char *value);
t_var		*find_path_lst(char *key);
char		*path_search(char *exec_name, char *exists);

/*
**	hash_path_comp.c
*/
char		*get_cmd_path(char *key);
void		delete_path_map(void);
int			create_path_map(void);
t_var		*create_path_elem(char *key, char *value);

#endif
