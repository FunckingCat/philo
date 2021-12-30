/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:47:22 by tyamcha           #+#    #+#             */
/*   Updated: 2021/12/30 18:21:34 by unix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*observer(void	*ptr)
{
	t_philo	*philo;

	philo = (t_philo*)ptr;
	printf("Im observer on %d\n", philo->name);
}

void	*philosoph(void *ptr)
{
	t_philo	*self;
	pthread_t	tid;

	self = (t_philo*)ptr;
	self->last_eat = get_time();
	self->death_lim = self->last_eat + self->state->tm_die;
	printf("Im %d and ill die at %lu\n", self->name, self->death_lim);
	pthread_create(&tid, NULL, observer, ptr);
	pthread_detach(tid);
	massage(self, EATING);
	massage(self, SLEEPING);
	massage(self, THINKING);
	massage(self, DIED);
	massage(self, TAKEN);
}

int	spawn_philo(t_state *state)
{
	int	i;
	void		*philo;
	pthread_t	tid;

	printf("OK start threading\n");
	state->start = get_time();
	i = 0;
	while (i < state->amount)
	{
		philo = (void*)(&state->philos[i]);
		pthread_create(&tid, NULL, philosoph, philo);
		pthread_detach(tid);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_state state;
	
	if (argc < 5 || argc > 6)
		return (error("bad arguments"));
	if (init(&state, argc, argv))
		return (clear_state(&state) && error("fatal error"));
	if (spawn_philo(&state))
		return (clear_state(&state) && error("threads error"));
	pthread_mutex_lock(&state.death_occur);
	pthread_mutex_unlock(&state.death_occur);
	sleep(1);
	return (0);
}
