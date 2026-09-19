/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_hf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverzilo <mverzilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 22:41:39 by mverzilo          #+#    #+#             */
/*   Updated: 2026/09/16 19:17:59 by mverzilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	is_valide_to_scheduler(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (ac != 9)
	{
		printf("1");
		fprintf((FILE *)1, "%s", "Unacceptable number of arguments");
		return (0);
	}
	while (i <= 7)
	{
		while (av[i][j])
		{
			if (!ft_isdigit (av[i][j]))
			{
				printf("%s", "Unacceptable argument input\n");
				return (0);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

int	valideit_the_scheduler(char **av)
{
	if (!(!strcmp (av[8], "fifo") || !strcmp (av[8], "edf")))
	{
		printf("%s", "Unacceptable argument input");
		return (0);
	}
	return (1);
}

int	convert_args(char **av, t_sim *sim)
{
	sim->number_of_coders = atoi(av[1]);
	sim->time_to_burnout = atoi(av[2]);
	sim->time_to_compile = atoi(av[3]);
	sim->time_to_debug = atoi(av[4]);
	sim->time_to_refactor = atoi(av[5]);
	sim->number_of_compiles_required = atoi(av[6]);
	sim->dongle_cooldown = atoi(av[7]);
	sim->scheduler = av[8];
	return (1);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	coder->last_action = get_time();
	coder->dead = 0;
	prinf_s(coder, "started");
	while (coder->compiles_done
		< coder->sim->number_of_compiles_required)
	{
		coder->state = THINKING;
		prinf_s(coder, "wants dongles");
		pthread_mutex_lock(&coder->sim->scheduler_mutex);
		coder->waiting_since = get_time();
		pthread_mutex_unlock(&coder->sim->scheduler_mutex);
		while (1)
		{
			if (is_my_turn(coder) && take_dongles(coder))
				break ;
			usleep(1000);
		}
		pthread_mutex_lock(&coder->sim->scheduler_mutex);
		coder->waiting_since = 0;
		pthread_mutex_unlock(&coder->sim->scheduler_mutex);
		prinf_s(coder, "got dongles");
		coder->state = COMPILING;
		prinf_s(coder, "is compiling");
		coder->last_action = get_time();
		smart_sleep(coder, coder->sim->time_to_compile);
		if (coder->dead)
			return (release_dongles(coder), NULL);
		coder->compiles_done++;
		print_c(coder);
		release_dongles(coder);
		coder->state = DEBUGGING;
		prinf_s(coder, "debugging");
		smart_sleep(coder, coder->sim->time_to_debug);
		if (coder->dead)
			return (release_dongles(coder), NULL);
		coder->state = REFACTORING;
		prinf_s(coder, "refactoring");
		smart_sleep(coder, coder->sim->time_to_refactor);
		if (coder->dead)
			return (release_dongles(coder), NULL);
	}
	return (NULL);
}


int	check_burnout(t_coder *coder)
{
	long long	now;

	now = get_time();
	if (now - coder->last_action >= coder->sim->time_to_burnout)
	{
		coder->dead = 1;
		printf("%lld Coder %d burned out\n",
			now - coder->sim->start_time,
			coder->id);
		return (1);
	}
	return (0);
}
