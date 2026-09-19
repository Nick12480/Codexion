/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverzilo <mverzilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 22:23:53 by mverzilo          #+#    #+#             */
/*   Updated: 2026/09/12 16:50:30 by mverzilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	main(int ac, char **av)
{
	t_sim		sim;
	pthread_t	*threads;

	if (!(p_i(ac, av, &sim)))
		return (1);
	threads = malloc(sizeof(pthread_t) * sim.number_of_coders);
	if (!threads)
		return (1);
	sim.coders[0].sim = &sim;
	sim.start_time = get_time();
	printf("Start: %lld ms\n", sim.start_time);
	if (!init_threads(&sim, threads))
		return (1);
	if (!wait_threads(&sim, threads))
		return (1);
	sim.start_time = get_time();
	printf("End: %lld ms\n", sim.start_time);
	return (0);
}
