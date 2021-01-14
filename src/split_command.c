/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:09:43 by amin              #+#    #+#             */
/*   Updated: 2021/01/14 15:52:01 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*specify_cmd(char *str, t_list *envs)
{
	char	*res;

	res = 0;
	if (isin_quote(str))
		res = parse_quote(str, envs);
	else if (isin_env(str))
		res = parse_env(str, envs);
	free(str);
	return (res);
}

char		**split_command(char *command, t_list *envs)
{
	int		i;
	char	**token;

	if (!(token = ft_split(command, ' ')))
		return (0);
	i = -1;
	while (token[++i])
	{
		if (token[i][0] == '\"' && ft_strchr(token[i], '\\'))
			parse_backslash_in_dquote(&token[i], envs);
		else if ((ft_strlen(token[i]) != 1)
			&& (isin_quote(token[i]) || isin_env(token[i])))
			token[i] = specify_cmd(token[i], envs);
	}
	return (token);
}
