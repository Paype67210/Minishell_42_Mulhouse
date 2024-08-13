/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeter <jpeter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:59:11 by jpeter            #+#    #+#             */
/*   Updated: 2024/05/26 16:19:49 by jpeter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*dblptr_to_ptr(char **str)
{
	char	*buff;
	int		i;

	i = 0;
	buff = NULL;
	while (str[i])
	{
		buff = ft_strjoin(buff, str[i]);
		buff = ft_strjoin(buff, " ");
		i++;
	}
	return (buff);
}

char	*ft_here_doc(char *str, char chr)
{
	char	*buff;
	char	*rlt;
	char	test[1];

	test[0] = chr;
	buff = ft_strdup(str);
	buff = ft_strjoin(buff, "\n");
	while (1)
	{
		rlt = readline("> ");
		if (!rlt)
			return (ft_strjoin(buff, &test[0]));
		buff = ft_strjoin(buff, rlt);
		if (ft_strchr(rlt, chr))
			break ;
		buff = ft_strjoin(buff, "\n");
	}
	ft_run_malloc(2, rlt);
	return (buff);
}

int	ft_findplus(const char *src, const char *value)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (value[0] == '\0' || src == NULL)
		return (-1);
	while (src[i] != '\0')
	{
		if (src[i] == value[0])
		{
			j = 0;
			while (src[i] == value[j])
			{
				j++;
				i++;
				if (value[j] == '\0')
					return (i - j);
			}
			i = i - j;
		}
		i++;
	}
	return (-1);
}

void	ft_remove_if_exist(t_data *data, char *new_value)
{
	t_list	*token;
	t_list	*temp;
	char	*str;
	int		i;

	data->envp_bis = ft_lstfirst(data->envp_bis);
	token = data->envp_bis;
	while (token)
	{
		i = 0;
		str = (char *)token->content;
		while (str[i] == new_value[i] && str[i] != '=')
			i++;
		temp = token->next;
		if (str[i] == '=' || str[i] == '\0')
		{
			if (new_value[i] == '=' || new_value[i] == '\0')
			{
				if (ft_strncmp(str, new_value, i) == 0)
					ft_lstremove(&data->envp_bis, token, &free);
			}
		}
		token = temp;
	}
	return ;
}

t_list	*ft_extract_if_exist(t_data *data, char *value)
{
	t_list	*token;
	t_list	*temp;
	char	*str;
	int		i;

	data->envp_bis = ft_lstfirst(data->envp_bis);
	token = data->envp_bis;
	while (token)
	{
		i = 0;
		str = (char *)token->content;
		while (str[i] == value[i] && str[i] != '=')
			i++;
		temp = token->next;
		if (str[i] == '=' || str[i] == '\0')
		{
			if (value[i] == '=' || value[i] == '+' || value[i] == '\0')
			{
				if (ft_strncmp(str, value, i - 1) == 0)
					return (ft_lstretrieve(&data->envp_bis, token));
			}
		}
		token = temp;
	}
	return (NULL);
}
