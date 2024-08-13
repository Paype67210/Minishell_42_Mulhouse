/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:52:57 by pdeson            #+#    #+#             */
/*   Updated: 2024/06/21 10:56:26 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_remove_if_exist2(t_data *data)
{
	t_list	*token;

	data->envp_bis = ft_lstfirst(data->envp_bis);
	token = data->envp_bis;
	while (token)
	{
		if (ft_strstr(ft_strbtwcpy2(token->content, -1, '='), \
			data->prompt->content) >= 0)
		{
			ft_lstremove(&data->envp_bis, token, NULL);
			return ;
		}
		if (token->next == NULL)
			break ;
		token = token->next;
	}
	return ;
}

int	ft_exec_unset(t_data *data)
{
	data->prompt = data->prompt->next;
	if (data->result || !data->prompt)
		data->result = NULL;
	data->envp_bis = ft_lstfirst(data->envp_bis);
	while (data->prompt->type == TEXTE)
	{
		ft_remove_if_exist2(data);
		data->prompt = data->prompt->next;
		if (data->prompt == NULL)
			break ;
	}
	return (data->exit_code);
}
