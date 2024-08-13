/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeter <jpeter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:59:11 by jpeter            #+#    #+#             */
/*   Updated: 2024/06/19 14:40:42 by jpeter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*if_prt(char *str, int i)
{
	int		nbr;

	nbr = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == '(')
		{
			nbr = 1;
			while (str[i] != ')' || nbr > 0)
			{
				i++;
				if (str[i] == '\0')
					return (printf("Mini: syntax error near unexpected \
token `('\n"), NULL);
				if (str[i] == '(')
					nbr++;
				if (str[i] == ')')
					nbr--;
			}
		}
		else if (str[i] == ')')
			return (printf("Mini: syntax error near unexpected \
token `)'\n"), NULL);
	}
	return (str);
}

static int	count_words(char *str, char c)
{
	int		i;
	int		nbr;

	i = 0;
	nbr = 0;
	while (str[i] == c)
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == 34 || str[i] == 39)
			i = while_prt(str, i);
		if (str[i] == '\0')
			break ;
		if (str[i] == c)
		{
			while (str[i] == c)
				i++;
			if (str[i] != '\0')
				nbr++;
		}
		else
			i++;
	}
	nbr++;
	return (nbr);
}

char	*ft_strbtwcpy2(char *str, int i, char chr2)
{
	int		j;
	int		nbr;

	j = (i + 1);
	while (str[j] != chr2)
	{
		if (str[j] == 34 || str[j] == 39)
			j = while_prt(str, j);
		else if (str[j] == '(')
		{
			nbr = 1;
			while (str[j] != ')' || nbr > 0)
			{
				j++;
				if (str[j] == '(')
					nbr++;
				if (str[j] == ')')
					nbr--;
			}
		}
		if (str[j] == '\0')
			return (ft_strbtwcpyi(str, i, j));
		j++;
	}
	return (ft_strbtwcpyi(str, i, j));
}

char	**ft_split_check(char *s, char c)
{
	size_t	i;
	size_t	j;
	char	**split;

	s = if_prt(s, -1);
	if (!s)
		return (NULL);
	split = ft_run_malloc(1, (count_words(s, c) + 1) * sizeof(char *));
	if (!s || !split)
		return (NULL);
	s = ft_strjoin(s, " ");
	i = 0;
	j = 0;
	while (s[i] == c)
		i++;
	while (s[i] != '\0')
	{
		split[j] = ft_strbtwcpy2(s, (i - 1), ' ');
		i = i + ft_strlen(split[j]);
		while (s[i] == c)
			i++;
		j++;
	}
	split[j] = NULL;
	return (split);
}
