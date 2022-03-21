/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjacinta <gjacinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:51:11 by gjacinta          #+#    #+#             */
/*   Updated: 2022/03/21 19:07:25 by gjacinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
		i +=2;
	}
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
	int	i;
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
				printf(RED "%lu %d died!!!\n", now_time - data->start_time, i + 1);
				return (1);
			}
			i++;
		}
		i = 0;
		usleep(1000);
	}
	return (0);
}

int	main(int	argc,char	**argv)
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
	thread_spawn(&data);
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
