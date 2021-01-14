/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_single_line_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:13:56 by gicho             #+#    #+#             */
/*   Updated: 2021/01/14 17:16:19 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	multiline_command(char *cmd)
{
	ft_putendl_fd("multiple line command not supported", 2);
	free(cmd);
	return (0);
}

int			is_single_line_command(char *cmd)
{
	char	c;
	int		i;
	int		escapable_backslash;

	i = -1;
	c = -1;
	escapable_backslash = 1;
	while (cmd[++i])
		if (cmd[i] == S_QUOTE || cmd[i] == D_QUOTE)
		{
			if (c == -1)
				c = cmd[i];
			else if (c == cmd[i] &&
			!(c == D_QUOTE && cmd[i - 1] == '\\' && escapable_backslash))
				c = -1;
		}
		else if (cmd[i] == '\\')
			escapable_backslash =
			!(i != 0 && cmd[i - 1] == '\\' && escapable_backslash);
	return (c != -1 ? multiline_command(cmd) : 1);
}
