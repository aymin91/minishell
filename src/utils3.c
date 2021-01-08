/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amin <amin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:22:36 by amin              #+#    #+#             */
/*   Updated: 2021/01/08 10:49:05 by amin             ###   ########.fr       */
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

int		ft_puterr_fd(char *s1, char *s2, int fd)
{
	ft_putstr_fd(s1, fd);
	ft_putendl_fd(s2, fd);
	return (127);
}

