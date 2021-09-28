#include "philo.h"

int	ft_str_is_numeric(char *str)
{
	int	a;
	int	b;

	a = 0;
	b = 1;
	while (str[a] != '\0')
	{
		if (str[0] == '+')
			a++;
		if (str[a] >= '0' && str[a] <= '9')
			b = b * 1;
		if (str[a] < '0' || str[a] > '9')
			b = 0;
		a++;
	}
	return (b);
}