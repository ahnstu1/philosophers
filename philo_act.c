/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahn <hahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 07:29:08 by hahn              #+#    #+#             */
/*   Updated: 2022/09/01 07:32:08 by hahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
