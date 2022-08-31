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
# include <string.h>
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
	int			*fork_state;
	long long	timestamp;
	pthread_mutex_t	printing;
	pthread_mutex_t	*share;
}	t_info;

typedef struct s_philo
{
	int				id;
	long long		timestamp;
	int				count_eat;
	int				must_flag;
	int				*left_state;
	int				*right_state;
	int				left;
	int				right;
	pthread_t		tid;
	pthread_mutex_t	*left_hand;
	pthread_mutex_t	*right_hand;
	struct s_philo	*first_philo;
	struct s_info	*info;
}	t_philo;

int			info_init(char **argv, t_info *info);
int	end_check(t_philo *philo);
int			mutex_init(t_info *info);
int			philo_init(t_info *info, t_philo **philo);
int			philo_main(t_info *info, t_philo *philo);
void		philo_free(t_philo *philo, int count);
void		*philo_rot(void	*philo);
int			philo_act(t_info *info, t_philo *philo);
void		philo_print(t_philo *philo, char *msg, int flag);
void		philo_usleep(t_philo *philo, int time_it_take);
long long	current_time(void);
int			ft_atoi(const char *str);
void		err_msg(void);
#endif