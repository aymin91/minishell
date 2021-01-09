/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 09:38:36 by amin              #+#    #+#             */
/*   Updated: 2021/01/09 16:22:11 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			find_equal(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

char		*find_str(char *str, int n)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * n);
	i = 1;
	j = 0;
	while (str[i] && i < n)
	{
		tmp[j] = str[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char		*find_dir(char *str, int n)
{
	int		i;
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * ft_strlen(str) - n + 2);
	i = 0;
	while (str[n + 1])
	{
		tmp[i] = str[n + 1];
		n++;
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

void		add_declear_env(char **tmp_env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tmp_env[i])
	{
		tmp = ft_strjoin("declare -x ", tmp_env[i]);
		tmp_env[i] = tmp;
		i++;
	}
}

int	enclosedWithPairOfQuote(char *str)
{
	int len;
	int i;

	i = 0;
	len = ft_strlen(str);
	while (str[i] != '\'' && str[i] != '\"')
		++i;
	if (i != len - 1 && str[i] == str[len - 1])
		return (1);
	return (0);
}
