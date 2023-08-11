/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:05:47 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/08/08 03:11:10 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	change_dir(char *arg)
{
	if (chdir(arg) == -1)
		error("minishell: chdir() failed", 1);
}

char	*get_destination(t_env **env, char *arg)
{
	char	*dst;
	char	*home;

	home = get_envvar(env, "HOME");
	if (!arg)
	{
		if (!home)
			return (error("cd: HOME not set", 1), NULL);
		else
			return (home);
	}
	else if (arg[0] == '~' && ft_strlen(arg) >= 1)
	{
		if (!home)
			return (error("cd: HOME not set", 1), NULL);
		if (!ft_strchr(arg, '/'))
			dst = home;
		else
			dst = ft_strjoin(home, ft_strchr(arg, '/'));
	}
	else
		return (free(home), ft_strdup(arg));
	return (dst);
}

void	update_pwd(t_env **env, char *tmp_oldpwd)
{
	char	*tmp_pwd;
	char	*op[2];
	char	*p[2];

	op[0] = ft_strjoin(ft_strdup("OLDPWD="), tmp_oldpwd);
	op[1] = NULL;
	tmp_pwd = getcwd(NULL, 0);
	p[0] = ft_strjoin(ft_strdup("PWD="), tmp_pwd);
	p[1] = NULL;
	free(tmp_pwd);
	_export(env, op, 1);
	_export(env, p, 1);
	free(op[0]);
	free(p[0]);
}

void	_cd(t_env **env, char *arg)
{
	char	*dst;
	char	*oldpwd;

	g_exit_status = 0;
	oldpwd = getcwd(NULL, 0);
	dst = get_destination(env, arg);
	if (!dst)
	{
		free(dst);
		free(oldpwd);
		return ;
	}
	if (!access(dst, F_OK))
		change_dir(dst);
	else
	{
		free(dst);
		free(oldpwd);
		error("cd: no such file or directory", 1);
		return ;
	}
	update_pwd(env, oldpwd);
	free(dst);
	free(oldpwd);
}
