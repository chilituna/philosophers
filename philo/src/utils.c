/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:05:26 by aarponen          #+#    #+#             */
/*   Updated: 2024/02/04 12:24:18 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	long	i;
	int		sign;
	long	nb;

	i = 0;
	nb = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (str[i] == '0')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i] - 48;
		i++;
	}
	return (nb * sign);
}

// get current time in milliseconds
long	ft_get_time(t_data *data)
{
	struct timeval	time;
	long			time_in_ms;

	if (gettimeofday(&time, NULL))
		ft_clean_error(data, RED "Error in gettimeofday" RESET);
	time_in_ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (time_in_ms);
}

// sleeping function that takes time in milliseconds
void	ft_usleep(long time_in_ms, t_data *data)
{
	long	start_time;
	long	end_time;

	start_time = ft_get_time(data);
	end_time = start_time + time_in_ms;
	if (ft_end_of_dinner(data) == 1)
		return ;
	while (ft_get_time(data) < end_time)
		usleep(100);
}

void	ft_print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (ft_end_of_dinner(philo->data) == 0)
		printf("%ld %d %s\n", ft_get_time(philo->data)
			- philo->data->start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
