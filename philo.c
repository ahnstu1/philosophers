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

void	philo_die(t_info *info, t_philo *philo)
{
	int			idx;
	long long	timestamp;

	while (!info -> end)
	{
		idx = 0;
		while (idx < info -> philo)
		{
			timestamp = current_time();
			if ((timestamp - philo[idx].timestamp) >= info -> die)
			{
				philo_print(&philo[idx], "died");
				info -> end = 1;
				break ;
			}
			idx++;
		}
	}
}
void	philo_left(t_philo *philo)
{
	pthread_mutex_lock(philo -> left);
	*philo -> left_state = 1;
	philo_print(philo, "has taken a fork");
	if (!philo -> right_state)
	{
		pthread_mutex_lock(philo -> right);
		*philo -> right_state = 1;
		philo_print(philo, "has taken a fork");
		philo -> timestamp = current_time();
		philo -> count_eat++;
		philo_print(philo, "is eating");
		philo_usleep(philo, 1);
		*philo -> right_state = 0;
		pthread_mutex_unlock(philo -> right);
	}
	*philo -> left_state = 0;
	pthread_mutex_unlock(philo -> left);
}

int	philo_act(t_info *info, t_philo *philo)
{
	philo_left(philo);
	//philo_right(info, philo);
	philo_print(philo, "is sleeping");
	philo_usleep(philo, 0);
	philo_print(philo, "is thinking");
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

void	*monitor_rot(void	*philo)
{
	int		idx;
	t_philo	*tmp;
	t_info	*info;

	tmp = philo;
	info = tmp -> info;
	while (1)
	{
		idx = 0;
		while (idx < info -> philo)
		{
			if (tmp[idx].must_flag == 0 && tmp[idx].count_eat == info -> must)
			{
				tmp[idx].must_flag = 1;
				info -> ate++;
			}
			if (info -> ate == info -> philo)
			{
				info -> end = 1;
				return (NULL);
			}
			idx++;
		}
		idx = 0;
		while (idx < info -> philo)
		{
			if ((current_time() - tmp[idx].timestamp) >= info -> die)
			{
				philo_print(&philo[idx], "died");
				info -> end = 1;
				return (NULL);
			}
			idx++;
		}
	}
	return (NULL);
}

void	philo_must(t_info *info, t_philo *philo)
{
	if (info -> must && !info -> end)
	{
		if (info -> must == philo -> count_eat)
			info -> ate++;
		if (info -> philo == info -> ate)
			info -> end = 1;
	}
}
int	philo_main(t_info *info, t_philo *philo)
{
	pthread_t	monitor;
	int			idx;

	idx = 0;

	while (idx < info -> philo)
	{
		if (pthread_create(&(philo[idx].tid), NULL, philo_rot, &(philo[idx])))
			return (1);
		idx++;
	}
	if (pthread_create(&monitor, NULL, monitor_rot, philo))
		return (1);
	pthread_join(monitor, NULL);
	philo_free(philo, idx);
	return (0);
}
