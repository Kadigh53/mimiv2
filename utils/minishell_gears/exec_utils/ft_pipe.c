/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:32:46 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/07/26 23:15:36 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	ft_pipe(int pipefds[])
{
	int	r;

	r = pipe(pipefds);
	if (r == -1)
	{
		error("minishell: pipe function fail", 1);
	}
	return ;
}
