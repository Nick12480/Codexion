/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongels.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverzilo <mverzilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 17:33:59 by mverzilo          #+#    #+#             */
/*   Updated: 2026/09/15 17:58:34 by mverzilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	tacke_dongle(t_coder *coder, int index)
{
	if (pthread_mutex_trylock(&coder->sim->dongles[index].mutex) != 0)
		return (0);
	return (1);
}

int	release_dongle(t_coder *coder, int index)
{
	if (pthread_mutex_unlock(&coder->sim->dongles[index].mutex) != 0)
		return (0);
	return (1);
}

int	take_dongles(t_coder *coder)
{
	int	l;
	int	r;

	l = coder->id - 1;
	r = coder->id % coder->sim->number_of_coders;
	if (coder->id % 2 == 0)
	{
		if (!tack_l_d(coder, l, r))
			return (0);
	}
	else
	{
		if (!tack_r_d(coder, l, r))
			return (0);
	}
	return (1);
}

int	release_dongles(t_coder *coder)
{
	int	l;
	int	r;

	l = coder->id - 1;
	r = coder->id % coder->sim->number_of_coders;
	if (pthread_mutex_unlock(&coder->sim->dongles[l].mutex) != 0)
		return (0);
	if (pthread_mutex_unlock(&coder->sim->dongles[r].mutex) != 0)
		return (0);
	return (1);
}
