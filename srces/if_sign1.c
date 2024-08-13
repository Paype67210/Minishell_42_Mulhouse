/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_sign1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeter <jpeter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:59:11 by jpeter            #+#    #+#             */
/*   Updated: 2024/06/19 14:40:42 by jpeter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

#define BUFFER_SIZE 8000

int	if_redi_opt(t_data *data)
{
	if (data->prompt->next == NULL)
	{
		printf("Mini: syntax error near unexpected token `newline'\n");
		return (2);
	}
	if (ft_strrchr(data->prompt->next->content, '&') != NULL || \
		ft_strrchr(data->prompt->next->content, '|') != NULL || \
			ft_strrchr(data->prompt->next->content, '>') != NULL || \
				ft_strrchr(data->prompt->next->content, '<') != NULL)
		return (2);
	data->prompt->next->type = FILE1;
	return (0);
}

int	if_dbl_redi_opt(t_data *data)
{
	if (data->prompt->next == NULL)
	{
		printf("Mini: syntax error near unexpected token `newline'\n");
		return (2);
	}
	if (ft_strrchr(data->prompt->next->content, '&') != NULL || \
		ft_strrchr(data->prompt->next->content, '|') != NULL || \
			ft_strrchr(data->prompt->next->content, '>') != NULL || \
				ft_strrchr(data->prompt->next->content, '<') != NULL)
		return (2);
	data->prompt->next->type = FILE1;
	return (0);
}

int	if_redi_ipt(t_data *data)
{
	if (data->prompt->next == NULL)
	{
		printf("Mini: syntax error near unexpected token `newline'\n");
		return (2);
	}
	data->prompt = data->prompt->next;
	data->prompt->type = FILE1;
	return (0);
}

int	if_here_doc(t_data *data)
{
	if (data->prompt->next == NULL)
	{
		printf("Mini: syntax error near unexpected token `newline'\n");
		return (2);
	}
	if (data->prompt->next->type >= DIROUT && \
		data->prompt->next->type <= WILDCARD)
	{
		printf("Mini: syntax error near unexpected token `%s'\n", \
			(char *)data->prompt->next->content);
		return (2);
	}
	data->exit_code = ft_exec_here_doc(data);
	data->old_exit_code = data->exit_code;
	return (data->exit_code);
}

int	ft_exec_here_doc2(t_data *data)
{
	data->prompt = data->prompt->next;
	if (data->exit_code != 0)
		return (data->exit_code);
	if (!data->prompt)
		return (2);
	data->std_in = ft_strdup((char *)data->prompt->content);
	data->prompt = data->prompt->next;
	return (0);
}
