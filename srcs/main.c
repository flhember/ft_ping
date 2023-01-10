#include "../includes/ft_ping.h"

int	find_host(char **av, int i, t_ping *ping)
{
	struct addrinfo		*addr = NULL;
	struct addrinfo		hint = {.ai_family = AF_INET, .ai_socktype = SOCK_RAW, .ai_protocol = IPPROTO_ICMP};
	//char			test[INET_ADDRSTRLEN];

	if (ping->raw_host != NULL) {
        dprintf(2, "ping: Host alerady set\n");
		return (-1);
	}
	ping->raw_host = av[i];
	int ret = 0;
	if ((ret = getaddrinfo(av[i], NULL, &hint, &addr)) != 0) {
        dprintf(2, "ping: %s: Name or service not known\n", av[1]);
        return (-1);
    }
    ping->internet_addr = *(struct sockaddr_in*)addr->ai_addr;
	//inet_ntop(addr->ai_family, &((struct sockaddr_in *)addr->ai_addr)->sin_addr, test, sizeof(test));
	//printf("test %s\n", test);
	//printf("host is %s\n", inet_ntoa(ping->internet_addr.sin_addr));
	freeaddrinfo(addr);
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
	} else {
        dprintf(2, "ping: usage error: usage --------------------------------------- \n");
		return (-1);
	}
	return (0);
}

int	parsing(int ac, char **av, t_ping *ping)
{
	int	i = 1;

	while (i < ac) {
		if (av[i][0] == '-') {
			if (find_opt(av, i, ping) < 0)
				return (-1);
		} else {
			if (find_host(av, i, ping) < 0)
				return (-1);
		}
		i++;
	}
	return (0);
}

int     main(int ac, char **av)
{
	t_ping	ping;

	// Set struct info to null and set first seq
	ft_memset((void *)&ping, 0, sizeof(ping));
	ping.seq = 1;

	// Check if user is root
	if (getuid() != 0)
	{
		dprintf(2, "Ping: need admin rights\n");
        return (1);
	}
	// Check if have adress
    if (ac < 2) {
        dprintf(2, "ping: usage error: Destination address required\n");
        return (1);
    }
	// Parse info
	if (parsing(ac, av, &ping) < 0) {
        dprintf(2, "ping: usage error: ------\n");
        return (1);
	}
	// if all ok start ping
	if (init_pck(&ping) < 0)
	{
        dprintf(2, "ping: ----------\n");
		return (1);
	}

	printf("opt v = %d\nopt h = %d\n", ping.opt_v, ping.opt_h); //debug print
    return (0);
}
