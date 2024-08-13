/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:59:11 by jpeter            #+#    #+#             */
/*   Updated: 2024/06/21 11:08:41 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

#define BUFFER_SIZE 8000

int	which_command(t_data *data)
{
	if (data->prompt->type == ECHO1)
		return (ft_exec_echo(data));
	else if (data->prompt->type == CD)
		return (ft_exec_cd(data));
	else if (data->prompt->type == PWD)
		return (ft_exec_pwd(data));
	else if (data->prompt->type == EXPORT)
		return (ft_exec_export(data));
	else if (data->prompt->type == UNSET)
		return (ft_exec_unset(data));
	else if (data->prompt->type == ENV)
		return (ft_exec_env(data));
	else if (data->prompt->type == EXIT)
		return (ft_exec_exit(data));
	return (which_sign(data));
}

int	which_sign(t_data *data)
{
	if (data->prompt->type == PIPE)
		return (ft_exec_pipe(data));
	else if (data->prompt->type == OU)
		return (ft_exec_dbl_pipe(data));
	else if (data->prompt->type == ET)
		return (ft_exec_dbl_esp(data));
	else if (data->prompt->type == WILDCARD)
		return (ft_exec_prt(data));
	else if (data->prompt->type == OPRT)
		return (data->prompt = data->prompt->next, data->exit_code);
	else if (data->prompt->type == CPRT)
	{
		ft_print_result(data);
		data->prompt = data->prompt->next;
		if (data->prompt)
			check_std(data);
		return (data->exit_code);
	}
	else
		return (ft_exec_other(data));
	return (0);
}

int	parent(t_data *data)
{
	int		code;
	int		i;

	g_signal = 1;
	i = 0;
	if (data->result)
		printf("%s", data->result);
	while (waitpid(data->num_pid[i], &code, 0) > 0)
		i++;
	if (data->result || data->exit_code != 0)
		code = data->exit_code;
	else
		code = ft_code(code);
	if (access(".buff", F_OK) >= 0)
		unlink (".buff");
	if (!data->prompt)
		return (data->result = NULL, data->std_in = NULL, (code % 255));
	while ((data->prompt->type <= CMD || data->prompt->type >= DOLLARS) \
		&& data->prompt->type != CPRT)
	{
		data->prompt = data->prompt->next;
		if (data->prompt == NULL)
			return (data->result = NULL, data->std_in = NULL, (code % 255));
	}
	return (data->result = NULL, data->std_in = NULL, (code % 255));
}

int	ft_execution2(t_data *data)
{
	int		i;

	i = 0;
	if (!data->prompt)
		return (0);
	data->nb_pipes = count_pipe(data->prompt);
	if (data->nb_pipes != 0)
	{
		data->pipes = ft_run_malloc(1, ((data->nb_pipes * 2) * sizeof(int)));
		if (!data->pipes)
			return (ft_msg("Error: ", "Pipe ", "Malloc failed\n", EXIT_FAILURE));
		while (data->nb_pipes != i)
		{
			if (pipe(data->pipes + 2 * i) == -1)
				return (ft_msg("Error: ", "Pipe Failed", "\n", EXIT_FAILURE));
			i++;
		}
	}
	data->exit_code = ft_exec_execve(data);
	return (data->exit_code);
}

int	execution(t_data *data)
{
	if (!data->prompt || data->prompt->content == NULL)
		return (1);
	data->exit_code = check_std(data);
	while (data->prompt)
	{
		if (data->prompt->type == EXEC || data->prompt->type == CMD)
			data->exit_code = ft_execution2(data);
		else
			data->exit_code = which_command(data);
	}
	while (data->exit_code < 0)
		data->exit_code = (256 + data->exit_code);
	data->exit_code = data->exit_code % 256;
	ft_print_result(data);
	return (ft_run_malloc(2, data->result), data->exit_code);
}
