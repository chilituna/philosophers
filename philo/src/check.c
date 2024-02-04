/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 09:32:37 by aarponen          #+#    #+#             */
/*   Updated: 2024/02/04 12:02:15 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// check if all arguments are positive numbers
void	ft_check_if_numbers(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				ft_error(RED "All args must be positive numbers.\n"
					GREEN U1 U2 U3 RESET);
			j++;
		}
		i++;
	}
}

// check if arguments are valid:
// 1. number of arguments
// 2. all arguments are numbers
// 3. number of philosophers is at least 2
// 4. number of philosophers is at most 200
// 5. time to die, eat and sleep are at least 1
void	ft_check_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		ft_error(RED "Wrong number of args.\n" GREEN U1 U2 U3 RESET);
	ft_check_if_numbers(argv);
	if (ft_atol(argv[1]) < 1)
		ft_error(RED "We need philosophers, please.\n" GREEN U1 U2 U3 RESET);
	if (ft_atol(argv[1]) > 200)
		ft_error(RED "The party is getting too big - max 200 guests allowed.\n"
			GREEN U1 U2 U3 RESET);
	if (ft_atol(argv[2]) <= 0 || ft_atol(argv[3]) <= 0 || ft_atol(argv[4]) <= 0)
		ft_error(RED "Please give some time to the philosophers.\n"
			GREEN U1 U2 U3 RESET);
	if (ft_atol(argv[2]) >= INT_MAX || ft_atol(argv[3]) >= INT_MAX
		|| ft_atol(argv[4]) >= INT_MAX)
		ft_error(RED "Keep the time below MAX_INT.\n" GREEN U1 U2 U3 RESET);
	if (argc == 6)
	{
		if (ft_atol(argv[5]) < 1)
			ft_error(RED "Let them eat at least once!\n" GREEN U1 U2 U3 RESET);
		if (ft_atol(argv[5]) > INT_MAX)
			ft_error(RED "Let's keep the meals times below INT_MAX\n"
				GREEN U1 U2 U3 RESET);
	}
}
