/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_command1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeter <jpeter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:59:11 by jpeter            #+#    #+#             */
/*   Updated: 2024/06/19 16:09:12 by jpeter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	if_echo(t_data *data)
{
	if (data->prompt->next == NULL)
		return (0);
	data->prompt = data->prompt->next;
	while (data->prompt->type <= CMD || data->prompt->type >= DOLLARS)
	{
		if ((data->prompt->type == OPRT) || (data->prompt->type == CPRT))
			break ;
		data->prompt->type = TEXTE;
		if (data->prompt->next == NULL)
			return (0);
		data->prompt = data->prompt->next;
	}
	data->prompt = data->prompt->prev;
	return (0);
}

int	if_cd(t_data *data)
{
	int	mem;

	mem = 0;
	if (data->prompt->next == NULL)
		mem = 1;
	else if (data->prompt->next->type > TEXTE || \
		(data->prompt->next->type >= DIROUT && \
			data->prompt->next->type <= WILDCARD))
		mem = 1;
	if (mem == 1)
	{
		data->envp_bis = ft_lstfirst(data->envp_bis);
		while (ft_strstr(ft_strbtwcpy2(data->envp_bis->content, -1, '='), \
			"HOME") <= 0)
		{
			if (data->envp_bis->next == NULL)
				return (0);
			data->envp_bis = data->envp_bis->next;
		}
		ft_lstaddbefore(data->prompt, \
			ft_lstnew(ft_strbtwcpy(data->envp_bis->content, '=', '\0'), 26, 0));
	}
	return (if_echo(data));
}

int	if_pwd(t_data *data)
{
	if (data->prompt->next == NULL)
		return (0);
	return (0);
}

int	if_export(t_data *data)
{
	if (data->prompt->next == NULL)
		return (0);
	data->prompt = data->prompt->next;
	while (data->prompt->type <= CMD || data->prompt->type >= DOLLARS)
	{
		if ((data->prompt->type == OPRT) || (data->prompt->type == CPRT))
			break ;
		data->prompt->type = TEXTE;
		if (data->prompt->next == NULL)
			return (0);
		data->prompt = data->prompt->next;
	}
	data->prompt = data->prompt->prev;
	return (0);
}

int	if_unset(t_data *data)
{
	if (data->prompt->next == NULL)
		return (0);
	data->prompt = data->prompt->next;
	while (data->prompt->type <= CMD || data->prompt->type >= DOLLARS)
	{
		if ((data->prompt->type == OPRT) || (data->prompt->type == CPRT))
			break ;
		data->prompt->type = TEXTE;
		if (data->prompt->next == NULL)
			return (0);
		data->prompt = data->prompt->next;
	}
	data->prompt = data->prompt->prev;
	return (0);
}
