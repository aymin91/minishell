/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amin <amin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:15:12 by amin              #+#    #+#             */
/*   Updated: 2021/01/05 15:17:43 by amin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handling(int sig)
{
	int		stat;

	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		g_exit = 1;
		return ;
	}
	else if (sig == SIGQUIT)
	{
		sig = wait(&stat);
		ft_putstr_fd("\n", 1);
		g_exit = 127;
		if (sig != -1)
			ft_putstr_fd("^\\Quit : 3\n", 1);
	}
	return ;
}
