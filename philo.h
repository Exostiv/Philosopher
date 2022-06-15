/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicoue <tnicoue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:45:46 by tnicoue           #+#    #+#             */
/*   Updated: 2022/06/14 16:06:45 by kevyn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>


struct s_philo;

typedef struct s_philo_content
{
	int		numphilo;
	pthread_t		philo;
	pthread_mutex_t	fork;
	int		action;
	int		death;
	struct s_philo *remont;
}	t_philoc ;

typedef struct s_philo
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_philosophers;
	int	number_of_time_philosopher_must_eat;
	long long sec;
	pthread_mutex_t	mutex;
	t_philoc *philo;
} t_mainphi;

void	* routine();
void	ft_eat(t_philoc *philo);
void	ft_sleep(t_philoc *philo);
int		parse(int argc, char **argv, t_mainphi *philo);
long	init_ms(void);
void	init_phil(t_mainphi *philo);

#endif
