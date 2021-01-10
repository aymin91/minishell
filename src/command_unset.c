/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:55:45 by amin              #+#    #+#             */
/*   Updated: 2021/01/10 22:21:37 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		free_element(t_list *element)
{
	free(((t_env *)element->content)->key);
	free(((t_env *)element->content)->value);
	free(element->content);
	free(element);
}

static int		is_equal_key(t_env *element, char *key)
{
	return (!ft_strncmp(element->key, key, ft_strlen(key)));
}

static void		erase_key(char *command, t_list **envs)
{
	t_list		*prev;
	t_list		*curr;

	prev = *envs;
	if (is_equal_key(prev->content, command))
	{
		*envs = prev->next;
		free_element(prev);
		return ;
	}
	curr = prev->next;
	while (curr)
	{
		if (is_equal_key(curr->content, command))
		{
			prev->next = curr->next;
			free_element(curr);
			return ;
		}
		prev = prev->next;
		curr = curr->next;

	}
}

void			command_unset(char **command, t_list **envs)
{
	command++;
	while (*command)
	{
		if (*find_value(*command, *envs))
			erase_key(*command, envs);
		command++;
	}
}
