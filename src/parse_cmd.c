/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amin <amin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:07:58 by amin              #+#    #+#             */
/*   Updated: 2021/01/07 17:46:02 by amin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_semicolon(const char *cmd)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = ft_strtrim(cmd, " ");
	if (tmp[0] == ';')
	{
		free(tmp);
		return (1);
	}
	while (tmp[++i])
	{
		if (tmp[i] == ';' && tmp[i + 1] == ';')
		{
			free(tmp);
			return (1);
		}
	}
	free(tmp);
	return (0);
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
		nothing = (!tmp || !(*tmp)) ? 1: 0;
		printf("trim - %s\n", cmds[i]);
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

static void		gnl_input(int n, char **line)
{
	char		*tmp;
	char		*buf;

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
