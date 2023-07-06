#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include<unistd.h>
#include <limits.h>
#include <sys/time.h>

typedef struct s_args
{
    int     num_philo;
    long    time_to_die;
    long    time_to_eat;
    long    time_to_sleep;
    int     number_of_times_must_eat;
    long    time_lunch;
}           t_args;

typedef struct s_mutex
{
    pthread_mutex_t mutex_a;
    pthread_mutex_t mutex_b;
    pthread_mutex_t mutex_c;
    pthread_mutex_t time_mutex;
    pthread_mutex_t print_mutex;

}               t_mutex;


typedef struct s_philo
{
    int index;
    long time_of_last_meal_eaten;
    int number_of_times_eat;
    int right_fork;
    int left_fork;
    t_args args;
    struct s_info *info;
    pthread_t thread;
}               t_philo;


typedef struct s_info
{
    t_args args;
    t_philo *philos;
    pthread_mutex_t *forks;
    t_mutex mutexs;
}               t_info;



void        *philo_routine(void *tmp);
void        eating(t_philo *philo);
void		ft_usleep(long time_to_eat);
void        display_msg(char *mgs, t_philo *philo, int a);
// long        _time();
void	    eating(t_philo *philo);
void		initialize_and_start(t_info *info);
long         get_current_time();
// long        get_time_from_1970();
// void		print_error(char *str);
int			check_arguments(int ac, char *av[]);
// void		print_message(t_philo *philo, char *str, int i);
// void		destroy_mutexes(t_info *info);
long        ft_atoi(char *str);
void        ft_usleep(long time_to_eat);
// int         philo_die(t_info *info);
int 		check_if_all_philo_eat_the_max(t_info info);
// void        create_threads(t_info *info);
void        intialize_args_and_mutex(int ac, char *av[], t_info *info);
void        join_and_destroy(t_info *info);

#endif