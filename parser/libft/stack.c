/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 13:37:09 by ale-goff          #+#    #+#             */
/*   Updated: 2018/11/10 22:58:29 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack *init_stack(void)
{
    t_stack *stack = (t_stack *)malloc(sizeof(t_stack));
    stack->top = NULL;
    return (stack);
}

void    *pop(t_stack *stack)
{
    t_node *tmp = stack->top;
    void *content = NULL;
    if (stack->top)
    {
        content = stack->top->content;
        stack->top = tmp->next;
        free(tmp);
        tmp = NULL;
    }
    return (content);    
}


void push(t_stack *stack, void *content)
{
    t_node *node = (t_node *)malloc(sizeof(t_node));
    node->content = content;
    node->next = stack->top;
    stack->top = node;
    return ;
}

int is_empty(t_stack *stack)
{
    return (stack->top == NULL);
}

void *peek(t_stack *stack)
{
    return (stack->top ? stack->top->content : 0);
}
