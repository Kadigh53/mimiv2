/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:35:54 by yel-hadd          #+#    #+#             */
/*   Updated: 2023/08/11 01:25:32 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getKey(int value)
{
	switch (value) {
		case WORD:
			return ("WORD");
		case QUOTE:
			return ("QUOTE");
		case REDIRECTION:
			return ("REDIRECTION");
		case PIPE:
			return ("PIPE");
		case SPACE_:
			return ("SPACE_");
		case VAR:
			return ("VAR");
		case R_REDIRECTION:
			return ("R_REDIRECTION");
		case L_REDIRECTION:
			return ("L_REDIRECTION");
		case A_REDIRECTION:
			return ("A_REDIRECTION");
		case H_REDIRECTION:
			return ("H_REDIRECTION");
		case FIRST_S:
			return ("FIRST_S");
		case SECOND_S:
			return ("SECOND_S");
		case FIRST_D:
			return ("FIRST_D");
		case SECOND_D:
			return ("SECOND_D");
		case EXEC_VAR:
			return ("EXEC_VAR");
		default:
			return ("UNKNOWN");
	}
}
int		g_exit_status = 0;

void	cleanup_(int *std_io, t_env *env_lst)
{
	int		i;
	char	*n;
	char	*filenam;

	free_envirenment(env_lst);
	free(std_io);
	i = 0;
	n = ft_itoa(i);
	filenam = ft_strjoin(ft_strdup("/tmp/herdoc"), n);
	while (!access(filenam, F_OK))
	{
		unlink(filenam);
		free(filenam);
		free(n);
		i++;
		n = ft_itoa(i);
		filenam = ft_strjoin(ft_strdup("/tmp/herdoc"), n);
	}
	free(filenam);
	free(n);
}

void	clean_then_exit(int **std_io, t_env **env_lst)
{
	write(1, "exit\n", 5);
	cleanup_(*std_io, *env_lst);
	exit(g_exit_status);
}

void	main_loop(int **std_io, t_env **env_lst)
{
	char	*command;
	t_cmds	**cmds;
	t_lexer	*c;

	while (1)
	{
		// command = readline("minishell $> ");
		command = readline(NULL);
		// command = ft_strdup("$as ");
		if (!command)
			clean_then_exit(std_io, env_lst);
		add_history(command);
		c = lexer(command, env_lst);
		// while (c)
		// {
		// 	printf("data: '%s',\ttype: %s\n", c->data, getKey(c->type));
		// 	c = c->next;
		// }
		// continue;
		// break;
		cmds = parser(&c, env_lst);
		if (!cmds)
		{
			free(command);
			continue ;
		}
		cmd_execute(cmds, env_lst);
		ft_dup2((*std_io)[0], STDIN_FILENO);
		ft_dup2((*std_io)[1], STDOUT_FILENO);
		free_cmds(cmds);
		free(command);
		break;
	}
	return ;
}

int	main(int ac, char **av, char **env)
{
	int		*std_io;
	t_env	*env_lst;

	(void)av;
	init(ac, env, &std_io, &env_lst);
	main_loop(&std_io, &env_lst);
	cleanup_(std_io, env_lst);
	return (0);
}
