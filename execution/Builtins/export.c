/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:09:19 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/08/08 03:11:23 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	export_with_noarg(t_env **env)
{
	t_env	*node;
	int		fd;

	fd = 1;
	node = *env;
	while (node)
	{
		if (node->env_var[0] == '_')
		{
			node = node->next;
			continue ;
		}
		write(fd, "declare -x ", 11);
		write(fd, node->env_var, ft_strlen(node->env_var));
		write(fd, "\n", 1);
		node = node->next;
	}
	return ;
}

void	export_only(t_env **env, char *arg)
{
	t_env	*tmp;
	t_env	*node;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->env_var, arg, ft_strlen(arg)))
			return ;
		tmp = tmp->next;
	}
	node = ft_envnew(ft_strdup(arg));
	node->env_or_export = 1;
	ft_envadd_back(env, node);
	return ;
}

int	valid_argument(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
	{
		error("not a valid identifier", 1);
		return (0);
	}
	while (arg[i] != '=' && arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			return (1);
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			error("not a valid identifier", 1);
			return (0);
		}
		i++;
	}
	return (1);
}

void	_export(t_env **env, char **args, int flag)
{
	int	i;

	i = 0;
	g_exit_status = 0;
	if ((!args || !args[0]) && !flag)
	{
		export_with_noarg(env);
		return ;
	}
	while (args[i])
	{
		if (flag == 0)
		{
			if (!valid_argument(args[i]))
				return ;
		}
		if (is_assigned(args[i]))
			export_to_env(env, args[i], is_assigned(args[i]));
		else
			export_only(env, args[i]);
		i++;
	}
}
