/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 09:38:25 by amin              #+#    #+#             */
/*   Updated: 2020/12/26 19:00:22 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_builtin(char **commands, char **envp)
{
	if (!ft_strncmp("echo", commands[0], 4))
		command_echo(*commands);
	// cd
	if (!ft_strncmp("cd", commands[0], 2))
		command_cd(commands, envp);
	// pwd
	if (!ft_strncmp("pwd", commands[0], 3))
		command_pwd();
	// export
	if (!ft_strncmp("export", commands[0], 6))
		printf("=======export\n");
	// unset
	if (!ft_strncmp("unset", commands[0], 5))
		printf("=======unset\n");
	// env
	if (!ft_strncmp("env", commands[0], 3))
		printf("=======env\n");
	// exit
	if (!ft_strncmp("exit", commands[0], 4))
		printf("=======exit\n");

}

void	exe_commands(char **commands, char **envp)
{
	/*	TODO:
	*	pipe, redir, dollar 기호 처리
	*/
	exe_builtin(commands, envp);

}

// TODO: quote 내부에 semicolon 있는 경우 구분 할 것
char			**get_commands(char *line)
{
	int			i;
	int			nothing;
	char		*tmp;
	char		**commands;

	nothing = 0;
	commands = ft_split(line, ';');
	i = -1;
	while (commands[++i])
	{
		tmp = ft_strtrim(commands[i], " ");
		nothing = (!tmp || !(*tmp)) ? 1 : 0;
		free(commands[i]);
		!nothing ? commands[i] = tmp : 0;
	}
	if (nothing)
	{ // 뭔가 더 필요.. 문법 검사 필요한 듯
		free(commands);
		ft_putendl_fd("error", 2);
		free(line);
		return (0);
	}
	free(line);
	//printf("-------------%s\n", commands[0]);
	return (commands);
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

void		set_envp(int argc, char **argv, char **envp)
{
	int		i;

	(void)argc;
	(void)argv;
	g_envp = (char **)ft_envmalloc(sizeof(char *) * (envp_len(envp) + 1));
	i = 0;
	while (envp[i])
	{
		if (!(g_envp[i] = ft_strdup(envp[i])))
			ft_exit();
		// printf("%d, %s\n", i, g_envp[i]);
		i++;
	}
}

int			main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**commands;
	//int		i;

	set_envp(argc, argv, envp);
	while (1)
	{
		write(1, ">", 1);
		if (!insert_input(&line))
			continue;
		exe_commands(&line, g_envp);
		// if ((commands = get_commands(line)) == NULL)
		// 	continue;
		// exe_commands(commands, g_envp);
		// free(commands);
	}
	return (0);
}
