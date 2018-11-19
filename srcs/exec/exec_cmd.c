/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 06:14:19 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/19 06:14:31 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

int		exec_cmd(t_tree *tree)
{
	if (tree->cmd->assign)
		//do all the assignments
	if (tree->cmd->redirects)
		//do all the redirects
	//search_simple_cmd();
}
