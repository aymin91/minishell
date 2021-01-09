/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 19:36:39 by gicho             #+#    #+#             */
/*   Updated: 2021/01/09 20:10:48 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_content(void *content)
{
	free(content);
}

char	**list_to_2d_char(t_list *list)
{
	char	**ret;
	int		size;
	int		i;
	t_list	*tmp;

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

void	push_last_ele(t_list **list, char *str)
{
	if (*str)
		ft_lstadd_back(list, ft_lstnew(str));
	else
		free(str);
}

char	*trim_spaces(char *str)
{
	char	*ret;

	ret = ft_strtrim(str, " ");
	free(str);
	return (ret);
}

int		is_valid_quote_pairs(char *str)
{
	char	c;

	c = -1;
	while (*str)
	{
		if (*str == '\"' || *str == '\'')
		{
			if (c == -1)
				c = *str;
			else if (c == *str)
				c = -1;
		}
		++str;
	}
	return (c == -1);
}
