/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:08:59 by amin              #+#    #+#             */
/*   Updated: 2021/01/17 15:04:58 by gicho            ###   ########.fr       */
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
		g_exit = 127;
		return (1);
	}
	return (0);
}

int			exe_builtin(char *commands, t_list **envs)
{
	char	**command;

	command = split_command(commands, *envs);
	if (!ft_strcmp("echo", command[0]))
		command_echo(command);
	else if (!ft_strcmp("cd", command[0]))
		command_cd(command, *envs);
	else if (!ft_strcmp("pwd", command[0]))
		command_pwd();
	else if (!ft_strcmp("export", command[0]))
		command_export(command, *envs);
	else if (!ft_strcmp("unset", command[0]))
		command_unset(command, envs);
	else if (!ft_strcmp("env", command[0]))
		command_env(command, *envs);
	else if (!ft_strcmp("exit", command[0]))
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
		g_exit = 127;
		return ;
	}
	signal(SIGINT, signal_handling);
	signal(SIGQUIT, signal_handling);
	if ((child = fork()) == 0 && execve(path, command, g_envp) == -1)
		exit(ft_puterr_fd(command[0], ": commands not found", 2));
	wait(&stat);
	free(path);
	ft_freearr(command);
	if (!g_interrupted)
		g_exit = stat / 256;
	g_interrupted = 0;
}

void		exe_commands(char *commands, t_list **envs)
{
	if (isin_pipe(commands))
		exe_pipe(commands, envs);
	else if (isin_redir(commands))
		exe_redir(commands, envs);
	else if (!exe_dollar(commands) && !exe_builtin(commands, envs))
		exe_else(commands, *envs);
}
