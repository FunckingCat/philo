/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:47:22 by tyamcha           #+#    #+#             */
/*   Updated: 2022/01/02 17:37:01 by unix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	spawn_philo(t_state *state)
{
	int	i;
	void		*philo;
	pthread_t	tid;

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
	clear_state(&state);
	return (0);
}
