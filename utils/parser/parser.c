/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:57:28 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/08/10 03:48:17 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	extract_rdrxs(t_cmds **cmds, t_lexer **tmp, int *i)
{
	(*cmds)->rdrxs_array[(*i)++] = ft_strdup((*tmp)->data);
	(*tmp) = (*tmp)->next;
	if ((*tmp)->type == SPACE_)
		(*tmp) = (*tmp)->next;
	(*cmds)->rdrxs_array[(*i)++] = ft_strdup((*tmp)->data);
	(*tmp) = (*tmp)->next;
}

void	extract_arg(t_cmds **cmds, t_lexer **tmp, int *j)
{
	char	**p;
	int		i;

	i = 0;
	if ((*tmp)->type == SPACE_)
		(*tmp) = (*tmp)->next;
	else if ((*tmp) && (*tmp)->data && (*tmp)->type == EXEC_VAR)
	{
		p = ft_split((*tmp)->data, ' ');
		while (p[i])
		{
			(*cmds)->cmd[(*j)++] = p[i++];
		}
		(*tmp) = (*tmp)->next;
		free(p);
	}
	else
	{
		(*cmds)->cmd[(*j)++] = ft_strdup((*tmp)->data);
		(*tmp) = (*tmp)->next;
	}
}

void	retrieve_rdrxs(t_cmds **cmds)
{
	t_lexer	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = (*cmds)->cmd_nd_args;
	(*cmds)->rdrxs_array = ft_calloc(ft_lstsize(tmp) + 1, sizeof(char *));
	(*cmds)->cmd = ft_calloc(ft_lstsize(tmp) + 1, sizeof(char *));
	while (tmp)
	{
		if (type_is_redirection(tmp->type))
			extract_rdrxs(cmds, &tmp, &i);
		else
			extract_arg(cmds, &tmp, &j);
	}
}

void	*process_heredoc(t_cmds **cmds, t_env **env)
{
	int		i;
	int		j;
	char	**rdrxs;

	i = -1;
	while (cmds[++i])
	{
		j = -1;
		rdrxs = cmds[i]->rdrxs_array;
		cmds[i]->herdoc_fd = -1;
		while (rdrxs[++j])
		{
			if (!ft_strncmp(rdrxs[j], "<<", 2))
			{
				cmds[i]->herdoc_fd = here_doc(rdrxs[j + 1], env);
				if (g_exit_status == -1)
					return (NULL);
				else if (rdrxs[j + 2] && !ft_strncmp(rdrxs[j + 2], "<", 1))
					ft_close((*cmds)->herdoc_fd);
			}
		}
	}
	return ((void *)1);
}

t_cmds	**parser(t_lexer **mi, t_env **env)
{
	t_cmds	**cmds;
	int		i;

	i = -1;
	if (!mi || !*mi)
		return (NULL);
	if (!syntaxe_error(mi))
		return (free_lexer(mi), NULL);
	cmds = splited_cmds(mi);
	while (cmds[++i])
	{
		retrieve_rdrxs(&cmds[i]);
		cmds[i]->in_fd = -1;
		cmds[i]->out_fd = -1;
	}
	if (!process_heredoc(cmds, env))
	{
		g_exit_status = 1;
		return (free_cmds(cmds), NULL);
	}
	return (cmds);
}

	// i = 0;
	// while (cmds[i])
	// {
	// 	j = -1;
	// 	rdrxs = cmds[i]->rdrxs_array;
	// 	cmds[i]->herdoc_fd = -1;
	// 	while (rdrxs[++j])
	// 	{
	// 		if (!ft_strncmp(rdrxs[j], "<<", 2))
	// 		{
	// 			cmds[i]->herdoc_fd = here_doc(rdrxs[j + 1], env);
	// 			if (rdrxs[j + 2] && !ft_strncmp(rdrxs[j + 2], "<", 1))
	// 				ft_close((*cmds)->herdoc_fd);
	// 		}
	// 	}
	// 	i++;
	// }