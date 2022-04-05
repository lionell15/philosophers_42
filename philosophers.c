/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespinoz <lespinoz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:25:08 by lespinoz          #+#    #+#             */
/*   Updated: 2022/04/05 16:25:10 by lespinoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mutex(t_game_rules *rules)
{
	int	i;

	i = rules->num_philos;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(rules->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(rules->write_status), NULL))
		return (1);
	if (pthread_mutex_init(&(rules->check_eat), NULL))
		return (1);
	return (0);
}

int	init_philosophers(t_game_rules *rules)
{
	int	i;

	i = (int)rules->num_philos;
	while (--i >= 0)
	{
		rules->philosophers[i].id_philo = i;
		rules->philosophers[i].num_eat_philo = 0;
		rules->philosophers[i].fork_left = i;
		rules->philosophers[i].fork_right = (i + 1) % rules->num_philos;
		rules->philosophers[i].last_time_eat = 0;
		rules->philosophers[i].rules = rules;
	}
	return (0);
}

int init_args(t_game_rules *rules, char **arguments)
{
	rules->num_philos = ft_atoi(arguments[1]);
	rules->time_death = ft_atoi(arguments[2]);
	rules->time_eat = ft_atoi(arguments[3]);
	rules->time_sleep = ft_atoi(arguments[4]);
	rules->all_philos_ate = 0;
	rules->died = 0;
	if (rules->num_philos == 1)
	{
		printf("0 1 died \n");
		exit(0);
	}
	if (arguments[5] != NULL || arguments[5] > 0)
		rules->num_limit_eat = ft_atoi(arguments[5]);
	else
		rules->num_limit_eat = 0;
	if (rules->num_philos < 1 || rules->time_death <= 0 || rules->time_eat <= 0
		|| rules->time_sleep <= 0 || rules->num_philos > 250 || rules->num_limit_eat < 0)
		return (1);
	if (init_mutex(rules) == 1)
		return (1);
	if (init_philosophers(rules) == 1)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game_rules	rules;

	if (argc < 5 || argc > 6)
		return (printf("Error: 5 or 6 arguments are needed\n"));
	if (init_args(&rules, argv) == 1)
		return (printf("Error: Wrong argument\n"));
	if (start_dinner(&rules) == 1)
		return (printf("Error: launching game"));
	return (0);
}
