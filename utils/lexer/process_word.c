/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:12:15 by yel-hadd          #+#    #+#             */
/*   Updated: 2023/07/26 11:47:03 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	process_word(char *cmd, int *c, t_lexer **head)
{
	c[2] = c[0];
	while (c[5] && cmd[c[0]] && cmd[c[0]] != '"' && cmd[c[0]] != '$')
		c[0]++;
	while (!c[5] && cmd[c[0]] && cmd[c[0]] != ' ' && cmd[c[0]] != '\t'
		&& cmd[c[0]] != '|' && cmd[c[0]] != '<' && cmd[c[0]] != '>'
		&& cmd[c[0]] != '"' && cmd[c[0]] != '\'' && cmd[c[0]] != '$')
		c[0]++;
	if (c[0] != c[2])
		lexer_add_back(head, lexer_new(ft_substr(cmd, c[2], c[0] - c[2]),
				++c[1], WORD));
}
