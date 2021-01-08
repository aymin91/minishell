/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 09:38:25 by amin              #+#    #+#             */
/*   Updated: 2021/01/08 17:31:48 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list		*set_envp(int argc, char **argv, char **envp)
{
	int		i;
	t_env	*env;
	t_list	*envs;

	(void)argc;
	(void)argv;
	g_exit = 0;
	i = 0;
	while (*envp)
	{
		env = (t_env *)malloc(sizeof(t_env));
		i = ft_strchr(*envp, '=') - *envp;
		env->key = ft_substr(*envp, 0, i);
		env->value = ft_substr(*envp, i + 1, ft_strlen(*envp) - i - 1);
		ft_lstadd_back(&envs, ft_lstnew(env));
		envp++;
	}
	return (envs);
}

int			main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**commands;
	int		i;
	t_list	*envs;

	g_envp = envp;
	envs = set_envp(argc, argv, envp);
	line = 0;
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
			exe_commands(commands[i], envs);
			free(commands[i]);
		}
		free(commands);
	}
	return (0);
}
