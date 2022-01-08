/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamcha <tyamcha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:47:22 by tyamcha           #+#    #+#             */
/*   Updated: 2022/01/08 13:50:19 by tyamcha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*spectator(void	*ptr)
{
	t_state	*state;
	int		i;

	state = (t_state *)ptr;
	i = 0;
	while (i++ < state->amount)
		wait(NULL);
	sem_post(state->death_occur);
	return (NULL);
}

int	spawn_philo(t_state *state)
{
	int			i;
	pthread_t	tid;

	state->start = get_time();
	i = 0;
	while (i < state->amount)
	{
		state->philos[i].pid = fork();
		if (state->philos[i].pid < 0)
			return (1);
		else if (state->philos[i].pid == 0)
		{
			philosoph(&state->philos[i]);
			exit(0);
		}
		i++;
	}
	if (state->must_eat > 0)
		pthread_create(&tid, NULL, spectator, (void *)state);
	return (0);
}

int	main(int argc, char **argv)
{
	int		i;
	t_state	state;

	if (argc < 5 || argc > 6)
		return (error("arguments ammount"));
	if (init(&state, argc, argv))
		return (clear_state(&state) && error("arguments"));
	if (spawn_philo(&state))
		return (clear_state(&state) && error("runtime"));
	sem_wait(state.death_occur);
	i = 0;
	while (i < state.amount)
		kill(state.philos[i++].pid, SIGKILL);
	clear_state(&state);
	return (0);
}
