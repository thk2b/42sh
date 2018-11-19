/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:10:15 by acakste           #+#    #+#             */
/*   Updated: 2018/11/18 19:10:16 by acakste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

t_table		g_op[NUM_OP] = {
	{T_CMD, exec_cmd}, {T_PIPE, exec_pipe}, {T_AND, exec_and},
	{T_OR, exec_or}, {T_SEMI, exec_semi}
};

int		exec_node(t_tree *tree, int use_current_process);
int		exec_semi(t_tree *tree, int use_current_process);
int		exec_pipe(t_tree *tree, int use_current_process);
int		exec_and(t_tree *tree, int use_current_process);
int		exec_or(t_tree *tree, int use_current_process);
int		exec_cmd(t_tree *tree);

