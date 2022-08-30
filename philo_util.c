#include "philo.h"

long long	current_time(void)
{
	struct timeval	time;
	long long		ret;

	gettimeofday(&time, NULL);
	ret = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ret);
}

int	ft_atoi(const char *str)
{
	int	output;

	output = 0;
	while (*str >= '0' && *str <= '9')
	{
		if (output > 0 && output * 10 <= 0)
			return (-1);
		output *= 10;
		output += *(str++) - '0';
	}
	if (*str)
		return (-1);
	return (output);
}

void	err_msg(void)
{
	printf("Error\n");
}

void	philo_print(t_philo *philo, char *msg)
{
	t_mutex		*mutex;
	t_info		*info;
	int			id;
	long long 	timestamp;

	mutex = philo -> mutex;
	info = philo -> info;
	id = philo -> id + 1;
	timestamp = current_time() - info -> timestamp;
	pthread_mutex_lock(&mutex -> printing);
	if (!info -> end)
		printf("%lld %d %s\n", timestamp, id, msg);
	pthread_mutex_unlock(&mutex -> printing);
}

void	philo_usleep(t_philo *philo, int flag)
{
	long long timestamp;
	long long timestamp_ing;
	long long time_it_take;

	timestamp = current_time();
	if (flag)
		time_it_take = (long long)(philo -> info -> eat);
	else
		time_it_take = (long long)(philo -> info -> sleep);
	while (!philo -> info -> end)
	{
		timestamp_ing = current_time();
		if ((timestamp_ing - timestamp) >= time_it_take)
			break;
		usleep(10);
	}
}