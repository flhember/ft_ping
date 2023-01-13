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