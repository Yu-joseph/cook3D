/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:03:51 by eismail           #+#    #+#             */
/*   Updated: 2025/01/31 10:58:26 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	check_pls(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\0' || ((str[i] == '-' 
					|| str[i] == '+') && str[i + 1] == '\0'))
			exit(write(2, "ERROR\nONLY SPACE\n", 17));
		else if (!(str[i] >= '0' && str[i] <= '9') 
			&& str[i] != '+' && str[i] != '-' && str[i] != ' ')
			exit(write(2, "ERROR\nbad numb\n", 16));
		else if ((str[i] == '-' || str[i] == '+') && str[i + 1] == ' ')
			exit(write(2, "ERROR\nbad sperator\n", 19));
		else if (ft_isdigit(str[i]) && (str[i + 1] == '-' || str[i + 1] == '+'))
			exit(write(2, "ERROR\nbad nb\n", 13));
		i++;
	}
}

int	ft_atoi(const char *str)
{
	int	i;
	int	neg_flg;
	int	res;

	i = 0;
	neg_flg = 1;
	res = 0;
	while ((str[i] == ' ') || ((str[i] >= 9) && (str[i] <= 13)))
		i++;
	check_pls(&str[i]);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg_flg *= -1;
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
		exit(write(2, "ERROR\nplus+-\n", 13));
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * neg_flg);
}
