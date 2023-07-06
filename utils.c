/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:36:22 by eej-jama          #+#    #+#             */
/*   Updated: 2023/07/06 16:17:16 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	res;

	sign = 1;
	i = 0;
	res = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\f' || *str == '\r')
		str++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (res * sign);
}

void	display_msg(char *msg, t_philo *philo, int a)
{
	pthread_mutex_lock(&philo->info->mutexs.print_mutex);
	printf("%ld ms %d %s\n", get_current_time() - philo->info->args.time_lunch,
		philo->index + 1, msg);
	if (a == 1)
		pthread_mutex_unlock(&philo->info->mutexs.print_mutex);
}

void	join_and_destroy(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->args.num_philo)
	{
		pthread_join(info->philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < info->args.num_philo)
	{
		pthread_mutex_destroy(&info->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&info->mutexs.mutex_a);
	pthread_mutex_destroy(&info->mutexs.mutex_b);
	pthread_mutex_destroy(&info->mutexs.mutex_c);
	pthread_mutex_destroy(&info->mutexs.time_mutex);
	pthread_mutex_destroy(&info->mutexs.print_mutex);
}

int	check_max_time_to_eat(t_info *info)
{
	pthread_mutex_lock(&info->mutexs.mutex_b);
	pthread_mutex_lock(&info->mutexs.time_mutex);
	pthread_mutex_lock(&info->mutexs.mutex_a);
	if (info->args.number_of_times_must_eat != -1)
	{
		if (check_if_all_philo_eat_the_max(*info))
		{
			display_msg("philos are died", &info->philos[0], 0);
			return (1);
		}
	}
	pthread_mutex_unlock(&info->mutexs.mutex_a);
	pthread_mutex_unlock(&info->mutexs.time_mutex);
	pthread_mutex_unlock(&info->mutexs.mutex_b);
	return (0);
}

int	philo_die(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->args.num_philo)
	{
		if (pthread_mutex_lock(&info->mutexs.time_mutex) != 0)
			exit(555);
		if (get_current_time() - info->args.time_lunch
			- info->philos[i].time_of_last_meal_eaten > info->args.time_to_die)
		{
			display_msg("is died", &info->philos[i], 0);
			return (1);
		}
		pthread_mutex_unlock(&info->mutexs.time_mutex);
		i++;
	}
	if (check_max_time_to_eat(info))
		return (1);
	return (0);
}
