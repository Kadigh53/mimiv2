/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:51:14 by yel-hadd          #+#    #+#             */
/*   Updated: 2023/08/10 06:22:07 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_lexer	**merge_words(t_lexer **head)
{
	t_lexer	*tmp;
	t_lexer	*tmp2;
	char	*new_data;

	tmp = *head;
	while (tmp != NULL)
	{
		if (tmp->type == WORD || tmp->type == VAR || tmp->type == EXEC_VAR)
		{
			tmp2 = tmp->next;
			if (tmp2 && (tmp2->type == WORD || tmp2->type == VAR || tmp2->type == EXEC_VAR))
			{
				new_data = ft_strjoin(tmp->data, tmp2->data);
				tmp->data = new_data;
				tmp->type = WORD;
				pop_node(head, tmp2);
			}
			else
				tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
	return (head);
}
