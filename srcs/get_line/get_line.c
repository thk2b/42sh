/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:25:02 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/20 11:44:05 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sh.h>
#include <libft.h>
#include <get_next_line.h>

static int	prompt(char *prompt_str)
{
	if (prompt_str)
	{
		ft_putstr(prompt_str);
		return (0);
	}
	// if ((prompt_str = get_local_var("PS1")) == NULL)
		// prompt_str = DEFAULT_PROMPT;
	ft_putstr(prompt_str);
	return (0);
}

static int	get_line_basic(int fd, char **line)
{
	return (get_next_line(fd, line) == 0);
}

static int	get_line_edit(int fd, char **linep)
{
	t_line	*line;
	ssize_t	nr;
	char	c;
	int		ret;

	MCK(line = line_new(), 1);
	while ((nr = read(fd, &c, 1)) == 1)
	{
		ret = handle_char(line, c);
		if (ret == -1)
			break ;
		else if (ret)
			return (1);
	}
	if (nr == -1)
		return (error("read"));
	MCK(*linep = line_render(line), 1);
	return (0);
}

int		get_line(int fd, char **line, char *prompt_str)
{
	prompt(prompt_str);
	if (TERMCAPS_ENABLED)
		return (get_line_edit(fd, line));
	return (get_line_basic(fd, line));
}

int main(void)
{
	char *line;
	term_init();
	while (get_line(0, &line, ">") == 0)
	{
		printf(">>%s\n", line);
		free(line);
	}
}
