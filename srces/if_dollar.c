/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: philippe <philippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:59:11 by jpeter            #+#    #+#             */
/*   Updated: 2024/06/20 13:53:19 by philippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*dollar_join(t_data *data, char *str, int i, int j)
{
	char	*buffer;
	char	*buff;

	buff = ft_strbtwcpy(data->envp_bis->content, '=', '\0');
	buffer = ft_strjoin((ft_strbtwcpyi(str, -1, i)), buff);
	buffer = ft_strjoin(buffer, ft_strbtwcpyi(str, (j - 1), ft_strlen(str)));
	return (buffer);
}

char	*dollar_join2(t_data *data, char *str)
{
	int		i;
	char	*tmp;
	char	*buffer;

	i = ft_int_strchr(str, '$');
	tmp = NULL;
	if (str[i + 1] != '?')
		return (tmp);
	buffer = ft_itoa(data->old_exit_code);
	tmp = ft_strjoin((ft_strbtwcpyi(str, -1, i)), buffer);
	tmp = ft_strjoin(tmp, ft_strbtwcpyi(str, (i + 1), ft_strlen(str)));
	return (tmp);
}

char	*if_dollar(t_data *data, char *str)
{
	int		i;
	int		j;
	char	*buff;

	if (!str)
		return (str);
	if (ft_strchr(str, '$') == NULL)
		return (str);
	buff = dollar_join2(data, str);
	i = if_dollar_i(str);
	if (i == -1)
		return (str);
	if (buff)
		return (str = if_dollar(data, buff));
	j = (i + 1);
	if (str[j] == ' ' || str[j] == '"' || str[j] == '\0')
		return (str);
	while (str[j] != ' ' && str[j] != '\0' && \
		str[j] != 34 && str[j] != 39 && str[j] != '$')
		j++;
	data->envp_bis = ft_lstfirst(data->envp_bis);
	buff = if_dollar_buff(data, str, i, j);
	return (str = if_dollar(data, buff));
}

char	*if_dollar_buff(t_data *data, char *str, int i, int j)
{
	char	*buff;

	buff = NULL;
	while (1)
	{
		if (ft_strstr(ft_strbtwcpy2(data->envp_bis->content, -1, '='), \
			ft_strbtwcpyi(str, i, j)) >= 0 && data->envp_bis->type == 0)
		{
			buff = dollar_join(data, str, i, j);
			break ;
		}
		if (data->envp_bis->next == NULL)
		{
			buff = ft_strjoin(ft_strbtwcpyi(str, -1, i), \
				ft_strbtwcpyi(str, (j - 1), ft_strlen(str)));
			break ;
		}
		data->envp_bis = data->envp_bis->next;
	}
	return (buff);
}

int	if_dollar_i(char *str)
{
	int	i;
	int	mem;

	i = 0;
	mem = 0;
	while (str[i] != '$' && str[i] != '\0')
	{
		if (str[i] == 34 && mem == 0)
			mem = 1;
		else if (str[i] == 34 && mem == 1)
			mem = 0;
		if (str[i] == 39 && mem == 0)
		{
			i++;
			while (str[i] != 39 && str[i] != '\0')
				i++;
			if (str[i] == '\0' || (ft_strnchr(str, '$', i) == NULL))
				return (-1);
		}
		i++;
	}
	return (i);
}
