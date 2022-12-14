/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahn <hahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 12:49:07 by hahn              #+#    #+#             */
/*   Updated: 2022/08/31 12:49:07 by hahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	current_time(void)
{
	struct timeval	time;
	long long		ret;

	gettimeofday(&time, NULL);
	ret = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ret);
}

int	ft_atoi(const char *str)
{
	int	output;

	output = 0;
	while (*str >= '0' && *str <= '9')
	{
		if (output > 0 && output * 10 <= 0)
			return (-1);
		output *= 10;
		output += *(str++) - '0';
	}
	if (*str)
		return (-1);
	return (output);
}

void	err_msg(void)
{
	printf("Error\n");
}

void	philo_print(t_philo *philo, char *msg, int flag)
{
	t_info		*info;
	int			id;
	long long	timestamp;

	info = philo -> info;
	id = philo -> id + 1;
	pthread_mutex_lock(&philo -> info -> printing);
	timestamp = current_time() - info -> timestamp;
	if (!info -> end || flag)
		printf("%lld %d %s\n", timestamp, id, msg);
	pthread_mutex_unlock(&philo -> info -> printing);
}

void	philo_usleep(t_philo *philo, int time_it_take)
{
	long long	timestamp;
	long long	timestamp_ing;

	timestamp = current_time();
	while (!philo -> info -> end)
	{
		timestamp_ing = current_time();
		if ((timestamp_ing - timestamp) >= time_it_take)
			break ;
		usleep(10);
	}
}
