/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 17:20:20 by amin              #+#    #+#             */
/*   Updated: 2021/01/10 22:27:03 by gicho            ###   ########.fr       */
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

int			parse_redir1(char *commands, t_redir *redir)
{
	int		i;
	int		j;
	int		start;

	i = -1;
	j = 0;
	start = 0;
	while (commands[++i])
	{
		if (ft_strchr("><", commands[i]))
		{
			if (j > 0 && ((redir->type[0] == BREDIR && commands[i] != '<') ||
			(redir->type[0] != BREDIR && commands[i] == '<')))
				return (0);
			redir->argv[j] = sub_trim(commands, start, i - start, " ");
			if (j == 0)
				redir->commands = ft_split(redir->argv[j], ' ');
			redir->type[j] = check_redir_type(commands, i);
			redir->type[j++] == DREDIR ? i++ : 0;
			start = i + 1;
		}
	}
	redir->argv[j] = sub_trim(commands, start, i - start, " ");
	return (parse_redir2(redir, j));
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

	init_redir(commands, &redir);
	if ((res = parse_redir1(commands, &redir)) <= 0)
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
