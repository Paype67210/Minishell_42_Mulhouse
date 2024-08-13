/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:35:32 by pdeson            #+#    #+#             */
/*   Updated: 2024/06/21 13:12:35 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_print_result(t_data *data)
{
	int	fd;

	fd = 0;
	if (data->result)
	{
		if (data->std_out->content && data->std_out->type == DIROUT2)
		{
			fd = open(data->std_out->content, O_WRONLY | O_APPEND, 0644);
			ft_fprintf(fd, "%s", data->result);
		}
		else if (data->std_out->content && data->std_out->type == DIROUT)
		{
			fd = open(data->std_out->content, O_WRONLY | O_TRUNC, 0644);
			ft_fprintf(fd, "%s", data->result);
		}
		else
			ft_fprintf(1, "%s", data->result);
	}
	if (fd != 0)
		close(fd);
	ft_run_malloc(2, data->result);
	data->result = NULL;
	data->std_out->content = NULL;
	data->std_out->type = VIDE;
	data->std_in = NULL;
}

void	ft_exit(t_data *data)
{
	ft_fprintf(data->fd_log, "FERMETURE MINISHELL\n");
	close(data->fd_log);
	if (access(".ctrlc", F_OK) == 0)
		unlink(".ctrlc");
	ft_run_malloc(4);
	while (data->exit_code < 0)
		data->exit_code = (256 + data->exit_code);
	data->exit_code = data->exit_code % 256;
	printf("exit\n");
	exit (data->exit_code);
}
