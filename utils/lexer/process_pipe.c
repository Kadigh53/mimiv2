/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hadd <yel-hadd@mail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:07:12 by yel-hadd          #+#    #+#             */
/*   Updated: 2023/07/02 13:18:28 by yel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	process_pipe(char *cmd, int *c, t_lexer **head)
{
	if (cmd[c[0]] == '|')
	{
		lexer_add_back(head, lexer_new(sdup("|"), ++c[1], PIPE));
		c[0]++;
	}
}
