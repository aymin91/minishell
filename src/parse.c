/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amin <amin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 15:42:53 by amin              #+#    #+#             */
/*   Updated: 2021/01/14 22:29:43 by amin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			init_quote(t_quote *q)
{
	q->type = -1;
	q->start = -1;
	q->end = -1;
}

void			check_end(char *str, int i, t_quote *q)
{
	if ((str[i] == '\'' && q->type == S_QUOTE) ||
		(str[i] == '\"' && q->type == D_QUOTE))
		q->end = i - 1;
	else if ((str[i + 1] == '\0' && q->type == S_QUOTE) ||
		(str[i + 1] == '\0' && q->type == D_QUOTE))
		q->end = i;
	else if (q->type == ETC &&
	(str[i + 1] == '\'' || str[i + 1] == '\"' || str[i + 1] == '\0'))
		q->end = i;
	return ;
}

void			check_quote(char *str, int i, t_quote *q)
{
	if (q->type == -1)
	{
		if (str[i] == '\'')
		{
			q->type = S_QUOTE;
			q->start = i + 1;
		}
		else if (str[i] == '\"')
		{
			q->type = D_QUOTE;
			q->start = i + 1;
		}
		else
		{
			q->type = ETC;
			q->start = i;
		}
		return ;
	}
	check_end(str, i, q);
}

char			*parse_env(char *res, t_list *envs)
{
	int			start_point;
	char		*str[4];

	g_i = -1;
	start_point = 0;
	while (res[++g_i])
	{
		if (res[g_i] == '$' || res[g_i + 1] == '\0')
		{
			if (start_point == 0)
			{
				str[3] = ft_substr(res, start_point, g_i);
				start_point = g_i + 1;
				continue;
			}
			str[0] = ft_substr(res, start_point, g_i - start_point + 1);
			str[1] = amin(str[0], envs);
			str[2] = ft_strjoin(str[3], str[1]);
			freeamin(str);
			str[3] = str[2];
			start_point = g_i + 1;
		}
	}
	free(res);
	return (str[3]);
}

char			*parse_quote(char *res, t_list *envs)
{
	int			i;
	char		*str[3];
	t_quote		q;

	i = -1;
	str[0] = "";
	init_quote(&q);
	while (res[++i])
	{
		check_quote(res, i, &q);
		if (q.end != -1)
		{
			str[1] = ft_substr(res, q.start, q.end - q.start + 1);
			if (q.type == D_QUOTE && isin_env(str[1]))
				str[1] = parse_env(str[1], envs);
			str[2] = ft_strjoin(str[0], str[1]);
			if (str[0] && *str[0])
				free(str[0]);
			if (str[1])
				free(str[1]);
			str[0] = str[2];
			init_quote(&q);
		}
	}
	return (str[2]);
}
