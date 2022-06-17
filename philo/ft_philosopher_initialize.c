/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosopher_initialize.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druth   <druth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:52:37 by druth             #+#    #+#             */
/*   Updated: 2022/06/08 16:40:40 by druth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_eat_check(t_info *info, t_setup setup)
{
	int	track;

	track = 0;
	pthread_mutex_lock(&info->eat_lock[track]);
	while (track < setup.philo_num && info->eat_track[track] >= setup.eat_num)
	{
		pthread_mutex_unlock(&info->eat_lock[track]);
		track++;
		pthread_mutex_lock(&info->eat_lock[track]);
	}
	pthread_mutex_unlock(&info->eat_lock[track]);
	if (track == setup.philo_num)
		return (1);
	return (-1);
}

void	ft_death_timing(t_info *info, t_setup setup, int track)
{
	while (1)
	{
		track = 0;
		while (track < setup.philo_num)
		{
			pthread_mutex_lock(&info->kill[track]);
			if (ft_current_time() >= info->kill_time[track])
			{
				pthread_mutex_unlock(&info->kill[track]);
				pthread_mutex_lock(&(info->print_mutex));
				printf("%lld %d died\n", ft_current_time() - setup.start_time,
					track + 1);
				info->print = 1;
				pthread_mutex_unlock(&(info->print_mutex));
				pthread_mutex_lock(&(info->death_mutex));
				info->death = 1;
				pthread_mutex_unlock(&(info->death_mutex));
				return ;
			}
			pthread_mutex_unlock(&info->kill[track]);
			track++;
		}
		if (setup.eat_num != -1 && ft_eat_check(info, setup) == 1)
			return ;
	}
}

int	ft_info_more(t_info *info, t_philo *philo, t_setup setup, int track)
{
	info->kill = malloc(sizeof(pthread_mutex_t) * setup.philo_num);
	if (info->kill == NULL)
		return (ft_free(info, philo, setup, "Error: Malloc Failed!"));
	while (++track < setup.philo_num)
		if (pthread_mutex_init(&info->kill[track], NULL) != 0)
			return (ft_free(info, philo, setup, "Error: Mutex Failed!"));
	if (setup.eat_num == -1)
		return (1);
	track = -1;
	info->eat_lock = malloc(sizeof(pthread_mutex_t) * setup.philo_num);
	if (info->eat_lock == NULL)
		return (ft_free(info, philo, setup, "Error: Malloc Failed!"));
	while (++track < setup.philo_num)
		if (pthread_mutex_init(&info->eat_lock[track], NULL) != 0)
			return (ft_free(info, philo, setup, "Error: Mutex Failed!"));
	track = -1;
	info->eat_track = malloc(sizeof(int) * setup.philo_num);
	if (info->eat_track == NULL)
		return (ft_free(info, philo, setup, "Error: Malloc Failed!"));
	while (++track < setup.philo_num)
		info->eat_track[track] = 0;
	return (1);
}

int	ft_info_set_up(t_info *info, t_philo *philo, t_setup setup, int track)
{
	info->death = 0;
	info->print = 0;
	info->kill_time = NULL;
	info->eat_track = NULL;
	info->kill = NULL;
	info->forks = NULL;
	info->eat_lock = NULL;
	info->forks = malloc(sizeof(pthread_mutex_t) * setup.philo_num);
	if (info->forks == NULL)
		return (ft_free(info, philo, setup, "Error: Malloc Failed!"));
	while (++track < setup.philo_num)
		if (pthread_mutex_init(&info->forks[track], NULL) != 0)
			return (ft_free(info, philo, setup, "Error: Mutex Failed!"));
	if (pthread_mutex_init(&info->print_mutex, NULL) != 0)
		return (ft_free(info, philo, setup, "Error: Mutex Failed!"));
	if (pthread_mutex_init(&info->death_mutex, NULL) != 0)
		return (ft_free(info, philo, setup, "Error: Mutex Failed!"));
	track = -1;
	info->kill_time = malloc(sizeof(long long) * setup.philo_num);
	if (info->kill_time == NULL)
		return (ft_free(info, philo, setup, "Error: Malloc Failed!"));
	while (++track < setup.philo_num)
		info->kill_time[track] = 0;
	return (ft_info_more(info, philo, setup, -1));
}

t_philo	*ft_philo_initialize(t_info *info, t_philo *philo, t_setup setup,
	int track)
{
	philo = malloc(sizeof(t_philo) * setup.philo_num);
	if (philo == NULL)
	{
		printf("Error: Malloc Failed!\n");
		return (NULL);
	}
	if (ft_info_set_up(info, philo, setup, -1) == -1)
		return (NULL);
	while (track < setup.philo_num - 1)
	{
		philo[track].locks[1] = track;
		philo[track + 1].locks[0] = track;
		philo[track].num = track + 1;
		philo[track].info = info;
		philo[track].setup = setup;
		track++;
	}
	philo[0].locks[0] = track;
	philo[track].locks[1] = track;
	philo[track].num = track + 1;
	philo[track].info = info;
	philo[track].setup = setup;
	return (philo);
}
