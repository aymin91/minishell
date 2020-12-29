/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amin <amin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 15:19:10 by amin              #+#    #+#             */
/*   Updated: 2020/12/29 21:56:37 by amin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_export_env(char **tmp_env)
{
	int		i;

	i = -1;
	while (tmp_env[++i])
	{
		ft_putendl_fd(tmp_env[i], 1);
		free(tmp_env[i]);
	}
}

void		add_declear_env(char **tmp_env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tmp_env[i])
	{
		tmp = ft_strjoin("declare -x ", tmp_env[i]);
		tmp_env[i] = tmp;
		i++;
	}
}

void		sort_env(char **tmp_env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tmp_env[i + 1])
	{
		if (ft_strncmp(tmp_env[i], tmp_env[i + 1], 100) > 0)
		{
			tmp = tmp_env[i];
			tmp_env[i] = tmp_env[i + 1];
			tmp_env[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
}

void		command_export(char **cmd, char **envp)
{
	char	**tmp;

	if (cmd[1] == NULL)
	{
		tmp = envp;
		sort_env(tmp);
		add_declear_env(tmp);
		print_export_env(tmp);
	}
	else // cmd[1] != NULL
	{

	}

}

