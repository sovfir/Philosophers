/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjacinta <gjacinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:53:14 by gjacinta          #+#    #+#             */
/*   Updated: 2022/03/14 19:42:39 by gjacinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#define RED "\x1b[31m"

# include <sys/types.h>
# include <sys/time.h>
# include <signal.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_philo
{
	int				id;
	int				eating;
	int				left_fork;
	int				right_fork;
	pthread_t		thread;
	unsigned long	time_last_eating;
	struct	s_data	*dinner;
}	t_philo;

typedef struct s_data
{
	t_philo			*philo;
	pthread_mutex_t	*fork;
	unsigned long	start_time;
	int				num_phil;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_had_dinner;
	int				dead;
}	t_data;

#endif