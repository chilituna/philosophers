/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:16:30 by aarponen          #+#    #+#             */
/*   Updated: 2024/02/04 12:01:05 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> //printf
# include <unistd.h> //write, usleep
# include <stdlib.h> //malloc, free
# include <string.h> //memset
# include <sys/time.h> //gettimeofday
# include <pthread.h> // phtread functions
# include <limits.h> // INT_MAX

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define YELLOW2 "\033[0;33m"
# define BLUE1 "\033[1;34m"
# define BLUE2 "\033[0;34m"
# define BLUE3 "\033[0;36m"
# define RESET "\033[0m"
# define U1 "Correct use:\n./philo\n1. number_of_philosophers\n"
# define U2 "2. time_to_die(ms)\n3. time_to_eat(ms)\n4. time_to_sleep(ms)\n"
# define U3 "5. [number_of_times_each_philosopher_must_eat (optional)]"

typedef struct s_data	t_data;

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork;
}		t_fork;

typedef struct s_philo
{
	int				id;
	t_fork			*first_fork;
	t_fork			*second_fork;
	long			times_eaten;
	long			last_meal;
	int				finished;
	pthread_t		thread_id;
	pthread_mutex_t	philo_mutex;
	t_data			*data;
}	t_philo;

struct s_data
{
	long			num_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meal_times;
	t_philo			*philo;
	t_fork			*fork;
	long			start_time;
	int				all_threads_ready;
	int				ready_to_start;
	int				end_of_dinner;
	long			finished_philos;
	int				mutex_count;
	pthread_mutex_t	all_ready_mutex;
	pthread_mutex_t	start_mutex;
	pthread_mutex_t	finished_mutex;
	pthread_mutex_t	end_mutex;
	pthread_mutex_t	print_mutex;
};

//main.c
int		main(int argc, char **argv);
void	ft_dinner_is_ready(t_data *data);
void	*ft_routine(void *philo);
void	ft_eat(t_philo *philo);
void	ft_eat_alone(t_philo *philo);

//monitor.c
int		ft_wait_to_start(t_data *data);
int		ft_end_of_dinner(t_data *data);
void	ft_monitor_threads(t_data *data);
int		ft_still_alive(t_philo *philo);
int		ft_start_monitoring(t_data *data);

//check.c
void	ft_check_if_numbers(char **argv);
void	ft_check_args(int argc, char **argv);

//init.c
void	ft_init_data(t_data *data, int argc, char **argv);
void	ft_init_fork(t_data *data);
void	ft_init_philo(t_data *data);
void	ft_assign_forks(t_philo *philo, t_fork *fork, int num_philo);
void	ft_init_mutex(pthread_mutex_t *mutex, t_data *data);

//error_exit.c
void	ft_error(char *msg);
void	ft_clean_error(t_data *data, char *msg);
void	ft_mutex_destroy(pthread_mutex_t *mutex);
void	ft_free(t_data *data);

//destroy.c
void	ft_destroy_mutex(t_data *data);
void	ft_destroy_fork_and_philo(t_data *data);

//utils.c
long	ft_atol(const char *str);
long	ft_get_time(t_data *data);
void	ft_usleep(long time_in_ms, t_data *data);
void	ft_print(t_philo *philo, char *msg);

#endif

//check valgrind --tool=helgrind --fair-sched=yes ./philo 5 410 200 200
