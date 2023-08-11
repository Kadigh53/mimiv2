/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_index.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadd <yel-hadd@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:50:38 by yel-hadd          #+#    #+#             */
/*   Updated: 2023/06/10 19:50:50 by yel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_lexer	*fix_index(t_lexer **head)
{
	t_lexer	*tmp;
	int		i;

	tmp = *head;
	i = 0;
	while (tmp != NULL)
	{
		tmp->index = i;
		i++;
		tmp = tmp->next;
	}
	return (*head);
}
