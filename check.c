#include "includes/philo.h"

size_t	my_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static int	my_isdigit(int smbl)
{
	if (smbl >= '0' && smbl <= '9')
		return (1);
	else
		return (0);
}

static int	my_atoi_for_philo(char *str)
{
	int				i;
	unsigned long	num;
	int				znak;

	i = 0;
	num = 0;
	znak = 1;
	if (!str)
		return (-1);
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 13) || str[i] == '\r')
		i++;
	if (str[i] == '-')
		znak = znak * (-1);
	if ((str[i] == '-' || str[i] == '+') && str[i + 1] != '\0')
		i++;
	while (my_isdigit(str[i]))
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (num * znak);
}

int	print_error(char *str)
{
	int	len;

	len = my_strlen(str);
	write(2, str, len);
	return (-1);
}

int	check_arguments(int argc, char **argv, t_all_for_philo *philo)
{
	if (argc != 5 && argc != 6)
		return (print_error("Wrong number of arguments\n"));
	philo->num = my_atoi_for_philo(argv[1]);
	philo->time_to_die = my_atoi_for_philo(argv[2]);
	philo->time_to_eat = my_atoi_for_philo(argv[3]);
	philo->time_to_sleep = my_atoi_for_philo(argv[4]);
	if (argc == 6)
		philo->num_of_meals = my_atoi_for_philo(argv[5]);
	else
		philo->num_of_meals = 0;
	if (philo->num > 200 || philo->num < 1)
		return (print_error("Wrong number of philosophers\n"));
	else if (philo->time_to_die < 60 || philo->time_to_eat < 60 || \
			philo->time_to_sleep < 60)
		return (print_error("Wrong time\n"));
	else
		return (0);
}
