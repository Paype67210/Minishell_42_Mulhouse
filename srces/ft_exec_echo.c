/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:59:11 by jpeter            #+#    #+#             */
/*   Updated: 2024/06/21 10:55:40 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_exec_echo2(t_data *data)
{
	while (data->prompt->type == TEXTE)
	{
		if (data->result && ft_strcmp(data->result, "") != 0)
			data->result = ft_strjoin(data->result, " ");
		data->result = ft_strjoin(data->result, (char *)data->prompt->content);
		data->prompt = data->prompt->next;
		if (data->prompt == NULL)
			break ;
	}
	return ;
}

static int	ft_echo_n(char *str)
{
	int	len;
	int	i;

	if (!str || ft_strcmp(str, "") == 0)
		return (-1);
	len = ft_strlen(str);
	if (ft_strncmp(str, "-n", len) == 0)
		return (0);
	if (str[0] != '-')
		return (-1);
	i = 0;
	while (++i < len)
	{
		if (str[i] != 'n')
			return (-1);
	}
	return (0);
}

int	ft_exec_echo(t_data *data)
{
	int		mem;

	data->prompt = data->prompt->next;
	if (data->result)
		data->result = NULL;
	if (!data->prompt)
	{
		printf("\n");
		return (0);
	}
	mem = 0;
	while (ft_echo_n(data->prompt->content) == 0)
	{
		mem = 1;
		data->prompt = data->prompt->next;
		if (!data->prompt)
			return (0);
	}
	ft_exec_echo2(data);
	if (mem == 0)
		data->result = ft_strjoin(data->result, "\n");
	return (data->exit_code);
}
