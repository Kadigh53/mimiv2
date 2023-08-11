/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_newenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:04:26 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/06/26 18:03:34 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**get_newenv(t_env **env)
{
	char	**new_env;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = *env;
	new_env = malloc(sizeof(char *) * (ft_envsize(*env) + 1));
	if (!new_env)
		return (NULL);
	while (tmp)
	{
		if (tmp->env_or_export == 0)
		{
			new_env[i] = ft_strdup(tmp->env_var);
			i++;
		}
		tmp = tmp->next;
	}
	new_env[i] = NULL;
	return (new_env);
}
