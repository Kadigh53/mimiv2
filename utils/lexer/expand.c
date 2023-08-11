/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:53:31 by yel-hadd          #+#    #+#             */
/*   Updated: 2023/08/10 01:46:13 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_exit_status_var(t_lexer **ptr)
{
	char	*envvar;
	t_lexer	*node;

	node = *ptr;
	envvar = ft_itoa(g_exit_status);
	free(node->data);
	node->data = envvar;
	node->type = WORD;
}

void	node_type(t_lexer **node_addr)
{
	t_lexer	*node;
	t_lexer	*prev;

	node = *node_addr;
	prev = (*node_addr)->prev;
	if (node->index == 1)
		node->type = EXEC_VAR;
	else if (prev)
	{
		if (prev->type == PIPE
			|| (prev->type == SPACE_ && prev->prev->type == PIPE))
			node->type = EXEC_VAR;
		else
			node->type = WORD;
	}
	else
		node->type = WORD;
}

static void	handle_env_var(t_lexer **ptr, t_env **env)
{
	char	*envvar;
	t_lexer	*node;
	char	*tmp;

	node = *ptr;
	tmp = node->data;
	envvar = get_envvar(env, tmp + 1);
	free(node->data);
	if (!envvar)
		node->data = sdup("");
	else
		node->data = envvar;
	node_type(&node);
}

t_lexer	**expander(t_lexer **head, t_env **env)
{
	t_lexer	*node;

	node = *head;
	while (node)
	{
		if (node->type == H_REDIRECTION)
		{
			node = node->next;
			if (node && node->type == SPACE_)
					node = node->next;
			while (node && (node->type == WORD || node->type == VAR))
			{
				node->type = WORD;
				node = node->next;
			}
		}
		if (node)
		{
			if (node->data[1] == '?' && node->type == VAR)
				handle_exit_status_var(&node);
			else if (node->type == VAR)
				handle_env_var(&node, env);
			node = node->next;
		}
	}
	return (head);
}

	// if (node->index == 1)
	// 	node->type = EXEC_VAR;
	// else if (prev)
	// {
	// 	if (prev->type == PIPE
	// 		|| (prev->type == SPACE_ && prev->prev->type == PIPE))
	// 		node->type = EXEC_VAR;
	// 	else
	// 		node->type = WORD;
	// }
	// else
	// 	node->type = WORD;