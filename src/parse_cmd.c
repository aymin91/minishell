/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:07:58 by amin              #+#    #+#             */
/*   Updated: 2021/01/09 18:58:08 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_semicolon(const char *cmd)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = ft_strtrim(cmd, " ");
	if (tmp[0] == ';')
	{
		free(tmp);
		return (1);
	}
	while (tmp[++i])
	{
		if (tmp[i] == ';' && tmp[i + 1] == ';')
		{
			free(tmp);
			return (1);
		}
	}
	free(tmp);
	return (0);
}

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
	if (*ft_strtrim(str, " "))
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
			ft_lstadd_back(&list, ft_lstnew(ft_substr(start, 0, str - start)));
			start = str + 1;
		}
		++str;
	}
	push_last_ele(&list, ft_substr(start, 0, str - start));
	return (list_to_2d_char(list));
}

char		**get_commands(char *cmd)
{
	int		i;
	int		nothing;
	char	*tmp;
	char	**cmds;

	i = -1;
	nothing = 0;
	cmds = split_commands(cmd);
	while (cmds[++i])
	{
		tmp = ft_strtrim(cmds[i], " ");
		nothing = (!tmp || !(*tmp)) ? 1 : 0;
		free(cmds[i]);
		!nothing ? cmds[i] = tmp : 0;
	}
	if (nothing || check_semicolon(cmd))
	{
		free(cmds);
		ft_putendl_fd("syntax error near unexpected token `;'", 2);
		return (0);
	}
	free(cmd);
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
