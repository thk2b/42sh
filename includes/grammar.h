/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 18:42:04 by dmendelo          #+#    #+#             */
/*   Updated: 2018/11/19 10:46:36 by dmendelo         ###   ########.fr       */
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

# define WORD 1
# define ASSIGNMENT_WORD 2
# define OPERATOR 3
# define NAME 4
# define NEWLINE 5
# define IO_NUMBER 6

# define RESERVED_IF "if"
# define RESERVED_THEN "then"
# define RESERVED_ELSE "else"
# define RESERVED_ELIF "elif"
# define RESERVED_FI "fi"
# define RESERVED_DO "do"
# define RESERVED_DONE "done"
# define RESERVED_CASE "case"
# define RESERVED_ESAC "esac"
# define RESERVED_WHILE "while"
# define RESERVED_UNTIL "until"
# define RESERVED_FOR "for"

t_cmd				*create_cmd(t_list **lst);

		

#endif
