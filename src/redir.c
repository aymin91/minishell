/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amin <amin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 17:20:20 by amin              #+#    #+#             */
/*   Updated: 2021/01/13 00:34:59 by amin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		init_redir(char *commands, t_redir *redir)
{
	int		i;

	i = 0;
	while (*commands)
	{
		if (ft_strchr("><", *commands))
			i++;
		commands++;
	}
	redir->argc = i + 1;
	redir->argv = (char **)malloc(sizeof(char *) * (redir->argc + 1));
	redir->type = (char *)malloc(sizeof(char) * (redir->argc + 1));
	redir->commands = NULL;
}

int			parse_redir2(t_redir *redir, int j)
{
	if (check_redir_error(redir->argv[j]))
		return (-1);
	redir->type[j++] = 0;
	redir->argv[j] = 0;
	redir->argc = j;
	return (1);
}

int			parse_redir1(char *cmds, t_redir *redir, t_quote *q)
{
	g_i = -1;
	g_j = 0;
	g_start = 0;
	func1(&cmds, g_i, q);
	while (cmds[++g_i])
	{
		if (ft_strchr("><", cmds[g_i]))
		{
			if (!(q->start < g_i && g_i < q->end))
			{
				if (g_j > 0 && ((redir->type[0] == BREDIR && cmds[g_i] != '<')
				|| (redir->type[0] != BREDIR && cmds[g_i] == '<')))
					return (0);
				redir->argv[g_j] = sub_trim(cmds, g_start, g_i - g_start, " ");
				if (g_j == 0)
					redir->commands = ft_split(redir->argv[g_j], ' ');
				redir->type[g_j] = check_redir_type(cmds, g_i);
				redir->type[g_j++] == DREDIR ? g_i++ : 0;
				g_start = g_i + 1;
			}
		}
	}
	redir->argv[g_j] = sub_trim(cmds, g_start, g_i - g_start, " ");
	return (parse_redir2(redir, g_j));
}

void		open_file(t_redir *redir)
{
	int		i;
	int		fd;

	i = 1;
	while (i < redir->argc - 1)
	{
		if (i > 1)
			close(fd);
		if (redir->type[i - 1] == REDIR)
			fd = open(redir->argv[i], O_WRONLY | O_CREAT | O_TRUNC, 0744);
		else if (redir->type[i - 1] == DREDIR)
			fd = open(redir->argv[i], O_WRONLY | O_CREAT | O_APPEND, 0744);
		else
			fd = open(redir->argv[i], O_RDONLY, 0644);
		i++;
	}
	close(fd);
}

void		exe_redir(char *commands, t_list **envs)
{
	int		i;
	int		res;
	t_redir	redir;
	t_quote	q;

	init_redir(commands, &redir);
	if ((res = parse_redir1(commands, &redir, &q)) <= 0)
	{
		if (res < 0)
			ft_putendl_fd("syntax error near unexpected token 'newline'", 1);
		return ;
	}
	i = -1;
	while (redir.commands[++i])
	{
		if (isin_quote(redir.commands[i]))
			redir.commands[i] = specify_cmd(redir.commands[i], *envs);
	}
	open_file(&redir);
	command_redir(&redir, envs);
}
