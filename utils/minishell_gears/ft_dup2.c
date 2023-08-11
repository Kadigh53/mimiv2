/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:08:02 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/07/30 07:27:12 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_dup2(int newfd, int oldfd)
{
	if (dup2(newfd, oldfd) == -1)
	{
		printf("%s\n", strerror(errno));
		return (error("minishell: dup2 function failed", 1));
	}
	return ;
}
