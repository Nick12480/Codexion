/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_initialization.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverzilo <mverzilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 20:30:56 by mverzilo          #+#    #+#             */
/*   Updated: 2026/09/16 18:36:14 by mverzilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	p_i(int ac, char **av, t_sim *sim)
{
	if (!is_valide_to_scheduler(ac, av) || !valideit_the_scheduler(av))
		return (0);
	convert_args(av, sim);
	if (pthread_mutex_init(&sim->scheduler_mutex, NULL) != 0)
	{
		printf("Scheduler mutex initialization failed\n");
		return (0);
	}
	if (!init_dongles(sim))
	{
		printf("Dongle initialization failed\n");
		return (0);
	}
	if (!init_coders(sim))
	{
		printf("Coder initialization failed\n");
		return (0);
	}
	return (1);
}

t_coder	*get_next_coder(t_sim *sim)
{
	int		i;
	t_coder	*next;

	i = 0;
	next = 0;
	while (i < sim->number_of_coders)
	{
		if (sim->number_of_coders > 0 && !sim->coders[i].dead)
		{
			if (next == NULL
				|| sim->coders[i].waiting_since < next->waiting_since)
				next = &sim->coders[i];
		}
		i++;
	}
	return (next);
}
