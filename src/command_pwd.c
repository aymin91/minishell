/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amin <amin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 10:37:13 by amin              #+#    #+#             */
/*   Updated: 2020/12/28 21:01:23 by amin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_pwd(void)
{
	//char	*pwd;

	g_pwd = getcwd(0, 1024);
	ft_putendl_fd(g_pwd, 1);
	//free(g_pwd);
}
