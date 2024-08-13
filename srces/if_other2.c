/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_other2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeter <jpeter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:59:11 by jpeter            #+#    #+#             */
/*   Updated: 2024/06/18 11:28:45 by jpeter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_prt(t_data *data)
{
	int		i;
	t_list	*ptr;
	char	**buff;

	i = ((int)ft_strlen(data->prompt->content) - 1);
	buff = ft_split_check(ft_strbtwcpyi(data->prompt->content, 0, i), ' ');
	i = 0;
	while (buff[i])
		i++;
	ft_lstaddbefore(data->prompt, ft_lstnew(")", CPRT, VIDE));
	while (i != 0)
	{
		i--;
		ft_lstaddbefore(data->prompt, ft_lstnew(buff[i], VIDE, VIDE));
		data->count_check++;
	}
	ft_lstaddbefore(data->prompt, ft_lstnew("(", OPRT, VIDE));
	ptr = data->prompt->next;
	ft_lstremove(&data->prompt, data->prompt, NULL);
	data->prompt = ptr;
	return (OPRT);
}

int	while_prt(char *str, int i)
{
	int	j;

	j = i;
	i++;
	while (str[i] != str[j])
	{
		if (str[i] == '\0')
			return (i);
		i++;
	}
	return (i);
}

char	*add_space3(char *str, int i)
{
	char	*buff;

	buff = NULL;
	buff = ft_strjoin((ft_strbtwcpyi(str, -1, i)), " ");
	buff = ft_strjoin(buff, ft_strbtwcpyi(str, (i - 1), ft_strlen(str)));
	return (buff);
}

int	add_space2(char *str, int i)
{
	size_t	j;

	j = i;
	i++;
	while (str[j] != str[i])
	{
		if (str[i] == '\0')
			return (i - 1);
		i++;
	}
	return (i);
}

char	*add_space(char	*str)
{
	size_t	i;

	i = 0;
	while (i != ft_strlen(str))
	{
		if (str[i] == 9)
			str[i] = 32;
		if (str[i] == '\'' || str[i] == '"')
			i = add_space2(str, i);
		else if (str[i] == '>' || str[i] == '<' || \
			str[i] == '|' || str[i] == '&')
		{
			str = add_space3(str, i);
			i++;
			while (str[i] == '>' || str[i] == '<' || str[i] == '|' \
				|| str[i] == '&')
				i++;
			str = add_space3(str, i);
		}
		i++;
	}
	return (str);
}
