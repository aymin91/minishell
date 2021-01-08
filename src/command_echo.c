/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 18:36:35 by gicho             #+#    #+#             */
/*   Updated: 2021/01/08 17:21:22 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		command_echo(char **command)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (command[++i])
	{
		while (command[i] && (j + 1) == i &&
		!ft_strncmp(command[i], "-n", ft_strlen(command[i])))
		{
			if (command[i + 1] == NULL)
				return ;
			j++;
			i++;
		}
		ft_putstr_fd(command[i], 1);
		if (command[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
	}
	if (!j)
		ft_putstr_fd("\n", 1);
}
