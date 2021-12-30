/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itnit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 14:38:01 by unix              #+#    #+#             */
/*   Updated: 2021/12/30 14:38:28 by unix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init(t_state *state, int argc, char **argv)
{
	state->forks_m = NULL;
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
	return (0);
}