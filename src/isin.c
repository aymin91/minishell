/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isin.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amin <amin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 15:41:44 by amin              #+#    #+#             */
/*   Updated: 2021/01/08 15:31:58 by amin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			isin_env(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
			return (1);
	}
	return (0);
}

int			isin_quote(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
	}
	return (0);
}

int			isin_pipe(char *str)
{
	int		num;

	num = 0;
	while (*str)
	{
		if (*str == '|')
			num++;
		str++;
	}
	return (num);
}

int			isin_redir(char *str)
{
	int		num;

	num = 0;
	while (*str)
	{
		if (ft_strchr("><", *str))
			num++;
		str++;
	}
	return (num);
}

int			isin_one_redir(char *command, int i)
{
	if (command[i] == '>' && command[i - 1] != '>' && command[i + 1] != '>')
		return (1);
	return (0);
}
