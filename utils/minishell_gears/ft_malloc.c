/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:11:56 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/07/26 23:15:14 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*ft_malloc(size_t size)
{
	void	*p;

	p = malloc(size);
	if (!p)
		error("ERROR:malloc failed", 1);
	return (p);
}
