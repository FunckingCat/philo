/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   massage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unix <unix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 18:14:58 by unix              #+#    #+#             */
/*   Updated: 2021/12/30 18:19:53 by unix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	massage(t_philo *philo, char *msg)
{
	uint64_t	delta;

	delta = get_time() - philo->state->start;
	pthread_mutex_lock(&philo->state->write);
	printf("%lu %d %s\n", delta, philo->name, msg);
	pthread_mutex_unlock(&philo->state->write);
}