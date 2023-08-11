/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_last.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 14:07:20 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/07/23 14:07:47 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_lexer	*lexer_last(t_lexer **ptr)
{
	t_lexer	*tmp;

	if (!*ptr)
		return (*ptr);
	tmp = *ptr;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
