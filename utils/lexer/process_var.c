/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 11:18:20 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/08/10 01:47:46 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_var_char(int c)
{
	if (ft_isdigit(c) || ft_isalpha(c) || c == '_')
		return (1);
	return (0);
}

void	skip_var_characters(char *cmd, int *c)
{
	c[7] = 1;
	c[8] = c[0];
	c[0]++;
	while (is_var_char(cmd[c[0]]) || cmd[c[0]] == '?')
	{
		c[0]++;
		if (cmd[c[0] - 1] == '?')
			break ;
	}
}

void	process_var(char *cmd, int *c, t_lexer **head)
{
	if (cmd[c[0]] == '$' && (!cmd[c[0] + 1] || cmd[c[0] + 1] == ' ' || cmd[c[0] + 1] == '$'))
	{
		lexer_add_back(head, lexer_new(sdup("$"), ++c[1], WORD));
		c[0]++;
	}
	else if (cmd[c[0]] == '$')
	{
		skip_var_characters(cmd, c);
		if (c[0] != c[8])
		{
			lexer_add_back(head, lexer_new(ft_substr(cmd, c[8], c[0]
						- c[8]), ++c[1], VAR));
		}
		process_var(cmd, c, head);
	}
}
