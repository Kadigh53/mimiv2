/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdup.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:33:21 by yel-hadd          #+#    #+#             */
/*   Updated: 2023/07/23 10:41:34 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*sdup(char *s1)
{
	char	*s2;
	size_t	len;

	len = ft_strlen(s1);
	s2 = ft_calloc((len + 1), sizeof(char));
	if (!s2 || !s1)
		return (NULL);
	ft_memcpy(s2, (void *)s1, ((len + 1) * sizeof(char)));
	return (s2);
}
