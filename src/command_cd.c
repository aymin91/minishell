/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amin <amin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 10:38:12 by amin              #+#    #+#             */
/*   Updated: 2021/01/08 10:50:10 by amin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_cd(char **commands, t_list *envs)
{
	char	*path;

	path = 0;
	if (commands[1] == NULL || ((commands[1] != NULL) &&
		(ft_strlen(commands[1]) == 1) && (commands[1][0] == '~')))
	{
		path = find_value("HOME", envs);
		if (chdir(path) == -1)
			ft_putendl_fd(strerror(errno), 2);
		return ;
	}
	else if (*commands[1] == '$')
	{
		path = find_value(commands[1] + 1, envs);
		if (chdir(path) == -1)
			ft_putendl_fd(strerror(errno), 2);
		return ;
	}
	if (chdir(commands[1]) == -1)
		ft_putendl_fd(strerror(errno), 2);
}
