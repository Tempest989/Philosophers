/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosopher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druth   <druth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:52:37 by druth             #+#    #+#             */
/*   Updated: 2022/06/08 16:40:40 by druth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_free_2(t_info *info)
{
	if (info->eat_track != NULL)
		free(info->eat_track);
	if (info->kill != NULL)
		free(info->kill);
	if (info->kill_time != NULL)
		free(info->kill_time);
	if (info->eat_lock != NULL)
		free(info->eat_lock);
	if (info->forks != NULL)
		free(info->forks);
}

int	ft_free(t_info *info, t_philo *philo, t_setup setup, char *output)
{
	if (output != NULL)
		printf("%s\n", output);
	pthread_mutex_destroy(&info->print_mutex);
	pthread_mutex_destroy(&info->death_mutex);
	setup.eat_num = -1;
	while (++setup.eat_num < setup.philo_num)
	{
		if (info->forks != NULL)
			pthread_mutex_destroy(&(info->forks[setup.eat_num]));
		if (info->eat_lock != NULL)
			pthread_mutex_destroy(&(info->eat_lock[setup.eat_num]));
		if (info->kill != NULL)
			pthread_mutex_destroy(&(info->kill[setup.eat_num]));
	}
	ft_free_2(info);
	free(philo);
	return (-1);
}

int	ft_single(t_setup setup)
{
	setup.start_time = ft_current_time();
	printf("%lld 1 has taken a fork\n", ft_current_time() - setup.start_time);
	usleep(1000 * setup.input_times[0]);
	printf("%lld 1 died\n", ft_current_time() - setup.start_time);
	return (0);
}

void	ft_thread_launch(t_philo *philo, t_info *info, t_setup setup, int track)
{
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * setup.philo_num);
	if (threads == NULL)
	{
		printf("Philosphers Error: Malloc (thread) Function Failed!\n");
		return ;
	}
	setup.start_time = ft_current_time();
	while (++track < setup.philo_num)
	{
		philo[track].setup.start_time = setup.start_time;
		if (setup.eat_num == -1)
			pthread_create(&threads[track], NULL, &ft_philosopher,
				(void *)&philo[track]);
		else
			pthread_create(&threads[track], NULL, &ft_philosopher_num_eat,
				(void *)&philo[track]);
	}
	usleep(150);
	ft_death_timing(info, setup, 0);
	track = -1;
	while (++track < setup.philo_num)
		pthread_join(threads[track], NULL);
	free(threads);
}

int	main(int ac, char *av[])
{
	t_info	info;
	t_setup	setup;
	t_philo	*philo;

	if ((ac != 5 && ac != 6) || ft_initialize(&setup, ac, av) < 0)
	{
		printf("Philosphers Error: Invalid arguments given.\n");
		return (0);
	}
	if (setup.philo_num == 1)
		return (ft_single(setup));
	philo = ft_philo_initialize(&info, NULL, setup, 0);
	if (philo == NULL)
		return (0);
	ft_thread_launch(philo, &info, setup, -1);
	ft_free(&info, philo, setup, NULL);
	return (0);
}
