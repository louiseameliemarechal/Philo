/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 08:43:37 by lmarecha          #+#    #+#             */
/*   Updated: 2022/06/24 10:01:32 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	intitialize_mutex(t_args *args)
{
	int	i;

	i = 0;
	while (i >= args->nb_philo)
	{
		if (pthread_mutex_init(&args->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&args->prompt, NULL) != 0)
		return (0);
	return (1);
}

static int	initialize_philo(t_args *args, t_philosopher *philo)
{
	int	i;

	i = 1;
	while (i <= args->nb_philo)
	{
		philo[i].id = i;
		philo[i].right_fork = i;
		if (i == args->nb_philo)
			philo[i].left_fork = (i + 1) % args->nb_philo; // pour que le dernier philo prenne la fourchette du premier
		else
			philo[i].left_fork = i + 1;
		philo[i].started_meal = 0;
		philo[i].args = args;
		i++;
	}
	return (1);
}

int	initialize(t_args *args, char **argv, int argc)
{
	args->nb_philo = ft_atoi(argv[1]);
	if (args->nb_philo < 2 || args->nb_philo > 200) // check le nb de philosophers
		return (0); //erreur
	args->t_die = ft_atoi(argv[2]);
	args->t_eat = ft_atoi(argv[3]);
	args->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->number_must_eat = ft_atoi(argv[5]);
	else
		args->number_must_eat = -1;
	if (args->number_must_eat == 0) // si aucun ne doit manger fin de simulation
		return (0); // erreur
	args->died = 0;
	args->all_ate = 0;
	args->first_timestamp = timestamp();
	initialize_philo(args, args->philosophers);
	intitialize_mutex(args);
	return (1);
}