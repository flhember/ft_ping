#include "../includes/ft_ping.h"

int	find_host(char **av, int i)
{
	char				*tmp_addr;
	struct addrinfo		*addr = NULL;
	struct addrinfo		hint = {.ai_family = AF_INET, .ai_socktype = SOCK_RAW, .ai_protocol = IPPROTO_ICMP};

	if (t_ping.hostname != NULL) {
        dprintf(2, "ping: Host alerady set\n");
		return (-1);
	}
	t_ping.hostname = av[i];

	if (getaddrinfo(t_ping.hostname, NULL, &hint, &addr) < 0) {
        dprintf(2, "ping: unknown host\n");
        return (-1);
    }

	if (!(tmp_addr = malloc(INET_ADDRSTRLEN))) {
		dprintf(2, "ping: Error malloc\n");
        return (-1);
	}
    t_ping.internet_addr = *(struct sockaddr_in*)addr->ai_addr;
	inet_ntop(addr->ai_family, &((struct sockaddr_in *)addr->ai_addr)->sin_addr, tmp_addr, INET_ADDRSTRLEN);
	t_ping.hostname_addr = tmp_addr;
	freeaddrinfo(addr);

	return (0);
}

int	find_opt(char **av, int i)
{
	if (av[i][1] == 'h') {
		if (av[i][1] == 'h' && av[i][2] == '\0')
			t_ping.opt_h = TRUE;
		if (av[i][1] == 'h' && av[i][2] == 'v' && av[i][3] == '\0') {
			t_ping.opt_h = TRUE;
			t_ping.opt_v = TRUE;
		}
	}
	else if (av[i][1] == 'v') {
		if (av[i][1] == 'v' && av[i][2] == '\0')
			t_ping.opt_v = TRUE;
		if (av[i][1] == 'v' && av[i][2] == 'h' && av[i][3] == '\0') {
			t_ping.opt_v = TRUE;
			t_ping.opt_h = TRUE;
		}
	} else {
		return (-1);
	}
	return (0);
}

int	parsing(int ac, char **av)
{
	int	i = 1;

	while (i < ac) {
		if (av[i][0] == '-') {
			if (find_opt(av, i) < 0)
				return (-1);
		} else {
			if (find_host(av, i) < 0)
				return (-1);
		}
		i++;
	}
	if (t_ping.opt_h)
		return (-1);
	return (0);
}