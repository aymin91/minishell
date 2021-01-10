/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:35:05 by amin              #+#    #+#             */
/*   Updated: 2021/01/10 22:20:41 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			run_bredir(t_redir *redir, t_list **envs)
{
	int		fd;
	char	*path;

	fd = open(redir->argv[redir->argc - 1], O_RDONLY, 0644);
	if (fd < 0)
	{
		ft_puterr_fd(redir->argv[redir->argc - 1],
		": No such file or directory", 2);
		return (EXIT_FAILURE);
	}
	if (!(path = find_path(redir->commands[0], *envs)))
		return (ft_puterr_fd(redir->commands[0], ": command not found", 2));
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (!exe_builtin(redir->argv[redir->argc - 1], envs) &&
		(execve(path, redir->commands, g_envp) == -1))
		return (ft_puterr_fd(redir->commands[0], ": command not found", 2));
	free(path);
	ft_freearr(redir->commands);
	return (EXIT_SUCCESS);
}

int			run_dredir(t_redir *redir, t_list **envs)
{
	int		fd;
	char	*path;

	fd = open(redir->argv[redir->argc - 1],
	O_WRONLY | O_CREAT | O_APPEND, 0744);
	if (fd < 0)
	{
		ft_puterr_fd(redir->argv[redir->argc - 1],
		": No such file or directory", 2);
		return (EXIT_FAILURE);
	}
	if (!(path = find_path(redir->commands[0], *envs)))
		return (ft_puterr_fd(redir->commands[0], ": command not found", 2));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (!exe_builtin(redir->argv[redir->argc - 1], envs) &&
		(execve(path, redir->commands, g_envp) == -1))
		return (ft_puterr_fd(redir->commands[0], ": command not found", 2));
	free(path);
	ft_freearr(redir->commands);
	return (EXIT_SUCCESS);
}

int			run_redir(t_redir *redir, t_list **envs)
{
	int		fd;
	char	*path;

	fd = open(redir->argv[redir->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0744);
	if (fd < 0)
	{
		ft_puterr_fd(redir->argv[redir->argc - 1], ": No such or directory", 2);
		return (EXIT_FAILURE);
	}
	if (!(path = find_path(redir->commands[0], *envs)))
		return (ft_puterr_fd(redir->commands[0], ": command not found", 2));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (!exe_builtin(redir->argv[redir->argc - 1], envs) &&
		(execve(path, redir->commands, g_envp) == -1))
		return (ft_puterr_fd(redir->commands[0], ": command not found", 2));
	free(path);
	ft_freearr(redir->commands);
	return (EXIT_SUCCESS);
}

void		command_redir(t_redir *redir, t_list **envs)
{
	int		i;
	int		res;
	int		stat;
	pid_t	child;

	i = 0;
	child = fork();
	if (child == 0)
	{
		if (redir->type[redir->argc - 2] == REDIR)
			res = run_redir(redir, envs);
		else if (redir->type[redir->argc - 2] == DREDIR)
			res = run_dredir(redir, envs);
		else
			res = run_bredir(redir, envs);
		exit(res);
	}
	wait(&stat);
	g_exit = stat / 256;
	free(redir->type);
	ft_freearr(redir->argv);
	ft_freearr(redir->commands);
}
