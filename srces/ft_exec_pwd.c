/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:51:27 by pdeson            #+#    #+#             */
/*   Updated: 2024/06/21 10:56:18 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_exec_pwd2(t_data *data)
{
	while (data->prompt->type <= CMD || data->prompt->type >= DOLLARS)
	{
		data->prompt = data->prompt->next;
		if (data->prompt == NULL)
			break ;
	}
	return (0);
}

int	ft_exec_pwd(t_data *data)
{
	char	*buffer;

	if (data->prompt->next != NULL)
	{
		if (data->prompt->next->type == OPTION)
		{
			printf("Mini: pwd: %s: invalid option\n", \
				(char *)data->prompt->next->content);
			ft_exec_pwd2(data);
			return (data->result = NULL, 2);
		}
	}
	ft_exec_pwd2(data);
	if (data->result)
		data->result = NULL;
	buffer = getcwd(NULL, 0);
	data->result = ft_strjoin(ft_strdup(buffer), "\n");
	free(buffer);
	return (data->exit_code);
}
