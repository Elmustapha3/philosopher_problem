/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 00:00:37 by maneddam          #+#    #+#             */
/*   Updated: 2023/07/06 14:11:02 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_usleep(long time_to_eat)
{
	long	time;

	time = get_current_time();
	while (get_current_time() - time < time_to_eat)
		usleep(100);
}
void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[philo->left_fork]);
	display_msg("take fork 1", philo, 1);
	pthread_mutex_lock(&philo->info->forks[philo->right_fork]);
	display_msg("take fork 2", philo, 1);
	display_msg("is eating", philo, 1);

	
	pthread_mutex_lock(&philo->info->mutexs.time_mutex);
	philo->time_of_last_meal_eaten = get_current_time() - philo->info->args.time_lunch;
	pthread_mutex_unlock(&philo->info->mutexs.time_mutex);
	
	pthread_mutex_lock(&philo->info->mutexs.mutex_b);
	philo->number_of_times_eat++;
	pthread_mutex_unlock(&philo->info->mutexs.mutex_b);
	
	ft_usleep(philo->args.time_to_eat);
	
	pthread_mutex_unlock(&philo->info->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->info->forks[philo->left_fork]);
}



void	*philo_routine(void *philo_recive)
{
	t_philo	*philo;

	philo = (t_philo *)philo_recive;
	if (philo->index % 2)
		usleep(200);
	while (1)
	{
		eating(philo);
		display_msg("is sleeping", philo, 1);
		ft_usleep(philo->info->args.time_to_sleep);
		display_msg("is thinkin", philo, 1);
	}
}

int check_if_all_philo_eat_the_max(t_info info)
{
	int i;
	
	i = 0;
	while(i < info.args.num_philo)
	{
		if (info.philos[i].number_of_times_eat < info.args.number_of_times_must_eat)
		{
			return 0;
		}
		i++;
	}
	return 1;
}

int	philo_die(t_info *info)
{
	int i; 
	
	i = 0;
	while (i < info->args.num_philo)
	{
		if (pthread_mutex_lock(&info->mutexs.time_mutex) != 0)
			exit(555);
		if(get_current_time() - info->args.time_lunch - info->philos[i].time_of_last_meal_eaten > info->args.time_to_die)
		{
			display_msg("is died", &info->philos[i] , 0);
			return 1;
		}
		pthread_mutex_unlock(&info->mutexs.time_mutex);
		i++;
	}

		pthread_mutex_lock(&info->mutexs.mutex_b);
		pthread_mutex_lock(&info->mutexs.time_mutex);
		pthread_mutex_lock(&info->mutexs.mutex_a);
		
		if(info->args.number_of_times_must_eat != -1)
		{
			if(check_if_all_philo_eat_the_max(*info))
			{
				display_msg("philos are died", &info->philos[0], 1);
				return 1;
			}
		}

		pthread_mutex_unlock(&info->mutexs.mutex_a);
		pthread_mutex_unlock(&info->mutexs.time_mutex);
		pthread_mutex_unlock(&info->mutexs.mutex_b);
	return 0;
}

void	initiliaze_philos(t_info *info)
{
	int i;

	i = 0;
	while (i < info->args.num_philo)
	{
		info->philos[i].index = i;
		info->philos[i].time_of_last_meal_eaten = 0;
		info->philos[i].number_of_times_eat = 0;
		info->philos[i].right_fork = (i + 1) % info->args.num_philo;
		info->philos[i].left_fork = i;
		info->philos[i].args = info->args;
		info->philos[i].info = info;
		if (pthread_create(&info->philos[i].thread, NULL, &philo_routine,
				&info->philos[i]) != 0)
		{
			printf("creating thread failed");
			return ;
		}
		i++;
	}
}

void	initialize_and_start(t_info *info)
{
	initiliaze_philos(info);
	while (1)
		if (philo_die(info))
			return ;
}
