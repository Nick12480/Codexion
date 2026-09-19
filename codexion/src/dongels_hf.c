/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongels_hf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverzilo <mverzilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 18:16:42 by mverzilo          #+#    #+#             */
/*   Updated: 2026/09/16 19:15:40 by mverzilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	tack_l_d(t_coder *coder, int l, int r)
{
	if (!tacke_dongle(coder, l))
		return (0);
	if (!tacke_dongle(coder, r))
	{
		release_dongle(coder, l);
		return (0);
	}
	return (1);
}

int	tack_r_d(t_coder *coder, int l, int r)
{
	if (!tacke_dongle(coder, r))
		return (0);
	if (!tacke_dongle(coder, l))
	{
		release_dongle(coder, r);
		return (0);
	}
	return (1);
}

void	smart_sleep(t_coder *coder, long long duration)
{
	long long	start;

	(void)coder;
	start = get_time();
	while (get_time() - start < duration)
		usleep(1000);
}
