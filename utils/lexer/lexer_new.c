/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadd <yel-hadd@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:04:40 by yel-hadd          #+#    #+#             */
/*   Updated: 2023/07/02 13:16:20 by yel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_lexer	*lexer_new(char *data, int index, int type)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->data = data;
	new->index = index;
	new->type = type;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}
