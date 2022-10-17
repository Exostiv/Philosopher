/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicoue <tnicoue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:45:46 by tnicoue           #+#    #+#             */
/*   Updated: 2022/09/06 13:59:33 by tnicoue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <ctype.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>
# include <fcntl.h>

struct	s_philo;

typedef struct s_philo_content
{
	int				numphi;
	pthread_t		philo;
	pthread_mutex_t	fork;
	int				action;
	int				death;
	struct s_philo	*remont;
}	t_philoc;

typedef struct s_philo
{
	int				finito;
	int				chkdeath;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_philosophers;
	int				number_of_time_philosopher_must_eat;
	long long		sec;
	pthread_mutex_t	print;
	t_philoc		*philo;
}	t_mainphi;

void	*routine(void *arg);
void	ft_eat(t_philoc *philo);
void	ft_eat2(t_philoc *philo);
void	ft_sleep(t_philoc *philo);
int		parse(int argc, char **argv, t_mainphi *philo);
long	init_ms(void);
void	init_phil(t_mainphi *philo);
void	ft_usleep(long time);
void	thread_lock(t_philoc *philo, int i);
void	thread_unlock(t_philoc *philo, int i);
void	ft_stop_mutex(t_mainphi *philo);

#endif
