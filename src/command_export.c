/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amin <amin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 15:19:10 by amin              #+#    #+#             */
/*   Updated: 2021/01/10 20:57:39 by amin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_val(t_env *env, t_list **envs)
{
	free(((t_env *)(*envs)->content)->value);
	((t_env *)(*envs)->content)->value = env->value;
	free(env->key);
	free(env);
}

void		sort_env(char **tmp_env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tmp_env[i + 1])
	{
		if (ft_strncmp(tmp_env[i], tmp_env[i + 1], 100) > 0)
		{
			tmp = tmp_env[i];
			tmp_env[i] = tmp_env[i + 1];
			tmp_env[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
}

char		**list_to_arr(t_list *envs)
{
	int		i;
	int		cnt;
	char	**arr;
	char	*arr_key;
	char	*arr_val;

	cnt = ft_lstsize(envs);
	if (!(arr = (char **)malloc(sizeof(char *) * (cnt + 1))))
		return (NULL);
	i = 0;
	while (envs)
	{
		arr_key = ft_strjoin(((t_env *)envs->content)->key, "=\"");
		arr_val = ft_strjoin((((t_env *)envs->content)->value), "\"");
		arr[i] = ft_strjoin(arr_key, arr_val);
		free(arr_key);
		free(arr_val);
		envs = envs->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

static void	arrange_env_val(char **command, t_list **envs)
{
	t_env	*env;
	t_list	*current;
	int		i;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		return ;
	i = ft_strchr(*command, '=') - *command;
	env->key = ft_substr(*command, 0, i);
	env->value = ft_substr(*command, i + 1, ft_strlen(*command) - i - 1);
	current = *envs;
	while (current)
	{
		if (isin_key(env->key, *envs))
		{
			update_val(env, &current);
			return ;
		}
		current = current->next;
	}
	if (current == NULL)
		ft_lstadd_back(envs, ft_lstnew(env));
}

void		command_export(char **command, t_list *envs)
{
	char	**tmp;

	if (command[1] == NULL)
	{
		tmp = list_to_arr(envs);
		sort_env(tmp);
		add_declear_env(tmp);
		print_export_env(tmp);
		return ;
	}
	command++;
	while (*command)
	{
		if (!check_export(*command))
		{
			ft_putstr_fd("export: '", 1);
			ft_putstr_fd(*command, 1);
			ft_putendl_fd("': not a valid identifier", 1);
			return ;
		}
		arrange_env_val(command, &envs);
		command++;
	}
}
