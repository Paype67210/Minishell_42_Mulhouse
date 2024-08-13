/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:19:00 by pdeson            #+#    #+#             */
/*   Updated: 2024/06/21 10:55:52 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_exec_env(t_data *data)
{
	t_list	*buffer;

	data->prompt = data->prompt->next;
	if (data->result)
		data->result = NULL;
	if (data->prompt)
	{
		if ((data->prompt->type <= CMD || data->prompt->type >= DOLLARS) \
			&& (data->prompt->type < OPRT))
		{
			printf("env: %s: No such file or directory\n", \
				(char *)data->prompt->content);
			return (127);
		}
	}
	buffer = ft_lstfirst(data->envp_bis);
	while (buffer && buffer->content)
	{
		if (buffer->type == VIDE)
			data->result = ft_strjoin(ft_strjoin(data->result, \
				(char *)(buffer->content)), "\n");
		buffer = buffer->next;
	}
	return (data->exit_code);
}
