/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:07:55 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/07/30 07:11:02 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_close(int fd)
{
	if (fd == -1)
		return ;
	if (close(fd) == -1)
		error("minishell: close function failed", 1);
}
