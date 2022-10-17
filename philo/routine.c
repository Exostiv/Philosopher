/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicoue <tnicoue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:52:22 by tnicoue           #+#    #+#             */
/*   Updated: 2022/09/07 11:03:25 by tnicoue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philoc	*philo;
	int			i;

	i = 0;
	usleep(10);
	philo = (t_philoc *)arg;
	if (philo->numphi % 2)
		ft_usleep(200);
	while (1)
	{
		ft_eat(philo);
		ft_sleep(philo);
		pthread_mutex_lock(&philo->remont->print);
		printf("%lld ms %d is thinking\n",
			(init_ms() - philo->remont->sec), philo->numphi + 1);
		pthread_mutex_unlock(&philo->remont->print);
		if (philo->remont->number_of_time_philosopher_must_eat > 0)
		{
			i++;
			if (i == philo->remont->number_of_time_philosopher_must_eat)
				return (0);
		}
	}
	philo->remont->finito++;
	return (NULL);
}

long	init_ms(void)
{
	struct timeval	timestruct;
	long long		ms;

	gettimeofday(&timestruct, NULL);
	ms = timestruct.tv_sec * 1000 + timestruct.tv_usec / 1000;
	return (ms);
}

int	checkdeath(t_philoc *philo)
{
	if (init_ms() - philo->remont->sec > philo->death
		&& philo->remont->chkdeath == 0)
	{
		pthread_mutex_lock(&philo->remont->print);
		printf("%lld ms %d died\n",
			(init_ms() - philo->remont->sec), philo->numphi + 1);
		return (1);
	}
	if (init_ms() - philo->remont->sec > philo->death)
		return (1);
	return (0);
}

void	ft_eat(t_philoc *philo)
{
	int	i;

	i = philo->numphi;
	thread_lock(philo, i);
	if (i == philo->remont->number_of_philosophers - 1)
		i = -1;
	pthread_mutex_lock(&philo->remont->print);
	printf("%lld ms %d has taken fork\n",
		(init_ms() - philo->remont->sec), philo->numphi + 1);
	pthread_mutex_unlock(&philo->remont->print);
	pthread_mutex_lock(&philo->remont->print);
	printf("%lld ms %d has taken fork to %d\n",
		(init_ms() - philo->remont->sec), philo->numphi + 1, i + 2);
	pthread_mutex_unlock(&philo->remont->print);
	if (checkdeath(philo) == 1)
		exit (0);
	ft_eat2(philo);
	if (checkdeath(philo) == 1)
		exit (0);
	pthread_mutex_lock(&philo->remont->print);
	printf("%lld ms %d is done eating\n",
		(init_ms() - philo->remont->sec), philo->numphi + 1);
	pthread_mutex_unlock(&philo->remont->print);
	philo->death += philo->remont->time_to_die;
	thread_unlock(philo, i);
}

void	ft_usleep(long time)
{
	long	start_time;

	start_time = init_ms();
	while (init_ms() - start_time < time)
		usleep(time * 10);
}
