/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 19:16:31 by tkobb             #+#    #+#             */
/*   Updated: 2018/11/20 11:33:57 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETLINE_H
# define GETLINE_H
# include <libft.h>
# include <stdlib.h>
# include <curses.h>
# include <termcap.h>

# define TERMCAPS_ENABLED	1
# define DEFAULT_PROMPT		"$> "

/*
**	line/ *.c
*/

# define LINE_BUFSIZE 48

struct				s_cursor
{
	unsigned int	start;
	unsigned int	end;
};

typedef struct		s_line
{
	char			*buf;
	unsigned int	bufsize;
	struct s_cursor	cursor;
}					t_line;

t_line				*line_new(void);
void				line_free(t_line *l);
int					line_resize(t_line *l);
int					line_append(t_line *l, char c);
int					line_delete(t_line *l);
int					line_move_left(t_line *l);
int					line_move_right(t_line *l);
char				*line_render(t_line *l);

/*
**	term.c
*/

int					term_init(void);
void				term_reset(void);
int					get_line(int fd, char **line, char *prompt);

/*
**	cursor.c
*/

# define DIR_UP		'A'
# define DIR_DOWN	'B'
# define DIR_RIGHT	'C'
# define DIR_LEFT	'D'

int					cursor_move(char dir);
int					cursor_putchar(char c);
int					cursor_delchar(void);

/*
**	handle_char.c
*/

int					handle_char(t_line *l, char c);
int					handle_escape(t_line *line);
int					handle_arrow(t_line *line, char c);
int					handle_backspace(t_line *line);

/*
**	termcaps_utils.c
*/

int					puttc(char *name);
// char				getchar(int fd);

#endif
