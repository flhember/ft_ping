#include "../includes/ft_ping.h"

struct	s_ping	t_ping = {
	.opt_h = FALSE,
	.opt_v = FALSE,
	.cur_pid = 0,
	.sockfd = 0,
	.hostname = NULL,
	.seq = 0,
	.rec = 0,
	.rtt_min = 0,
	.rtt_max = 0,
	.rtt_avg = 0,
	.rtt_mul = 0,
	.ttl_rec = 0,
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
		if (t_ping.opt_h)
			print_help();
        return (1);
	}
	// if all ok start ping
	if (init_pck() < 0)
		return (1);

    return (0);
}