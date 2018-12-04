/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 12:07:35 by acakste           #+#    #+#             */
/*   Updated: 2018/12/03 20:23:31 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>

void	free_assignments(t_assign *lst)
{
	t_assign	*cur;
	t_assign	*tmp;

	cur = lst;
	while (cur)
	{
		ft_strdel(&cur->value);
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
}

void	free_redirects(t_redirect *lst)
{
	t_redirect	*cur;
	t_redirect	*next;

	cur = lst;
	while (cur)
	{
		ft_strdel(&cur->path);
		next = cur->next;
		free(cur);
		cur = next;
	}
}

void	free_tree(t_tree *root)
{
	int			i;

	if (!root)
		return ;
	free_tree(root->left);
	free_tree(root->right);
	if (root->data)
	{
		if (root->data->argv)
		{
			i = 0;
			while (root->data->argv[i])
			{
				free(root->data->argv[i]);
				i++;
			}
		}
		free(root->data->argv);
		free_assignments(root->data->assign);
		free_redirects(root->data->redirects);
		free(root->data);
	}
	free(root);
}
