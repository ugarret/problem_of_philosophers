#include "includes/philo.h"

static void	mutex_init(int i, t_all_for_philo *var)
{
	while (++i < var->num)
	{
		if (pthread_mutex_init(&var->fork[i], NULL))
			print_error("Mutex was not inited\n");
	}
	if (pthread_mutex_init(&var->msg, NULL))
		print_error("Mutex was not inited\n");
}

static void	init_philo(t_one_of_philo *philo, int i, t_all_for_philo var)
{
	philo->index = i;
	philo->info = &var;
	philo->last_eat = var.time_of_start;
	philo->right_fork = &var.fork[i];
	if (i == 0)
		philo->left_fork = &var.fork[var.num - 1];
	else
		philo->left_fork = &var.fork[i - 1];
	if (pthread_create(&var.thread[i], NULL, (void *)live_life, philo))
		print_error("Thread was not created\n");
	usleep(100);
	pthread_detach(var.thread[i]);
}

static void	free_all(int i, t_one_of_philo *philo, t_all_for_philo *var)
{
	while (--i >= 0)
		pthread_mutex_destroy(&var->fork[i]);
	pthread_mutex_destroy(&var->msg);
	free(var->thread);
	free(var->fork);
	free(philo);
}

int	main(int argc, char **argv)
{
	t_all_for_philo	var;
	t_one_of_philo	*philo;
	pthread_t		tid;
	int				i;

	if (!(check_arguments(argc, argv, &var)))
	{
		var.thread = (pthread_t *)malloc(sizeof(pthread_t) * var.num);
		var.fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * var.num);
		philo = (t_one_of_philo *)malloc(sizeof(t_one_of_philo) * var.num);
		i = -1;
		mutex_init(i, &var);
		var.time_of_start = current_time();
		var.fi = philo;
		i = -1;
		while (++i < var.num)
			init_philo(&philo[i], i, var);
		if (pthread_create(&tid, NULL, (void *)death_note, (void *)&var))
			print_error("Thread was not created\n");
		pthread_join(tid, NULL);
		free_all(i, philo, &var);
	}
	return (0);
}
