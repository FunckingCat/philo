/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:47:22 by tyamcha           #+#    #+#             */
/*   Updated: 2022/01/02 17:56:18 by unix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*spectator(void	*ptr)
{
	t_state	*state;
	int		i;
	int		en;

	state = (t_state*)ptr;
	while (1)
	{
		i = 0;
		en = 0;
		while (i < state->amount)
		{
			if (state->philos[i++].eat_count >= state->must_eat)
				en++;
		}
		if (en == state->amount)
			break;
		usleep(2500);
	}
	pthread_mutex_unlock(&state->death_occur);
}

int	spawn_philo(t_state *state)
{
	int	i;
	void		*philo;
	pthread_t	tid;

	state->start = get_time();
	i = 0;
	if (state->must_eat > 0)
	{
		philo = (void*)state;
		pthread_create(&tid, NULL, spectator, philo);
		pthread_detach(tid);
	}
	while (i < state->amount)
	{
		philo = (void*)(&state->philos[i]);
		pthread_create(&tid, NULL, philosoph, philo);
		
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
	clear_state(&state);
	return (0);
}
