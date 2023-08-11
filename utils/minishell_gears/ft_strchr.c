/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 21:23:34 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/07/14 23:32:13 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strchr(char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (s[i] != (char)c)
	{
		if (!s[i])
			return (NULL);
		i++;
	}
	return ((char *)s + i);
}
