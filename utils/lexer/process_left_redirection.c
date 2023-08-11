/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_left_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadd <yel-hadd@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:10:33 by yel-hadd          #+#    #+#             */
/*   Updated: 2023/07/02 13:38:18 by yel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	process_left_redirection(char *cmd, int *c, t_lexer **head)
{
	if (cmd[c[0]] == '<')
	{
		if (cmd[c[0] + 1] == '<')
		{
			lexer_add_back(head, lexer_new(sdup("<<"), ++c[1], H_REDIRECTION));
			c[0] += 1;
		}
		else
		{
			lexer_add_back(head, lexer_new(sdup("<"), ++c[1], L_REDIRECTION));
		}
		c[0]++;
	}
}
