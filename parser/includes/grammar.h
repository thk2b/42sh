/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 18:42:04 by dmendelo          #+#    #+#             */
/*   Updated: 2018/11/18 18:58:08 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAMMAR_H
# define GRAMMAR_H

typedef struct			s_t_node
{
	char				*content;
	int					type;
	struct s_t_node		*next;
}						t_t_node;

typedef struct			s_token_list
{
	struct s_t_node		*head;
	struct s_t_node		*tail;
}						t_token_list;

#endif
