/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:57:48 by pdeson            #+#    #+#             */
/*   Updated: 2024/06/21 11:38:22 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_execve_args2(t_data *data, char **args, int i)
{
	while (data->prompt->type <= CMD || data->prompt->type >= DOLLARS)
	{
		if (data->prompt->type >= OPRT)
			break ;
		args[i++] = (char *)data->prompt->content;
		if (data->prompt == NULL || data->prompt->next == NULL)
			break ;
		data->prompt = data->prompt->next;
	}
	return (i);
}

char	**ft_execve_args(t_data *data)
{
	char	**args;
	int		i;

	args = ft_run_malloc(1, 64 * sizeof(char *));
	if (!args)
		return (NULL);
	if (data->prompt->execve_path)
		args[0] = data->prompt->execve_path;
	else
		args[0] = data->prompt->content;
	i = 1;
	data->prompt = data->prompt->next;
	if (data->prompt == NULL)
		return (args[i] = NULL, args);
	i = ft_execve_args2(data, args, i);
	args[i] = NULL;
	return (args);
}

int	fils(t_data *data, int i)
{
	char	**args;

	if (data->exit_code != 0)
		exit (data->exit_code);
	if (signal(SIGQUIT, &ft_sig_handler3) == SIG_ERR)
		exit(close_all(data, errno));
	args = ft_execve_args(data);
	if (data->std_in)
		ft_exec_stdin(data);
	else if (i != 0)
	{
		if (dup2(data->pipes[i - 2], STDIN_FILENO) == -1)
			exit(close_all(data, errno));
	}
	if (data->std_out->content)
		ft_exec_stdout(data);
	else if (i != (data->nb_pipes * 2))
	{
		if (dup2(data->pipes[i + 1], STDOUT_FILENO) == -1)
			exit(close_all(data, errno));
	}
	close_all(data, 0);
	return (execve(args[0], args, chainlist_to_dblpoint(data->envp_bis)));
}

int	ft_exec_execve2(t_data *data, int i)
{
	while (i != (data->nb_pipes * 2) + 2)
	{
		if (data->prompt->type < EXEC || data->prompt->type == TEXTE)
		{
			data->result = NULL;
			data->exit_code = which_command(data);
			if (data->std_out->content)
				ft_print_result(data);
		}
		else
		{
			if (start_fils(data, i) != 0)
				return (1);
		}
		two_close(data, i);
		i += 2;
		if (i == (data->nb_pipes * 2) + 2)
			break ;
		trucmuche(data);
		data->exit_code = check_std(data);
	}
	return (data->exit_code = parent(data));
}

int	ft_exec_execve(t_data *data)
{
	data->num_pid = ft_run_malloc(1, ((data->nb_pipes + 2) * sizeof(pid_t)));
	data->num_pid[data->nb_pipes + 1] = '\0';
	ft_exec_execve2(data, 0);
	close_all(data, 0);
	ft_run_malloc(2, data->pipes);
	ft_run_malloc(2, data->num_pid);
	data->nb_pipes = 0;
	return (data->exit_code);
}
