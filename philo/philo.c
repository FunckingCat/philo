/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 16:15:49 by unix              #+#    #+#             */
/*   Updated: 2022/01/05 13:02:53 by unix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*observer(void	*ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		pthread_mutex_lock(&philo->eating_m);
		if (get_time() > philo->death_lim)
		{
			massage(philo, DIED);
			pthread_mutex_unlock(&philo->eating_m);
			pthread_mutex_unlock(&philo->state->death_occur);
		}
		pthread_mutex_unlock(&philo->eating_m);
		usleep(1000);
	}
}

void	eat(t_philo *self)
{
	pthread_mutex_lock(&self->state->forks[self->fork_r]);
	massage(self, TAKEN);
	pthread_mutex_lock(&self->state->forks[self->fork_l]);
	massage(self, TAKEN);
	pthread_mutex_lock(&self->eating_m);
	self->last_eat = get_time();
	self->death_lim = self->last_eat + self->state->tm_die;
	massage(self, EATING);
	usleep(self->state->tm_eat * 1000);
	self->eat_count++;
	pthread_mutex_unlock(&self->eating_m);
	pthread_mutex_unlock(&self->state->forks[self->fork_l]);
	pthread_mutex_unlock(&self->state->forks[self->fork_r]);
}

void	*philosoph(void *ptr)
{
	t_philo		*self;
	pthread_t	tid;

	self = (t_philo *)ptr;
	self->last_eat = get_time();
	self->death_lim = self->last_eat + self->state->tm_die;
	pthread_create(&tid, NULL, observer, ptr);
	pthread_detach(tid);
	if (self->name % 2 == 1 || (self->state->amount % 2 == 1
			&& self->name == self->state->amount - 1))
	{
		massage(self, THINKING);
		usleep(self->state->tm_eat * 500);
	}
	while (1)
	{
		eat(self);
		massage(self, SLEEPING);
		usleep(self->state->tm_sleep * 1000);
		massage(self, THINKING);
	}
}
