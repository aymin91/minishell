/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:15:12 by amin              #+#    #+#             */
/*   Updated: 2021/01/16 18:21:51 by gicho            ###   ########.fr       */
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

void	print_prompt(void)
{
	ft_putstr_fd("> ", 1);
}

void	terminated_by_ctrl_c(int sig)
{
	if (sig != SIGINT)
		return ;
	ft_putendl_fd("",1);
	g_exit = 130;
}

void	sigint_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	g_exit = 1;
	ft_putendl_fd("\b\b  \b\b", 1);
	print_prompt();
}
