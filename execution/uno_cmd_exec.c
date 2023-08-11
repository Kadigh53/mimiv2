/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uno_cmd_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:22:38 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/08/10 22:51:00 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *cmd)
{
	if ((!ft_strncmp("cd", cmd, ft_max(ft_strlen(cmd), ft_strlen("cd"))))
		|| (!ft_strncmp("export", cmd, ft_max(ft_strlen(cmd),
					ft_strlen("export"))))
		|| (!ft_strncmp("env", cmd, ft_max(ft_strlen(cmd), ft_strlen("env"))))
		|| (!ft_strncmp("pwd", cmd, ft_max(ft_strlen(cmd), ft_strlen("pwd"))))
		|| (!ft_strncmp("echo", cmd, ft_max(ft_strlen(cmd), ft_strlen("echo"))))
		|| (!ft_strncmp("unset", cmd, ft_max(ft_strlen(cmd),
					ft_strlen("unset"))))
		|| (!ft_strncmp("exit", cmd, ft_max(ft_strlen(cmd),
					ft_strlen("exit")))))
		return (1);
	else
		return (0);
}

void	single_execute(char *cmd, char **cmd_args, t_env **env_lst)
{
	int		pid;
	char	**env;

	pid = ft_fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		env = envlist_toarray(env_lst);
		if (a_builtin_cmd(cmd, cmd_args + 1, env_lst, 3))
			exit (g_exit_status);
		else if (execve(cmd, cmd_args, env) == -1)
		{
			printf("%s\n", strerror(errno));
			exit(1);
		}
	}
	waitpid(pid, &g_exit_status, 0);
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	else if (WIFSIGNALED(g_exit_status))
		g_exit_status = WTERMSIG(g_exit_status) + 128;
	ft_close(STDIN_FILENO);
	ft_close(STDOUT_FILENO);
}

void	single_cmd_execute(char *cmd, char **cmd_args, t_env **env)
{
	char	*cmd_path;

	if (!cmd || !*cmd)
		return ;
	if (!is_builtin(cmd))
	{
		cmd_path = get_cmd_path(cmd, env);
		if (!cmd_path)
			return ;
	}
	else
		cmd_path = ft_strdup(cmd);
	single_execute(cmd_path, cmd_args, env);
	free(cmd_path);
}
