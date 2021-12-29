/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:47:22 by tyamcha           #+#    #+#             */
/*   Updated: 2021/12/29 15:31:05 by unix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t mutex;

int
	clear_state(t_state *state)
{
	int	i;

	if (state->forks_m)
	{
		i = 0;
		while (i < state->amount)
			pthread_mutex_destroy(&state->forks_m[i++]);
		free(state->forks_m);
	}
	if (state->philos)
	{
		i = 0;
		while (i < state->amount)
		{
			pthread_mutex_destroy(&state->philos[i].mutex);
			pthread_mutex_destroy(&state->philos[i++].eat_m);
		}
		free(state->philos);
	}
	pthread_mutex_destroy(&state->write_m);
	pthread_mutex_destroy(&state->somebody_dead_m);
	return (1);
}

int	init(t_state *state, int argc, char **argv)
{
	state->amount = ft_atoi(argv[1]);
	state->tm_die = ft_atoi(argv[2]);
	state->tm_eat = ft_atoi(argv[3]);
	state->tm_sleep = ft_atoi(argv[4]);
	state->must_eat = 0;
	if (argc == 6)
		state->must_eat = ft_atoi(argv[5]);
	if (state->amount < 2 || state->amount > 200 || state->tm_die < 60
		|| state->tm_eat < 60 || state->tm_sleep < 60
		|| state->must_eat < 0)
		return (1);
	state->forks_m = NULL;
	state->philos = NULL;
	state->philos = (t_philo*)malloc(sizeof(*(state->philos)) * state->amount);
	if (!state->philos)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_state state;
	
	if (argc < 5 || argc > 6)
		return (error("bad arguments"));
	if (init(&state, argc, argv))
		return (clear_state(&state) && error("fatal error"));
	printf("State %d %lu %lu\n", state.amount, state.tm_die, state.tm_eat);
	return (0);
}
