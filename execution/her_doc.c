/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:05:54 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/08/11 00:03:02 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*heredoc_handle_var(int *counter, char *tmp, char *line, t_env **env)
{
	char	*var_value;
	char	*var;
	int		i;
	int		j;

	i = *counter;
	j = i + 1;
	while (tmp[j] && (ft_isalnum(tmp[j]) || tmp[j] == '_'))// || tmp[j] == '?'))
		j++;
	if (tmp[j] == '?')
	{
		var_value = ft_itoa(g_exit_status);
		j++;
	}
	else
	{
		var = ft_substr(tmp, i + 1, j - i - 1);
		var_value = get_envvar(env, var);
		if (!var_value)
			var_value = ft_strdup("");
		free(var);
	}
	line = ft_strjoin(line, var_value);
	free(var_value);
	*counter = j;
	return (line);
}

char	*herdoc_expand(char *line, t_env **env)
{
	char	*var;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strdup(line);
	free(line);
	line = ft_strdup("");
	while (tmp[i])
	{
		if (tmp[i] == '$' && (ft_isalnum(tmp[i + 1]) || tmp[i + 1] == '_'
			|| tmp[i + 1] == '?'))
			line = heredoc_handle_var(&i, tmp, line, env);
		else
		{
			var = ft_substr(tmp, i, 1);
			line = ft_strjoin(line, var);
			free(var);
			i++;
		}
	}
	free(tmp);
	return (line);
}

char	*heredoc_file(void)
{
	char	*filenam;
	char	*n;
	int		i;

	i = 0;
	n = ft_itoa(i);
	filenam = ft_strjoin(ft_strdup("/tmp/herdoc"), n);
	while (access(filenam, F_OK) != -1)
	{
		free(filenam);
		free(n);
		i++;
		n = ft_itoa(i);
		filenam = ft_strjoin(ft_strdup("/tmp/herdoc"), n);
	}
	free(n);
	return (filenam);
}

void	heredoc_main_loop(int herdoc_fd, t_env **env, char *deli)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(deli, line, ft_max(ft_strlen(deli),
					ft_strlen(line))) || g_exit_status == -1)
		{
			free(line);
			break ;
		}
		line = herdoc_expand(line, env);
		write(herdoc_fd, line, ft_strlen(line));
		write(herdoc_fd, "\n", 1);
		free(line);
	}
}

int	here_doc(char *deli, t_env **env)
{
	int		fd;
	char	*filenam;
	int		herdoc_fd;

	filenam = heredoc_file();
	herdoc_fd = ft_open(filenam, (O_CREAT | O_RDWR | O_APPEND), 0644);
	setup_signal_handlers();
	heredoc_main_loop(herdoc_fd, env, deli);
	close_and_restore_signals(herdoc_fd);
	if (g_exit_status == -1)
	{
		free(filenam);
		return (-2);
	}
	fd = ft_open(filenam, O_RDONLY, 0644);
	free(filenam);
	return (fd);
}
