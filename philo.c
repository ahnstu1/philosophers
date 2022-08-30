#include "philo.h"

int	philo_ate(t_info *info, t_philo *philo)
{
	if (info -> must && !info -> end)
	{
		if (info -> must == philo -> count_eat)
			info -> ate++;
		if (info -> philo == info -> ate)
		{
			info -> end++;
			return (1);
		}
	}
	return (0);
}

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
				break;
			}
			idx++;
		}
	}
}

int	philo_act(t_info *info, t_philo *philo)
{
	t_mutex	*mutex;

	mutex = philo -> mutex;
	pthread_mutex_lock(&(mutex -> fork[philo -> left]));
	philo_print(philo, "has taken a fork");
	if (info -> philo != 1)
	{
		pthread_mutex_lock(&(mutex -> fork[philo -> right]));
		philo_print(philo, "has taken a fork");
		philo_print(philo, "is eating");
		philo -> timestamp = current_time();
		philo -> count_eat++;
		philo_usleep(philo, 1);
		pthread_mutex_unlock(&(mutex -> fork[philo -> right]));
	}
	pthread_mutex_unlock(&(mutex -> fork[philo -> left]));
	if (philo_ate(info, philo))
		return (1);
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
	while (!(info -> end))
	{
		if (philo_act(info, philo))
			break;
	} 
}

void philo_free(t_philo *philo, int count)
{
	int	idx;
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

int	philo_main(t_info *info, t_philo *philo, t_mutex *mutex)
{
	int	idx;

	idx = 0;
	while (idx < info -> philo)
	{
		philo[idx].timestamp = current_time();
		if (pthread_create(&(philo[idx].tid), NULL, philo_rot, &(philo[idx])))
			return(1);
		idx++;
	}
	philo_die(info, philo);
	philo_free(philo, idx);
	return (0);
}