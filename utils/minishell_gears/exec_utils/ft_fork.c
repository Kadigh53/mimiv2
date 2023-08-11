/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:30:16 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/07/26 23:15:31 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		error("minishell: fork function failed", 1);
	}
	return (pid);
}
