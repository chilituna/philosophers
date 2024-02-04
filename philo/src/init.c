/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:20:07 by aarponen          #+#    #+#             */
/*   Updated: 2024/02/04 11:53:45 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//initialize data struct with values from argv
//if there is no meal_times, set it to -1
//set monitor variables to 0
//initialize mutexes
//initialize fork and philo structs
void	ft_init_data(t_data *data, int argc, char **argv)
{
	data->num_philo = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		data->meal_times = ft_atol(argv[5]);
	else
		data->meal_times = -1;
	data->fork = NULL;
	data->philo = NULL;
	data->start_time = 0;
	data->all_threads_ready = 0;
	data->ready_to_start = 0;
	data->end_of_dinner = 0;
	data->finished_philos = 0;
	data->mutex_count = 0;
	ft_init_mutex(&data->all_ready_mutex, data);
	ft_init_mutex(&data->start_mutex, data);
	ft_init_mutex(&data->finished_mutex, data);
	ft_init_mutex(&data->end_mutex, data);
	ft_init_mutex(&data->print_mutex, data);
	ft_init_fork(data);
	ft_init_philo(data);
}

//initialize fork struct for each fork with malloc
//mutex each fork
void	ft_init_fork(t_data *data)
{
	int		i;
	t_fork	*fork;

	data->fork = malloc(sizeof(t_fork) * data->num_philo);
	if (!data->fork)
		ft_clean_error(data, RED "Malloc error.\n" GREEN U1 U2 U3 RESET);
	i = 0;
	fork = data->fork;
	while (i < data->num_philo)
	{
		fork[i].fork_id = i + 1;
		ft_init_mutex(&fork[i].fork, data);
		i++;
	}
}

//initialize philo struct for each philosopher with malloc
//initialize mutex for each philosopher
void	ft_init_philo(t_data *data)
{
	int		i;
	t_philo	*philo;

	data->philo = malloc(sizeof(t_philo) * data->num_philo);
	if (!data->philo)
		ft_clean_error(data, RED "Malloc error.\n" GREEN U1 U2 U3 RESET);
	i = 0;
	philo = data->philo;
	while (i < data->num_philo)
	{
		philo[i].id = i + 1;
		philo[i].times_eaten = 0;
		philo[i].last_meal = 0;
		philo[i].finished = 0;
		philo[i].data = data;
		ft_init_mutex(&philo[i].philo_mutex, data);
		i++;
	}
	ft_assign_forks(data->philo, data->fork, data->num_philo);
}

//assign fork to each philosopher:
//odd philosophers start with left fork
//even philosophers start with right fork
//the right fork of the first philosopher is the last fork
void	ft_assign_forks(t_philo *philo, t_fork *fork, int num_philo)
{
	int	i;

	i = 0;
	while (i < num_philo)
	{
		if (philo[i].id % 2 != 0)
		{
			philo[i].first_fork = &fork[i];
			if (i == 0)
				philo[i].second_fork = &fork[num_philo - 1];
			else
				philo[i].second_fork = &fork[i - 1];
			i++;
		}
		else
		{
			philo[i].first_fork = &fork[i - 1];
			philo[i].second_fork = &fork[i];
			i++;
		}
	}
}

//initialize mutex with error check
void	ft_init_mutex(pthread_mutex_t *mutex, t_data *data)
{
	if (pthread_mutex_init(mutex, NULL))
		ft_clean_error(data, "Can't initialize mutex");
	data->mutex_count++;
}
