/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_initialization.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverzilo <mverzilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 20:00:37 by mverzilo          #+#    #+#             */
/*   Updated: 2026/09/16 19:13:13 by mverzilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	init_dongles(t_sim *sim)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	sim->dongles = malloc(sizeof (t_dongle) * sim->number_of_coders);
	if (!sim->dongles)
		return (0);
	while (i < sim->number_of_coders)
	{
		if (pthread_mutex_init(&sim->dongles[i].mutex, NULL) != 0)
		{
			while (j < i)
			{
				pthread_mutex_destroy(&sim->dongles[j].mutex);
				j++;
			}
			free(sim->dongles);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_coders(t_sim *sim)
{
	int	i;

	i = 0;
	sim->coders = malloc(sizeof(t_coder) * sim->number_of_coders);
	if (!sim->coders)
		return (0);
	while (i < sim->number_of_coders)
	{
		sim->coders[i].id = i + 1;
		sim->coders[i].last_action = sim->start_time;
		sim->coders[i].waiting_since = 0;
		sim->coders[i].state = THINKING;
		sim->coders[i].dead = 0;
		sim->coders[i].sim = sim;
		i++;
	}
	return (1);
}

int	init_threads(t_sim *sim, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < sim->number_of_coders)
	{
		sim->coders[i].sim = sim;
		if (pthread_create(&threads[i], NULL,
				coder_routine, &sim->coders[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	wait_threads(t_sim *sim, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < sim->number_of_coders)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}