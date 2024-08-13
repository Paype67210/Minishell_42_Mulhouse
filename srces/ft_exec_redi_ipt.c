/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_redi_ipt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeter <jpeter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:59:11 by jpeter            #+#    #+#             */
/*   Updated: 2024/06/19 14:40:42 by jpeter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

#define BUFFER_SIZE 8000

int	ft_exec_redi_ipt(t_data *data)
{
	char	*buffer;

	if (data->exit_code != 0)
		return (idk(data));
	if (data->prompt->next == NULL)
		return (1);
	data->fd[0] = open(data->prompt->next->content, O_RDONLY, 0644);
	if (data->fd[0] == -1 && data->prompt->type == FILE1)
	{
		printf("Mini: %s: No such file or directory\n", \
			(char *)data->prompt->content);
		return (data->result = NULL, 1);
	}
	buffer = (char *)ft_run_malloc(1, BUFFER_SIZE * sizeof(char));
	if (read(data->fd[0], buffer, (BUFFER_SIZE - 1)) == -1 || !buffer)
		return (1);
	buffer[ft_strlen(buffer)] = '\0';
	return (data->std_in = buffer, close(data->fd[0]));
}
