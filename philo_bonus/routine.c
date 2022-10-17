/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicoue <tnicoue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:52:22 by tnicoue           #+#    #+#             */
/*   Updated: 2022/09/07 14:09:00 by tnicoue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philoc	*philo;
	int			i;

	i = 0;
	philo = (t_philoc *)arg;
	usleep(10);
	if (philo->numphi % 2)
		usleep(200);
	while (1)
	{
		ft_eat(philo);
		ft_sleep(philo);
		sem_wait(philo->remont->print);
		printf("%lld ms %d is thinking\n",
			(init_ms() - philo->remont->sec), philo->numphi + 1);
		sem_post(philo->remont->print);
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
		sem_wait(philo->remont->print);
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
	if (i == philo->remont->number_of_philosophers - 1)
		i = -1;
	sem_wait(philo->remont->fork);
	sem_wait(philo->remont->fork);
	sem_wait(philo->remont->print);
	printf("%lld ms %d has taken fork\n",
		(init_ms() - philo->remont->sec), philo->numphi + 1);
	sem_post(philo->remont->print);
	sem_wait(philo->remont->print);
	printf("%lld ms %d has taken fork\n",
		(init_ms() - philo->remont->sec), philo->numphi + 1);
	sem_post(philo->remont->print);
	if (i == philo->remont->number_of_philosophers - 1)
		i = -1;
	if (checkdeath(philo) == 1)
		exit (0);
	ft_eat2(philo);
	if (checkdeath(philo) == 1)
		exit (0);
	philo->death += philo->remont->time_to_die;
	sem_unlock(philo);
}

/*void	ft_eat(t_philoc *philo)
{
	sem_wait(philo->remont->fork);
	ft_print(philo, "has taken fork");
	sem_wait(philo->remont->fork);
	ft_print(philo, "has taken fork");
	ft_print(philo, "is eating");
	ft_usleep(philo->remont->time_to_eat);
	sem_post(philo->remont->fork);
	sem_post(philo->remont->fork);
}*/

void	ft_usleep(long time)
{
	long	start_time;

	start_time = init_ms();
	while (init_ms() - start_time < time)
		usleep(time * 10);
}
