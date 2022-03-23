/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjacinta <gjacinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:53:14 by gjacinta          #+#    #+#             */
/*   Updated: 2022/03/23 15:03:41 by gjacinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# define RED "\x1b[31m"
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
	struct s_data	*dinner;
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

int				check_arguments(t_data	*data);
void			init_phil(t_data	*data, int i);
int				init_fork(t_data *data);
int				read_arguments(char **argv, t_data *data, int argc);

int				ft_atoi(const char *s);
unsigned long	get_time(void);
void			ft_usleep(int time_waiting);

void			ft_life(t_philo *philo);
void			thread_create(t_data	*data);
void			thread_create2(t_data *data);
int				death_check(t_data *data);

#endif