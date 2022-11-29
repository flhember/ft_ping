#include "../includes/ft_ping.h"

int	find_host(char **av, int i, int ac)
{
	printf("host is %s\n", av[i]);
	if (i + 1 != ac)
		printf("Too much option, ac == %d, i == %d\n", ac, i );\
	//check if host is alredy set
	return (0);
}

int	find_opt(char **av, int i, t_ping *ping)
{
	if (av[i][1] == 'h') {
		if (av[i][1] == 'h' && av[i][2] == '\0')
			ping->opt_h = TRUE;
		if (av[i][1] == 'h' && av[i][2] == 'v' && av[i][3] == '\0') {
			ping->opt_h = TRUE;
			ping->opt_v = TRUE;
		}
	}
	else if (av[i][1] == 'v') {
		if (av[i][1] == 'v' && av[i][2] == '\0')
			ping->opt_v = TRUE;
		if (av[i][1] == 'v' && av[i][2] == 'h' && av[i][3] == '\0') {
			ping->opt_v = TRUE;
			ping->opt_h = TRUE;
		}
	} else
		return (-1);
	return (0);
}

int	parsing(int ac, char **av, t_ping *ping)
{
	int	i = 1;

	while (i < ac) {
		if (av[i][0] == '-') {
			if (!find_opt(av, i, ping))
				return (1);
		} else {
			if (!find_host(av, i, ac))
				return (1);
		}
		i++;
	}
	return (0);
}

int     main(int ac, char **av)
{
	t_ping	ping;

	ft_memset((void *)&ping, 0, sizeof(ping));
	if (getuid() != 0)
	{
		dprintf(2, "Ping: need admin rights\n");
                return (1);
	}
        if (ac < 2) {
                dprintf(2, "ping: usage error: Destination address required\n");
                return (1);
        }
	if (!parsing(ac, av, &ping)) {
                return (1);
	}
	printf("opt v = %d\nopt h = %d\n", ping.opt_v, ping.opt_h);
        return (0);
}
