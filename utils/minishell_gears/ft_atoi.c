/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:15:30 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/07/23 10:51:27 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_space_(const char *str)
{
	int	i;

	i = 0;
	while (((str[i] > 8 && str[i] < 14) || (str[i] == 32)) && str[i] != 0)
		i++;
	return (i);
}

long	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	i = is_space_(str);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= (-1);
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
		result = result * 10 + (str[i++] - 48);
	return (result * sign);
}
