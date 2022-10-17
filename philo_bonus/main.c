/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicoue <tnicoue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:45:25 by tnicoue           #+#    #+#             */
/*   Updated: 2022/09/07 13:28:22 by tnicoue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse2(char **argv, int i)
{
	int	y;

	y = 0;
	while (argv[i])
	{
		while (argv[i][y])
		{
			if (isdigit(argv[i][y]) == 0)
			{
				printf("Les arguments en entrée ne sont pas des digits\n");
				return (0);
			}
			y++;
		}
		y = 0;
		i++;
	}
	return (1);
}

void	init_phil(t_mainphi *philo)
{
	int	i;

	i = 0;
	philo->philo = malloc(sizeof(t_philoc) * philo->number_of_philosophers);
	while (i != philo->number_of_philosophers)
	{
		philo->philo[i].death = philo->time_to_die;
		philo->philo[i].remont = philo;
		i++;
	}
}

int	parse(int argc, char **argv, t_mainphi *philo)
{
	int	i;

	philo->sec = init_ms();
	if (argc < 5 || argc > 6)
	{
		printf("Il n'y a pas le bon nombre d'arguments\n");
		return (0);
	}
	i = 1;
	if (parse2(argv, i) == 0)
		return (0);
	philo->finito = 0;
	philo->chkdeath = 0;
	philo->number_of_philosophers = atoi(argv[1]);
	philo->time_to_die = atoi(argv[2]);
	philo->time_to_eat = atoi(argv[3]);
	philo->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		philo->number_of_time_philosopher_must_eat = atoi(argv[5]);
	else
		philo->number_of_time_philosopher_must_eat = 0;
	init_phil(philo);
	return (1);
}

void	pcreate(t_mainphi *p)
{	
	int	i;

	i = 0;
	while (i < p->number_of_philosophers)
	{
		pthread_create(&p->philo[i].philo, NULL, &routine, &p->philo[i]);
		p->philo[i].numphi = i;
		i++;
		pthread_detach(p->philo[i].philo);
	}
	i = 0;
	while (i < p->number_of_philosophers)
	{
		pthread_join(p->philo[i].philo, NULL);
		i++;
	}
	ft_stop_sem(p);
}

int	main(int argc, char *argv[])
{
	t_mainphi	p;

	if (parse(argc, argv, &p) == 0)
		return (0);
	if (atoi(argv[1]) == 1)
	{
		printf("%d 1 died\n", atoi(argv[2]));
		return (0);
	}
	if (atoi(argv[1]) == 0)
	{
		printf("Error no Philo\n");
		return (0);
	}
	sem_unlink("print");
	sem_unlink("forks");
	p.print = sem_open("print", O_CREAT, 0666, 1);
	p.fork = sem_open("forks", O_CREAT, 0666, p.number_of_philosophers);
	pcreate(&p);
	return (0);
}
