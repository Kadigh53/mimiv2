/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:05:47 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/08/08 03:11:33 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	_env(t_env **env)
{
	int		fd;
	t_env	*tmp;

	fd = 1;
	tmp = *env;
	g_exit_status = 0;
	while (tmp)
	{
		if (!tmp->env_or_export)
		{
			write(fd, tmp->env_var, ft_strlen(tmp->env_var));
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
}
