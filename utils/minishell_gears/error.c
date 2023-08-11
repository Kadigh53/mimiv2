/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:30:21 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/07/26 23:12:50 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error(char *err_msg, int exit_int)
{
	if (err_msg)
	{
		write(2, err_msg, ft_strlen(err_msg));
		write(2, "\n", 1);
	}
	g_exit_status = exit_int;
}
