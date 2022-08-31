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
	t_mutex	*mutex;
	t_info	*info;

	idx = 0;
	mutex = philo[0].mutex;
	info = philo[0].info;
	pthread_mutex_destroy(&mutex -> printing);
	pthread_mutex_destroy(&mutex -> eating);
	while (idx < info -> philo)
		pthread_mutex_destroy(&(mutex -> fork[idx++]));
	idx = 0;
	while (idx < count)
		pthread_join(philo[idx++].tid, NULL);
	free(philo);
}

int	main(int argc, char **argv)
{
	t_info		info;
	t_mutex		mutex;
	t_philo		*philo;

	if (!(argc == 5 || argc == 6) || info_init(argv, &info)
		||mutex_init(&info, &mutex) || philo_init(&info, &philo, &mutex)
		|| philo_main (&info, philo, &mutex))
		err_msg();
}
