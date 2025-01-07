/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:41:02 by eismail           #+#    #+#             */
/*   Updated: 2025/01/07 10:17:31 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*temp;
	size_t	t_size;

	if (size != 0 && count > INT_MAX / size)
		return (0);
	t_size = size * count;
	temp = malloc(t_size);
	if (temp != NULL)
		ft_bzero(temp, t_size);
	return (temp);
}
