/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:55:03 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/08/08 03:12:03 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

size_t	env_var_len(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}

void	pop_env_node(t_env **head, t_env *node)
{
	if (!node->prev)
	{
		*head = node->next;
		if (node->next)
			node->next->prev = NULL;
	}
	else if (!node->next)
		node->prev->next = NULL;
	else
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	free(node->env_var);
	free(node);
}

void	unset_var(t_env **env, char *var)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp(tmp->env_var, var, ft_max(ft_strlen(var),
					env_var_len(tmp->env_var))) == 0)
		{
			pop_env_node(env, tmp);
			break ;
		}
		tmp = tmp->next;
	}
	return ;
}

void	_unset(t_env **env, char **args)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = *env;
	g_exit_status = 0;
	while (args[i])
	{
		if (!valid_argument(args[i]))
		{
			i++;
			continue ;
		}
		unset_var(env, args[i]);
		i++;
	}
}
