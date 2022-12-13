#include "../includes/ft_ping.h"

int     set_sockopt(int sockfd)
{
	int             ttl_val;
	struct  timeval tv_out;

	ttl_val = TTL_VAL;
	tv_out.tv_sec = RECV_TIMEOUT;
	tv_out.tv_usec = 0;
	if (setsockopt(sockfd, SOL_IP, IP_TTL, &ttl_val, sizeof(ttl_val)) != 0)
	{
		printf("error set option ttl socket\n");
		return (-1);
	}
	if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv_out, sizeof(tv_out)) != 0)
	{
		printf("error set option timeout socket\n");
		return (-1);
	}
	return (0);
}

int	init_sock(t_ping *ping)
{
	int sockfd = 0;

	if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0
		|| set_sockopt(sockfd) == 1) {
		printf("Error Socket");
		return (-1);
	}
	ping->sockfd = sockfd;
	return (0);
}

void	fill_pck(t_ping_pkt *pckt, t_ping *ping)
{
	unsigned int msg = 0;

	ft_bzero(pckt, sizeof(pckt));
	pckt->hdr.type = ICMP_ECHO;
	pckt->hdr.code = 0;
	pckt->hdr.un.echo.id = htons(getpid());
	pckt->hdr.un.echo.sequence = htons(ping->seq);
	while (msg < sizeof(pckt->msg))
	{
		pckt->msg[msg] = msg;
		msg++;
	}
	gettimeofday((void *)pckt->msg, NULL);
	printf("%zu size hdr pck\n", sizeof(pckt));
	pckt->hdr.checksum = checksum(pckt, 64);
}

int	send_ping(t_ping *ping)
{
	t_ping_pkt pckt;

	fill_pck(&pckt, ping);
	if (sendto(ping->sockfd, &pckt, sizeof(pckt), 0, (struct sockaddr*)&ping->internet_addr,
							sizeof(ping->internet_addr)) <= 0) {
		printf("Packet sending fail!\n");
		return (-1);
	}
	return (0);
}

int	init_pck(t_ping *ping)
{
	if ((init_sock(ping)) < 0)
		return (-1);

	if ((send_ping(ping)) < 0)
		return (-1);
	// init pck
	// 	->header ip
	// 	->header icmp
	// send
	// rec
	// check


	return (0);
}
