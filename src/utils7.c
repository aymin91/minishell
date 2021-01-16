/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amin <amin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:28:50 by amin              #+#    #+#             */
/*   Updated: 2021/01/16 22:53:31 by amin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_redir(t_redir *redir)
{
	free(redir->type);
	ft_freearr(redir->argv);
	ft_freearr(redir->commands);
}

//static char	*replace_str2(char *search, char *replace, char *subject,
//							char *result)
//{
//	int i;
//	int j;
//	int start_pos;

//	i = -1;
//	start_pos = ft_strstr(subject, search) - subject;
//	while (++i < start_pos)
//		result[i] = subject[i];
//	j = i;
//	i = 0;
//	while (replace[i])
//	{
//		result[j] = replace[i];
//		j++;
//		i++;
//	}
//	i = ft_strlen(search);
//	while (subject[start_pos + i])
//	{
//		result[j] = subject[start_pos + i];
//		i++;
//		j++;
//	}
//	result[j] = '\0';
//	return (result);
//}

//char		*replace_str(char *search, char *replace, char *subject)
//{
//	int		len;
//	char	*result;

//	if (!search || !replace || !subject)
//		return (NULL);
//	if (!ft_strstr(subject, search))
//		return (NULL);
//	len = ft_strlen(subject) - ft_strlen(search) + ft_strlen(replace);
//	if (!(result = (char*)malloc(sizeof(char) * len + 1)))
//		return (NULL);
//	return (replace_str2(search, replace, subject, result));
//}
