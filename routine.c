/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicoue <tnicoue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:52:22 by kevyn             #+#    #+#             */
/*   Updated: 2022/06/27 11:46:36 by tnicoue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philoc *philo;

	philo = (t_philoc *)arg;
	ft_eat(philo);
	ft_sleep(philo);
	printf("%lld ms %d is thinking\n", (init_ms() - philo->remont->sec), philo->numphilo);
	return (NULL);
}

long	init_ms(void)
{
	struct timeval timestruct;
	long long	ms;

	gettimeofday(&timestruct, NULL);
	ms = timestruct.tv_sec * 1000LL + timestruct.tv_usec / 1000;
	return (ms);
}

//augmenter la taille de la fonction pour tuer le philo ici (plus de place ft_eat)
int	checkdeath(t_philoc *philo)
{
	if ((init_ms() - philo->remont->sec) > philo->death)
		return(1);
	return (0);
}


void	ft_eat(t_philoc *philo)
{
	int	i;
	
	i = philo->numphilo;
	if (i == philo->remont->number_of_philosophers)
		i = -1;
	//bug present lors de l acces aux valeurs dessous
	pthread_mutex_lock(&philo->fork);
	//printf("prise de pouvoir \n", philo->remont->philo[i + 1]);
	pthread_mutex_lock(&philo->remont->philo[i + 1].fork);
	printf("%lld ms %d has taken fork\n", (init_ms() - philo->remont->sec), philo->numphilo);
	printf("%lld ms %d has taken fork to %d\n", 
			(init_ms() - philo->remont->sec), philo->numphilo, i + 1);
	if (checkdeath(philo) == 1)
	{
		printf("%lld ms %d died\n", (init_ms() - philo->remont->sec), philo->numphilo);
		exit (0);
	}
	printf("%lld ms %d is eating\n", (init_ms() - philo->remont->sec), philo->numphilo);
	usleep(philo->remont->time_to_eat);
	if (checkdeath(philo) == 1)
	{
		printf("%lld ms %d died\n", (init_ms() - philo->remont->sec), philo->numphilo);
		exit (0);
	}
	printf("%lld ms %d is done eating\n", (init_ms() - philo->remont->sec), philo->numphilo);
	philo->death += philo->remont->time_to_die;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->remont->philo[i + 1].fork);
}

void	ft_usleep(long	time)
{
	long start_time;

	start_time = init_ms();
	while (init_ms() - start_time < time)
		usleep(time * 10);
}

void	ft_sleep(t_philoc *philo)
{
	printf("%lld ms %d is sleeping\n", (init_ms() - philo->remont->sec), philo->numphilo);
	//usleep();
}
