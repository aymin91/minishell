/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amin <amin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 14:25:18 by amin              #+#    #+#             */
/*   Updated: 2021/01/08 00:28:36 by amin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		print_env(t_list *envs)
{
	if (envs == NULL)
		return ;
	ft_putstr_fd(((t_env *)envs->content)->key, 1);
	ft_putchar_fd('=', 1);
	ft_putendl_fd(((t_env *)envs->content)->value, 1);
	print_env(envs->next);
}

int		check_env_value(char *command)
{
	if (command[0] == '=')
		return (1);
	if (!ft_strchr(command, '='))
		return (2);
	return (0);
}

static char 	*make_tmp(char *tmp, char *command)
{
	char 		*t;

	if (tmp == NULL)
		tmp = ft_strjoin(command, "\n");
	else
	{
		t = ft_strjoin(command, "\n");
		tmp = ft_strjoin(tmp, t);
		free(t);
	}
	return (tmp);
}

static int	check_env(char *command)
{
	if (check_env_value(command) == 1)
	{
		ft_putstr_fd("env: setenv", 1);
		ft_putstr_fd(command, 1);
		ft_putendl_fd(" : Invalid argument", 1);
		return (0);
	}
	if (check_env_value(command) == 2)
	{
		ft_putstr_fd("env: ", 1);
		ft_putstr_fd(command, 1);
		ft_putendl_fd(": No such file of directory", 1);
		return (0);
	}
	return (1);
}

void		command_env(char **command, t_list *envs)
{
	char	*tmp;

	tmp = 0;
	command++;
	while (*command)
	{
		if (!check_env(*command))
			return ;
		tmp = make_tmp(tmp, *command);
		command++;
	}
	print_env(envs);
	if (tmp != NULL)
	{
		ft_putstr_fd(tmp, 1);
		free(tmp);
	}
}
