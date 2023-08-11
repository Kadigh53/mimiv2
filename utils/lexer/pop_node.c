/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 22:36:14 by yel-hadd          #+#    #+#             */
/*   Updated: 2023/07/23 17:57:40 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pop_node(t_lexer **head, t_lexer *node)
{
	if (!node->prev)
	{
		*head = node->next;
		if (node->next)
			node->next->prev = NULL;
	}
	else if (!node->next)
		node->prev->next = NULL;
	else
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	free(node->data);
	node->data = NULL;
	free(node);
	node = NULL;
}
