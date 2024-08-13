/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: philippe <philippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:59:11 by jpeter            #+#    #+#             */
/*   Updated: 2024/06/20 15:13:05 by philippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	second_check_args(t_data *data)
{
	data->prompt = ft_lstfirst(data->prompt);
	while (1)
	{
		if (data->prompt->type == WILDCARD)
			if_wild(data);
		if (data->prompt->next == NULL)
			break ;
		data->prompt = data->prompt->next;
	}
	data->prompt = ft_lstfirst(data->prompt);
	while (1)
	{
		data->exit_code = second_check_command(data);
		if (data->exit_code != 0)
			return (data->exit_code);
		if (data->prompt->next == NULL)
			break ;
		data->prompt = data->prompt->next;
	}
	if (data->prompt->type >= DIROUT && data->prompt->type < WILDCARD)
		heredoc_end(data);
	return (0);
}

int	heredoc_end(t_data *data)
{
	char	*str;

	str = NULL;
	while (!str)
	{
		str = readline("> ");
		if (!str)
		{
			ft_fprintf(1, "bash: syntax error: unexpected end of file\n");
			ft_ctrl_d_handler(data);
		}
		data->history = ft_strjoin(data->history, str);
		check_args(data, str);
	}
	return (0);
}

int	second_check_command(t_data *data)
{
	if (data->prompt->type == ECHO1)
		return (if_echo(data));
	else if (data->prompt->type == CD)
		return (if_cd(data));
	else if (data->prompt->type == PWD)
		return (if_pwd(data));
	else if (data->prompt->type == EXPORT)
		return (if_export(data));
	else if (data->prompt->type == UNSET)
		return (if_unset(data));
	else if (data->prompt->type == ENV)
		return (if_env(data));
	else if (data->prompt->type == EXIT)
		return (if_exit(data));
	else if (data->prompt->type == EXEC)
		return (if_exec(data));
	else if (data->prompt->type == CMD)
		return (if_execve(data));
	return (second_check_sign(data));
}

int	second_check_sign(t_data *data)
{
	if (data->prompt->type == DIROUT)
		return (if_redi_opt(data));
	else if (data->prompt->type == DIROUT2)
		return (if_dbl_redi_opt(data));
	else if (data->prompt->type == DIRIN2)
		return (if_redi_ipt(data));
	else if (data->prompt->type == HEREDOC)
		return (if_here_doc(data));
	else if (data->prompt->type == PIPE)
		return (if_pipe(data));
	else if (data->prompt->type == OU)
		return (if_dbl_pipe(data));
	else if (data->prompt->type == ET)
		return (if_dbl_esp(data));
	else if (data->prompt->type == OPRT)
		return (if_parenthese(data));
	else if (data->prompt->type == CPRT)
		return (if_parenthese2(data));
	return (0);
}
