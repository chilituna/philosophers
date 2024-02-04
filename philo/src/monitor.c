/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarpo e  <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 00:09:41 by aarpo e           #+#    #+#             */
/*   Updated: 2024/02/04 09:35:28 by aarpo e          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//wait until all threads have been created
int	ft_wait_to_start(t_data *data)
{
	pthread_mutex_lock(&data->start_mutex);
	if (data->ready_to_start == data->num_philo)
	{
		pthread_mutex_unlock(&data->start_mutex);
		return (0);
	}
	pthread_mutex_unlock(&data->start_mutex);
	return (1);
}

//check if all philosophers have finished eating:
//if finished_philos == num_philo, return 1
//check if someone has died:
//if end_of_dinner == 1, return 1
int	ft_end_of_dinner(t_data *data)
{
	pthread_mutex_lock(&data->finished_mutex);
	if (data->finished_philos == data->num_philo)
	{
		pthread_mutex_unlock(&data->finished_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->finished_mutex);
	pthread_mutex_lock(&data->end_mutex);
	if (data->end_of_dinner == 1)
	{
		pthread_mutex_unlock(&data->end_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->end_mutex);
	return (0);
}

//wait until all threads have the last meal time set
int	ft_start_monitoring(t_data *data)
{
	pthread_mutex_lock(&data->start_mutex);
	if (data->ready_to_start < data->num_philo)
	{
		pthread_mutex_unlock(&data->start_mutex);
		return (0);
	}
	pthread_mutex_unlock(&data->start_mutex);
	return (1);
}

//monitor if anyone has died
//if someone has died, set end_of_dinner to 1
void	ft_monitor_threads(t_data *data)
{
	int	i;

	while (ft_start_monitoring(data) == 0)
		;
	while (ft_end_of_dinner(data) == 0)
	{
		i = 0;
		while (ft_end_of_dinner(data) == 0 && i < data->num_philo)
		{
			if (ft_still_alive(&data->philo[i]) == 0)
				return ;
			i++;
		}
	}
}

//check if philosopher is still alive:
//if philo is finished, ignore
int	ft_still_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_mutex);
	if (philo->finished == 1)
	{
		pthread_mutex_unlock(&philo->philo_mutex);
		return (1);
	}
	if (ft_get_time(philo->data) - philo->last_meal > philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->end_mutex);
		philo->data->end_of_dinner = 1;
		pthread_mutex_unlock(&philo->data->end_mutex);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf(RED "%ld %d DIED\n" RESET, ft_get_time(philo->data)
			- philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_unlock(&philo->philo_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->philo_mutex);
	return (1);
}
