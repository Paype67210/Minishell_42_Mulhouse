/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_prt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:59:11 by jpeter            #+#    #+#             */
/*   Updated: 2024/06/17 13:49:51 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_exec_prt2(t_data *data)
{
	pid_t	pid;

	if (data->prompt->type == EXEC || data->prompt->type == CMD)
	{
		if (pipe(data->fd) == -1)
			return (130);
		pid = fork();
		if (pid == -1)
			return (130);
		if (pid == 0)
			data->exit_code = which_command(data);
		else if (pid > 0)
			data->exit_code = parent(data);
	}
	else
		data->exit_code = which_command(data);
	data->prompt = data->prompt->next;
	return (data->exit_code);
}

int	ft_exec_prt(t_data *data)
{
	int		nbr;

	if (((data->prompt->prev->type == OU) && (data->exit_code == 0)) || \
		((data->prompt->prev->type == ET) && (data->exit_code != 0)))
	{
		nbr = 1;
		while (data->prompt->type != CPRT || nbr > 0)
		{
			data->prompt = data->prompt->next;
			if (data->prompt->type == OPRT)
				nbr++;
			if (data->prompt->type == CPRT)
				nbr--;
		}
		return (data->exit_code);
	}
	data->exit_code = 0;
	data->prompt = data->prompt->next;
	while (data->prompt->type != CPRT)
	{
		data->exit_code = ft_exec_prt2(data);
		if (data->exit_code == 130)
			return (data->exit_code);
	}
	return (data->exit_code);
}
