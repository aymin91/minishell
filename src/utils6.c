/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amin <amin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 00:20:15 by amin              #+#    #+#             */
/*   Updated: 2021/01/16 00:40:23 by amin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		check_right_end_quote(char **command, int i, t_quote *q)
{
	while ((*command)[++i])
	{
		if ((*command)[i] == '\"')
		{
			q->end = i;
			break ;
		}
		else if ((*command)[i] == '\'')
		{
			q->end = i;
			break ;
		}
	}
}

void		check_right_start_quote(char **command, int i, t_quote *q)
{
	while ((*command)[++i])
	{
		if ((*command)[i] == '\"')
		{
			q->type = D_QUOTE;
			q->start = i;
			break ;
		}
		else if ((*command)[i] == '\'')
		{
			q->type = S_QUOTE;
			q->start = i;
			break ;
		}
	}
	check_right_end_quote(command, i, q);
}

int			check_redir_syntax(char *commands)
{
	int		i;

	i = -1;
	while (commands[++i])
	{
		if (commands[i] == '>' && commands[i + 1] == '<')
			return (-1);
		else if (commands[i] == '>' && commands[i + 1] == '>' &&
		commands[i + 2] == '>')
			return (-2);
	}
	return (1);
}

void		print_redir_syn(int syn, t_redir *redir)
{
	if (syn == -1)
		ft_putendl_fd("syntax error near unexpected token `<'", 1);
	else if (syn == -2)
		ft_putendl_fd("syntax error near unexpected token `>'", 1);
	free_redir(redir);
	return ;
}

void		free_redir(t_redir *redir)
{
	free(redir->type);
	ft_freearr(redir->argv);
	ft_freearr(redir->commands);
}
