/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hf_gen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverzilo <mverzilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 22:51:43 by mverzilo          #+#    #+#             */
/*   Updated: 2026/09/14 19:25:14 by mverzilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	ft_isdigit(int c)
{
	if (!('0' <= c && c <= '9'))
		return (0);
	return (1);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

void	prinf_s(t_coder *coder, char *message)
{
	printf("%lld Coder %d %s\n",
		get_time() - coder->sim->start_time, coder->id,
		message);
}

void	print_c(t_coder *coder)
{
	printf("%lld Coder %d comiled (%d/%d)\n",
		get_time() - coder->sim->start_time,
		coder->id, coder->compiles_done,
		coder->sim->number_of_compiles_required);
}
