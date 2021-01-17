/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 09:37:55 by amin              #+#    #+#             */
/*   Updated: 2021/01/17 14:40:31 by gicho            ###   ########.fr       */
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

# define BUFFER_SIZE	1
# define S_QUOTE		39
# define D_QUOTE		34
# define ETC			42
# define REDIR			62
# define DREDIR			6
# define BREDIR			60

typedef	struct	s_env
{
	char		*key;
	char		*value;
}				t_env;

typedef	struct	s_quote
{
	int			type;
	int			start;
	int			end;
}				t_quote;

typedef	struct	s_pipe
{
	char		*line;
	char		**cmds;
}				t_pipe;

typedef struct	s_redir
{
	int			argc;
	char		**argv;
	char		**commands;
	char		*type;
}				t_redir;

char			**g_envp;
int				g_exit;
int				g_i;
int				g_j;
int				g_start;
int				interrupted;


void			command_cd(char **commands, t_list *envs);
void			command_echo(char **command);
void			command_env(char **command, t_list *envs);
void			command_exit(char **command);
void			command_export(char **command, t_list *envs);
void			command_pwd(void);
void			command_redir(t_redir *redir, t_list **envs);
void			command_unset(char **command, t_list **envs);
int				exe_builtin(char *commands, t_list **envs);
void			exe_else(char *commands, t_list *envs);
void			exe_commands(char *commands, t_list **envs);
int				get_next_line(int fd, char **line);
size_t			ft_strlen(char const *s);
char			*ft_strdup(char const *s1);
void			ft_strdel(char **as);
int				isin_env(char *str);
int				isin_quote(char *str);
int				isin_pipe(char *str);
int				isin_redir(char *str);
int				isin_one_redir(char *command, int i);
char			**get_commands(char *cmd);
int				insert_input(char **line);
void			init_quote(t_quote *q);
char			*parse_env(char *res, t_list *envs);
char			*parse_quote(char *res, t_list *envs);
void			parse_pipe(char **command, t_pipe *p, t_list *envs, t_quote *q);
void			exe_zero_case(int ch_zero, int fd[2], t_list **envs, t_pipe p);
void			exe_one_case(int ch_one, int fd[2], t_list **envs,
char *commands);
void			exe_pipe(char *commands, t_list **envs);
void			init_redir(char *commands, t_redir *redir);
int				parse_redir2(t_redir *redir, int j);
int				parse_redir1(char *commands, t_redir *redir, t_quote *q);
void			open_file(t_redir *redir);
void			exe_redir(char *commands, t_list **envs);
void			signal_handling(int sig);
char			*specify_cmd(char *str, t_list *envs);
char			**split_command(char *command, t_list *envs);
int				check_redir_error(char *str);
int				check_export(char *command);
void			print_export_env(char **tmp_env);
char			*sub_trim(char *command, int start, int i, char *str);
int				check_redir_type(char *command, int i);
void			*ft_envmalloc(size_t size);
void			ft_freearr(char **arr);
int				envp_len(char **envp);
int				isin_key(char *key, t_list *envs);
char			*find_value(char *key, t_list *envs);
int				find_equal(char *str);
char			*find_str(char *str, int n);
char			*find_dir(char *str, int n);
char			*find_path(char *commands, t_list *envs);
int				ft_puterr_fd(char *s1, char *s2, int fd);
void			add_declear_env(char **tmp_env);
char			*amin(char *str, t_list *envs);
void			freeamin(char **str);
int				is_single_line_command(char *cmd);
void			check_quote(char *str, int i, t_quote *q);
void			check_end(char *str, int i, t_quote *q);
void			check_right_start_quote(char **command, int i, t_quote *q);
void			check_right_end_quote(char **command, int i, t_quote *q);
char			**tokenize_quoted_string(char *str, char separator);
char			**remove_empty_str(char **strs);
void	sigint_handler(int sig);
void	print_prompt(void);
void	terminated_by_ctrl_c(int sig);
void	sigquit_handler(int sig);

#endif
