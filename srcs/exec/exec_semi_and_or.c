/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_semi_and_or.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:19:45 by acakste           #+#    #+#             */
/*   Updated: 2018/11/28 18:19:46 by acakste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

int			exec_and(t_tree *tree, int use_current_process)
{
	int return_status[2];

	(void)use_current_process;
	return_status[0] = exec_node(tree->left, 0);
	if (return_status[0] != 0)
		return (return_status[0]);
	return_status[1] = exec_node(tree->right, 0);
	return (return_status[1]);
}

int			exec_or(t_tree *tree, int use_current_process)
{
	int return_status[2];

	(void)use_current_process;
	return_status[0] = exec_node(tree->left, 0);
	if (return_status[0] == 0)
		return (return_status[0]);
	return_status[1] = exec_node(tree->right, 0);
	return (return_status[1]);
}

int			exec_semi(t_tree *tree, int use_current_process)
{
	int return_status[2];

	(void)use_current_process;
	return_status[0] = exec_node(tree->left, 0);
	return_status[1] = exec_node(tree->right, 0);
	return (return_status[1]);
}
