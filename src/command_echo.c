/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amin <amin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 18:36:35 by gicho             #+#    #+#             */
/*   Updated: 2021/01/08 00:55:04 by amin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		command_echo(char **command)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (command[++i])
	{
		while (command[i] && (j + 1) == i &&
		!ft_strncmp(command[i], "-n", ft_strlen(command[i])))
		{
			if (command[i + 1] == NULL)
				return ;
			j++;
			i++;
		}
		ft_putstr_fd(command[i], 1);
		if (command[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
	}
	if (!j)
		ft_putstr_fd("\n", 1);
}

//char		*get_token(char **str, char con)
//{
//	char	*token;
//	size_t	i;

//	i = 0;
//	while ((*str)[i] && (*str)[i] != con)
//		++i;
//	token = (char *)malloc(i + 1);
//	token[i] = 0;
//	ft_strlcpy(token, *str, i + 1);
//	*str += i + ((*str)[i] ? 1 : 0);
//	return (token);
//}

//t_list			*split_str_including_quotes(char *str)
//{
//	t_list		*head;
//	char		c;

//	head = 0;
//	while (*str)
//	{
//		c = *(str++);
//		if (c == ' ')
//			continue;
//		if (c != '\'' && c != '\"')
//		{
//			c = ' ';
//			--str;
//		}
//		ft_lstadd_back(&head, ft_lstnew(get_token(&str, c)));
//	}
//	return (head);
//}

//void	print_lst(void *content)
//{
//	ft_putendl_fd((char *)content, 1);
//}

//void		print_strs(t_list *head)
//{
//	int		hasOptionN;

//	hasOptionN = 0;
//	while ((head = head->next))
//	{
//		if (ft_strcmp((char *)head->content, "-n") != 0)
//			break;
//		hasOptionN = 1;
//	}
//	if (head)
//	{
//		ft_putstr_fd((char *)head->content, 1);
//		while ((head = head->next))
//		{
//			ft_putchar_fd(' ', 1);
//			ft_putstr_fd((char *)head->content, 1);
//		}
//	}
//	if (!hasOptionN)
//		ft_putchar_fd('\n', 1);
//}

//void	command_echo(char *com)
//{
//	// TODO: 변수값 처리 $var
//	// echo "$(cat my_file.txt)"
//	t_list *head = split_str_including_quotes(com);
//	print_strs(head);
//}
