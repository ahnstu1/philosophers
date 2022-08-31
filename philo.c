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

void	philo_left(t_philo *philo)
{
	pthread_mutex_lock(&philo -> left_hand);
	if (philo -> left_state)
	{
		*philo -> left_state = 0;
		pthread_mutex_unlock(&philo -> left_hand);
		philo -> left = 1;
		philo_print(philo, "has taken a fork");
	}
	else
		pthread_mutex_unlock(&philo -> left_hand);
}

void	philo_right(t_philo *philo)
{
	pthread_mutex_lock(&philo -> right_hand);
	if (philo -> right_state)
	{
		*philo -> right_state = 0;
		pthread_mutex_unlock(&philo -> right_hand);
		philo -> right = 1;
		philo_print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo -> left_hand);
		*philo -> left_state = 1;
		pthread_mutex_unlock(&philo -> left_hand);
		philo -> left = 0;
		pthread_mutex_unlock(&philo -> right_hand);
	}
}

void	philo_eating(t_philo *philo)
{
	if (philo -> left && philo -> right)
	{
		pthread_mutex_lock(&philo -> left_hand);
		pthread_mutex_lock(&philo -> right_hand);
		philo_print(philo, "is eating");
		philo -> timestamp = current_time();
		philo -> count_eat++;
		philo_usleep(philo, 1);
		philo -> right = 0;
		philo -> left = 0;
		pthread_mutex_unlock(&philo -> left_hand);
		pthread_mutex_unlock(&philo -> right_hand);
		*philo -> right_state = 1;
		*philo -> left_state = 1;
		philo_print(philo, "is sleeping");
		philo_usleep(philo, 0);
		philo_print(philo, "is thinking");
	}
}

int	end_check(t_philo *philo)
{
	int		idx;
	t_info	*info;
	long long timestamp;
	pthread_mutex_lock(&philo -> info -> die_check);
	info = philo -> info;
	idx = 0;
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
	idx = 0;
	while (idx < info -> philo)
	{
		timestamp = current_time();
		if ((timestamp - philo[idx].timestamp) >= info -> die)
		{
			philo_print(&philo[idx], "died");
			info -> end = 1;
			return (1);
		}
		idx++;
	}
	pthread_mutex_unlock(&philo -> info -> die_check);
	return (0);
}

int	philo_act(t_info *info, t_philo *philo)
{
	if (end_check(philo -> first_philo))
		return (1);
	philo_left(philo);
	if (philo -> left)
		philo_right(philo);
	philo_eating(philo);
	return (0);
}

void	*philo_rot(void	*philo)
{
	t_philo	*tmp;
	t_info	*info;

	tmp = philo;
	info = tmp -> info;
	if (tmp -> id % 2)
		usleep(1000);
	while (!info -> end)
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
	philo_free(philo, idx);
	return (0);
}
