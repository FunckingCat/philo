/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 14:38:01 by unix              #+#    #+#             */
/*   Updated: 2022/01/02 17:30:54 by unix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_state *state)
{
	int	i;

	pthread_mutex_init(&state->write, NULL);
	pthread_mutex_init(&state->death_occur, NULL);
	pthread_mutex_lock(&state->death_occur);
	state->forks = malloc(sizeof(*(state->forks)) * state->amount);
	if (!state->forks)
		return (1);
	i = 0;
	while (i < state->amount)
		pthread_mutex_init(&state->forks[i++], NULL);
	return (0);
}

void	init_philos(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->amount)
	{
		state->philos[i].name = i;
		state->philos[i].is_eating = 0;
		state->philos[i].fork_r = i;
		state->philos[i].fork_l = (i + 1) % state->amount;
		state->philos[i].eat_count = 0;
		state->philos[i].state = state;
		pthread_mutex_init(&state->philos[i].eating_m, NULL);
		pthread_mutex_init(&state->philos[i].eat_m, NULL);
		pthread_mutex_lock(&state->philos[i].eat_m);
		i++;
	}
}

int	init(t_state *state, int argc, char **argv)
{
	state->forks = NULL;
	state->philos = NULL;
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
	state->philos = (t_philo*)malloc(sizeof(*(state->philos)) * state->amount);
	if (!state->philos)
		return (1);
	init_philos(state);
	return (init_forks(state));
}