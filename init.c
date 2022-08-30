#include "philo.h"

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
		info -> must = 0;
	info -> ate = 0;
	info -> end = 0;
	if (info -> philo == -1 || info -> die == -1 || info -> eat == -1 \
		|| info -> sleep == -1 || (argv[5] != NULL && info -> must < 1))
			return (1);
	return (0);
}

int	mutex_init(t_info *info, t_mutex *mutex)
{
	int	idx;

	idx = 0;
	mutex -> fork = malloc(sizeof(pthread_mutex_t) * info -> philo);
	if (!mutex -> fork || pthread_mutex_init(&mutex -> eating, NULL)
		|| (pthread_mutex_init(&mutex -> printing, NULL)))
		return (1);
	while (idx < info -> philo)
		if (pthread_mutex_init(&(mutex -> fork[idx++]), NULL))
			return (1);
	return (0);
}

int	philo_init(t_info *info, t_philo **philo, t_mutex *mutex)
{
	int	idx;

	idx = 0;
	*philo = malloc(sizeof(t_philo) * info -> philo);
	if (!(*philo))
		return (1);
	while (idx < info -> philo)
	{
		(*philo)[idx].id = idx;
		(*philo)[idx].left = idx;
		(*philo)[idx].right = (idx + 1) % info -> philo;
		(*philo)[idx].count_eat = 0;
		(*philo)[idx].info = info;
		(*philo)[idx].mutex = mutex;
		idx++;
	}
	return (0);
}