/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:47:27 by tyamcha           #+#    #+#             */
/*   Updated: 2022/01/05 12:48:59 by unix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <stdio.h>
# include <stdint.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <inttypes.h>
# include <sys/wait.h>
# include <semaphore.h>

# define SEM_FORK	"/sem_Fork"
# define SEM_WRITE	"/sem_Write"
# define SEM_DEAD	"/sem_Dead"
# define SEM_PHILO	"/sem_Philo"

# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"
# define TAKEN "has taken a fork"

typedef struct s_philo
{
	pid_t			pid;
	int				name;
	int				eat_count;
	uint64_t		last_eat;
	uint64_t		death_lim;
	sem_t			*eat_sem;
	struct s_state	*state;
}	t_philo;

typedef struct s_state
{
	int				amount;
	int				must_eat;
	t_philo			*philos;
	uint64_t		start;
	uint64_t		tm_die;
	uint64_t		tm_eat;
	uint64_t		tm_sleep;
	sem_t			*forks;
	sem_t			*write;
	sem_t			*death_occur;
}	t_state;

int			ft_atoi(const char *str);
uint64_t	get_time(void);
void		massage(t_philo *philo, char *msg);
int			clear_state(t_state *state);
int			error(char *msg);
int			ft_strcpy(char *dst, const char *src);
void		make_name(char *buf, int pos);

int			init(t_state *state, int argc, char **argv);
void		*philosoph(t_philo *self);

#endif