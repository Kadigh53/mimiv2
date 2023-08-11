/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:08:10 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/07/26 16:30:19 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_heredoc(int sig_num)
{
	char	c;

	c = '\n';
	if (sig_num == SIGINT)
	{
		g_exit_status = -1;
		ioctl(0, TIOCSTI, &c);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	close_and_restore_signals(int herdoc_fd)
{
	close(herdoc_fd);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, sig_handler);
}

void	setup_signal_handlers(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, exit_heredoc);
}
