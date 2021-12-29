/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:47:27 by tyamcha           #+#    #+#             */
/*   Updated: 2021/12/29 15:12:12 by unix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdint.h>
#include <inttypes.h>

typedef struct		s_philo
{
	int				name;
	int				is_eating;
	uint64_t		last_eat;
	uint64_t		death_lim;
	int				fork_l;
	int				fork_r;
	int				eat_count;
	struct s_state	*state;
	pthread_mutex_t	mutex;
	pthread_mutex_t	eat_m;
}					t_philo;

typedef struct		s_state
{
	int				amount;
	int				must_eat;
	uint64_t		tm_die;
	uint64_t		tm_eat;
	uint64_t		tm_sleep;
	uint64_t		start;
	t_philo			*philos;
	pthread_mutex_t	*forks_m;
	pthread_mutex_t	write_m;
	pthread_mutex_t	somebody_dead_m;
}					t_state;

//UTILS
int			ft_atoi(const char *str);
uint64_t	get_time(void);
int			error(char *msg);

#endif