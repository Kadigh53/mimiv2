/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:34:09 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/07/26 13:10:32 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*shlvl(char *shlvl)
{
	char	*shlvl_var;
	char	*lvl;
	int		i;

	i = 0;
	while (shlvl[i] && shlvl[i] != '=')
		i++;
	lvl = ft_itoa(ft_atoi(shlvl + i + 1) + 1);
	shlvl_var = ft_strjoin(ft_strdup("SHLVL="), lvl);
	free(lvl);
	return (shlvl_var);
}

t_env	*emergency_env(void)
{
	t_env	*node;
	t_env	*tmp;
	t_env	*tmp0;
	char	*pwd;

	node = ft_envnew(ft_strdup("SHLVL=1"));
	node->env_or_export = 0;
	tmp = ft_envnew(
			ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:"));
	tmp->env_or_export = 0;
	ft_envadd_back(&node, tmp);
	pwd = getcwd(NULL, 0);
	tmp0 = ft_envnew(ft_strjoin(ft_strdup("PWD="), pwd));
	ft_envadd_back(&node, tmp0);
	free(pwd);
	return (node);
}

t_env	*set_env(char **envp)
{
	int		i;
	t_env	*env;
	t_env	*node;

	i = -1;
	env = NULL;
	if (!envp || !*envp)
		env = emergency_env();
	else
	{
		while (envp[++i])
		{
			if (!ft_strncmp(envp[i], "SHLVL=", 6))
				node = ft_envnew(shlvl(envp[i]));
			else
				node = ft_envnew(ft_strdup(envp[i]));
			node->env_or_export = 0;
			if (!env)
				env = node;
			else
				ft_envadd_back(&env, node);
		}
	}
	return (env);
}
