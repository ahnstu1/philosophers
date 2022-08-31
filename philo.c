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
