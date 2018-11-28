/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack2.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 13:37:30 by ale-goff          #+#    #+#             */
/*   Updated: 2018/11/27 20:38:01 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include "parser.h"

typedef struct s_node
{
	int				content;
    struct s_node  *next;
}               t_node;

typedef struct s_stack
{
    struct s_node *top;
}               t_stack;

t_stack *init_stack(void);
int			pop(t_stack *stack);
void		push(t_stack *stack, int content);
int			is_empty(t_stack *stack);
int			peek(t_stack *stack);

#endif
