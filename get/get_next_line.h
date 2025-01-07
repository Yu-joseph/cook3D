/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 13:18:04 by ysouhail          #+#    #+#             */
/*   Updated: 2024/02/24 13:18:04 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// #include "../cub3D.h"
# include "../libft/libft.h"
// #include "../cub3D.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
// size_t	ft_strlen(char *s);
char	*ft_strjwan(char *s, char *p);
// char	*ft_strchr(char *s, char c);
char	*str_jwan(char *s, char *p);
#endif
