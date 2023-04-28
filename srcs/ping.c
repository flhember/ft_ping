#include "../includes/ft_ping.h"

/* Fill pck */
void	fill_pck(t_ping_pkt *pckt)
{
	unsigned int 	msg = 0;
	unsigned int 	start_data = sizeof(struct timeval);

	pckt->hdr.type = ICMP_ECHO;
	pckt->hdr.code = 0;
	pckt->hdr.un.echo.id = htons(t_ping.cur_pid);
	pckt->hdr.un.echo.sequence = htons(t_ping.seq);
	if (gettimeofday((void *)pckt->msg, NULL) == -1)
		dprintf(2, "gettimeofday function error\n");
	while (start_data < sizeof(pckt->msg))
	{  
		pckt->msg[start_data] = msg;
		msg++;
		start_data++;
	}
	pckt->hdr.checksum = checksum(pckt, 64);
}

/* Create fill and send pck */
int		send_ping( )
{
	t_ping_pkt pckt;

	ft_bzero(&pckt, sizeof(pckt));
	fill_pck(&pckt);
	if (sendto(t_ping.sockfd, &pckt, sizeof(pckt), 0, (struct sockaddr*)&t_ping.internet_addr, sizeof(t_ping.internet_addr)) <= 0) {
		dprintf(2, "Packet sending fail!\n");
		return (-1);
	}
	return (0);
}

/* Send and rec pck */
int		ping_loop()
{
	printf("PING %s (%s): %lu data bytes", t_ping.hostname, t_ping.hostname_addr, sizeof(t_ping_pkt) - sizeof(struct icmphdr));
	if (t_ping.opt_v)
		printf(", id 0x%x = %d", t_ping.cur_pid, t_ping.cur_pid);
	printf("\n");
	while (1) {
		// send packet
		if (send_ping() < 0) {
			printf("error send ping\n");
			return (-1);
		}
		//rec packet
		if (rec_ping(t_ping.sockfd) < 0) {
			printf("error rec ping\n");
			return (-1);
		}
		// sleep 1s
		usleep(PING_SLEEP);
		t_ping.seq++;
	}
	return (0);
}

/* https://unix.stackexchange.com/questions/223672/ping-statistics */
/* When loop stop print stat*/
void	stop_ping()
{
	float		loss;
	suseconds_t	avg;
	suseconds_t	stddev;

	t_ping.seq++;
	loss = (((float)t_ping.seq - (float)t_ping.rec) / (float)t_ping.seq ) * 100.0;
	printf("--- %s ping statistics ---\n", t_ping.hostname);
	printf("%d packets transmitted, %d packets received, %d%% packet loss\n", t_ping.seq, t_ping.rec, (int)loss);

	if (t_ping.rec)
	{
		avg = t_ping.rtt_avg / t_ping.rec;
		stddev = sqrt((t_ping.rtt_mul / t_ping.rec) - (avg * avg));
		printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n", t_ping.rtt_min / 1000.0, avg / 1000.0, t_ping.rtt_max / 1000.0, stddev / 1000.0);
	}
	exit(0);
}

/* Init socket and start loop ping */
int		init_pck()
{
	if ((init_sock()) < 0)
		return (-1);
	
	//set function when loop stop with ctrl + c
	signal(SIGINT, &stop_ping);

	t_ping.cur_pid = getpid();

	// Loop send ping
	if ((ping_loop()) < 0)
		return (-1);
	return (0);
}