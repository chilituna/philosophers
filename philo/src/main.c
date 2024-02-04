/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:23:04 by aarponen          #+#    #+#             */
/*   Updated: 2024/02/04 17:00:33 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	ft_print(philo, BLUE1 "has taken a fork" RESET);
	pthread_mutex_lock(&philo->second_fork->fork);
	ft_print(philo, BLUE2 "has taken a fork" RESET);
	ft_print(philo, BLUE3 "is eating" RESET);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal = ft_get_time(philo->data);
	pthread_mutex_unlock(&philo->philo_mutex);
	ft_usleep(philo->data->time_to_eat, philo->data);
	philo->times_eaten++;
	if (philo->times_eaten == philo->data->meal_times)
	{
		ft_print(philo, GREEN "had all meals" RESET);
		pthread_mutex_lock(&philo->philo_mutex);
		philo->finished = 1;
		pthread_mutex_unlock(&philo->philo_mutex);
		pthread_mutex_lock(&philo->data->finished_mutex);
		philo->data->finished_philos++;
		pthread_mutex_unlock(&philo->data->finished_mutex);
	}
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

// Routine function for each philosopher
// Wait for all threads are created
// Set last_meal to starting time and wait for all the threads to be ready
// Eat, sleep, think until finished or end_of_dinner
void	*ft_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (ft_wait_to_start(philo->data) == 0)
		;
	if (philo->last_meal == 0)
	{
		pthread_mutex_lock(&philo->philo_mutex);
		philo->last_meal = ft_get_time(data);
		pthread_mutex_unlock(&philo->philo_mutex);
		pthread_mutex_lock(&philo->data->start_mutex);
		philo->data->ready_to_start++;
		pthread_mutex_unlock(&philo->data->start_mutex);
	}
	while (philo->finished == 0 && ft_end_of_dinner(philo->data) == 0)
	{
		ft_eat(philo);
		ft_print(philo, YELLOW "is sleeping" RESET);
		ft_usleep(philo->data->time_to_sleep, philo->data);
		ft_print(philo, YELLOW2 "is thinking" RESET);
	}
	return (NULL);
}

//routine for one philosopher:
//take fork
//die after time_to_die
void	ft_eat_alone(t_philo *philo)
{
	ft_print(philo, BLUE1 "has taken a fork" RESET);
	ft_usleep(philo->data->time_to_die, philo->data);
	ft_print(philo, RED "died" RESET);
}

// create a thread for each philosopher
// monitor threads
// once one philosopher has died or all are finished, join threads
void	ft_dinner_is_ready(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_create(&data->philo[i].thread_id, NULL,
				ft_routine, &data->philo[i]))
			ft_clean_error(data, "Can't create thread");
		i++;
	}
	pthread_mutex_lock(&data->all_ready_mutex);
	data->all_threads_ready = 1;
	pthread_mutex_unlock(&data->all_ready_mutex);
	ft_monitor_threads(data);
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_join(data->philo[i].thread_id, NULL))
			ft_clean_error(data, "Can't join thread");
		i++;
	}
}

// argv[1] number_of_philosophers (and number_of_forks)
// argv[2] time_to_die (in ms) If a philosopher didn’t start eating
//   time_to_die milliseconds since the beginning of their last meal or
//   the beginning of the simulation, they die
// argv[3] time_to_eat (in ms) The time it takes for a philosopher to eat.
//   During that time, they will need to hold two forks.
// argv[4] time_to_sleep (in ms) The time a philosopher will spend sleeping.
// argv[5] [number_of_times_each_philosopher_must_eat] (optional) if all
//   philosophers have eaten at least number_of_times_each_philosopher_must_eat
//   times, the simulation stops. If not specified, the simulation stops when
//   a philosopher dies.
int	main(int argc, char **argv)
{
	t_data	*data;

	ft_check_args(argc, argv);
	printf(GREEN "All arguments are valid.\n" RESET);
	data = malloc(sizeof(t_data));
	if (!data)
		ft_error(RED "Malloc error.\n" GREEN U1 U2 U3 RESET);
	ft_init_data(data, argc, argv);
	data->start_time = ft_get_time(data);
	printf(GREEN "Let's get this dinner started!\n" RESET);
	if (data->num_philo == 1)
		ft_eat_alone(&data->philo[0]);
	else
		ft_dinner_is_ready(data);
	printf("END OF SIMULATION.\n");
	ft_destroy_mutex(data);
	ft_free(data);
	return (0);
}

