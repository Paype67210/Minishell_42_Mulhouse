/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:59:11 by jpeter            #+#    #+#             */
/*   Updated: 2024/06/21 11:07:27 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_isallnum_chr(t_data *data, char *str)
{
	int		i;

	i = 0;
	if (data->prompt->type >= DIROUT && data->prompt->type <= WILDCARD)
		return (0);
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && (str[i] != '-') && \
			(str[i] != '+'))
			return (1);
		i++;
	}
	return (0);
}

int	ft_exec_exit3(t_data *data)
{
	int	buffer;

	if (data->exit_code != 0)
		return (data->exit_code);
	if (ft_isallnum_chr(data, data->prompt->content) == 1)
	{
		printf("Mini: exit: %s: numeric argument required\n", \
			(char *)data->prompt->content);
		data->exit_code = 2;
		return (data->result = NULL, ft_exit(data), 0);
	}
	else if (data->prompt->type <= CMD || data->prompt->type >= DOLLARS)
	{
		buffer = ft_atoi(data->prompt->content);
		if ((buffer < 0 && ft_int_strchr(data->prompt->content, '-') == -1) || \
			(buffer >= 0 && ft_int_strchr(data->prompt->content, '-') > -1))
		{
			printf("Mini: exit: %s: numeric argument required\n", \
				(char *)data->prompt->content);
			data->exit_code = 2;
			return (data->result = NULL, ft_exit(data), 0);
		}
		return (buffer);
	}
	return (0);
}

int	ft_exec_exit2(t_data *data)
{
	if (!data->prompt || (data->prompt->type >= DIROUT && \
		data->prompt->type < DOLLARS))
		return (0);
	data->prompt = data->prompt->next;
	if (data->prompt && (data->prompt->type <= CMD || \
		data->prompt->type >= DOLLARS))
	{
		printf("exit\nMini: exit: too many arguments\n");
		return (1);
	}
	return (0);
}

int	ft_exec_exit4(t_data *data, t_list *buff)
{
	if (!data->prompt && !data->std_in && buff->prev == NULL)
	{
		data->exit_code = data->old_exit_code;
		ft_exit(data);
	}
	return (0);
}

int	ft_exec_exit(t_data *data)
{
	int		ext;
	t_list	*buff;

	buff = data->prompt;
	ext = 0;
	data->prompt = data->prompt->next;
	ft_exec_exit4(data, buff);
	if (data->prompt)
		ext = ft_exec_exit3(data);
	if (ft_exec_exit2(data) == 1)
		return (data->result = NULL, 1);
	if (data->std_in)
		return (data->result = NULL, ext);
	if (buff->prev->type == PIPE)
		return (data->result = NULL, ext);
	if (data->exit_code != 0)
		return (data->exit_code);
	if (data->prompt)
	{
		if (data->prompt->type == PIPE)
			return (data->result = NULL, ext);
	}
	while (ext < 0)
		ext = (256 + ext);
	return (data->exit_code = ext % 256, data->result = NULL, ft_exit(data), 0);
}
