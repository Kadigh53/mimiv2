/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envvar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 19:48:54 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/07/23 16:01:14 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

size_t	var_len(char *var)
{
	size_t	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}

char	*get_envvar(t_env **env, char *str)
{
	t_env	*tmp;
	char	*var_value;
	int		len;

	tmp = *env;
	while (tmp)
	{
		len = var_len(tmp->env_var);
		if (!ft_strncmp(tmp->env_var, str, ft_max(ft_strlen(str), len)))
		{
			var_value = ft_substr(tmp->env_var, len + 1, ft_strlen(tmp->env_var)
					- len - 1);
			return (var_value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
