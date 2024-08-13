/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:12:16 by pdeson            #+#    #+#             */
/*   Updated: 2024/06/17 10:27:41 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*buffer;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup((char *)s2));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	buffer = ft_run_malloc(1, sizeof(char) * (len1 + len2 + 1));
	if (!buffer)
		return (NULL);
	ft_strcpy(buffer, s1);
	ft_strcpy(buffer + len1, s2);
	return (buffer);
}
/*
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*buffer;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup((char *)s2));
	buffer = ft_run_malloc(1, sizeof(char) * \
		(ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!buffer)
		exit (EXIT_FAILURE);
	i = -1;
	j = -1;
	while (s1 && s1[++i] != '\0')
		buffer[i] = s1[i];
	while (s2 && s2[++j] != '\0')
		buffer[i + j] = s2[j];
	buffer[i + j] = '\0';
	return (buffer);mkdir 
}
*/
