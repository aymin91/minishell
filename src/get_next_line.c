/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 16:41:13 by amin              #+#    #+#             */
/*   Updated: 2020/12/25 18:23:52 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*ft_strjoin_gnl(char *s1, char *s2)
{
	char		*res;
	size_t		l_s1;
	size_t		l_s2;
	size_t		len;

	l_s1 = 0;
	l_s2 = ft_strlen(s2);
	if (s1)
		l_s1 = ft_strlen(s1);
	len = l_s1 + l_s2;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	if (s1)
	{
		ft_strlcpy(res, s1, (l_s1 + 1));
		ft_strdel(&s1);
	}
	ft_strlcpy(res + l_s1, s2, (l_s2 + 1));
	return (res);
}

static int		is_line(char **word, char **line)
{
	char		*line_f;
	size_t		end;
	size_t		len;

	len = 0;
	line_f = NULL;
	if ((line_f = ft_strchr(*word, '\n')))
	{
		end = line_f - *word;
		len = ft_strlen(line_f);
		*line = ft_substr(*word, 0, end);
		ft_strlcpy(*word, (line_f + 1), (len + 1));
		return (1);
	}
	return (0);
}

int				get_next_line(int fd, char **line)
{
	int			read_num;
	char		buffer[BUFFER_SIZE + 1];
	static char	*word;

	if (!line || fd < 0 || BUFFER_SIZE < 1)
		return (-1);
	if (word && is_line(&word, line))
		return (1);
	while ((read_num = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[read_num] = '\0';
		if (!(word = ft_strjoin_gnl(word, buffer)))
			return (-1);
		if (is_line(&word, line))
			return (1);
	}
	if (word && *word)
		*line = ft_strdup(word);
	else
		*line = ft_strdup("");
	ft_strdel(&word);
	return (read_num);
}
