/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:55:45 by amin              #+#    #+#             */
/*   Updated: 2021/01/08 17:30:26 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		erase_key(char *command, t_list *envs)
{
	t_list		*current;
	t_list		*next;

	current = envs;
	while (current->next)
	{
		if (isin_key(command, envs))
		{
			next = current->next;
			current->next = next->next;
			free(((t_env *)next->content)->key);
			free(((t_env *)next->content)->value);
			free(next->content);
			free(next);
			return ;
		}
		current = current->next;
	}
}

void			command_unset(char **command, t_list *envs)
{
	command++;
	while (*command)
	{
		erase_key(*command, envs);
		command++;
	}
}
