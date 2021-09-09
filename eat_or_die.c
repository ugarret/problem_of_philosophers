#include "includes/philo.h"

unsigned long	current_time(void)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

static void	my_usleep(int waiting)
{
	unsigned long	end;

	end = current_time() + waiting;
	while (1)
	{
		if (current_time() >= end)
			break ;
		usleep(10);
	}
}

static void	printing(t_one_of_philo *philo, char *message, int death)
{
	unsigned long	time;

	time = current_time() - philo->info->time_of_start;
	pthread_mutex_lock(&philo->info->msg);
	printf("%lu	%d	%s\n",
		time, philo->index + 1, message);
	if (!death)
		pthread_mutex_unlock(&philo->info->msg);
}

void	live_life(t_one_of_philo *philo)
{
	while (42 / 2 == 21)
	{
		pthread_mutex_lock(philo->left_fork);
		printing(philo, "has taken a left fork", 0);
		pthread_mutex_lock(philo->right_fork);
		printing(philo, "has taken a right fork", 0);
		printing(philo, "start eating", 0);
		philo->last_eat = current_time();
		my_usleep(philo->info->time_to_eat);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		if (++philo->already_ate == philo->info->num_of_meals)
			philo->well_fed_philo = 1;
		printing(philo, "start sleeping", 0);
		my_usleep(philo->info->time_to_sleep);
		printing(philo, "start thinking", 0);
	}
}

void	*death_note(t_all_for_philo	*var)
{
	int				philo_is_full;
	int				i;

	while (42 / 2 == 21)
	{
		i = -1;
		philo_is_full = 0;
		while (++i < var->num)
		{
			if (var->fi[i].well_fed_philo == 1)
				philo_is_full++;
			if ((int)(current_time() - var->fi[i].last_eat) > var->time_to_die)
			{
				printing(var->fi, "died of starvation", 1);
				return ((void *)1);
			}
			if (var->num_of_meals && philo_is_full == var->num)
			{
				printing(var->fi, "ate last and happy to live", 1);
				return ((void *)1);
			}
		}
		usleep(500);
	}
	return (NULL);
}
