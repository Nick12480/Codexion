/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverzilo <mverzilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 22:23:57 by mverzilo          #+#    #+#             */
/*   Updated: 2026/09/16 19:25:51 by mverzilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// pthread_*
#include <pthread.h>

// gettimeofday
#include <sys/time.h>

// clock_gettime
#include <time.h>

// usleep, write
#include <unistd.h>

// malloc, free, atoi
#include <stdlib.h>

// printf, fprintf
#include <stdio.h>

// strcmp, strlen, memset
#include <string.h>

#define THINKING 0
#define COMPILING 1
#define DEBUGGING 2
#define REFACTORING 3
#define DEAD 4

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
}	t_dongle;

typedef struct s_sim	t_sim;

typedef struct s_coder
{
	int			id;
	int			compiles_done;
//	long long	last_compile;
	long long	last_action;
	long long	waiting_since;
	int			state;
	int			dead;
	t_sim		*sim;
}	t_coder;

typedef struct s_sim
{
	int				number_of_coders;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				number_of_compiles_required;
	int				dongle_cooldown;
	char			*scheduler;
	t_dongle		*dongles;
	t_coder			*coders;
	long long		start_time;
	pthread_mutex_t	monitor_thread;
	int				sim_over;
}	t_sim;

int			ft_isdigit(int c);

int			is_valide_to_scheduler(int ac, char **av);
int			valideit_the_scheduler(char **av);
int			convert_args(char **av, t_sim *sim);
int			init_dongles(t_sim *sim);
int			init_coders(t_sim *sim);
int			init_threads(t_sim *sim, pthread_t *threads);
int			wait_threads(t_sim *sim, pthread_t *threads);
long long	get_time(void);
void		*coder_routine(void *arg);
int			p_i(int ac, char **av, t_sim *sim);
int			tacke_dongle(t_coder *coder, int index);
int			take_dongles(t_coder *coder);
int			tack_l_d(t_coder *coder, int l, int r);
int			tack_r_d(t_coder *coder, int l, int r);
int			release_dongle(t_coder *coder, int index);
int			release_dongles(t_coder *coder);
int			check_burnout(t_coder *coder);
void		smart_sleep(t_coder *coder, long long duration);
void		prinf_s(t_coder *coder, char *message);
void		print_c(t_coder *coder);
t_coder		*get_next_coder(t_sim *sim);
int			is_my_turn(t_coder *coder);
