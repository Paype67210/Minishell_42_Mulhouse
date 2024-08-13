/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeter <jpeter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:59:11 by jpeter            #+#    #+#             */
/*   Updated: 2024/06/19 13:02:57 by jpeter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

#define BUFFER_SIZE 8000

int	count_pipe(t_list *lst)
{
	int		i;
	t_list	*buffer;

	buffer = lst;
	i = 0;
	if (buffer->next == NULL)
		return (0);
	while (buffer)
	{
		while (!(buffer->type >= HEREDOC && buffer->type <= WILDCARD))
		{
			if (buffer->next == NULL)
				return (i);
			buffer = buffer->next;
		}
		if (buffer->type != PIPE)
			return (i);
		i++;
		buffer = buffer->next;
	}
	return (i);
}

void	ft_sig_handler3(int sig)
{
	return ((void)sig);
}

void	ft_exec_stdin(t_data *data)
{
	data->fd[0] = open(".buff", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->fd[1] == -1)
	{
		perror("open");
		exit(errno);
	}
	write(data->fd[0], data->std_in, ft_strlen(data->std_in));
	close(data->fd[0]);
	data->fd[0] = open(".buff", O_RDONLY, 0644);
	if (data->fd[1] == -1)
	{
		perror("open");
		exit(errno);
	}
	if (dup2(data->fd[0], STDIN_FILENO) == -1)
		exit(errno);
	close(data->fd[0]);
	return ;
}

void	ft_exec_stdout(t_data *data)
{
	if (data->std_out->type == DIROUT2)
		data->fd[1] = open(data->std_out->content, \
			O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		data->fd[1] = open(data->std_out->content, \
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->fd[1] == -1)
	{
		perror("open");
		exit(errno);
	}
	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
		exit(errno);
	close(data->fd[1]);
	return ;
}
