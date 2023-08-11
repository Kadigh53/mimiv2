/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 19:58:29 by yel-hadd          #+#    #+#             */
/*   Updated: 2023/08/03 05:32:24 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
	the c array is used to keep track of various counters
	I implemented this technique to comply with the norm
	(max variables per function)
	
	c[0] is used to keep track of the index of the current character
	c[1] is used to keep track of the index of the current token
	* c[2] is used to keep track of the lenght of the current word
	c[3] is used to keep track of the number of double quotes
	c[4] is used to keep track of the number of single quotes
	c[5] is used to keep tack of the status of the current token,
	in double quotes or not
	c[6] is used to keep tack of the status of the current token,
	in single quotes or not
	c[7] is used to keep tack of the status of the current token,
	in env variable quotes or not
	* c[8] is used to keep track of the lenght of the current variable
*/

t_lexer	**remove_quotes(t_lexer **head)
{
	t_lexer	*tmp;
	t_lexer	*next;

	tmp = *head;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->type == FIRST_D || tmp->type == SECOND_D)
			pop_node(head, tmp);
		else if (tmp->type == FIRST_S || tmp->type == SECOND_S)
			pop_node(head, tmp);
		tmp = next;
	}
	return (head);
}

void	process_space(char *cmd, int *c, t_lexer **head)
{
	while (cmd[c[0]] == ' ' || cmd[c[0]] == '\t')
		c[0]++;
	lexer_add_back(head, lexer_new(sdup(" "), ++c[1], SPACE_));
}

t_lexer	*lexer(char *cmd, t_env **env)
{
	t_lexer	*head;
	int		c[9];

	ft_init_vars(&head, c, 9);
	while (cmd[c[0]])
	{
		if (!cmd[c[0]])
			return (NULL);
		if ((cmd[c[0]] == ' ' || cmd[c[0]] == '\t'))
		{
			process_space(cmd, c, &head);
			continue ;
		}
		process_pipe(cmd, c, &head);
		process_single_quote(cmd, c, &head);
		process_double_quote(cmd, c, &head);
		process_left_redirection(cmd, c, &head);
		process_right_redirection(cmd, c, &head);
		process_var(cmd, c, &head);
		process_word(cmd, c, &head);
	}
	if (c[4] % 2 != 0 || c[3] % 2 != 0)
		return (error("minishell : syntax error unclosed quote", 1),
			free_lexer(&head), NULL);
	return (fix_index(merge_words(expander(&head, env))));
}
