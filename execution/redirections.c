/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:29:34 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/08/10 02:56:25 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*redirect_output(t_cmds **cmds, char **redrxs, int out_flag)
{
	if (!access(redrxs[1], F_OK) && access(redrxs[1], W_OK) == -1)
		return (error(strerror(errno), 1), NULL);
	else if (is_directory(redrxs[1]))
		return (error("minishell: is a directory", 1), NULL);
	if (out_flag == O_TRUNC)
	{
		(*cmds)->out_fd = ft_open(redrxs[1],
				(O_WRONLY | O_CREAT | O_TRUNC), 0644);
		if (redrxs[2] && !ft_strncmp(redrxs[2], ">", 1))
			ft_close((*cmds)->out_fd);
	}
	else if (out_flag == O_APPEND)
	{
		(*cmds)->out_fd = ft_open(redrxs[1],
				(O_WRONLY | O_CREAT | O_APPEND), 0644);
		if (redrxs[2] && !ft_strncmp(redrxs[2], ">", 1))
			ft_close((*cmds)->out_fd);
	}
	return ((void *)1);
}

void	*redirect_input(t_cmds **cmds, char **redrxs, int h)
{
	if (!h)
	{
		if (access(redrxs[1], F_OK) == -1 || access(redrxs[1], R_OK) == -1)
			return (error(strerror(errno), 1), NULL);
		else if (is_directory(redrxs[1]))
			return (error("minishell: is a directory", 1), NULL);
		else
			(*cmds)->in_fd = ft_open(redrxs[1], (O_RDONLY), 0644);
		if (redrxs[2] && !ft_strncmp(redrxs[2], "<", 1))
			ft_close((*cmds)->in_fd);
	}
	else if (h)
	{
		(*cmds)->in_fd = (*cmds)->herdoc_fd;
		if ((*cmds)->in_fd < -1)
			return (NULL);
	}
	return ((void *)1);
}

char	*redirect(t_cmds **cmds)
{
	char	**redrxs;
	char	*rtrn;
	int		i;

	i = 0;
	redrxs = (*cmds)->rdrxs_array;
	if (!redrxs || !redrxs[0])
		return ((void *)1);
	while (redrxs[i])
	{
		if (!ft_strncmp(redrxs[i], ">", ft_max(ft_strlen(redrxs[i]), 1)))
			rtrn = redirect_output(cmds, &redrxs[i], O_TRUNC);
		else if (!ft_strncmp(redrxs[i], ">>", 2))
			rtrn = redirect_output(cmds, &redrxs[i], O_APPEND);
		else if (!ft_strncmp(redrxs[i], "<", ft_max(ft_strlen(redrxs[i]), 1)))
			rtrn = redirect_input(cmds, &redrxs[i], 0);
		else if (!ft_strncmp(redrxs[i], "<<", 2))
			rtrn = redirect_input(cmds, &redrxs[i], 1);
		if (!rtrn)
			return (NULL);
		i += 2;
	}
	return ((void *)1);
}
