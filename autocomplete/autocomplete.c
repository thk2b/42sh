/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:28:33 by dmendelo          #+#    #+#             */
/*   Updated: 2018/11/26 20:04:32 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <limits.h>

# define WOW() printf("->%s\n", __func__)

# define ARG 0
# define EXE 1
# define MAXPATHLEN 4096

extern char		**environ;

typedef struct	s_list
{
	char			*name;
	struct s_list	*next;
}				t_list;

void			print_strings(char **strings, int p)
{
	if (!strings)
		return ;
	if (strings[p])
	{
		printf("%s\n", strings[p]);
	}
	if (strings[p + 1])
	{
		print_strings(strings, p + 1);
	}
}

char		*replace_char(char *s, int old, int new)
{
	WOW();
	char			*ret;
	int				p;

	ret = strdup(s);
	p = 0;
	while (s[p])
	{
		if (s[p] == old)
		{
			ret[p] = new;
		}
		p += 1;
	}
	return (ret);
}

char			*ft_strdup_range(const char *str, int begin, int end)
{
	WOW();
	int				p;
	char			*dup;
	int				dp;

	if (begin > end)
		return (NULL);
	p = begin;
	dup = malloc(sizeof(char) * (end - begin + 2));
	bzero(dup, end - begin + 2);
	dp = 0;
	while (p <= end)
	{
		dup[dp] = str[p];
		dp += 1;
		p += 1;
	}
	printf("dup = %s\n", dup);
	return (dup);
}

int				skip_whitespaces(char *s, int p)
{
	while (s[p] && (s[p] == ' ' || s[p] == '\t'))
	{
		p += 1;
	}
	return (p);
}

int				count_words(char *s)
{
	WOW();
	int				p;
	int				count;

	p = 0;
	count = 0;
	while (s[p])
	{
		if (s[p] == ' ' || s[p] == '\t')
		{
			p = skip_whitespaces(s, p);
		}
		else
		{
			count += 1;
			while (s[p] && s[p] != ' ' && s[p] != '\t')
			{
				p += 1;
			}
		}
	}
	return (count);
}

char			**str_split(char *s)
{
	WOW();
	int				p;
	char			**strings;
	int				sp;
	int				word_count;
	int				begin;

	word_count = count_words(s);
	p = 0;
	sp = 0;
	strings = malloc(sizeof(*strings) * (word_count + 1));
	while (s[p])
	{
		if (s[p] == ' ' || s[p] == '\t')
		{
			p = skip_whitespaces(s, p);
		}
		else
		{
			begin = p;
			while (s[p] && s[p] != '\t' && s[p] != ' ')
			{
				p += 1;
			}
			strings[sp] = ft_strdup_range(s, begin, p - 1);
			sp += 1;
		}
	}
	strings[sp] = NULL;
	return (strings);
}

char			*search_env(char **env)
{
	WOW();
	int			p = 0;
	while (env[p])
	{
		printf("%s\n", env[p]);
		if (!strncmp(env[p], "PATH", 4))
			return (ft_strdup_range(env[p], 5, strlen(env[p])));
		p += 1;
	}
	 return (NULL);

}

void			enqueue(t_list **head, char *content)
{
	t_list				*new;
	t_list				*traverse;

	new = malloc(sizeof(*new));
	new->name = strdup(content);
	new->next = NULL;
	if (!(*head))
	{
		*head = new;
		return ;
	}
	traverse = *head;
	while (traverse && traverse->next)
	{
		traverse = traverse->next;
	}
	traverse->next = new;
}

void			add_potential_expansions(t_list **head, char *s, int size, DIR *dirp)
{
	WOW();
	struct dirent		*entry;

	while ((entry = readdir(dirp)))
	{
		if (!strncmp(s, entry->d_name, size))
		{
			enqueue(head, entry->d_name);
		}
	}
}

int				search_directory(char *s, char **dirs, int p, t_list **expansions)
{
	DIR				*dirp;
	
	if (!dirs[p])
		return (0);
	dirp = opendir(dirs[p]);
	if (!dirp)
		return (-1);
	add_potential_expansions(expansions, s, strlen(s), dirp);
	closedir(dirp);
	return (1);
}

int				count_list(t_list *list)
{
	t_list		*traverse;
	int			p;

	p = 0;
	traverse = list;
	while (traverse)
	{
		p += 1;
		traverse = traverse->next;
	}
	return (p);
}

char			**copy_list(t_list *list)
{
	int			count;
	char		**copy;
	int			p;
	t_list		*traverse;

	count = count_list(list);
	copy = malloc(sizeof(*copy) * (count + 1));
	p = 0;
	traverse = list;
	while (traverse)
	{
		copy[p] = strdup(traverse->name);
		traverse = traverse->next;
		p += 1;
	}
	copy[p] = NULL;
	return (copy);
}

void			print_list(t_list *list)
{
	t_list		*traverse;

	traverse = list;
	while (traverse)
	{
		printf("--------------%s\n", traverse->name);
		traverse = traverse->next;
	}
}

char			**search_directories(char *s, char **directories)
{
	t_list		*expansions;
	int			p = 0;

	expansions = NULL;
	while (search_directory(s, directories, p, &expansions))
	{
		p += 1;
	}
	print_list(expansions);
	return (copy_list(expansions));
	
}

char			**autocomplete_path(char *s)
{
	char		*path = search_env(environ);

	char		**directories = str_split(replace_char(path, ':', ' '));

	char		**expansions = search_directories(s, directories);
//	return (directories);
	return (expansions);
}

char			**get_pwd(void)
{
	char		**pwd;
	char		buf[MAXPATHLEN];

	pwd = malloc(sizeof(*pwd) * 2);
	pwd[0] = strdup(getcwd(buf, MAXPATHLEN));
	pwd[1] = NULL;
	return (pwd);
}

char			**autocomplete_pwd(char *s)
{
	t_list		*expansions;
	char		**pwd_null;

	pwd_null = get_pwd();
	expansions = NULL;
	search_directory(s, pwd_null, 0, &expansions);
	return (copy_list(expansions));
}

char			**autocomplete(char *s, int mode)
{
	if (mode == EXE)
		return (autocomplete_path(s));
	else
		return (autocomplete_pwd(s));
}

int				main(int argc, char **argv)
{
	if (argc == 2)
	{
		print_strings(autocomplete(argv[1], ARG), 0);
	}
	return (0);
}
