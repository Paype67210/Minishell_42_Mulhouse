/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:59:11 by jpeter            #+#    #+#             */
/*   Updated: 2024/06/21 13:19:17 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	check_std3(t_data *data)
{
	if (data->prompt->type == HEREDOC)
		return (0);
	if (access(data->prompt->next->content, F_OK) < 0)
	{
		printf("Mini: %s: No such file or directory\n", \
			(char *)data->prompt->next->content);
		return (1);
	}
	else if (access(data->prompt->next->content, R_OK) < 0)
	{
		printf("Mini: %s: Permission denied\n", \
			(char *)data->prompt->next->content);
		return (1);
	}
	return (0);
}

int	check_std2(t_data *data, int i, int fd)
{
	if (data->prompt->type == DIROUT || data->prompt->type == DIROUT2)
	{
		data->std_out->content = data->prompt->next->content;
		data->std_out->type = data->prompt->type;
		if (data->prompt->type == DIROUT2)
			fd = open(data->std_out->content, O_CREAT | O_WRONLY | \
				O_APPEND, 0644);
		else
			fd = open(data->std_out->content, O_CREAT | O_WRONLY | \
				O_TRUNC, 0644);
		ft_blurp(data);
		close(fd);
	}
	else if (data->prompt->type == DIRIN2 || data->prompt->type == HEREDOC)
	{
		i = check_std3(data);
		if (data->prompt->type == DIRIN2)
			ft_exec_redi_ipt(data);
		else
			data->std_in = ft_strdup(data->prompt->next->content);
		ft_blurp(data);
	}
	return (i);
}

int	check_std(t_data *data)
{
	t_list	*buffer;

	buffer = data->prompt;
	while (buffer->type == DIROUT || buffer->type == DIROUT2 || \
		buffer->type == DIRIN2 || buffer->type == HEREDOC)
	{
		buffer = buffer->next->next;
		if (!buffer)
			break ;
	}
	while (data->prompt->type != ET && data->prompt->type != OU && \
		data->prompt->type != CPRT && data->prompt->type != PIPE)
	{
		if (check_std2(data, 0, 0) != 0)
			return (1);
		if (data->prompt->next == NULL)
			break ;
		data->prompt = data->prompt->next;
	}
	data->prompt = buffer;
	return (0);
}

int	close_all(t_data *data, int i)
{
	int		j;

	j = 0;
	if (!data->pipes)
		return (i);
	while (j != (data->nb_pipes * 2))
	{
		if (data->pipes[j] != -1)
		{
			close(data->pipes[j]);
			data->pipes[j] = -1;
		}
		j++;
	}
	return (i);
}

void	two_close(t_data *data, int i)
{
	if (i != 0)
		close(data->pipes[i - 2]);
	if (i != (data->nb_pipes * 2))
		close(data->pipes[i + 1]);
	return ;
}
