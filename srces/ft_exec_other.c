/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_other.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:59:11 by jpeter            #+#    #+#             */
/*   Updated: 2024/06/21 10:05:04 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_exec_other(t_data *data)
{
	if (data->exit_code != 0)
		return (idk(data));
	if (!data->prompt->content || ft_strlen(data->prompt->content) == 0)
		return (data->prompt = data->prompt->next, 0);
	data->exit_code = 127;
	if (chdir(data->prompt->content) == 0)
	{
		printf("Mini: %s: Is a directory\n", (char *)data->prompt->content);
		chdir(data->path);
		data->exit_code = 126;
	}
	else if (strchr(data->prompt->content, '/') != NULL)
		printf("Mini: %s: No such file or directory\n", \
			(char *)data->prompt->content);
	else
		printf("%s: command not found\n", (char *)data->prompt->content);
	while (data->prompt)
	{
		if (data->prompt->type >= DIROUT && data->prompt->type <= WILDCARD)
			break ;
		data->prompt = data->prompt->next;
	}
	return (data->exit_code);
}
