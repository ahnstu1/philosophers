/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahn <hahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 07:28:18 by hahn              #+#    #+#             */
/*   Updated: 2022/09/01 07:36:52 by hahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	must_check(t_philo *philo)
{
	int		idx;
	t_info	*info;

	info = philo -> info;
	while (idx < info -> philo)
	{
		if (philo[idx].must_flag == 0 && philo[idx].count_eat == info -> must)
		{
			philo[idx].must_flag = 1;
			info -> ate++;
		}
		if (info -> ate == info -> philo)
		{
			info -> end = 1;
			return (1);
		}
		idx++;
	}
	return (0);
}

int	end_check(t_philo *philo)
{
	int			idx;
	t_info		*info;
	long long	timestamp;

	info = philo -> info;
	while (!info -> end)
	{
		if (philo -> info -> must > 0 && must_check(philo))
			return (1);
		idx = 0;
		while (idx < info -> philo)
		{
			timestamp = current_time();
			if ((timestamp - philo[idx].timestamp) >= (long long)info -> die)
			{
				info -> end = 1;
				philo_print(&philo[idx], "died", 1);
				return (1);
			}
			idx++;
		}
	}
	return (0);
}
