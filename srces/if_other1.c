/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_other1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeter <jpeter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:59:11 by jpeter            #+#    #+#             */
/*   Updated: 2024/06/19 16:18:12 by jpeter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	if_parenthese(t_data *data)
{
	if ((data->prompt->prev->type != OU) \
		&& (data->prompt->prev->type != ET) \
			&& (data->prompt->prev->type != VIDE) \
				&& (data->prompt->prev->type != PIPE))
	{
		printf("Mini: syntax error near unexpected token `%s'\n", \
			(char *)data->prompt->prev->content);
		return (2);
	}
	if (data->prompt->next->type >= PIPE)
	{
		printf("Mini: syntax error near unexpected token `%s'\n", \
			(char *)data->prompt->next->content);
		return (2);
	}
	return (0);
}

int	if_parenthese2(t_data *data)
{
	if (data->prompt->next == NULL)
		return (0);
	if ((data->prompt->next->type != OU) && (data->prompt->next->type != ET) && \
		(data->prompt->next->type != VIDE) && \
		(data->prompt->next->type != CPRT) && \
		(data->prompt->next->type != PIPE))
	{
		printf("Mini: syntax error near unexpected token `%s'\n", \
			(char *)data->prompt->next->content);
		return (2);
	}
	return (0);
}

char	*ft_strbtwcpyi(char *str, int i, int j)
{
	char	*dst;
	int		k;

	if (i == j)
		return (NULL);
	dst = ft_run_malloc(1, ((j - i)) * sizeof(char));
	if (!dst)
		return (NULL);
	k = 0;
	i++;
	while (i != j)
	{
		dst[k] = str[i];
		k++;
		i++;
	}
	dst[k] = '\0';
	return (dst);
}

char	*if_quote(t_data *data, char *str, int i)
{
	char	*dst;
	size_t	j;

	if (ft_strchr(str, 34) == NULL && ft_strchr(str, 39) == NULL)
		return (str);
	dst = NULL;
	while (str[i] != 34 && str[i] != 39)
	{
		if (str[i] == '\0')
			return (str);
		i++;
	}
	if (ft_strnchr(str, str[i], (i + 1)) == NULL)
		return (data->prompt->type = TEXTE, \
			ft_strbtwcpyi(str, -1, (int)ft_strlen(str)));
	j = (i + 1);
	while (str[j] != str[i])
		j++;
	if (i != 0)
		dst = ft_strjoin(dst, ft_strbtwcpyi(str, -1, i));
	dst = ft_strjoin(dst, ft_strbtwcpyi(str, i, j));
	if (str[j + 1] != '\0')
		dst = ft_strjoin(dst, ft_strbtwcpyi(str, j, (int)ft_strlen(str)));
	dst = if_quote(data, dst, (j - 1));
	return (data->prompt->type = TEXTE, dst);
}

int	if_env_variable(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '=' || (str[i] == '+' && str[i + 1] == '=')) && i != 0)
			return (1);
		if (str[i] == '_')
			i++;
		else if (str[i] >= 48 && str[i] <= 57)
			i++;
		else if (str[i] >= 65 && str[i] <= 90)
			i++;
		else
			return (0);
	}
	return (0);
}
