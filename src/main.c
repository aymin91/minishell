/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amin <amin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 09:38:25 by amin              #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2020/12/24 11:28:55 by amin             ###   ########.fr       */
=======
/*   Updated: 2020/12/28 17:35:14 by amin             ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_builtin(char **commands, char **envp)
{
	//printf("%s\n", envp[0]);
	// echo
	if (!ft_strncmp("echo", commands[0], 4))
		printf("=======echo\n");
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
<<<<<<< Updated upstream
	if (!ft_strncmp("exit", commands[0], 4))
		printf("=======exit\n");
=======
	else if (!ft_strncmp("exit", commands[0], 4))
		command_exit(commands);
	/*
	* TODO:
	* else execve 써야함..
	*/
>>>>>>> Stashed changes

}

void	exe_commands(char **commands, char **envp)
{
	/*	TODO:
	*	pipe, redir, dollar 기호 처리
	*/
	exe_builtin(commands, envp);
}

<<<<<<< Updated upstream
char			**get_commands(char *line)
=======
char			**get_commands(char *cmd)
>>>>>>> Stashed changes
{
	//int			i;
	int			nothing;
<<<<<<< Updated upstream
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
=======
	char		**tmp;

	nothing = 0;
	tmp = ft_split(cmd, ' ');
	nothing = (!tmp || !(tmp)) ? 1: 0;
	free(cmd);
	!nothing ? cmd = *tmp : 0;
>>>>>>> Stashed changes
	if (nothing)
	{ // 뭔가 더 필요.. 문법 검사 필요한 듯
		free(cmd);
		ft_putendl_fd("syntax error near unexpected token `;'", 2);
		return (0);
	}
<<<<<<< Updated upstream
	free(line);
	//printf("-------------%s\n", commands[0]);
	return (commands);
=======
	return (tmp);
>>>>>>> Stashed changes
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
		i++;
	}
}

int			main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**commands;
<<<<<<< Updated upstream
	//int		i;
=======
	char	**tmp;
	int		i;
>>>>>>> Stashed changes

	i = -1;
	set_envp(argc, argv, envp);
	while (1)
	{
		write(1, ">", 1);
		if (!insert_input(&line))
			continue;
<<<<<<< Updated upstream
		if ((commands = get_commands(line)) == NULL)
			continue;
		exe_commands(commands, g_envp);
		free(commands);
		//printf("%s\n", line);
=======
		if (ft_strchr(line, ';'))
			commands = ft_split(line, ';');
		else
			commands = ft_split(line, '\n');
		while (commands[++i])
		{
			tmp = get_commands(commands[i]);
			exe_commands(tmp, g_envp);
		}
		i = -1;
		free(commands);
>>>>>>> Stashed changes
	}
	return (0);
}
