/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:18:11 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/08/11 00:32:46 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*init_fds(void)
{
	int				*std_io;
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag = term.c_lflag & ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	std_io = malloc(sizeof(int) * 2);
	std_io[0] = dup(STDIN_FILENO);
	std_io[1] = dup(STDOUT_FILENO);
	return (std_io);
}

void	init(int ac, char **env, int **std_io, t_env **env_lst)
{
	if (ac != 1)
	{
		error("minishell: too many arguments", 1);
		exit(1);
	}
	*env_lst = NULL;
	*env_lst = set_env(env);
	*std_io = init_fds();
	signals();
}
