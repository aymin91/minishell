/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amin <amin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 09:38:31 by amin              #+#    #+#             */
/*   Updated: 2021/01/10 21:44:18 by amin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		*ft_envmalloc(size_t size)
{
	void	*memory;

	if (!(memory = malloc(size)))
		return (NULL);
	ft_bzero(memory, size);
	return (memory);
}

void		ft_freearr(char **arr)
{
	int		i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int			envp_len(char **envp)
{
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	while (envp[i])
	{
		i++;
		cnt++;
	}
	return (cnt);
}

int			isin_key(char *key, t_list *envs)
{
	int		i;
	int		len;
	int		key_point;

	len = ft_strlen(key);
	key_point = ft_strlen((char *)((t_env *)envs->content)->key);
	i = (len > key_point) ? len : key_point;
	if (ft_strncmp(key, ((t_env *)envs->content)->key, i) == 0)
		return (1);
	return (0);
}

char		*find_value(char *key, t_list *envs)
{
	while (envs)
	{
		if (isin_key(key, envs))
			return (((t_env *)envs->content)->value);
		envs = envs->next;
	}
	return ("");
}
