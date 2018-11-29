/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:12:54 by ale-goff          #+#    #+#             */
/*   Updated: 2018/11/28 19:20:40 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void				print_redirect_info(t_redirect *r)
{
	if (!r)
		return ;
	printf("-----------redirect---------\n");
	if (r->type == REDIRECT_LEFT)
		printf("<\n");
	else if (r->type == REDIRECT_RIGHT)
		printf(">\n");
	else if (r->type == REDIRECT_APPEND_RIGHT)
		printf(">>\n");
	else if (r->type == HEREDOC_DOC)
		printf("<<");
	else if (r->type == HEREDOC_STR)
		printf("<<<");
	printf("fd = %d\n", r->fd);
	printf("fd dest = %d\n", r->fd_dest);
	printf("close = %d\n", r->close);
	printf("path = %s\n", r->path);
}

void				print_assign_info(t_assign *s)
{
	t_assign			*traverse;

	traverse = s;
	printf("----------assign_info---------\n");
	while (traverse)
	{
		if (traverse->value)
			printf("value = %s\n", traverse->value);
		traverse = traverse->next;
	}
}
