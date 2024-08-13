/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:59:11 by jpeter            #+#    #+#             */
/*   Updated: 2024/06/21 13:19:50 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	trucmuche(t_data *data)
{
	while (data->prompt->type != PIPE)
		data->prompt = data->prompt->next;
	data->prompt = data->prompt->next;
	while (data->prompt)
	{
		if (data->prompt->type == 29)
			data->prompt = data->prompt->next;
		else
			break ;
	}
	data->std_in = NULL;
	data->std_out->content = NULL;
	data->std_out->type = VIDE;
	usleep(1000);
	return ;
}

int	start_fils(t_data *data, int i)
{
	if (data->result)
		data->std_in = data->result;
	data->result = NULL;
	data->num_pid[i / 2] = fork();
	if (data->num_pid[i / 2] == -1)
		return (ft_msg("Error: ", "Fork failed\n", NULL, EXIT_FAILURE));
	else if (data->num_pid[i / 2] == 0)
		fils(data, i);
	return (0);
}

void	ft_blurp(t_data *data)
{
	data->prompt = data->prompt->prev;
	ft_lstremove(&data->prompt, data->prompt->next, NULL);
	ft_lstremove(&data->prompt, data->prompt->next, NULL);
	return ;
}
