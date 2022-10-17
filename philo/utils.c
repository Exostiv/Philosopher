/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicoue <tnicoue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:38:26 by tnicoue           #+#    #+#             */
/*   Updated: 2022/09/07 14:03:50 by tnicoue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat2(t_philoc *p)
{
	pthread_mutex_lock(&p->remont->print);
	printf("%lld ms %d is eating\n",
		(init_ms() - p->remont->sec), (p->numphi + 1));
	pthread_mutex_unlock(&p->remont->print);
	ft_usleep(p->remont->time_to_eat);
}

void	ft_sleep(t_philoc *p)
{
	pthread_mutex_lock(&p->remont->print);
	printf("%lld ms %d is sleeping\n",
		(init_ms() - p->remont->sec), (p->numphi + 1));
	pthread_mutex_unlock(&p->remont->print);
	ft_usleep(p->remont->time_to_sleep);
}

void	thread_lock(t_philoc *philo, int i)
{
	if (i == philo->remont->number_of_philosophers - 1)
		i = -1;
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->remont->philo[i + 1].fork);
}

void	thread_unlock(t_philoc *philo, int i)
{
	if (i == philo->remont->number_of_philosophers - 1)
		i = -1;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->remont->philo[i + 1].fork);
}

void	ft_stop_mutex(t_mainphi *philo)
{
	int	i;

	i = 0;
	if (philo->finito == philo->number_of_philosophers || philo->chkdeath > 0)
	{
		while (i < philo->number_of_philosophers)
		{
			pthread_mutex_destroy(&philo->philo[i++].fork);
		}
		pthread_mutex_destroy(&philo->print);
		free(philo->philo);
	}
}
