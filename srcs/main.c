#include "../includes/ft_ping.h"

struct	s_ping	t_ping = {
	.opt_h = FALSE,
	.opt_v = FALSE,
	.sockfd = 0,
	.hostname = NULL,
	.hostname_addr = NULL,
	.seq = 0,
	.stat_rec = 0,
	.internet_addr = 
	{
		.sin_family = AF_INET,
		.sin_port = 0
	}
};

int     main(int ac, char **av)
{
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
	if (parsing(ac, av) < 0) {
        dprintf(2, "ping: usage error: parsing \n");
        return (1);
	}
	// if all ok start ping
	if (init_pck() < 0)
	{
        dprintf(2, "ping: error init_pck \n");
		return (1);
	}

	printf("opt v = %d\nopt h = %d\n", t_ping.opt_v, t_ping.opt_h); //debug print
    return (0);
}