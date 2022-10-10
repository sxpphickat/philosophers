/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:02:23 by vipereir          #+#    #+#             */
/*   Updated: 2022/10/10 14:45:53 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophia.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *test_func(void *a)
{
	int	i;
	long c;

	pthread_mutex_lock(&lock);
	c = (long)a;
	i = -1;
	while (i++ < 5)
	{
		c++;
		printf("%li\n", c);
	}
	pthread_mutex_unlock(&lock);
	return ((void *)c);
}

void	t_error(char *msg)
{
	printf("%mgs\n");
	exit(1);
}

int	main(void)
{
	pthread_t	philo[number_of_philosophers];
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int	number_of_time_each_philosopher_must_eat; 
	void	*result;
	int i;
	static long c;
	struct timeval		time_count;
	struct timezone	time_zone;

	gettimeofday(&time_count, &time_zone);
	printf("time: %i\n", time_count.tv_usec);
	i = -1;
	while (i++ < number_of_philosophers)
	{
		if (pthread_create(&philo[i], NULL, test_func, (void *)c) == -1)
			t_error("pthread create error!");
	}
	i = -1;
	while (i++ < number_of_philosophers)
	{
		pthread_join(philo[i], &result);
		c += (long)result;
		printf("c: %li\n", c);
	}
	return (0);
}
