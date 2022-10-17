/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicoue <tnicoue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:38:26 by tnicoue           #+#    #+#             */
/*   Updated: 2022/09/07 14:04:01 by tnicoue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat2(t_philoc *p)
{
	sem_wait(p->remont->print);
	printf("%lld ms %d is eating\n",
		(init_ms() - p->remont->sec), (p->numphi + 1));
	sem_post(p->remont->print);
	ft_usleep(p->remont->time_to_eat);
}

void	ft_sleep(t_philoc *p)
{
	sem_wait(p->remont->print);
	printf("%lld ms %d is sleeping\n",
		(init_ms() - p->remont->sec), (p->numphi + 1));
	sem_post(p->remont->print);
	ft_usleep(p->remont->time_to_sleep);
}

void	sem_lock(t_philoc *philo)
{
	sem_wait(philo->remont->fork);
	sem_wait(philo->remont->fork);
}

void	sem_unlock(t_philoc *philo)
{
	sem_post(philo->remont->fork);
	sem_post(philo->remont->fork);
}

void	ft_stop_sem(t_mainphi *philo)
{
	if (philo->finito == philo->number_of_philosophers || philo->chkdeath > 0)
	{
		sem_unlink("print");
		sem_unlink("fork");
		free(philo->philo);
	}
}
