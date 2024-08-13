/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_dbl_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeter <jpeter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:59:11 by jpeter            #+#    #+#             */
/*   Updated: 2024/06/19 11:27:06 by jpeter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_exec_dbl_pipe2(t_data *data)
{
	int	nbr;

	nbr = 1;
	while (data->prompt->type != CPRT || nbr != 0)
	{
		data->prompt = data->prompt->next;
		if (!data->prompt)
			break ;
		if (data->prompt->type == OPRT)
			nbr++;
		if (data->prompt->type == CPRT)
			nbr--;
	}
	return ;
}

int	ft_exec_dbl_pipe(t_data *data)
{
	ft_print_result(data);
	if (data->exit_code == 0)
	{
		while (data->prompt->type != ET)
		{
			if (data->prompt->type == OPRT)
				return (ft_exec_dbl_pipe2(data), data->exit_code);
			else if (data->prompt->type == CPRT)
				return (data->exit_code);
			data->prompt = data->prompt->next;
			if (data->prompt == NULL)
				return (data->exit_code);
		}
	}
	data->prompt = data->prompt->next;
	check_std(data);
	return (0);
}
