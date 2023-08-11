/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:24:41 by yel-hadd          #+#    #+#             */
/*   Updated: 2023/07/23 10:47:00 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*pb;

	pb = (unsigned char *)b;
	while (len != 0)
	{
		*pb = (unsigned char)c;
		pb++;
		len--;
	}
	return (b);
}
