/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 14:11:06 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/08/10 02:09:37 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer(t_lexer **mi)
{
	t_lexer	*tmp;
	t_lexer	*tmp2;

	if (!mi || !*mi)
		return ;
	tmp = *mi;
	while (tmp)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2->data);
		free(tmp2);
	}
}

void	free_envirenment(t_env *env_lst)
{
	t_env	*tmp;

	while (env_lst)
	{
		tmp = env_lst;
		env_lst = env_lst->next;
		if (tmp->env_var)
			free(tmp->env_var);
		if (tmp)
			free(tmp);
	}
	return ;
}

void	free_unecmds(t_cmds *tmp)
{
	int		j;
	t_lexer	*next;
	t_lexer	*lex_node;

	j = -1;
	while (tmp->cmd[++j])
	{
		// printf("am here		%s\n", tmp->cmd[j]);
		free(tmp->cmd[j]);
	}
	free(tmp->cmd);
	j = -1;
	while (tmp->rdrxs_array[++j])
		free(tmp->rdrxs_array[j]);
	free(tmp->rdrxs_array);
	lex_node = tmp->cmd_nd_args;
	while (lex_node)
	{
		next = lex_node->next;
		free(lex_node->data);
		free(lex_node);
		lex_node = next;
	}
}

void	free_cmds(t_cmds **cmds)
{
	t_cmds	*tmp;
	int		i;

	i = 0;
	while (cmds[i])
	{
		tmp = cmds[i];
		free_unecmds(tmp);
		free(tmp);
		i++;
	}
	free(cmds);
	cmds = NULL;
	return ;
}
