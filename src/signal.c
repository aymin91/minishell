/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:15:12 by amin              #+#    #+#             */
/*   Updated: 2021/01/17 14:42:24 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(void)
{
	ft_putstr_fd("> ", 1);
}

void	signal_handling(int sig)
{
	if (sig == SIGINT)
		ft_putendl_fd("", 1);
	else if (sig == SIGQUIT)
		ft_putendl_fd("Quit: 3", 1);
	g_exit = 128 + sig;
	interrupted = 1;
}

void	sigquit_handler(int sig)
{
	if (sig != SIGQUIT)
		return ;
	ft_putstr_fd("\b\b  \b\b", 1);
}

void	sigint_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	g_exit = 1;
	ft_putendl_fd("\b\b  \b\b", 1);
	print_prompt();
}
