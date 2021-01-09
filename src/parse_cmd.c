/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amin <amin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:07:58 by amin              #+#    #+#             */
/*   Updated: 2021/01/09 15:15:57 by amin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update(char a, char *b)
{
	if (*b == -1)
		*b = a;
	else if (*b == a)
		*b = -1;
}

char		**split_commands(char *str)
{
	t_list	*list;
	char	quote;
	char	*start;

	list = 0;
	start = str;
	quote = -1;
	while (*str)
	{
		if (*str == S_QUOTE || *str == D_QUOTE)
			update(*str, &quote);
		else if (quote == -1 && *str == ';')
		{
			ft_lstadd_back(&list,
			ft_lstnew(trim_spaces(ft_substr(start, 0, str - start))));
			start = str + 1;
		}
		++str;
	}
	push_last_ele(&list, trim_spaces(ft_substr(start, 0, str - start)));
	return (list_to_2d_char(list));
}

static void	gnl_input(int n, char **line)
{
	char	*tmp;
	char	*buf;

	buf = "";
	while (!(get_next_line(0, line)))
	{
		tmp = ft_strjoin(buf, *line);
		*buf ? free(buf) : 0;
		buf = tmp;
		if (!(**line) && !n)
		{
			ft_putstr_fd("exit\n", 1);
			free(buf);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd("  \b\b", 1);
		n = 1;
		free(*line);
	}
	if (n)
	{
		free(*line);
		*line = ft_strdup(buf);
	}
	*buf ? free(buf) : 0;
}

int			insert_input(char **line)
{
	int		n;
	char	*tmp;

	n = 0;
	gnl_input(n, line);
	if (**line == '\n')
	{
		free(*line);
		return (0);
	}
	if (*line != NULL)
	{
		tmp = ft_strtrim(*line, " ");
		if (*line)
		{
			free(*line);
			*line = NULL;
		}
		*line = tmp;
	}
	return (1);
}

char		**get_commands(char *cmd)
{
	int		i;
	int		nothing;
	char	*tmp;
	char	**cmds;

	i = -1;
	nothing = 0;
	cmds = ft_split(cmd, ';');
	while (cmds[++i])
	{
		tmp = ft_strtrim(cmds[i], " ");
		nothing = (!tmp || !(*tmp)) ? 1 : 0;
		free(cmds[i]);
		!nothing ? cmds[i] = tmp : 0;
	}
	if (nothing || check_semicolon(cmd))
	{
		free(cmds);
		ft_putendl_fd("syntax error near unexpected token `;'", 2);
		return (0);
	}
	free(cmd);
	return (cmds);
}
