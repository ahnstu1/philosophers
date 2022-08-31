/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahn <hahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 12:50:41 by hahn              #+#    #+#             */
/*   Updated: 2022/08/31 12:50:41 by hahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_info
{
	int			philo;
	int			die;
	int			eat;
	int			sleep;
	int			must;
	int			ate;
	int			end;
	long long	timestamp;
}	t_info;

typedef struct s_philo
{
	int				id;
	int				left;
	int				right;
	long long		timestamp;
	int				count_eat;
	pthread_t		tid;
	struct s_info	*info;
	struct s_mutex	*mutex;
}	t_philo;

typedef struct s_mutex {
	pthread_mutex_t	*fork;
	pthread_mutex_t	printing;
	pthread_mutex_t	eating;
}	t_mutex;

int			info_init(char **argv, t_info *info);
int			mutex_init(t_info *info, t_mutex *mutex);
int			philo_init(t_info *info, t_philo **philo, t_mutex *mutex);
int			philo_main(t_info *info, t_philo *philo, t_mutex *mutex);
void		philo_free(t_philo *philo, int count);
void		*philo_rot(void	*philo);
int			philo_act(t_info *info, t_philo *philo);
void		philo_print(t_philo *philo, char *msg);
void		philo_usleep(t_philo *philo, int flag);
long long	current_time(void);
int			ft_atoi(const char *str);
void		err_msg(void);
#endif