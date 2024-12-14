/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:13:26 by eismail           #+#    #+#             */
/*   Updated: 2024/01/18 10:22:18 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_line(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_free(char *cup_buffer, char **s)
{
	if (*s)
	{
		free (*s);
		*s = NULL;
	}
	free (cup_buffer);
	return (NULL);
}

char	*re_line(char **s)
{
	int		i;
	char	*temp;
	char	*line;

	i = find_line(*s);
	if (i == -1)
	{
		line = sub_buf(*s, 0, ft_strlen(*s) - 1);
		free (*s);
		*s = NULL;
		return (line);
	}
	line = sub_buf(*s, 0, i);
	if (!line)
		return (ft_free(NULL, s), NULL);
	temp = sub_buf(*s, i + 1, ft_strlen(*s) - 1);
	free (*s);
	*s = NULL;
	*s = temp;
	return (line);
}

char	*get_next_line(int fd)
{
	char static	*next_line;
	char		*cup_buffer;
	ssize_t		count;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	cup_buffer = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!cup_buffer)
		return (ft_free(NULL, &next_line), NULL);
	count = 42;
	while ((find_line(next_line) == -1) && count > 0)
	{
		count = read(fd, cup_buffer, BUFFER_SIZE);
		if (count < 0)
			return (ft_free(cup_buffer, &next_line));
		cup_buffer[count] = '\0';
		next_line = add_buffer(next_line, cup_buffer);
		if (!next_line || !next_line[0])
			return (ft_free(cup_buffer, &next_line));
	}
	free (cup_buffer);
	return (re_line(&next_line));
}
