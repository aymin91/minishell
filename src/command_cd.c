/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 10:38:12 by amin              #+#    #+#             */
/*   Updated: 2021/01/17 15:09:39 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		init_oldpwd(char *value, t_list **envs)
{
	t_env		*env;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		return ;
	env->key = ft_strdup("OLDPWD");
	env->value = ft_strdup(value);
	ft_lstadd_back(envs, ft_lstnew(env));
	g_first_old = 1;
}

static void		gicho(char *key, char *str, t_list *envs)
{
	if (!str)
		return ;
	while (envs)
	{
		if (!ft_strcmp(key, ((t_env *)envs->content)->key))
		{
			free(((t_env *)envs->content)->value);
			((t_env *)envs->content)->value = ft_strdup(str);
			return ;
		}
		envs = envs->next;
	}
}

char			*check_root(char **commands, t_list *envs)
{
	if (commands[1] == NULL || ((commands[1] != NULL) &&
		(ft_strlen(commands[1]) == 1) && (commands[1][0] == '~')) ||
		((commands[1] != NULL) && (!ft_strcmp(commands[1], "--"))))
		return (find_value("HOME", envs));
	return ("");
}

void			command_cd(char **commands, t_list *envs)
{
	char		*path;
	char		*cwd;
	char		*oldpwd;

	oldpwd = ft_strdup(find_value("PWD", envs));
	if (g_first_old == 0 && !find_value("OLDPWD", envs))
		init_oldpwd(oldpwd, &envs);
	else
		gicho("OLDPWD", oldpwd, envs);
	if ((path = check_root(commands, envs))[0])
	{
		if (chdir(path) == -1)
			ft_putendl_fd("HOME not set", 2);
	}
	else if (chdir(commands[1]) == -1)
		ft_putendl_fd(strerror(errno), 2);
	cwd = getcwd(NULL, 0);
	gicho("PWD", cwd, envs);
	free(cwd);
	free(oldpwd);
}
