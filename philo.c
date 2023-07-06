/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:10:34 by maneddam          #+#    #+#             */
/*   Updated: 2023/07/06 14:12:52 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_current_time()
{
	struct timeval	tv;
	long time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void display_msg(char *msg, t_philo *philo, int a)
{
	pthread_mutex_lock(&philo->info->mutexs.print_mutex);
	printf("%ld ms %d %s\n", get_current_time() - philo->info->args.time_lunch, philo->index + 1, msg);
	if(a == 1)
		pthread_mutex_unlock(&philo->info->mutexs.print_mutex);
}

void	create_philos(t_info *info)
{
	info->args.time_lunch = get_current_time();
	initialize_and_start(info);
}

int allocate(t_info *info)
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
void intialize_args_and_mutex(int ac, char *av[], t_info *info)
{
    int i;

	info->args.num_philo = atoi(av[1]);
	info->args.time_to_die = ft_atoi(av[2]);
	info->args.time_to_eat = ft_atoi(av[3]);
	info->args.time_to_sleep = ft_atoi(av[4]);
	if(ac == 6)
		info->args.number_of_times_must_eat = ft_atoi(av[5]);
	else
		info->args.number_of_times_must_eat = -1;
	info->philos = malloc(sizeof(t_philo) * info->args.num_philo);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->args.num_philo);
	i = 0;
	while(i < info->args.num_philo)
	{
		if(pthread_mutex_init(&info->forks[i], NULL) != 0)
			printf("Error");
		i++;
	}

	pthread_mutex_init(&info->mutexs.mutex_a, NULL);
	pthread_mutex_init(&info->mutexs.mutex_b, NULL);
	pthread_mutex_init(&info->mutexs.mutex_c, NULL);
	pthread_mutex_init(&info->mutexs.time_mutex, NULL);
	pthread_mutex_init(&info->mutexs.print_mutex, NULL);
}
void join_and_destroy(t_info *info)
{
	int i;

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

int check_arguments(int ac, char **av)
{
	int i;
	int j;

	i = 1;
	while(i < ac)
	{
		if(!av[i][0])
		{
			printf("error");	
			return 0;	
		}
		i++;
	}
	i = 1;
	while(i < ac)
	{
		j = 0;
		while(av[i][j])
		{
			if(av[i][j] < '0' || av[i][j] > '9')
			{
				printf("error");
				return 0;
			}
			j++;
		}
		i++;
	}
	i = 1;
	while(i < ac)
	{	
		if(ft_atoi(av[i]) > INT_MAX)
		{
			printf("error");	
			return 0;	
		}
		i++;
	}
	return 1;
}


int	main(int ac, char *av[])
{
	t_info	info;

	if (ac == 5 || ac == 6)
	{
		if(!check_arguments(ac, av))
			return 0;
		if(allocate(&info))
		{
			intialize_args_and_mutex(ac, av, &info);
		 	create_philos(&info);
			sleep(1);
			// join_and_destroy(&info);

			
		}
	}
	return (0);
}
