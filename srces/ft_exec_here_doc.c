/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:59:11 by jpeter            #+#    #+#             */
/*   Updated: 2024/06/17 16:00:57 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

#define BUFFER_SIZE 8000

void	send_buffer(t_data *data)
{
	data->fd[0] = open(".buff", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	write(data->fd[0], data->std_in, ft_strlen(data->std_in));
	close(data->fd[0]);
	return ;
}

int	ft_exec_here_doc_2(t_data *data, char *buffer)
{
	data->std_in = "";
	if (buffer)
		data->std_in = ft_strjoin(ft_strdup(buffer), "\n");
	ft_fprintf(1, "bash: warning: here-document at line 8 delimited by end-of-file \
(wanted `%s')\n", (char *)data->prompt->content);
	send_buffer(data);
	return (exit(0), 0);
}

int	ft_exec_here_docbis(t_data *data)
{
	char	*buffer;
	char	*str;

	ft_signal2();
	buffer = NULL;
	while (1)
	{
		str = readline("> ");
		if (!str)
			return (ft_exec_here_doc_2(data, buffer));
		if (ft_strstr(str, data->prompt->content) >= 0 && \
			ft_strlen(str) == ft_strlen(data->prompt->content))
			break ;
		buffer = ft_strjoin(buffer, str);
		buffer = ft_strjoin(buffer, "\n");
	}
	data->prompt = data->prompt->next;
	if (data->exit_code != 0)
		return (exit(idk(data)), 0);
	data->std_in = ft_strdup(buffer);
	send_buffer(data);
	return (exit(0), 0);
}

char	*parent2(t_data *data, int *code)
{
	char	*buffer;

	buffer = NULL;
	wait(code);
	if (access(".buff", F_OK) >= 0)
	{
		data->fd[0] = open(".buff", O_RDONLY, 0644);
		buffer = ft_run_malloc(1, BUFFER_SIZE * sizeof(char));
		if (buffer == NULL)
			return (buffer);
		if (read(data->fd[0], buffer, (BUFFER_SIZE - 1)) == -1)
			return (buffer);
		buffer[ft_strlen(buffer)] = '\0';
		unlink (".buff");
		close(data->fd[0]);
	}
	return (buffer);
}

int	ft_exec_here_doc(t_data *data)
{
	pid_t	pid;
	int		code;
	char	*buffer;

	code = 0;
	g_signal = 1;
	buffer = NULL;
	data->prompt = data->prompt->next;
	if (!data->prompt)
		return (1);
	if (pipe(data->fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		ft_exec_here_docbis(data);
	else if (pid > 0)
		buffer = parent2(data, &code);
	if (!buffer)
		code = 130;
	g_signal = 0;
	code = code % 256;
	data->prompt->content = ft_strdup(buffer);
	return (data->prompt->type = TEXTE, code);
}
