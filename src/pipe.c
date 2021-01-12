/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amin <amin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 23:38:19 by amin              #+#    #+#             */
/*   Updated: 2021/01/12 23:47:49 by amin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		func1(char **command, int i, t_quote *q)
{
	while ((*command)[++i])
	{
		if ((*command)[i] == '\"')
		{
			q->type =  D_QUOTE;
			q->start = i;
			break;
		}
		else if ((*command)[i] == '\'')
		{
			q->type = S_QUOTE;
			q->start = i;
			break;
		}
	}
	while ((*command)[++i])
	{
		if ((*command)[i] == '\"')
		{
			q->end = i;
			break;
		}
		else if ((*command)[i] == '\'')
		{
			q->end = i;
			break;
		}
	}
}

void		parse_pipe(char **command, t_pipe *p, t_list *envs, t_quote *q)
{
	int		i;
	char	*str1;
	char	*str2;

	i = -1;
	func1(command, i, q);
	while ((*command)[++i])
	{
		if ((*command)[i] == '|' && check_right_pipe(command, i))
		{
			if (!(q->start < i && i < q->end))
			{
				str1 = ft_substr(*command, 0, i);
				p->line = ft_strtrim(str1, " ");
				free(str1);
				str1 = ft_substr(*command, i + 1, ft_strlen(*command) - i);
				str2 = ft_strtrim(str1, " ");
				free(str1);
				*command = str2;
				p->cmds = split_command(p->line, envs);
				return ;
			}
		}
	}
}

void		exe_zero_case(int ch_zero, int fd[2], t_list **envs, t_pipe p)
{
	if (ch_zero == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		exe_commands(p.line, envs);
		exit(EXIT_SUCCESS);
	}
}

void		exe_one_case(int ch_one, int fd[2], t_list **envs, char *commands)
{
	if (ch_one == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		exe_commands(commands, envs);
		exit(EXIT_SUCCESS);
	}
}

void		exe_pipe(char *commands, t_list **envs)
{
	int		fd[2];
	int		child[2];
	int		stat[2];
	t_pipe	p;
	t_quote	q;

	init_quote(&q);
	parse_pipe(&commands, &p, *envs, &q);
	pipe(fd);
	child[0] = fork();
	exe_zero_case(child[0], fd, envs, p);
	ft_freearr(p.cmds);
	free(p.line);
	child[1] = fork();
	exe_one_case(child[1], fd, envs, commands);
	free(commands);
	close(fd[0]);
	close(fd[1]);
	waitpid(child[1], &stat[1], 0);
	waitpid(child[0], &stat[0], WNOHANG);
}
