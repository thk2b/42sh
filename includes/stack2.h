/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack2.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 13:37:30 by ale-goff          #+#    #+#             */
/*   Updated: 2018/11/27 21:23:00 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK2_H
# define STACK2_H
# include <stdlib.h>

typedef struct	s_node
{
	int				content;
	struct s_node	*next;
}				t_node;

int				pop(t_node **top);
void			push(t_node **top, int content);
int				is_empty(t_node *top);
int				peek(t_node *top);

#endif
