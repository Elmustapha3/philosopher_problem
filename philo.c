/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:36:10 by eej-jama          #+#    #+#             */
/*   Updated: 2023/07/06 16:00:28 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize_and_create_philo(t_info *info)
{
	create_philo(info);
	while (1)
		if (philo_die(info))
			return ;
	join_and_destroy(info);
}

void	intialize_args_and_mutex(int ac, char *av[], t_info *info)
{
	int	i;

	info->args.num_philo = atoi(av[1]);
	info->args.time_to_die = ft_atoi(av[2]);
	info->args.time_to_eat = ft_atoi(av[3]);
	info->args.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		info->args.number_of_times_must_eat = ft_atoi(av[5]);
	else
		info->args.number_of_times_must_eat = -1;
	info->philos = malloc(sizeof(t_philo) * info->args.num_philo);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->args.num_philo);
	i = 0;
	while (i < info->args.num_philo)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
			printf("Error");
		i++;
	}
	pthread_mutex_init(&info->mutexs.mutex_a, NULL);
	pthread_mutex_init(&info->mutexs.mutex_b, NULL);
	pthread_mutex_init(&info->mutexs.mutex_c, NULL);
	pthread_mutex_init(&info->mutexs.time_mutex, NULL);
	pthread_mutex_init(&info->mutexs.print_mutex, NULL);
}

int	allocate(t_info *info)
{
	info->forks = malloc(sizeof(pthread_mutex_t) * info->args.num_philo);
	info->philos = malloc(sizeof(t_philo) * info->args.num_philo);
	if (!(info->philos) || !(info->forks))
	{
		printf("Error");
		return (0);
	}
	return (1);
}

long	get_current_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

int	main(int ac, char *av[])
{
	t_info	info;

	if (ac == 5 || ac == 6)
	{
		info.args.time_lunch = get_current_time();
		if (!check_arguments(ac, av))
			return (0);
		if (allocate(&info))
		{
			intialize_args_and_mutex(ac, av, &info);
			initialize_and_create_philo(&info);
			usleep(1000000);
		}
	}
	return (0);
}
