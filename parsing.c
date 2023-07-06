/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:35:59 by eej-jama          #+#    #+#             */
/*   Updated: 2023/07/06 16:25:48 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_empty(int ac, char *av[])
{
    int i;
    
    i = 1;
    while (i < ac)
	{
		if (!av[i][0])
		{
			printf("error");	
			return (0);	
		}
		i++;
	}
    return (1);
}

int check_digit_and_negative(int ac, char *av[])
{
    int i;
    int j;
    
    i = 1;
    while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				printf("error");
				return (0);
			}
			j++;
		}
		i++;
	}
    return (1);
}

int check_max(int ac, char *av[])
{
    int i;

    i = 1;
    while (i < ac)
	{	
		if (ft_atoi(av[i]) > INT_MAX)
		{
			printf("error");	
			return 0;	
		}
		i++;
	}
    return (1);
}

int check_arguments(int ac, char **av)
{
	if (!check_empty(ac, av) || !check_digit_and_negative(ac, av)
		|| !check_max(ac, av))
		return (0);
	return (1);
}
