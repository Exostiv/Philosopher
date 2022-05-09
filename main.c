/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicoue <tnicoue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:45:25 by tnicoue           #+#    #+#             */
/*   Updated: 2022/05/09 13:13:04 by tnicoue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t mutex;

void* test()
{
    pthread_mutex_lock(&mutex);
    printf("test des threads\n");
    sleep(0.2);
    printf("ca fonctionne bien\n");
    pthread_mutex_unlock(&mutex);
    return(NULL);
}

int test2(int argc, char* argv[]){
    
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_time_philosopher_must_eat;
    
    if (argc < 5 || argc > 6)
        return(0);
    number_of_philosophers = atoi(argv[1]);
    time_to_die = atoi(argv[2]);
    time_to_eat = atoi(argv[3]);
    time_to_sleep = atoi(argv[4]);
    if (argc == 6)
        number_of_time_philosopher_must_eat = atoi(argv[5]);
    else
        number_of_time_philosopher_must_eat = 0;
    printf("numbers of philo = %d\n", number_of_philosophers);
    printf("time to die  = %d\n", time_to_die);
    printf("time to eat  = %d\n", time_to_eat);
    printf("time to sleep  = %d\n", time_to_sleep);
    printf("numbers of philo must eat = %d\n", number_of_time_philosopher_must_eat);
    //recuperer les valeur et les mettre a /1000 (pour les time to, conversion seconde a millisecondes)
    return(1);
}

int main(int argc, char* argv[])
{
    pthread_t philo, philo2, philo3;
    if (test2(argc, argv) == 0)
        return(printf("Il n'y a pas le bon nombre d'arguments en entrée\n"));
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&philo, NULL, &test, NULL);
    pthread_create(&philo2, NULL, &test, NULL);
    pthread_create(&philo3, NULL, &test, NULL);
    pthread_join(philo, NULL);
    pthread_join(philo2, NULL);
    pthread_join(philo3, NULL);
    return 0;
}

//numbers of philosophers
//time to die 
//time to eat 
//time to sleep 
//number of times each philosopher must eat (optionnal)

//chaques philosophers se voit assigner un numero entre n et 1 (min 1 philo)
//chaque philo est assis entre le philo n - 1 et n + 1

//afficher le timestamp avec ce que font les philosophers 1 par 1 
//(taken a fork, eating, sleeping, thinking, died)

//chaque messages bien disctints, pas plus de 10 ms 
//entre la mort d'un philosophe et son affichage ( ils doivent eviter de mourir)

//chaque philo represente par un thread