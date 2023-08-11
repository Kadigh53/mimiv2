/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:06:37 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/08/08 03:11:56 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	flags(char **args, bool *n)
{
	int	j;
	int	i;

	j = 0;
	if (!args[0] || !args)
		return (0);
	while (args[j] && ft_strncmp(args[j], "-n", 2) == 0)
	{
		i = 1;
		while (args[j][i] && args[j][i] == 'n')
			i++;
		if (i == (int)ft_strlen(args[j]))
			*n = true;
		else
			return (j);
		j++;
	}
	return (j);
}

void	_echo(char **args)
{
	int		i;
	int		fd;
	bool	n;

	fd = STDOUT_FILENO;
	g_exit_status = 0;
	n = false;
	i = flags(args, &n);
	if (!args[0] || !args)
	{
		if (!n)
			write(fd, "\n", 1);
		return ;
	}
	while (args[i])
	{
		write(fd, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (!n)
		write(fd, "\n", 1);
	return ;
}
