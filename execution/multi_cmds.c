/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 20:50:04 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/08/10 22:48:35 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	one_command(t_cmds **cmds, t_env **env)
{
	if (!cmds)
		return ;
	if (!redirect(cmds))
	{
		if (g_exit_status == -1)
			g_exit_status = 1;
		return ;
	}
	if (cmds[0]->in_fd != -1)
		ft_dup2(cmds[0]->in_fd, STDIN_FILENO);
	if (cmds[0]->out_fd != -1)
		ft_dup2(cmds[0]->out_fd, STDOUT_FILENO);
	if (a_builtin_cmd(cmds[0]->cmd[0], cmds[0]->cmd + 1, env, 0))
	{
		ft_close(cmds[0]->in_fd);
		ft_close(cmds[0]->out_fd);
		return ;
	}
	single_cmd_execute(cmds[0]->cmd[0], cmds[0]->cmd, env);
	ft_close(cmds[0]->in_fd);
	ft_close(cmds[0]->out_fd);
	return ;
}

void	execute_cmd(char **cmd, t_env **env)
{
	char	*cmd_path;
	char	**p;

	if (!cmd || !*cmd)
		exit (127);
	cmd_path = get_cmd_path(cmd[0], env);
	if (!cmd_path)
		exit(127);
	p = envlist_toarray(env);
	if (execve(cmd_path, cmd, p) == -1)
	{
		printf("minishell: %s\n", strerror(errno));
		exit(1);
	}
}

void	process(t_cmds *cmd_strct, t_env **env)
{
	int	pid;
	int	fds[2];

	ft_pipe(fds);
	pid = ft_fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		ft_dup2(fds[1], STDOUT_FILENO);
		if (cmd_strct->in_fd != -1)
			ft_dup2(cmd_strct->in_fd, STDIN_FILENO);
		if (cmd_strct->out_fd != -1)
			ft_dup2(cmd_strct->out_fd, STDOUT_FILENO);
		ft_close(fds[0]);
		ft_close(fds[1]);
		if (a_builtin_cmd(cmd_strct->cmd[0], cmd_strct->cmd + 1, env, 3))
			exit(g_exit_status);
		execute_cmd(cmd_strct->cmd, env);
	}
	else
	{
		ft_dup2(fds[0], STDIN_FILENO);
		ft_close(fds[0]);
		ft_close(fds[1]);
	}
}

void	*cmd_execute_loop(int *counter, t_cmds **cmds, t_env **env)
{
	int	i;

	i = 0;
	while (cmds[i + 1])
	{
		if (!redirect(&cmds[i]))
		{
			i++;
			continue ;
		}
		process(cmds[i], env);
		ft_close(cmds[i]->in_fd);
		ft_close(cmds[i]->out_fd);
		i++;
	}
	*counter = i;
	return ((void *)1);
}

void	cmd_execute(t_cmds **cmds, t_env **env)
{
	int	i;

	if (!cmds[1] || !cmds)
		return (one_command(cmds, env));
	i = 0;
	if (!cmd_execute_loop(&i, cmds, env))
		return ;
	if (!redirect(&cmds[i]))
		return ;
	if (cmds[i]->in_fd != -1)
		ft_dup2(cmds[i]->in_fd, STDIN_FILENO);
	if (cmds[i]->out_fd != -1)
		ft_dup2(cmds[i]->out_fd, STDOUT_FILENO);
	single_cmd_execute(cmds[i]->cmd[0], cmds[i]->cmd, env);
	ft_close(cmds[i]->in_fd);
	ft_close(cmds[i]->out_fd);
	while (wait(NULL) != -1)
		;
}

/*
int in = dup(STDIN)
void	execute(){

... reder, herdoc....

while (commands)
{
	pipe = 0;
	if (next)
		{{{pipe...; int pipe=1}
		int save_in = fd[0];}}
	if (child)
	{
		if (pip)
			dup2(fd[1], STDOUT);
		exec
	}
	wait(0)
	if (pipe)
		dup(fd[0], STDIN);
}
}
dup2(in, STDIN);
*/