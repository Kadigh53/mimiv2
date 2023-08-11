/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_inlexer_toarray.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:04:51 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/07/26 11:46:35 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

size_t	cmd_ndargs_size(t_lexer *cmd_nd_args)
{
	size_t	size;
	t_lexer	*tmp;

	size = 0;
	tmp = cmd_nd_args;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

void	cmd_inlexer_toarray(t_cmds **cmds)
{
	t_lexer	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cmds[i])
	{
		cmds[i]->cmd = ft_calloc(sizeof(char *),
				(cmd_ndargs_size(cmds[i]->cmd_nd_args) + 1));
		j = 0;
		tmp = cmds[i]->cmd_nd_args;
		while (tmp)
		{
			cmds[i]->cmd[j] = ft_strdup(tmp->data);
			tmp = tmp->next;
			j++;
		}
		cmds[i]->cmd[j] = NULL;
		i++;
	}
}
