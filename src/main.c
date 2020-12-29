/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amin <amin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 09:38:25 by amin              #+#    #+#             */
/*   Updated: 2020/12/29 22:39:40 by amin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*specify_cmd(char *str)
{
	char	*res;

	res = 0;
	if (check_quote(str))
		res = parse_quote(str);
	else if (check_env(str))
		res = parse_env(str);
	free(str);
	return (res);
}

char		**split_cmds(char *cmd)
{
	int		i;
	char	**cmd;

	if (!(cmd = ft_split(cmd, ' ')))
		return (0);
	i = -1;
	while (cmd[++i])
	{
		if ((ft_strlen(cmd[i] != 1)
			&& (check_quote(cmd[i]) || check_env(cmd[i]))))
			cmd[i] = specify_cmd(cmd[i]);
	}
	return (cmd);
}

void		exe_builtin(char *commands)
{
	char	**command;

	command = split_cmds(commands);
	if (!ft_strncmp("echo", command[0], 4))
		command_echo(commands);
	// cd
	else if (!ft_strncmp("cd", command[0], 2))
		command_cd(commands, g_list);
	// pwd
	else if (!ft_strncmp("pwd", command[0], 3))
		command_pwd();
	// export
	else if (!ft_strncmp("export", command[0], 6))
		command_export(commands, g_list);
	// unset
	else if (!ft_strncmp("unset", command[0], 5))
		printf("=======unset\n");
	// env
	else if (!ft_strncmp("env", command[0], 3))
		command_env(g_list);
	// exit
	else if (!ft_strncmp("exit", command[0], 4))
		command_exit(commands);
	/*
	* TODO:
	* else execve 써야함..
	*/

}

void	exe_commands(char *commands)
{
	/*	TODO:
	*	pipe, redir, dollar 기호 처리
	*/
	exe_builtin(commands);
}

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

t_list		*set_envp(int argc, char **argv, char **envp)
{
	int		i;
	t_env	*env;

	(void)argc;
	(void)argv;
	i = 0;
	while (*envp)
	{
		env = (t_env *)malloc(sizeof(t_env));
		i = ft_strchr(*envp, '=') - *envp;
		env->key = ft_substr(*envp, 0, i);
		env->value = ft_substr(*envp, i + 1, ft_strlen(*envp) - i - 1);
		ft_lstadd_back(&g_list, ft_lstnew(env));
		envp++;
	}
	return (g_list);
}

int			main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**commands;
	char	**tmp;
	int		i;

	set_envp(argc, argv, envp);
	while (1)
	{
		write(1, ">", 1);
		if (!insert_input(&line))
			continue;
		if ((commands = get_commands(line)) == NULL)
			continue;
		i = -1;
		while (commands[++i])
		{
			exe_commands(commands[i]);
			free(commands[i]);
		}
		free(commands);
	}
	return (0);
}
