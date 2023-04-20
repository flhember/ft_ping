#include "../includes/ft_ping.h"

void			set_rtt_stat(suseconds_t rtt)
{
	if (t_ping.seq == 0) {
		t_ping.rtt_min = rtt;
		t_ping.rtt_max = rtt;
		t_ping.rtt_avg = rtt;
		t_ping.rtt_mul = rtt * rtt;
	} else {
		t_ping.rtt_min = rtt < t_ping.rtt_min ? rtt : t_ping.rtt_min;
		t_ping.rtt_max = rtt > t_ping.rtt_max ? rtt : t_ping.rtt_max;
		t_ping.rtt_avg = t_ping.rtt_avg + rtt;
		t_ping.rtt_mul += rtt * rtt;
	}
}

/* Get send time of ping and subtract to current time to have total ping time*/
suseconds_t		get_rtt_ping(struct timeval *ping_time)
{
	struct timeval	curr_time;
	suseconds_t		time_now;
	suseconds_t		rtt;

	if (gettimeofday(&curr_time, NULL) == -1) {
		dprintf(2, "gettimeofday function error\n");
		return (0);
	}
	time_now = curr_time.tv_sec * 1000000 + curr_time.tv_usec;
	rtt = time_now - ping_time->tv_sec * 1000000 - ping_time->tv_usec;
	set_rtt_stat(rtt);
	return (rtt);
}

/* Check ping, if it's for us, reply code and calculat the time*/
int		check_rec_ping(char *receive_packet, ssize_t bytes_rec)
{
	suseconds_t		rtt;
	struct icmphdr *rec_ping_icmp = (void *)receive_packet + sizeof(struct iphdr);

	//check if packet is for me
	if (htons(rec_ping_icmp->un.echo.id) != getpid())
		return (-1);
	
	//check valid icmp reply code
	if (rec_ping_icmp->type != ICMP_ECHOREPLY)
	{
		printf("Error Packet received with ICMP type %d\n", rec_ping_icmp->type);
		return (-1);
	} else {
		rtt = get_rtt_ping((void *)receive_packet + sizeof(struct iphdr) + sizeof(struct icmphdr));
		printf("%lu bytes from %s: icmp_seq=%d ttl=%d time=%ld.%02ld ms\n",
			bytes_rec - sizeof(struct iphdr), /*t_ping.hostname,*/ t_ping.hostname_addr, t_ping.seq, TTL_VAL, rtt / 1000l, rtt % 1000l);
		t_ping.rec++;
	}

	return (0);
}

/* Rec ping */
int 	rec_ping(int sockfd)
{
	ssize_t ret;
	char	control[1000];
	char    receive_packet[84];

	struct iovec io =
	{                    
        .iov_base = receive_packet,					/* Adresse de début */
    	.iov_len = 84								/* Nombre d'octets à transférer */
    };

    struct msghdr msg =
	{
        .msg_name		= NULL,						/* adresse optionnelle */
        .msg_namelen	= 0,						/* taille de l'adresse */
        .msg_iov		= &io, 						/* tableau scatter/gather */
        .msg_iovlen		= 1,						/* # éléments dans msg_iov */
        .msg_control	= &control,					/* métadonnées, voir ci‐dessous */
        .msg_controllen	= sizeof(control),			/* taille du tampon de métadonnées */
        .msg_flags		= 0							/* attributs du message reçu */
    };

	ft_memset(receive_packet, 0, sizeof(receive_packet));
	ret = recvmsg(sockfd, &msg, 0);

	if (check_rec_ping(receive_packet, ret) < 0) {
		return (-1);
	}
	return (0);
}

/* Fill pck */
void	fill_pck(t_ping_pkt *pckt)
{
	unsigned int msg = 0;

	pckt->hdr.type = ICMP_ECHO;
	pckt->hdr.code = 0;
	pckt->hdr.un.echo.id = htons(getpid());
	pckt->hdr.un.echo.sequence = htons(t_ping.seq);
	while (msg < sizeof(pckt->msg))
	{  
		pckt->msg[msg] = msg;
		msg++;
	}
	if (gettimeofday((void *)pckt->msg, NULL) == -1)
		dprintf(2, "gettimeofday function error\n");
	pckt->hdr.checksum = checksum(pckt, 64);
}

/* Create fill and send pck */
int		send_ping( )
{
	t_ping_pkt pckt;

	ft_bzero(&pckt, sizeof(pckt));
	fill_pck(&pckt);
	t_ping.seq++;
	if (sendto(t_ping.sockfd, &pckt, sizeof(pckt), 0, (struct sockaddr*)&t_ping.internet_addr, sizeof(t_ping.internet_addr)) <= 0) {
		dprintf(2, "Packet sending fail!\n");
		return (-1);
	}
	return (0);
}

/* Send and rec pck */
int		ping_loop()
{
	//printf("PING %s (%s) %lu(%lu) bytes of data.\n", t_ping.hostname, t_ping.hostname_addr, sizeof(t_ping_pkt) - sizeof(struct icmphdr), sizeof(t_ping_pkt) + sizeof(struct iphdr));
	printf("PING %s (%s): %lu data bytes\n", t_ping.hostname, t_ping.hostname_addr, sizeof(t_ping_pkt) - sizeof(struct icmphdr));
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

	avg = t_ping.rtt_avg / t_ping.rec;
	stddev = sqrt((t_ping.rtt_mul / t_ping.rec) - (avg * avg));
	printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n", t_ping.rtt_min / 1000.0, avg / 1000.0, t_ping.rtt_max / 1000.0, stddev / 1000.0);

	exit(0);
}

/* Init socket and start loop ping */
int		init_pck()
{
	if ((init_sock()) < 0)
		return (-1);
	
	//set function when loop stop with ctrl + c
	signal(SIGINT, &stop_ping);

	// Loop send ping
	if ((ping_loop()) < 0)
		return (-1);
	return (0);
}