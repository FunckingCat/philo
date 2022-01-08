/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamcha <tyamcha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 14:09:45 by unix              #+#    #+#             */
/*   Updated: 2022/01/08 13:50:43 by tyamcha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	massage(t_philo *philo, char *msg)
{
	uint64_t	delta;
	static int	dead = 0;

	sem_wait(philo->state->write);
	delta = get_time() - philo->state->start;
	if (dead > 0)
		return ;
	if (msg[0] == 'd')
		dead = 1;
	printf("%llu %d %s\n", delta, philo->name + 1, msg);
	usleep(10);
	sem_post(philo->state->write);
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
	int		i;
	char	name[100];

	sem_unlink(SEM_FORK);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_DEAD);
	if (state->philos)
	{
		i = 0;
		while (i < state->amount)
		{
			make_name(name, i);
			sem_unlink(name);
			i++;
		}
		free(state->philos);
	}
	return (1);
}

int	error(char *msg)
{
	printf("Error: %s\n", msg);
	return (1);
}
