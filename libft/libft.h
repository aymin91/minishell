/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amin <amin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 10:07:44 by amin              #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2020/12/24 10:07:46 by amin             ###   ########.fr       */
=======
/*   Updated: 2020/12/28 17:20:09 by amin             ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

typedef	struct		s_list
{
	void			*content;
	struct	s_list	*next;
}					t_list;

int			ft_atoi(const char *nptr);
void		ft_bzero(void *s, size_t n);
int			ft_isdigit(int n);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(char const *s, char c);
char		*ft_strcat(char *s1, char const *s2);
char		*ft_strcpy(char *s1, char const *s2);
char		*ft_strdup(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char* str1, const char *str2, size_t n);
char		*ft_strnew(size_t size);
char		*ft_strtrim(char const *s1, char const *set);
void		ft_toupper(char *str);
size_t		ft_strlcpy(char *des, const char *src, size_t n);
char		*ft_strchr(const char *str, int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);

#endif
