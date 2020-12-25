/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amin <amin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 09:37:55 by amin              #+#    #+#             */
/*   Updated: 2020/12/24 15:42:13 by amin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "../libft/libft.h"

# define BUFFER_SIZE 1

char	**g_envp;

/* main */


/* utils1 */
void		ft_exit(void);
void		*ft_envmalloc(size_t size);
void		ft_freearr(char **arr);
int			envp_len(char **envp);

/* utils2 */
int			find_equal(char *str);
char		*find_str(char *str, int n);
char		*find_dir(char *str, int n);

/* gnl */
int			get_next_line(int fd, char **line);
size_t		ft_strlcpy(char *dst, char const *src, size_t size);
size_t		ft_strlen(char const *s);
char		*ft_strchr(char const *s, int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strdup(char const *s1);
void		ft_strdel(char **as);

/* command_pwd */
void		command_pwd(void);

/* command_cd */
char		*find_home_path(char *home, char **envp);
void		command_cd(char **commands, char **envp);

/* command_env */
void		command_env(char **envp);

#endif
