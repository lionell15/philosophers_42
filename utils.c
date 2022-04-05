/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lespinoz <lespinoz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:35:20 by lespinoz          #+#    #+#             */
/*   Updated: 2022/04/05 16:25:46 by lespinoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	timestamp(void)
{
	struct timeval	t1;

	gettimeofday(&t1, NULL);
	return ((t1.tv_sec * 1000) + (t1.tv_usec / 1000));
}

long long	time_result(long long start, long long finish)
{
	return (finish - start);
}

void	sleep_philo(long long time, t_game_rules *rules)
{
	long long	i;

	i = timestamp();
	while (!(rules->died))
	{
		if (time_result(i, timestamp()) >= time)
			break ;
		usleep(50);
	}
}

void	print_status(t_game_rules *rules, int id, char *str)
{
	pthread_mutex_lock(&(rules->write_status));
	if (!(rules->died))
	{
		printf("%lli ", timestamp() - rules->start_time);
		printf("%i ", id + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(rules->write_status));
	return ;
}
