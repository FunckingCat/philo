/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 14:37:57 by unix              #+#    #+#             */
/*   Updated: 2022/01/02 16:58:29 by unix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clear_state(t_state *state)
{
	int	i;

	if (state->forks)
	{
		i = 0;
		while (i < state->amount)
			pthread_mutex_destroy(&state->forks[i++]);
		free(state->forks);
	}
	if (state->philos)
	{
		i = 0;
		while (i < state->amount)
		{
			pthread_mutex_destroy(&state->philos[i].eating_m);
			pthread_mutex_destroy(&state->philos[i++].eat_m);
		}
		free(state->philos);
	}
	pthread_mutex_destroy(&state->write);
	pthread_mutex_destroy(&state->death_occur);
	return (1);
}

int	error(char *msg)
{
	printf("Error: %s\n", msg);
	return (1);
}
