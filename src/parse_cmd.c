/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:07:58 by amin              #+#    #+#             */
/*   Updated: 2021/01/09 19:24:28 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_content(void *content)
{
	free(content);
}

char **list_to_2d_char(t_list *list)
{
	char **ret;
	int size;
	int i;
	t_list *tmp;

	i = 0;
	tmp = list;
	size = ft_lstsize(list);
	ret = (char**)malloc(sizeof(char*) * (size + 1));
	ret[size] = 0;
	while (list)
	{
		ret[i++] = ft_strdup(list->content);
		list = list->next;
	}
	ft_lstclear(&tmp, free_content);
	return (ret);
}

void push_last_ele(t_list **list, char *str)
{
	if (*str)
		ft_lstadd_back(list, ft_lstnew(str));
	else
		free(str);
}

void update(char a, char *b)
{
	if (*b == -1)
		*b = a;
	else if (*b == a)
		*b = -1;
}

char *trim_spaces(char *str)
{
	char *ret;

	ret = ft_strtrim(str, " ");
	free(str);
	return (ret);
}

char **split_commands(char *str)
{
	t_list *list;
	char quote;
	char *start;

	list = 0;
	start = str;
	quote = -1;
	while (*str)
	{
		if (*str == S_QUOTE || *str == D_QUOTE)
			update(*str, &quote);
		else if (quote == -1 && *str == ';')
		{
			ft_lstadd_back(&list, ft_lstnew(trim_spaces(ft_substr(start, 0, str - start))));
			start = str + 1;
		}
		++str;
	}
	push_last_ele(&list, trim_spaces(ft_substr(start, 0, str - start)));
	return (list_to_2d_char(list));
}

char		**get_commands(char *cmd)
{
	int		i;
	int		nothing;
	char	**cmds;

	i = -1;
	nothing = 0;
	cmds = split_commands(cmd);
	free(cmd);
	while (cmds[++i])
	{
		if (!(*cmds[i]))
		{
			ft_freearr(cmds);
			ft_putendl_fd("syntax error near unexpected token `;'", 2);
			return (0);
		}
	}
	return (cmds);
}

static void	gnl_input(int n, char **line)
{
	char	*tmp;
	char	*buf;

	buf = "";
	while (!(get_next_line(0, line)))
	{
		tmp = ft_strjoin(buf, *line);
		*buf ? free(buf) : 0;
		buf = tmp;
		if (!(**line) && !n)
		{
			ft_putstr_fd("exit\n", 1);
			free(buf);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd("  \b\b", 1);
		n = 1;
		free(*line);
	}
	if (n)
	{
		free(*line);
		*line = ft_strdup(buf);
	}
	*buf ? free(buf) : 0;
}

int			insert_input(char **line)
{
	int		n;
	char	*tmp;

	n = 0;
	gnl_input(n, line);
	if (**line == '\n')
	{
		free(*line);
		return (0);
	}
	if (*line != NULL)
	{
		tmp = ft_strtrim(*line, " ");
		if (*line)
		{
			free(*line);
			*line = NULL;
		}
		*line = tmp;
	}
	return (1);
}
