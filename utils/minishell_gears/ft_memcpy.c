/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:19:10 by yel-hadd          #+#    #+#             */
/*   Updated: 2023/07/23 10:47:18 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	void	*dstcpy;

	dstcpy = dst;
	if (!dst && !src)
		return (dstcpy);
	while ((n > 0))
	{
		*(char *)dst++ = *(char *)src++;
		n--;
	}
	return (dstcpy);
}
