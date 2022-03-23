/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjacinta <gjacinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:51:11 by gjacinta          #+#    #+#             */
/*   Updated: 2022/03/23 14:56:35 by gjacinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_life(t_philo *philo)
{
	while (!philo->dinner->dead
		&& philo->eating != philo->dinner->times_had_dinner)
	{
		pthread_mutex_lock(&philo->dinner->fork[philo->right_fork]);
		printf("%lu %d took a fork\n", get_time()
			- philo->dinner->start_time, philo->id);
		pthread_mutex_lock(&philo->dinner->fork[philo->left_fork]);
		printf("%lu %d took a fork\n", get_time()
			- philo->dinner->start_time, philo->id);
		printf("%lu %d is eating\n", get_time()
			- philo->dinner->start_time, philo->id);
		ft_usleep(philo->dinner->time_to_eat);
		philo->time_last_eating = get_time();
		pthread_mutex_unlock(&philo->dinner->fork[philo->right_fork]);
		pthread_mutex_unlock(&philo->dinner->fork[philo->left_fork]);
		if (philo->eating != philo->dinner->times_had_dinner)
		{
			printf("%lu %d is sleeping\n", get_time()
				- philo->dinner->start_time, philo->id);
			ft_usleep(philo->dinner->time_to_sleep);
			printf("%lu %d is thinking\n", get_time()
				- philo->dinner->start_time, philo->id);
		}
		philo->eating++;
	}
}

void	thread_create(t_data	*data)
{
	int	i;

	i = 0;
	while (i < data->num_phil)
	{
		pthread_create(&data->philo[i].thread, NULL,
			(void *)ft_life, &data->philo[i]);
		usleep(100);
		i += 2;
	}
	i = 1;
	while (i < data->num_phil)
	{
		pthread_create(&data->philo[i].thread, NULL,
			(void *)ft_life, &data->philo[i]);
		usleep(100);
		i += 2;
	}
	thread_create2(data);
}

void	thread_create2(t_data *data)
{
	int	i;

	if (death_check(data))
		return ;
	i = 0;
	while (i < data->num_phil)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
}

int	death_check(t_data *data)
{
	int				i;
	unsigned long	now_time;

	i = 0;
	while (1)
	{
		while (i < data->num_phil)
		{
			now_time = get_time();
			if (data->philo[i].eating == data->times_had_dinner)
				return (1);
			if (now_time - data->philo[i].time_last_eating
				> (unsigned long)data->time_to_die)
			{
				data->dead = 1;
				printf(RED "%lu %d died!!!\n",
					now_time - data->start_time, i + 1);
				return (1);
			}
			i++;
		}
		i = 0;
		usleep(1000);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (read_arguments(argv, &data, argc))
	{
		printf("Invalid arguments!!!\n");
		return (1);
	}
	if (init_fork(&data))
		return (1);
	data.start_time = get_time();
	thread_create(&data);
	free(data.fork);
	free(data.philo);
	i = 0;
	while (i < data.num_phil)
	{
		pthread_mutex_destroy(&data.fork[i]);
		i++;
	}
	return (0);
}
