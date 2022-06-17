/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:22:28 by druth             #+#    #+#             */
/*   Updated: 2022/06/16 16:22:29 by druth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

/* input times: [0] = time to die since starting last meal,
	[1] = time to eat 1 meal, [2] = time to sleep */

typedef struct s_setup
{
	int			philo_num;
	long long	input_times[3];
	int			eat_num;
	long long	start_time;
}	t_setup;

typedef struct s_info
{
	int				death;
	int				print;
	long long		*kill_time;
	int				*eat_track;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	*kill;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*eat_lock;

}	t_info;

typedef struct s_philo
{
	int		num;
	int		locks[2];
	t_info	*info;
	t_setup	setup;
}	t_philo;

int			ft_initialize(t_setup *setup, int ac, char *av[]);
t_philo		*ft_philo_initialize(t_info *info, t_philo *philo,
				t_setup setup, int track);
long long	ft_current_time(void);
void		*ft_philosopher(void *parameter);
int			ft_death_check(t_philo *philo, int flag);
int			ft_waiting(t_philo *philo, long long limit, int flag);
void		*ft_philosopher_num_eat(void *parameter);
void		ft_death_timing(t_info *info, t_setup setup, int track);
int			ft_free(t_info *info, t_philo *philo, t_setup setup, char *output);
void		ft_printer(t_philo *philo, char *message);
void		ft_philosopher_loop(t_philo *philo);
void		ft_philosopher_eat_loop(t_philo *philo);
int			ft_sleep_think(t_philo *philo);
int			ft_eating_forks(t_philo *philo);

#endif
