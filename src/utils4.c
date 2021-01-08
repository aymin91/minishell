/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amin <amin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 23:48:06 by amin              #+#    #+#             */
/*   Updated: 2021/01/08 15:32:37 by amin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_redir_error(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_strchr(" \n", str[i]))
			return (0);
		i++;
	}
	return (1);
}

int		check_redir_type(char *command, int i)
{
	if (command[i] == '>' && command[i + 1] == '>')
		return (DREDIR);
	else if (isin_one_redir(command, i))
		return (REDIR);
	return (BREDIR);
}

int		check_export(char *command)
{
	if (ft_isdigit(command[0]) || command[0] == '=')
		return (0);
	if (ft_strchr(command, '='))
		return (1);
	return (0);
}

void		print_export_env(char **tmp_env)
{
	int		i;

	i = -1;
	while (tmp_env[++i])
	{
		ft_putendl_fd(tmp_env[i], 1);
		free(tmp_env[i]);
	}
}

char	*sub_trim(char *command, int start, int i, char *str)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_substr(command, start, i);
	tmp2 = ft_strtrim(tmp1, str);
	free(tmp1);
	return (tmp2);
}
