/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_right_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadd <yel-hadd@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:11:31 by yel-hadd          #+#    #+#             */
/*   Updated: 2023/07/02 13:38:07 by yel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	process_right_redirection(char *cmd, int *c, t_lexer **head)
{
	if (cmd[c[0]] == '>')
	{
		if (cmd[c[0] + 1] == '>')
		{
			lexer_add_back(head, lexer_new(sdup(">>"), ++c[1], A_REDIRECTION));
			c[0] += 1;
		}
		else
			lexer_add_back(head, lexer_new(sdup(">"), ++c[1], R_REDIRECTION));
		c[0]++;
	}
}
