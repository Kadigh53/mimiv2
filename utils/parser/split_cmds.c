/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:20:16 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/07/28 20:10:27 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

unsigned int	cmds_nbr(t_lexer **mi)
{
	t_lexer			*tmp;
	unsigned int	i;

	i = 0;
	tmp = *mi;
	if (!tmp)
		return (1);
	while (tmp)
	{
		if (tmp->type == PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i + 1);
}

void	pop_pipe(t_lexer **tmp, t_lexer *pipe_node)
{
	if ((*tmp)->prev)
		(*tmp)->prev->next = NULL;
	if ((*tmp)->next)
		(*tmp)->next->prev = NULL;
	(*tmp) = (*tmp)->next;
	free(pipe_node->data);
	free(pipe_node);
}

t_cmds	**splited_cmds(t_lexer **mi)
{
	t_cmds	**cmds;
	t_lexer	*tmp;
	t_lexer	*pipe_node;
	int		i;

	i = 1;
	tmp = *mi;
	pipe_node = *mi;
	cmds = ft_calloc(cmds_nbr(mi) + 1, sizeof(t_cmds *));
	cmds[0] = ft_calloc(1, sizeof(t_cmds));
	cmds[0]->cmd_nd_args = *mi;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			pipe_node = tmp;
			cmds[i] = ft_calloc(1, sizeof(t_cmds));
			cmds[i++]->cmd_nd_args = tmp->next;
			pop_pipe(&tmp, pipe_node);
		}
		else
			tmp = tmp->next;
	}
	cmds[i] = NULL;
	return (cmds);
}
