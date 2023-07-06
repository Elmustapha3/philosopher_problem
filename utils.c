/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 03:05:04 by maneddam          #+#    #+#             */
/*   Updated: 2023/07/06 13:51:04 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long ft_atoi(char *str)
{
	int i;
	int sign;
	long res;
	
	sign = 1;
	i = 0;
	res = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f' || *str == '\r')
		str++;
	if(str[i] == '+' || str[i] == '-')
	{
		if(str[i] == '-')
			sign = -1;
		i++;
	}
	while(str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (res * sign);
}
