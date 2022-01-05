/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 16:15:49 by unix              #+#    #+#             */
/*   Updated: 2022/01/05 12:36:53 by unix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*observer(void	*ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		sem_wait(philo->eat_sem);
		if (get_time() > philo->death_lim)
		{
			massage(philo, DIED);
			sem_post(philo->state->death_occur);
		}
		sem_post(philo->eat_sem);
		usleep(1000);
	}
}

void	eat(t_philo *self)
{
	sem_wait(self->state->forks);
	massage(self, TAKEN);
	sem_wait(self->state->forks);
	massage(self, TAKEN);
	sem_wait(self->eat_sem);
	self->last_eat = get_time();
	self->death_lim = self->last_eat + self->state->tm_die;
	massage(self, EATING);
	usleep(self->state->tm_eat * 1000);
	self->eat_count++;
	sem_post(self->eat_sem);
	sem_post(self->state->forks);
	sem_post(self->state->forks);
}

void	*philosoph(t_philo *self)
{
	pthread_t	tid;

	self->last_eat = get_time();
	self->death_lim = self->last_eat + self->state->tm_die;
	pthread_create(&tid, NULL, observer, (void *)self);
	pthread_detach(tid);
	if (self->name % 2 == 1 || (self->state->amount % 2 == 1 && 
		self->name == self->state->amount - 1))
	{
		massage(self, THINKING);
		usleep(self->state->tm_sleep * 1000);
	}
	while (1)
	{
		eat(self);
		massage(self, SLEEPING);
		usleep(self->state->tm_sleep * 1000);
		massage(self, THINKING);
		if (self->state->must_eat > 0 && 
			self->eat_count >= self->state->must_eat)
			return (0);
		usleep(100);
	}
}
