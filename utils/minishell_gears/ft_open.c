/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 20:09:31 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/07/26 23:15:21 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_open(char *filenam, int oflag, mode_t mode)
{
	int	fd;

	if (!filenam)
		error("error: file name is null", 1);
	fd = open(filenam, oflag, mode);
	if (fd < 0)
		error("error: file failed at opening", 1);
	return (fd);
}
