/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahn <hahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 12:49:53 by hahn              #+#    #+#             */
/*   Updated: 2022/08/31 12:49:53 by hahn             ###   ########.fr       */
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
	int		idx;
	t_info	*info;
	long long timestamp;

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
				printf("catch time %lld\n", timestamp - philo[idx].timestamp);
				info -> end = 1;
				philo_print(&philo[idx], "died", 1);
				return (1);
			}
			idx++;
		}
	}
	return (0);
}

void	philo_left(t_philo *philo)
{
	pthread_mutex_lock(philo -> left_hand);
	if (*philo -> left_state)
	{
		*philo -> left_state = 0;
		pthread_mutex_unlock(philo -> left_hand);
		philo_print(philo, "has taken a fork", 0);
		philo -> left = 1;
	}
	else
		pthread_mutex_unlock(philo -> left_hand);
}

void	philo_eating(t_philo *philo)
{
		pthread_mutex_lock(philo -> left_hand);
		pthread_mutex_lock(philo -> right_hand);
		philo_print(philo, "is eating", 0);
		philo -> timestamp = current_time();
		philo -> count_eat++;
		philo_usleep(philo, philo -> info -> eat);
		*philo -> right_state = 1;
		*philo -> left_state = 1;
		pthread_mutex_unlock(philo -> left_hand);
		pthread_mutex_unlock(philo -> right_hand);
		philo -> right = 0;
		philo -> left = 0;
		philo_print(philo, "is sleeping", 0);
		philo_usleep(philo, philo -> info -> sleep);
		usleep(200);
		philo_print(philo, "is thinking", 0);
}

void	philo_right(t_philo *philo)
{
	pthread_mutex_lock(philo -> right_hand);
	if (*philo -> right_state)
	{
		*philo -> right_state = 0;
		pthread_mutex_unlock(philo -> right_hand);
		philo_print(philo, "has taken a fork", 0);
		philo -> right = 1;
		philo_eating(philo);
	}
	else
		pthread_mutex_unlock(philo -> right_hand);
}

int	philo_act(t_info *info, t_philo *philo)
{
	philo_left(philo);
	if (info -> philo > 1 && philo -> left)
		philo_right(philo);
	return (0);
}

void	*philo_rot(void	*philo)
{
	t_philo	*tmp;
	t_info	*info;
	int		state;

	tmp = philo;
	info = tmp -> info;
	if (tmp -> id % 2)
		usleep(1000);
	else
		usleep(500);
	while (!tmp -> info -> end)
	{
		if (philo_act(info, philo))
			break ;
	}
	return (NULL);
}

int	philo_main(t_info *info, t_philo *philo)
{
	int			idx;

	idx = 0;
	while (idx < info -> philo)
	{
		if (pthread_create(&(philo[idx].tid), NULL, philo_rot, &(philo[idx])))
			return (1);
		idx++;
	}
	end_check(philo -> first_philo);
	philo_free(philo, idx);
	return (0);
}
