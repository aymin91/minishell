/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:22:36 by amin              #+#    #+#             */
/*   Updated: 2021/01/11 23:19:48 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char				*find_path(char *commands, t_list *envs)
{
	int				i;
	char			*tmp;
	char			*n_path;
	char			**paths;
	struct stat		s;

	if (!(tmp = find_value("PATH", envs)))
		return (NULL);
	paths = ft_split(tmp, ':');
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin("/", commands);
		n_path = ft_strjoin(paths[i], tmp);
		free(tmp);
		if (stat(n_path, &s) == 0)
		{
			ft_freearr(paths);
			return (n_path);
		}
		free(n_path);
	}
	ft_freearr(paths);
	return (ft_strdup(commands));
}

int					ft_puterr_fd(char *s1, char *s2, int fd)
{
	ft_putstr_fd(s1, fd);
	ft_putendl_fd(s2, fd);
	return (127);
}

char				*amin(char *str, t_list *envs)
{
	if (!ft_strncmp(str, "?", ft_strlen(str)))
		return (ft_itoa(g_exit));
	return (ft_strdup(find_value(str, envs)));
}

void				freeamin(char **str)
{
	free(str[0]);
	free(str[1]);
	free(str[3]);
}

int					is_single_line_command(char *cmd)
{
	char	c;
	int		i;

	i = -1;
	c = -1;
	while (cmd[++i])
		if (cmd[i] == S_QUOTE || cmd[i] == D_QUOTE)
		{
			if (c == -1)
				c = cmd[i];
			else if (c == cmd[i])
				c = -1;
		}
	if (c != -1)
	{
		ft_putendl_fd("multiple line command not supported", 2);
		free(cmd);
		return (0);
	}
	return (1);
}
