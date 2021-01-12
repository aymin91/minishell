/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_backslash_in_dquote.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 23:42:28 by gicho             #+#    #+#             */
/*   Updated: 2021/01/13 00:57:34 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	append_char(char **dst, char c)
{
	char	*tmp;
	int		len;

	tmp = *dst;
	len = ft_strlen(tmp);
	*dst = (char*)malloc(len + 2);
	*dst = ft_strcpy(*dst, tmp);
	(*dst)[len] = c;
	(*dst)[len + 1] = 0;
	free(tmp);
}

static int	append_variable(char **dst, char *src, t_list *envs)
{
	char *value;
	char *key;
	int key_len;
	int i;

	key_len = 0;
	while (src[key_len] && src[key_len] != ' ')
		++key_len;
	key = ft_substr(src, 0, key_len);
	value = find_value(key, envs);
	free(key);
	i = -1;
	while (value[++i])
		append_char(dst, value[i]);
	return (key_len);
}

int			parse_backslash_in_dquote(char **src, t_list *envs)
{
	char	*tmp;
	int		i;

	i = -1;
	tmp = ft_substr(*src, 1, ft_strlen(*src) - 2);
	*src = (char*)malloc(1);
	**src = 0;
	while (tmp[++i])
	{
		if (tmp[i] == '$' && tmp[i + 1] != ' ')
		{
			i += append_variable(src, tmp + i + 1, envs);
			continue;
		}
		if (tmp[i] == '\\' && ft_strchr("\\\"$", tmp[i + 1]))
			++i;
		append_char(src, tmp[i]);
	}
	free(tmp);
	return (1);
}
