/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:56:40 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/07/23 10:45:16 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	i = 0;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	if (!n)
		return (0);
	while (n-- > 0)
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		if (p1[i] == '\0' && p2[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}
