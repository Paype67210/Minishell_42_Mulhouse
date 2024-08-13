/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:46:06 by pdeson            #+#    #+#             */
/*   Updated: 2024/06/21 13:01:24 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_exec_cd2(t_data *data)
{
	char	buffer[4096];

	data->envp_bis = ft_lstfirst(data->envp_bis);
	getcwd(buffer, sizeof(buffer));
	if (chdir((char *)data->prompt->content) == -1)
	{
		printf("Mini: cd: %s: No such file or directory\n", \
			(char *)data->prompt->content);
		data->prompt = data->prompt->next;
		return (1);
	}
	if (data->std_in)
		return (chdir(buffer), 0);
	ft_export_value(&data->envp_bis, ft_strjoin("OLDPWD=", buffer), 0);
	return (0);
}

int	cd_args(t_data *data)
{
	data->prompt = data->prompt->next;
	if (data->prompt == NULL)
		return (1);
	if (data->prompt->next)
	{
		if (data->prompt->next->type == TEXTE)
		{
			printf("Mini: cd: too many arguments\n");
			while (data->prompt->type < 10 || data->prompt->type > 20)
			{
				data->prompt = data->prompt->next;
				if (!data->prompt)
					return (1);
			}
			return (1);
		}
	}
	return (0);
}

int	ft_exec_cd(t_data *data)
{
	char	buffer[4096];

	if (cd_args(data) == 1)
		return (data->std_in = NULL, 1);
	if (ft_exec_cd2(data) == 1)
		return (data->std_in = NULL, 1);
	if (data->result || data->std_in)
		data->result = NULL;
	data->envp_bis = ft_lstfirst(data->envp_bis);
	getcwd(buffer, sizeof(buffer));
	ft_export_value(&data->envp_bis, ft_strjoin("PWD=", buffer), 0);
	return (data->prompt = data->prompt->next, data->exit_code);
}
