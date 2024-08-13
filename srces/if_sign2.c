/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_sign2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeter <jpeter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:59:11 by jpeter            #+#    #+#             */
/*   Updated: 2024/06/19 15:38:01 by jpeter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	if_pipe(t_data *data)
{
	if (data->prompt->prev->content == NULL)
	{
		printf("Mini: syntax error near unexpected token '%s'\n", \
			(char *)data->prompt->content);
		return (2);
	}
	if (data->prompt->next == NULL)
		return (0);
	if (data->prompt->next->type > HEREDOC && data->prompt->next->type < TEXTE)
		return (2);
	return (0);
}

int	if_dbl_pipe(struct data_s *data)
{
	if (data->prompt->prev->content == NULL)
	{
		printf("Mini: syntax error near unexpected token %s\n", \
			(char *)data->prompt->content);
		return (2);
	}
	if (data->prompt->next == NULL)
		return (0);
	if (data->prompt->next->type > HEREDOC && data->prompt->next->type < TEXTE)
		return (2);
	return (0);
}

int	if_dbl_esp(t_data *data)
{
	if (data->prompt->prev->content == NULL)
	{
		printf("Mini: syntax error near unexpected token %s\n", \
			(char *)data->prompt->content);
		return (2);
	}
	if (data->prompt->next == NULL)
		return (0);
	if (data->prompt->next->type > HEREDOC && data->prompt->next->type < TEXTE)
	{
		printf("hi\n");
		return (2);
	}
	return (0);
}

int	if_wild(t_data *data)
{
	char	**files;

	files = ft_main_wc();
	if (!files)
		return (EXIT_FAILURE);
	if (ft_strchr(data->prompt->content, '*'))
	{
		ft_replace_wc(data, data->prompt, files, 0);
		ft_run_malloc(2, files);
	}
	if (ft_strchr((char *)data->prompt->content, '*'))
		return (data->prompt->type = TEXTE, 0);
	return (EXIT_SUCCESS);
}

int	idk(t_data *data)
{
	while (1)
	{
		data->prompt = data->prompt->next;
		if (data->prompt == NULL)
			return (data->exit_code);
		else if (data->prompt->type == OU)
			return (data->exit_code);
	}
}
