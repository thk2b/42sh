/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clist.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 22:08:37 by tkobb             #+#    #+#             */
/*   Updated: 2018/12/03 20:08:46 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIST_H
# define CLIST_H
# include <libft.h>

typedef struct	s_clist
{
	struct s_clist	*prev;
	struct s_clist	*next;
	void			*data;
}				t_clist;

typedef void	(*t_clist_del_fn)(void *);
typedef int		(*t_clist_cmp_fn)(void *, void *);

t_clist			*clist_new(void *data);
void			clist_free(t_clist *cl, t_clist_del_fn del);
int				clist_push(t_clist **cl, void *data);
void			*clist_pop(t_clist **cl);
int				clist_rotate(t_clist **cl);
int				clist_rrotate(t_clist **cl);
int				clist_swap_next(t_clist **cl);
int				clist_is_sorted(t_clist *clist, t_clist_cmp_fn cmp);
void			*clist_find(t_clist *clist, void *ctx, t_clist_cmp_fn cmp);

#endif
