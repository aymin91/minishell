/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amin <amin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 10:38:12 by amin              #+#    #+#             */
/*   Updated: 2020/12/24 17:03:00 by amin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*find_home_path(char *home, char **envp)
{
	char	*path;
	int		n;
	int		i;

	i = -1;
	n = 0;
	while (envp[++i])
	{
		if (!(ft_strncmp(home, envp[i], ft_strlen(home))))
		{
			path = find_dir(envp[i], ft_strlen(home));
			return (path);
		}
	}
	return (0);
}

void	command_cd(char **commands, char **envp)
{
	char	*path;
	char	*env_name;

	path = 0;
	if (commands[1] == NULL || ((commands[1] != NULL) &&
		(ft_strlen(&commands[1][0]) == 1) && (commands[1][0] == '~')))
	{
		path = find_home_path("HOME", envp);
		if (path == NULL || chdir(path) == -1)
			ft_putstr_fd("error", 2);
		return ;
	}
	else if (commands[1][0] == '$')
	{
		env_name = find_str(commands[1], ft_strlen(commands[1]));
		path = find_home_path(env_name, envp);
		if (path == NULL || chdir(path) == -1)
				ft_putstr_fd("error\n", 2);
		return ;
	}
	else
	{
		if (chdir(commands[1]) == -1)
			ft_putstr_fd("error", 2);
	}
}
