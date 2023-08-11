/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 20:32:16 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/08/10 03:51:09 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	number_of_spaces(char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			while (str[i] == ' ' && str[i])
				i ++;
		}
		if (i != 0 && str[i - 1] == ' ')
			j ++;
		i ++;
	}
	return (i);
}

int	ft_lstsize(t_lexer *lst)
{
	t_lexer			*tmp;
	unsigned int	i;

	i = 0;
	if (!lst)
		return (0);
	tmp = lst;
	while (tmp)
	{
		if (tmp->type == EXEC_VAR)
			i += number_of_spaces(tmp->data);
		else
			i++;
		tmp = tmp->next;
	}
	return (i);
}
