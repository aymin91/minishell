/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amin <amin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:08:59 by amin              #+#    #+#             */
/*   Updated: 2021/01/08 12:24:58 by amin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	write_exit(void)
{
	ft_putstr_fd(ft_itoa(g_exit), 1);
	ft_putendl_fd(": command not found", 1);
	return (1);
}

static int	exe_dollar(char *commands)
{
	if (commands[0] == '$' && commands[1] == '?')
	{
		write_exit();
		return (1);
	}
	return (0);
}

int			exe_builtin(char *commands, t_list *envs)
{
	char	**command;

	command = split_command(commands,envs);
	if (!ft_strncmp("echo", command[0], ft_strlen(command[0])))
		command_echo(command);
	else if (!ft_strncmp("cd", command[0], 2))
		command_cd(command, envs);
	else if (!ft_strncmp("pwd", command[0], 3))
		command_pwd();
	else if (!ft_strncmp("export", command[0], 6))
		command_export(command, envs);
	else if (!ft_strncmp("unset", command[0], 5))
		command_unset(command, envs);
	else if (!ft_strncmp("env", command[0], 3))
		command_env(command, envs);
	else if (!ft_strncmp("exit", command[0], 4))
		command_exit(command);
	else
	{
		ft_freearr(command);
		return (0);
	}
	ft_freearr(command);
	g_exit = 0;
	return (1);
}

void		exe_else(char *commands, t_list *envs)
{
	int		stat;
	char	*path;
	char	**command;
	pid_t	child;

	command = split_command(commands, envs);
	path = find_path(command[0], envs);
	if (!path)
	{
		ft_puterr_fd(command[0], ": command not found", 2);
		return ;
	}
	child = fork();
	if (child == 0)
	{
		if (execve(path, command, g_envp) == -1)
			exit(ft_puterr_fd(command[0], ": commands not found", 2));
		exit(EXIT_SUCCESS);
	}
	wait(&stat);
	free(path);
	ft_freearr(command);
	g_exit = stat / 256;
}

void	exe_commands(char *commands, t_list *envs)
{
	if (isin_pipe(commands))
		exe_pipe(commands, envs);
	else if (isin_redir(commands))
		exe_redir(commands, envs);
	else if (!exe_dollar(commands) && !exe_builtin(commands, envs))
		exe_else(commands, envs);
}
