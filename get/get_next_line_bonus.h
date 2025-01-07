/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:06:54 by ysouhail          #+#    #+#             */
/*   Updated: 2025/01/07 10:20:00 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "../libft/libft.h"

char	*get_next_line(int fd);
size_t	ft_strlen(char *s);
char	*ft_strjwan(char *s, char *p);
char	*ft_strchr(char *s, char c);
char	*str_jwan(char *s, char *p);
#endif
