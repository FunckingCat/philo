/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 14:09:45 by unix              #+#    #+#             */
/*   Updated: 2022/01/05 13:00:21 by unix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	massage(t_philo *philo, char *msg)
{
	uint64_t	delta;
	static int	dead = 0;

	if (dead > 0)
		return ;
	delta = get_time() - philo->state->start;
	pthread_mutex_lock(&philo->state->write);
	if (msg[0] == 'd' && msg[1] == 'i')
		dead = 1;
	printf("%lu %d %s\n", delta, philo->name + 1, msg);
	pthread_mutex_unlock(&philo->state->write);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	is_neg;
	int	res;

	if (!str)
		return (0);
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	is_neg = 1;
	if (str[i] == '-')
		is_neg = -1;
	if (is_neg == -1 || str[i] == '+')
		i++;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
		res = (res * 10) + (str[i++] - '0');
	return (res * is_neg);
}

uint64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

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
			pthread_mutex_destroy(&state->philos[i++].eating_m);
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
