/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjacinta <gjacinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:30:17 by gjacinta          #+#    #+#             */
/*   Updated: 2022/03/14 19:42:35 by gjacinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	read_arguments(char **argv, t_data	*data, int	argc)
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