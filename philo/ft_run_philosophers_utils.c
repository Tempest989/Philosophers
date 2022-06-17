/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_philosopher_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druth   <druth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:52:37 by druth             #+#    #+#             */
/*   Updated: 2022/06/08 16:40:40 by druth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_philosopher_loop(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->death_mutex);
	while (philo->info->death == 0)
	{
		pthread_mutex_unlock(&philo->info->death_mutex);
		if (ft_eating_forks(philo) == -1)
			return ;
		if (ft_waiting(philo, philo->setup.input_times[1]
				+ ft_current_time(), 2) == -1)
			return ;
		pthread_mutex_unlock(&philo->info->forks[philo->locks[0]]);
		pthread_mutex_unlock(&philo->info->forks[philo->locks[1]]);
		if (ft_sleep_think(philo) == -1)
			return ;
		pthread_mutex_lock(&philo->info->death_mutex);
	}
	pthread_mutex_unlock(&philo->info->death_mutex);
}

void	ft_philosopher_eat_loop(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->death_mutex);
	while (philo->info->death == 0)
	{
		pthread_mutex_unlock(&philo->info->death_mutex);
		if (ft_eating_forks(philo) == -1)
			return ;
		if (ft_waiting(philo, philo->setup.input_times[1]
				+ ft_current_time(), 2) == -1)
			return ;
		pthread_mutex_unlock(&philo->info->forks[philo->locks[0]]);
		pthread_mutex_unlock(&philo->info->forks[philo->locks[1]]);
		pthread_mutex_lock(&philo->info->eat_lock[philo->num - 1]);
		philo->info->eat_track[philo->num - 1]++;
		if (philo->setup.eat_num == philo->info->eat_track[philo->num - 1])
		{
			pthread_mutex_unlock(&philo->info->eat_lock[philo->num - 1]);
			return ;
		}
		pthread_mutex_unlock(&philo->info->eat_lock[philo->num - 1]);
		if (ft_sleep_think(philo) == -1)
			return ;
		pthread_mutex_lock(&philo->info->death_mutex);
	}
	pthread_mutex_unlock(&philo->info->death_mutex);
}

int	ft_death_check(t_philo *philo, int flag)
{
	pthread_mutex_lock(&philo->info->death_mutex);
	if (philo->info->death != 0)
	{
		pthread_mutex_unlock(&philo->info->death_mutex);
		if (flag > 0)
			pthread_mutex_unlock(&philo->info->forks[philo->locks[0]]);
		if (flag == 2)
			pthread_mutex_unlock(&philo->info->forks[philo->locks[1]]);
		return (-1);
	}
	pthread_mutex_unlock(&philo->info->death_mutex);
	return (1);
}

int	ft_waiting(t_philo *philo, long long limit, int flag)
{
	while (ft_current_time() < limit)
	{
		if (ft_death_check(philo, flag) == -1)
			return (-1);
	}
	return (0);
}

void	ft_printer(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->info->print_mutex);
	if (philo->info->print == 0)
		printf("%lld %d %s\n", ft_current_time() - philo->setup.start_time,
			philo->num, message);
	pthread_mutex_unlock(&philo->info->print_mutex);
}
