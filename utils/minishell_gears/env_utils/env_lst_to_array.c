/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_to_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:24:59 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/07/23 10:41:10 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	**envlist_toarray(t_env **env)
{
	char	**env_array;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = *env;
	env_array = ft_malloc(sizeof(char *) * (ft_envsize(*env) + 1));
	while (tmp)
	{
		env_array[i] = ft_strdup(tmp->env_var);
		tmp = tmp->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
