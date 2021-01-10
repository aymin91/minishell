/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amin <amin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:55:45 by amin              #+#    #+#             */
/*   Updated: 2021/01/10 21:46:10 by amin             ###   ########.fr       */
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

static void		erase_key(char *command, t_list *envs)
{
	t_list		*current;
	t_list		*next;

	current = envs;
	next = envs->next;
	while (current->next)
	{
		if (ft_strncmp(((t_env *)next->content)->key, command, ft_strlen(command)))
		{
			current->next = next->next;
			free_element(next);
			return ;
		}
		next = next->next;
		current = current->next;
	}
}

void			command_unset(char **command, t_list *envs)
{
	command++;
	while (*command)
	{
		if (*find_value(*command, envs))
			erase_key(*command, envs);
		command++;
	}
}
