/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_empty_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:57:02 by gicho             #+#    #+#             */
/*   Updated: 2021/01/15 22:10:04 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_not_empty_str(char **strs)
{
	int	cnt;

	cnt = 0;
	while(*strs)
		if (**(strs++))
			++cnt;
	return (cnt);
}

char	**remove_empty_str(char **strs)
{
	int		i;
	int		j;
	char	**ret;

	ret = (char**)malloc(sizeof(char*) * (count_not_empty_str(strs) + 1));
	i = -1;
	j = 0;
	while (strs[++i])
	{
		if(*(strs[i]))
			ret[j++] = strs[i];
		else
			free(strs[i]);
	}
	free(strs);
	ret[j] = 0;
	return (ret);
}
