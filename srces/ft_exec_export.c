/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:57:48 by pdeson            #+#    #+#             */
/*   Updated: 2024/06/21 11:49:10 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*ft_newvalue(char *str)
{
	char	*buffer;
	int		i;
	int		j;

	buffer = (char *)ft_run_malloc(1, sizeof(char) * ft_strlen(str));
	if (!buffer)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			i++;
		buffer[j++] = str[i++];
	}
	buffer[j] = '\0';
	ft_run_malloc(2, str);
	return (buffer);
}

void	ft_change_value(t_data *data, t_list *token, char *str)
{
	t_list	*buffer;
	char	*tmp;

	buffer = ft_extract_if_exist(data, str);
	if (!buffer)
	{
		if (ft_findplus(str, "+=") != -1)
			token->content = ft_newvalue(str);
		ft_lstadd_back(&data->envp_bis, token);
	}
	else
	{
		if (ft_findplus(str, "+=") != -1)
		{
			tmp = ft_strchr(str, '+') + 2;
			ft_run_malloc(2, buffer->content);
			buffer->content = ft_strjoin(buffer->content, tmp);
			ft_lstadd_back(&data->envp_bis, buffer);
		}
		else
			ft_lstadd_back(&data->envp_bis, token);
	}
}	

int	ft_verif_name(char *str, int type)
{
	int		i;

	i = 0;
	if ((str[i] >= 48 && str[i] <= 57) || ft_strcmp(str, "") == 0)
		return (1);
	if ((str[i] == '=' || !ft_strchr(str, '=')) && type == 0)
		return (1);
	while (str[i] != '=' && str[i] != '+' && str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9') && \
				!(str[i] >= 'A' && str[i] <= 'Z') && \
					!(str[i] >= 'a' && str[i] <= 'z') && \
						str[i] != '_')
			return (1);
		i++;
	}
	if (str[i] == '+' && str[i + 1] != '=')
		return (1);
	return (0);
}

int	ft_export_value(t_list **envp, char *str, int type)
{
	t_list	*buffer;

	buffer = *envp;
	if (!str || !buffer)
		return (1);
	if (ft_verif_name(str, type) == 1)
	{
		printf("Minishell: export: '%s': not a valid identifier\n", str);
		return (1);
	}
	while (buffer)
	{
		if (ft_strstr(ft_strbtwcpy2(ft_strbtwcpy2(str, -1, '='), -1, '+'), \
			ft_strbtwcpy2((char *)buffer->content, -1, '=')) != -1)
			break ;
		buffer = buffer->next;
	}
	if (!buffer)
		ft_lstadd_back(envp, ft_lstnew(ft_strwchr(str, '+'), type, VIDE));
	else if (buffer && !ft_strchr(str, '+') && type == VIDE)
		buffer->content = str;
	else if (type == VIDE)
		buffer->content = ft_strjoin((char *)(buffer->content), \
			ft_strbtwcpy(str, '=', '\0'));
	return (0);
}

int	ft_exec_export(t_data *data)
{
	data->prompt = data->prompt->next;
	ft_lstfirst(data->envp_bis);
	if (data->result)
		data->result = NULL;
	if (!data->prompt || data->prompt->type != TEXTE)
		return (ft_print_export(data, data->envp_bis), 0);
	while (data->prompt->type == TEXTE)
	{
		data->envp_bis = ft_lstfirst(data->envp_bis);
		if (!ft_strchr(data->prompt->content, '='))
		{
			if (ft_export_value(&data->envp_bis, data->prompt->content, 1) != 0)
				return (1);
		}
		else
		{
			if (ft_export_value(&data->envp_bis, data->prompt->content, 0) != 0)
				return (1);
		}
		data->prompt = data->prompt->next;
		if (!data->prompt)
			break ;
	}
	return (data->exit_code);
}
