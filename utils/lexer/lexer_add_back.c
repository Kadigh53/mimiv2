/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_add_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadd <yel-hadd@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:04:08 by yel-hadd          #+#    #+#             */
/*   Updated: 2023/05/25 22:36:08 by yel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	lexer_add_back(t_lexer **ptr, t_lexer *new)
{
	t_lexer	*tmp;

	if (!*ptr)
	{
		*ptr = new;
		return ;
	}
	tmp = *ptr;
	while (tmp && tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}
