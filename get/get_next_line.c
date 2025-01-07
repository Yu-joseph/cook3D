/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 13:01:31 by ysouhail          #+#    #+#             */
/*   Updated: 2024/02/24 13:01:31 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_next(char *buffer)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	line = malloc((ft_strlen(buffer) - i + 1) * sizeof(char));
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	line[j] = '\0';
	return (free(buffer), line);
}

char	*ft_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
	{
		line = malloc((i + 2) * sizeof(char));
	}
	else
		line = malloc((i + 1) * sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*read_fd(int fd, char *res)
{
	char	*temp;
	int		byte_red;

	temp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	byte_red = 1;
	while (byte_red > 0)
	{
		byte_red = read(fd, temp, BUFFER_SIZE);
		if (byte_red == -1)
		{
			free(temp);
			free(res);
			return (NULL);
		}
		temp[byte_red] = '\0';
		res = ft_strjwan(res, temp);
		if (ft_strchr(temp, '\n'))
			break ;
	}
	free(temp);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_fd(fd, buffer);
	if (!buffer || buffer[0] == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = ft_line(buffer);
	buffer = ft_next(buffer);
	return (line);
}
