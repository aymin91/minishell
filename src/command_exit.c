/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 23:33:48 by amin              #+#    #+#             */
/*   Updated: 2021/01/08 17:32:07 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_digit_str(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void		command_exit(char **command)
{
	int		i;

	i = 0;
	while (command[i] != NULL)
		i++;
	if (i == 1)
	{
		ft_putendl_fd("exit", 1);
		exit(EXIT_SUCCESS);
	}
	else if (i == 2 && check_digit_str(command[1]))
	{
		exit(ft_atoi(command[1]));
	}
	else if (i > 2 && check_digit_str(command[1]))
		ft_putendl_fd("exit: too many arguments", 1);
	else
	{
		ft_putstr_fd("exit: numeric argument required", 1);
		exit(2);
	}
}
