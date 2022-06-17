/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:29:31 by druth             #+#    #+#             */
/*   Updated: 2022/06/16 16:29:33 by druth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_check(char *str, int *track, char type)
{
	char	*limit;
	int		count;
	int		flag;

	if (type == 'i')
		limit = "2147483647";
	else
		limit = "9223372036854775807";
	flag = 0;
	if (str[0] == '+')
		flag = 1;
	count = flag;
	while (count <= *track && str[count] <= limit[count - flag])
		count++;
	printf("limit = %c\nstr = %c\ncheck = %d\ntrack = %d\n",
		limit[count - flag], str[count], count, *track);
	if (count > *track)
		return (1);
	return (-1);
}

long long	ft_av_convert(char *str, char *error, int track)
{
	long long	output;

	if (str[0] == '+')
		track++;
	if (str[track] == '0' && str[track + 1] == '\0')
		return (0);
	output = 0;
	while (str[track] >= '0' && str[track] <= '9'
		&& (track < 18 || (track < 19 && str[0] == '+')))
	{
		output = (output * 10) + (str[track] - '0');
		track++;
	}
	if ((track == 18 || (track == 19 && str[0] == '+'))
		&& str[track] >= '0' && str[track] <= '9')
	{
		if (str[track + 1] == '\0' && ft_check(str, &track, 'l') == 1)
			output = (output * 10) + (str[track] - '0');
		else
			*error = '1';
	}
	else if (str[track] != '\0')
		*error = '1';
	return (output);
}

int	ft_atoi(char *str, char *error, int track)
{
	int	output;

	if (str[0] == '+')
		track++;
	if (str[track] == '0' && str[track + 1] == '\0')
		return (0);
	output = 0;
	while (str[track] >= '0' && str[track] <= '9'
		&& (track < 9 || (track < 10 && str[0] == '+')))
	{
		output = (output * 10) + (str[track] - '0');
		track++;
	}
	if ((track == 9 || (track == 10 && str[0] == '+'))
		&& str[track] >= '0' && str[track] <= '9')
	{
		if (str[track + 1] == '\0' && ft_check(str, &track, 'i') == 1)
			output = (output * 10) + (str[track] - '0');
		else
			*error = '1';
	}
	else if (str[track] != '\0')
		*error = '1';
	return (output);
}

int	ft_initialize(t_setup *setup, int ac, char *av[])
{
	int		track;
	char	error;

	track = 0;
	error = '0';
	setup->philo_num = ft_atoi(av[1], &error, 0);
	if (error == '1' || setup->philo_num == 0)
		return (-1);
	while (track < 3)
	{
		setup->input_times[track] = ft_av_convert(av[2 + track], &error, 0);
		if (error == '1' || setup->input_times[track] == 0)
			return (-1);
		track++;
	}
	if (ac == 6)
	{
		setup->eat_num = ft_atoi(av[5], &error, 0);
		if (error == '1' || setup->eat_num == 0)
			return (-1);
	}
	else
		setup->eat_num = -1;
	return (1);
}
