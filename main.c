#include "philo.h"

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