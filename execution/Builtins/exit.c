/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:19:18 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/08/08 03:50:50 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(char **args, int flag)
{
	int	i;

	i = -1;
	if (!flag)
		write(1, "exit\n", 5);
	if (!args || !args[0])
		exit(g_exit_status);
	while (args[0][++i])
	{
		if (!ft_isdigit(args[0][i]) && args[0][i] != '-' && args[0][i] != '+')
		{
			error("exit: numeric argument required", 255);
			exit(255);
		}
	}
	if (args[1])
		return (error("exit: too many arguments", 1));
	if (args[0])
		exit((unsigned char)ft_atoi(args[0]));
}
