/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:13:47 by eismail           #+#    #+#             */
/*   Updated: 2024/01/18 10:32:44 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*sub_buf(char *s, size_t start, size_t end)
{
	char	*temp;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	temp = malloc(sizeof(char) * ((end - start) + 2));
	if (!temp)
		return (NULL);
	while (start <= end)
		temp[i++] = s[start++];
	temp[i] = '\0';
	return (temp);
}

char	*add_buffer(char *s1, char *s2)
{
	char	*new_str;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
	{
		s1 = malloc (sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	new_str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new_str)
		return (ft_free (NULL, &s1), NULL);
	while (s1[++i])
		new_str[i] = s1[i];
	while (s2[++j])
		new_str[i + j] = s2[j];
	new_str[i + j] = '\0';
	free (s1);
	return (new_str);
}
