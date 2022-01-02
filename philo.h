/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:47:27 by tyamcha           #+#    #+#             */
/*   Updated: 2022/01/02 18:29:39 by unix             ###   ########.fr       */
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
# include <inttypes.h>

# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"
# define TAKEN "has taken a fork"

typedef struct s_philo
{
	int				name;
	int				is_eating;
	uint64_t		last_eat;
	uint64_t		death_lim;
	int				fork_l;
	int				fork_r;
	int				eat_count;
	struct s_state	*state;
	pthread_mutex_t	eating_m;
	pthread_mutex_t	eat_m;
}	t_philo;

typedef struct s_state
{
	int				amount;
	int				must_eat;
	uint64_t		start;
	uint64_t		tm_die;
	uint64_t		tm_eat;
	uint64_t		tm_sleep;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	death_occur;
}	t_state;

//UTILS
int			ft_atoi(const char *str);
uint64_t	get_time(void);
void		massage(t_philo *philo, char *msg);

//EXIT
int			error(char *msg);
int			clear_state(t_state *state);

//INIT
int			init(t_state *state, int argc, char **argv);

void		*philosoph(void *ptr);

#endif