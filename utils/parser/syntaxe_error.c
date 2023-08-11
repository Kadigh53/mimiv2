/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:36:46 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/08/10 07:44:11 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	type_is_redirection(int type)
{
	if (type == L_REDIRECTION || type == R_REDIRECTION)
		return (1);
	else if (type == A_REDIRECTION || type == H_REDIRECTION)
		return (1);
	return (0);
}

int	pipe_syntaxe(t_lexer *tmp, t_lexer *next)
{
	if (!tmp->prev || !next || next->type == PIPE
		|| (next->type == SPACE_ && !next->next)
		|| (next->type == SPACE_ && next->next->type == PIPE)
		|| (tmp->prev->type == SPACE_ && !tmp->prev->prev))
		return (1);
	return (0);
}

int	rdrxs_syntaxe(t_lexer *next)
{
	if (!next || (next->type == SPACE_ && !next->next))
		return (1);
	else if (next->type == PIPE || (next->type == SPACE_
			&& next->next->type == PIPE))
		return (1);
	else if (next->type == SPACE_
		&& type_is_redirection(next->next->type))
		return (1);
	else if (type_is_redirection(next->type))
		return (1);
	return (0);
}

char	*syntaxe_error(t_lexer **mi)
{
	t_lexer	*tmp;
	t_lexer	*next;

	tmp = *mi;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->type == PIPE)
		{
			if (pipe_syntaxe(tmp, next))
			{
				return (error("syntax error near unexpected token", 258), NULL);
			}
		}
		else if (type_is_redirection(tmp->type))
		{
			if (rdrxs_syntaxe(next))
				return (error("syntax error near unexpected token", 258), NULL);
		}
		tmp = next;
	}
	return ((char *)1);
}
