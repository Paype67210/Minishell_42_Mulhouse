/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:59:11 by jpeter            #+#    #+#             */
/*   Updated: 2024/06/21 10:24:57 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_exec_pipe(t_data *data)
{
	data->prompt = data->prompt->next;
	if (data->std_out->content)
		ft_print_result(data);
	if (data->result)
		data->std_in = data->result;
	else
		data->std_in = "";
	data->result = NULL;
	check_std(data);
	return (0);
}
