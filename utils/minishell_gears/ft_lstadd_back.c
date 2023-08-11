/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 22:12:48 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/06/26 18:03:05 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_rdrxadd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*tmp;

	tmp = (*lst);
	if (!new)
		return ;
	if (*lst)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	else
	{
		*lst = new;
	}
}
