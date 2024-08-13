/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_command2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:59:11 by jpeter            #+#    #+#             */
/*   Updated: 2024/06/17 13:59:41 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	if_env(t_data *data)
{
	if (data->prompt->next == NULL)
		return (0);
	return (0);
}

int	if_exit(t_data *data)
{
	if (data->prompt->next == NULL)
		return (0);
	data->prompt = data->prompt->next;
	while (data->prompt->type <= CMD || data->prompt->type >= DOLLARS)
	{
		if ((data->prompt->type == OPRT) || (data->prompt->type == CPRT))
			break ;
		data->prompt->type = TEXTE;
		if (data->prompt->next == NULL)
			return (0);
		data->prompt = data->prompt->next;
	}
	data->prompt = data->prompt->prev;
	return (0);
}

int	if_exec(t_data *data)
{
	if (data->prompt->next == NULL)
		return (0);
	return (0);
}

int	if_execve(t_data *data)
{
	if (data->prompt->next == NULL)
		return (0);
	data->prompt = data->prompt->next;
	while (data->prompt->type >= DOLLARS || data->prompt->type <= CMD)
	{
		if ((data->prompt->type == OPRT) || (data->prompt->type == CPRT))
			break ;
		if (data->prompt->type != OPTION)
			data->prompt->type = TEXTE;
		if (data->prompt->next == NULL)
			return (0);
		data->prompt = data->prompt->next;
	}
	data->prompt = data->prompt->prev;
	return (0);
}
