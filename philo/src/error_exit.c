/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:40:40 by aarponen          #+#    #+#             */
/*   Updated: 2024/02/04 12:02:08 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//error during checking arguments
void	ft_error(char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

void	ft_clean_error(t_data *data, char *msg)
{
	printf("%s\n", msg);
	ft_destroy_mutex(data);
	ft_free(data);
	exit(EXIT_FAILURE);
}

//error during mutex destroy
void	ft_mutex_destroy(pthread_mutex_t *mutex)
{
	if (pthread_mutex_destroy(mutex))
		ft_error("Can't destroy mutex");
}

//free fork and philo structs if they were already malloced
void	ft_free(t_data *data)
{
	if (data->fork)
	{
		free(data->fork);
		data->fork = NULL;
	}
	if (data->philo)
	{
		free(data->philo);
		data->philo = NULL;
	}
	free(data);
}
