/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_single_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:10:07 by yel-hadd          #+#    #+#             */
/*   Updated: 2023/08/03 05:31:25 by aaoutem-         ###   ########.fr       */
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

void	next_to_sq(char *cmd, int *c, t_lexer **head)
{
	if (!c[6])
		return ;
	c[2] = c[0];
	while (c[6] && cmd[c[0]] && cmd[c[0]] != '\'')
		c[0]++;
	if (cmd[c[0]] == '\'')
	{
		c[4]++;
		c[6] = 0;
	}
	if (c[0] != c[2] && cmd[c[0]] != '\0')
		lexer_add_back(head, lexer_new(ft_substr(cmd, c[2], c[0] - c[2]),
				++c[1], WORD));
}

void	process_single_quote(char *cmd, int *c, t_lexer **head)
{
	if (cmd[c[0]] == '\'')
	{
		if (c[4] % 2 == 0)
		{
			c[6] = 1;
			c[0]++;
			next_to_sq(cmd, c, head);
		}
		c[4]++;
		c[0]++;
	}
}

/*
void	process_single_quote(char *cmd, int *c, t_lexer **head)
{
	if (cmd[c[0]] == '\'')
	{
		if (c[4] % 2 == 0)
			lexer_add_back(head, lexer_new(sdup("'"), ++c[1], sdup("1st_s")));
		else
			lexer_add_back(head, lexer_new(sdup("'"), ++c[1], sdup("2nd_s")));
		c[4]++;
		c[0]++;
	}
}
*/