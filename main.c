/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjacinta <gjacinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:51:11 by gjacinta          #+#    #+#             */
/*   Updated: 2022/03/14 19:42:43 by gjacinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
