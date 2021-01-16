/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amin <amin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 10:38:12 by amin              #+#    #+#             */
/*   Updated: 2021/01/16 23:19:51 by amin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define R_D replace_dir
#define R_S replace_str

static void	modify_pwd_val(char *path, t_list *envs, int old)
{
	if (!old)
	{
		while (envs)
		{
			if (!ft_strcmp(((t_env *)envs->content)->key, "PWD"))
				((t_env *)envs->content)->key = path;
			envs = envs->next;
		}
	}
	else
	{
		while (envs)
		{
			if (!ft_strcmp(((t_env *)envs->content)->key, "OLDPWD"))
				((t_env *)envs->content)->key = path;
			envs = envs->next;
		}
	}

}

static void	print_error(char *str, char *new_dir, int p)
{
	if (p == 3)
		ft_putendl_fd("cd : too many arguments", 2);
	else if (p == 2 && !new_dir)
	{
		ft_putstr_fd("cd :string not in pwd: ", 2);
		ft_putendl_fd(str, 1);
	}
	else if (access(new_dir, F_OK) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(new_dir, 1);
	}
	else if (access(new_dir, R_OK) == -1)
	{
		ft_putstr_fd("cd: permission denied: ", 2);
		ft_putendl_fd(new_dir, 1);
	}
	else
	{
		ft_putstr_fd("cd: not a directory: ", 2);
		ft_putendl_fd(new_dir, 1);
	}
	if (p == 2)
		free(new_dir);
	return ;
}

//static void	replace_dir(char *new_dir, char *old_dir,
//						char *search, t_list *envs)
//{
//	char	pwd[1024];
//	char	*home;

//	if (chdir(new_dir) == -1)
//		print_error(search, new_dir, 2);
//	getcwd(pwd, 1024);
//	if (find_value("PWD", envs))
//		modify_pwd_val(pwd, envs, 0);
//	if (find_value("OLDPWD", envs))
//		modify_pwd_val(old_dir, envs, 1);
//	if (!(home = find_value("HOME", envs)))
//		ft_putstr_fd(pwd, 2);
//	free(new_dir);
//}

static void	change_dir(char *new_dir, char *old_dir,
						t_list *envs, int p)
{
	char	pwd[1024];
	char	*home;

	if (chdir(new_dir) == -1)
		print_error(NULL, new_dir, p);
	getcwd(pwd, 1024);
	if (find_value("PWD", envs))
		modify_pwd_val(pwd, envs, 0);
	if (find_value("OLDPWD", envs))
		modify_pwd_val(old_dir, envs, 1);
	if (!(home = find_value("HOME", envs)))
		ft_putstr_fd(pwd, 2);
}

void		command_cd(char **commands, t_list *envs)
{
	int		len;
	char	pwd[1024];
	char	*home;
	char	*oldpwd;

	g_i = 1;
	len = 0;
	while (commands[len])
		len++;
	getcwd(pwd, 1024);
	home = find_value("HOME", envs);
	oldpwd = find_value("OLDPWD", envs);
	printf("pwd : %s\n home : %s\n oldpwd : %s\n", pwd, home, oldpwd);
	printf("commands : %s\n", commands[0]);
	if (!commands[1] || (ft_strequ("~", commands[1]) && !commands[2]))
		change_dir(home, pwd, envs, 0);
	if (!commands[1] && )
		//change_dir(home, pwd, envs, 0);


	if (ft_strequ("--", commands[g_i]))
		g_i++;
	if (len - g_i >= 3)
		return (print_error(NULL, NULL, 3));
	if (ft_strequ("-", commands[g_i]) && !commands[g_i + 1])
		return (change_dir(oldpwd, pwd, envs, 1));
	if (commands[g_i] && commands[g_i + 1])
		return (R_D(R_S(commands[g_i], commands[g_i + 1], pwd),
			pwd, commands[g_i], envs));
	return (change_dir(commands[g_i], pwd, envs, 0));
}
