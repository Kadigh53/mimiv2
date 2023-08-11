/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_abs_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:17:50 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/08/10 22:51:20 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	free_array(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*get_abs_cmd(char *cmd, char *path)
{
	char	**path_array;
	char	*abs_cmd;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strjoin(ft_strdup("/"), cmd);
	path_array = ft_split(path, ':');
	while (path_array[i])
	{
		abs_cmd = ft_strjoin(ft_strdup(path_array[i]), tmp);
		if (!access(abs_cmd, X_OK))
		{
			free(tmp);
			free_array(path_array);
			return (abs_cmd);
		}
		free(abs_cmd);
		i++;
	}
	free(tmp);
	free_array(path_array);
	return (NULL);
}

char	*absolute_cmd(char *cmd)
{
	char 	*cwd;
	char 	*abs_cmd;

	cwd = getcwd(NULL, 0);
	cwd = ft_strjoin(cwd, "/");
	if (cmd[0] == '.')
		abs_cmd = ft_strjoin(ft_strdup(cwd), cmd);
	else
		abs_cmd = ft_strdup(cmd);
	if (is_directory(abs_cmd))
		return (error("minishell: command is a directory", 126), NULL);
	if (!access(abs_cmd, X_OK))
		return (ft_strdup(abs_cmd));
	else if (!access(abs_cmd, F_OK))
		return (error("minishell: permission denied", 126), NULL);
	return (abs_cmd);
}

char	*get_cmd_path(char *cmd, t_env **env)
{
	t_env	*tmp;
	char	*cmd_path;

	tmp = *env;
	if (ft_strchr(cmd, '/'))
		return (absolute_cmd(cmd));
	while (tmp)
	{
		if (!ft_strncmp(tmp->env_var, "PATH=", 5) && !tmp->env_or_export)
		{
			cmd_path = get_abs_cmd(cmd, tmp->env_var + 5);
			if (!cmd_path)
				error("error:command not found", 127);
			return (cmd_path);
		}
		tmp = tmp->next;
	}
	if (!tmp)
		error("minishell: no such file or directory", 127);
	return (NULL);
}
