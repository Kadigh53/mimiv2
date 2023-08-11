/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:07:07 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/08/08 03:11:42 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	_pwd(void)
{
	int		fd;
	char	*cwd;

	fd = 1;
	g_exit_status = 0;
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		write(fd, cwd, ft_strlen(cwd));
		write(fd, "\n", 1);
	}
	else
		error("ERROR:gtcwd failed", 1);
	free(cwd);
}
