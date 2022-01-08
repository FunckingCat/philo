/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamcha <tyamcha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 14:38:01 by unix              #+#    #+#             */
/*   Updated: 2022/01/08 13:53:02 by tyamcha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_state *state)
{
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_DEAD);
	state->forks = sem_open(SEM_FORK, O_CREAT | O_EXCL, 0644, state->amount);
	state->write = sem_open(SEM_WRITE, O_CREAT | O_EXCL, 0644, 1);
	state->death_occur = sem_open(SEM_DEAD, O_CREAT | O_EXCL, 0644, 0);
	return (0);
}

int	ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (i);
}

void	make_name(char *buf, int pos)
{
	int	i;

	i = ft_strcpy(buf, SEM_PHILO);
	pos++;
	while (pos > 0)
	{
		buf[i++] = (pos % 10) + '0';
		pos /= 10;
	}
	buf[i] = 0;
}

void	init_philos(t_state *state)
{
	int		i;
	char	name[100];

	i = 0;
	while (i < state->amount)
	{
		state->philos[i].name = i;
		state->philos[i].eat_count = 0;
		state->philos[i].state = state;
		make_name(name, i);
		sem_unlink(name);
		state->philos[i].eat_sem = sem_open(name, O_CREAT | O_EXCL, 0644, 1);
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
	if (state->amount < 1 || state->must_eat < 0)
		return (1);
	state->philos = (t_philo *)malloc(sizeof(*(state->philos)) * state->amount);
	if (!state->philos)
		return (1);
	init_philos(state);
	return (init_forks(state));
}
