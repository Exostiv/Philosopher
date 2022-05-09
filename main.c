/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicoue <tnicoue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:45:25 by tnicoue           #+#    #+#             */
/*   Updated: 2022/05/09 11:57:57 by tnicoue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t mutex;

void* test()
{
    pthread_mutex_lock(&mutex);
    printf("test des threads\n");
    sleep(5);
    printf("ca fonctionne bien\n");
    pthread_mutex_unlock(&mutex);
}

int main()
{
    pthread_t philo, philo2;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&philo, NULL, &test, NULL);
    pthread_create(&philo2, NULL, &test, NULL);
    pthread_join(philo, NULL);
    pthread_join(philo2, NULL);
    return 0;
}