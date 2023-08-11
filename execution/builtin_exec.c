/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:17:06 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/08/10 02:21:34 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	a_builtin_cmd(char *cmd, char **args, t_env **env, int flag)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp("cd", cmd, ft_max(ft_strlen(cmd), ft_strlen("cd"))))
		_cd(env, args[0]);
	else if (!ft_strncmp("export", cmd, ft_max(ft_strlen(cmd),
				ft_strlen("export"))))
		_export(env, args, 0);
	else if (!ft_strncmp("env", cmd, ft_max(ft_strlen(cmd), ft_strlen("env"))))
		_env(env);
	else if (!ft_strncmp("pwd", cmd, ft_max(ft_strlen(cmd), ft_strlen("pwd"))))
		_pwd();
	else if (!ft_strncmp("echo", cmd, ft_max(ft_strlen(cmd),
				ft_strlen("echo"))))
		_echo(args);
	else if (!ft_strncmp("unset", cmd, ft_max(ft_strlen(cmd),
				ft_strlen("unset"))))
		_unset(env, args);
	else if (!ft_strncmp("exit", cmd, ft_max(ft_strlen(cmd),
				ft_strlen("exit"))))
		ft_exit(args, flag);
	else
		return (0);
	return (1);
}
