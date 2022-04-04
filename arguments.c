/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejafer <ejafer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:30:17 by gjacinta          #+#    #+#             */
/*   Updated: 2022/04/04 17:43:11 by ejafer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_arguments(t_data	*data)
{
	if (data->num_phil <= 0 || data->time_to_die <= 0
		|| data->time_to_sleep <= 0 || data->time_to_eat <= 0)
		return (1);
	return (0);
}

void	init_phil(t_data	*data, int i)
{
	data->philo[i].id = i + 1;
	data->philo[i].right_fork = i;
	data->philo[i].left_fork = i + 1;
	data->philo[i].dinner = data;
	data->philo[i].eating = 0;
	if (data->philo[i].left_fork == data->num_phil)
		data->philo[i].left_fork = 0;
	data->philo[i].time_last_eating = get_time();
}

int	init_fork(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->num_phil);
	if (!data->philo)
		return (1);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->num_phil);
	if (!data->fork)
	{
		free(data->philo);
		return (1);
	}
	while (i < data->num_phil)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		init_phil(data, i);
		i++;
	}
	return (0);
}

int	read_arguments(char **argv, t_data *data, int argc)
{
	if (argc != 5 && argc != 6)
		return (1);
	data->num_phil = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->dead = 0;
	if (argc == 6)
		data->times_had_dinner = ft_atoi(argv[5]);
	else
		data->times_had_dinner = -1;
	if (check_arguments(data))
		return (1);
	return (0);
}
