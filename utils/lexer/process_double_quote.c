/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_double_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:08:25 by yel-hadd          #+#    #+#             */
/*   Updated: 2023/08/03 05:32:02 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
// the c array is used to keep track of various counters
// I implemented this technique to comply with the norm
// (max variables per function)
// c[0] is used to keep track of the index of the current character
// c[1] is used to keep track of the index of the current token
// * c[2] is used to keep track of the lenght of the current word
// c[3] is used to keep track of the number of double quotes
// c[4] is used to keep track of the number of single quotes
// c[5] is used to keep tack of the status of the current token,
// in double quotes or not
// c[6] is used to keep tack of the status of the current token,
// in single quotes or not
// c[7] is used to keep tack of the status of the current token,
// in env variable quotes or not
// * c[8] is used to keep track of the lenght of the current variable
*/

void	next_to_dq(char *cmd, int *c, t_lexer **head)
{
	if (!c[5])
		return ;
	c[2] = c[0];
	while (c[5] && cmd[c[0]] && cmd[c[0]] != '"' && cmd[c[0]] != '$')
		c[0]++;
	if (cmd[c[0]] == '"')
		c[5] = 0;
	if (c[0] != c[2] && cmd[c[0]] != '\0')
		lexer_add_back(head, lexer_new(ft_substr(cmd, c[2], c[0] - c[2]),
				++c[1], WORD));
}

void	process_double_quote(char *cmd, int *c, t_lexer **head)
{
	if (cmd[c[0]] == '"')
	{
		if (c[3] % 2 == 0)
		{
			c[5] = 1;
			c[0]++;
			c[3]++;
			next_to_dq(cmd, c, head);
		}
		else
		{
			c[5] = 0;
			c[0]++;
			c[3]++;
		}
		process_var(cmd, c, head);
	}
}
