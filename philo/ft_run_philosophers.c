/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_philosopher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druth   <druth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:52:37 by druth             #+#    #+#             */
/*   Updated: 2022/06/08 16:40:40 by druth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	ft_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000LL + time.tv_usec / 1000);
}

int	ft_sleep_think(t_philo *philo)
{
	if (ft_death_check(philo, 0) == -1)
		return (-1);
	ft_printer(philo, "is sleeping");
	if (ft_death_check(philo, 0) == -1)
		return (-1);
	if (ft_waiting(philo, philo->setup.input_times[2] + ft_current_time(), 0)
		== -1)
		return (-1);
	if (ft_death_check(philo, 0) == -1)
		return (-1);
	ft_printer(philo, "is thinking");
	if (ft_death_check(philo, 0) == -1)
		return (-1);
	return (0);
}

int	ft_eating_forks(t_philo *philo)
{
	if (ft_death_check(philo, 0) == -1)
		return (-1);
	pthread_mutex_lock(&philo->info->forks[philo->locks[0]]);
	ft_printer(philo, "has taken a fork");
	if (ft_death_check(philo, 1) == -1)
		return (-1);
	pthread_mutex_lock(&philo->info->forks[philo->locks[1]]);
	pthread_mutex_lock(&philo->info->print_mutex);
	if (philo->info->print == 0)
	{
		printf("%lld %d has taken a fork\n", ft_current_time()
			- philo->setup.start_time, philo->num);
		printf("%lld %d is eating\n", ft_current_time()
			- philo->setup.start_time, philo->num);
	}
	pthread_mutex_unlock(&philo->info->print_mutex);
	pthread_mutex_lock(&philo->info->kill[philo->num - 1]);
	philo->info->kill_time[philo->num - 1] = ft_current_time()
		+ philo->setup.input_times[0];
	pthread_mutex_unlock(&philo->info->kill[philo->num - 1]);
	if (ft_death_check(philo, 2) == -1)
		return (-1);
	return (0);
}

void	*ft_philosopher(void *parameter)
{
	t_philo		*philo;

	philo = (t_philo *)parameter;
	pthread_mutex_lock(&philo->info->kill[philo->num - 1]);
	philo->info->kill_time[philo->num - 1] = philo->setup.start_time
		+ philo->setup.input_times[0];
	pthread_mutex_unlock(&philo->info->kill[philo->num - 1]);
	if (philo->num % 2)
		usleep(1500);
	ft_philosopher_loop(philo);
	return (0);
}

void	*ft_philosopher_num_eat(void *parameter)
{
	t_philo		*philo;

	philo = (t_philo *)parameter;
	pthread_mutex_lock(&philo->info->kill[philo->num - 1]);
	philo->info->kill_time[philo->num - 1] = philo->setup.start_time
		+ philo->setup.input_times[0];
	pthread_mutex_unlock(&philo->info->kill[philo->num - 1]);
	if (philo->num % 2)
		usleep(1500);
	ft_philosopher_eat_loop(philo);
	return (0);
}
