/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   massage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 18:14:58 by unix              #+#    #+#             */
/*   Updated: 2022/01/02 17:20:23 by unix             ###   ########.fr       */
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
	printf("%lu %d %s\n", delta, philo->name, msg);
	pthread_mutex_unlock(&philo->state->write);
}