/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:00:28 by aarponen          #+#    #+#             */
/*   Updated: 2024/02/04 12:02:22 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//destroy mutexes based on mutex_count and the order they were initialized
void	ft_destroy_mutex(t_data *data)
{
	if (data->mutex_count > 4)
		ft_mutex_destroy(&data->print_mutex);
	if (data->mutex_count > 3)
		ft_mutex_destroy(&data->end_mutex);
	if (data->mutex_count > 2)
		ft_mutex_destroy(&data->finished_mutex);
	if (data->mutex_count > 1)
		ft_mutex_destroy(&data->start_mutex);
	if (data->mutex_count > 0)
		ft_mutex_destroy(&data->all_ready_mutex);
	if (data->mutex_count > 5)
		ft_destroy_fork_and_philo(data);
}

void	ft_destroy_fork_and_philo(t_data *data)
{
	int	i;

	i = 0;
	while (data->mutex_count - 5 < data->num_philo)
	{
		ft_mutex_destroy(&data->fork[i].fork);
		i++;
	}
	if (data->mutex_count > (data->num_philo + 5))
	{
		i = 0;
		while (data->mutex_count - (data->num_philo + 5) < data->num_philo)
		{
			ft_mutex_destroy(&data->philo[i].philo_mutex);
			i++;
		}
	}
}
