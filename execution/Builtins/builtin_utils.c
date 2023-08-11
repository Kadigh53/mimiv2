/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:05:19 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/08/02 19:51:49 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_assigned(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i + 1] == '=' && arg[i] == '+')
			return (i);
		else if (arg[i] == '=')
			return (i);
	}
	return (0);
}

void	update_env(t_env *tmp, char *arg)
{
	int		i;
	char	*to_append;

	if (arg[is_assigned(arg)] == '+')
	{
		i = is_assigned(tmp->env_var);
		if (i)
			to_append = ft_strdup(ft_strchr(arg, '=') + 1);
		else
			to_append = ft_strdup(ft_strchr(arg, '='));
		tmp->env_var = ft_strjoin(tmp->env_var, to_append);
		free(to_append);
	}
	else
	{
		free(tmp->env_var);
		tmp->env_var = ft_strdup(arg);
	}
	tmp->env_or_export = 0;
}

void	export_to_env(t_env **env, char *arg, int var_len)
{
	t_env	*tmp;
	t_env	*node;
	char	*var;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->env_var, arg, var_len))
		{
			update_env(tmp, arg);
			return ;
		}
		tmp = tmp->next;
	}
	var = ft_strjoin(ft_substr(arg, 0, is_assigned(arg)), ft_strchr(arg, '='));
	node = ft_envnew(var);
	node->env_or_export = 0;
	ft_envadd_back(env, node);
}
