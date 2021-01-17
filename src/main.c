/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 09:38:25 by amin              #+#    #+#             */
/*   Updated: 2021/01/17 15:03:59 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		init_sig(void)
{
	signal(SIGQUIT, sigquit_handler);
	signal(SIGINT, sigint_handler);
}

void		set_envp(int argc, char **argv, char **envp, t_list **envs)
{
	int		i;
	t_env	*env;

	(void)argc;
	(void)argv;
	g_exit = 0;
	i = 0;
	while (*envp)
	{
		env = (t_env *)malloc(sizeof(t_env));
		i = ft_strchr(*envp, '=') - *envp;
		env->key = ft_substr(*envp, 0, i);
		if (!ft_strcmp("PWD", env->key))
			env->value = getcwd(NULL, 0);
		else
			env->value = ft_substr(*envp, i + 1, ft_strlen(*envp) - i - 1);
		ft_lstadd_back(envs, ft_lstnew(env));
		envp++;
	}
}

int			main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**commands;
	int		i;
	t_list	*envs;

	g_envp = envp;
	set_envp(argc, argv, envp, &envs);
	line = 0;
	while (1)
	{
		init_sig();
		print_prompt();
		if (!insert_input(&line) ||
			!is_single_line_command(line) ||
			(commands = get_commands(line)) == NULL)
			continue;
		i = -1;
		while (commands[++i])
		{
			exe_commands(commands[i], &envs);
			free(commands[i]);
		}
		free(commands);
	}
	return (0);
}
