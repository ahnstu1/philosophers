/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahn <hahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 12:50:57 by hahn              #+#    #+#             */
/*   Updated: 2022/08/31 12:50:57 by hahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_init(t_info *info)
{
	int	idx;

	idx = 0;

	info -> share = malloc(sizeof(pthread_mutex_t) * info -> philo);
	if (!info -> share || pthread_mutex_init(&info -> printing, NULL))
		return (1);
	while (idx < info -> philo)
	{
		if (pthread_mutex_init(&(info -> share[idx++]), NULL))
			return (1);
	}
	return (0);
}

int	info_init(char **argv, t_info *info)
{
	if (!info)
		return (1);
	info -> philo = ft_atoi(argv[1]);
	info -> die = ft_atoi(argv[2]);
	info -> eat = ft_atoi(argv[3]);
	info -> sleep = ft_atoi(argv[4]);
	info -> timestamp = current_time();
	if (argv[5] != NULL)
		info -> must = ft_atoi(argv[5]);
	else
		info -> must = -1;
	info -> ate = 0;
	info -> end = 0;
	info -> fork_state = malloc(sizeof(int) * info -> philo);
	memset(info -> fork_state, 1, sizeof(int) * info -> philo);
	if (info -> philo == -1 || info -> die == -1
		|| !info -> fork_state || info -> eat == -1 || info -> sleep == -1
		|| (argv[5] != NULL && info -> must < 1) 
		|| mutex_init(info))
		return (1);
	return (0);
}

int	philo_init(t_info *info, t_philo **philo)
{
	int	idx;

	idx = 0;
	*philo = malloc(sizeof(t_philo) * info -> philo);
	if (!(*philo))
		return (1);
	while (idx < info -> philo)
	{
		(*philo)[idx].id = idx;
		(*philo)[idx].left = 0;
		(*philo)[idx].right = 0;
		(*philo)[idx].left_state = &info -> fork_state[idx];
		(*philo)[idx].right_state = &(info -> fork_state[(idx + 1) % info -> philo]);
		(*philo)[idx].left_hand = &(info -> share[idx]);
		(*philo)[idx].right_hand = &(info -> share[(idx + 1) % info -> philo]);
		(*philo)[idx].count_eat = 0;
		(*philo)[idx].must_flag = 0;
		(*philo)[idx].info = info;
		(*philo)[idx].timestamp = info -> timestamp;
		(*philo)[idx].first_philo = &(*philo)[0];
		idx++;
	}
	return (0);
}
