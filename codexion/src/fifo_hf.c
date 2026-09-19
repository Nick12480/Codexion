/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo>_hf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverzilo <mverzilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 18:43:55 by mverzilo          #+#    #+#             */
/*   Updated: 2026/09/16 18:52:00 by mverzilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/codexion.h"

int	is_my_turn(t_coder *coder)
{
	t_coder	*next;

	pthread_mutex_lock(&coder->sim->scheduler_mutex);
	next = get_next_coder(coder->sim);
	if (next == coder)
	{
		pthread_mutex_unlock(&coder->sim->scheduler_mutex);
		return (1);
	}
	pthread_mutex_unlock(&coder->sim->scheduler_mutex);
	return (0);
}