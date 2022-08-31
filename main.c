/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahn <hahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 12:50:32 by hahn              #+#    #+#             */
/*   Updated: 2022/08/31 12:50:32 by hahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_free(t_philo *philo, int count)
{
	int		idx;
	t_info	*info;

	idx = 0;
	info = philo[0].info;
	pthread_mutex_destroy(&philo -> info -> printing);
	pthread_mutex_destroy(&philo -> info -> eating);
	while (idx < philo -> count_eat)
	{
		pthread_mutex_destroy(&philo[idx].left_hand);
		pthread_mutex_destroy(&philo[idx].right_hand);
		idx++;
	}
	idx = 0;
	while (idx < count)
		pthread_join(philo[idx++].tid, NULL);
	free(philo);
}

int	main(int argc, char **argv)
{
	t_info		info;
	t_philo		*philo;

	if (!(argc == 5 || argc == 6) || info_init(argv, &info)
		|| philo_init(&info, &philo)
		|| philo_main (&info, philo))
		err_msg();
}
