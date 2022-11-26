#include "../includes/ft_ping.h"

//Timout delay fo receiving packets
#define RECV_TIMEOUT 1
//Ttl value
#define TTL_VAL 64
// Packet size
#define PING_PKT_S 64

//Struct ping packet
struct ping_pkt
{
	struct icmphdr hdr;
	char msg[PING_PKT_S - sizeof(struct icmphdr)];
};

unsigned short checksum(void *b, int len)
{
	unsigned short *buf = b;
	unsigned int sum=0;
	unsigned short result;

	for ( sum = 0; len > 1; len -= 2 )
		sum += *buf++;
	if ( len == 1 )
		sum += *(unsigned char*)buf;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	result = ~sum;
	return result;
}

int	set_sockopt(int sockfd)
{
	int		ttl_val;
	struct	timeval	tv_out;

	ttl_val = TTL_VAL;
	tv_out.tv_sec = RECV_TIMEOUT;
	tv_out.tv_usec = 0;
	if (setsockopt(sockfd, SOL_IP, IP_TTL, &ttl_val, sizeof(ttl_val)) != 0)
	{
		printf("error set option ttl socket\n");
		return (1);
	}
	if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv_out, sizeof(tv_out)) != 0)
	{
		printf("error set option timeout socket\n");
		return (1);
	}
	return (0);
}

int	rec_ping(int sockfd, struct sockaddr_in *ping_addr)
{
	struct msghdr	msg;
	struct iovec	iov[1];
	char		msg_buffer[PING_PKT_S];
	struct cmsghdr	ct_buf;

	memset(&msg_buffer, 0, sizeof(msg_buffer));
	memset(iov, 0, sizeof(iov));
	memset(&msg, 0, sizeof(msg));

	iov[0].iov_base = msg_buffer;
	iov[0].iov_len = sizeof(msg_buffer);
	msg.msg_name = &ping_addr;
	msg.msg_namelen = sizeof((void *)ping_addr);
	msg.msg_iov = iov;
	msg.msg_iovlen = 1;
	msg.msg_control = &ct_buf;
	msg.msg_controllen = sizeof(ct_buf);

	printf("ret recvmsg %zd\n", recvmsg(sockfd, &msg, 0));

	struct icmphdr *icmp = (void *)msg_buffer + sizeof(struct iphdr);

	if (icmp->type == 0)
		return (0);
	return (1);
	//printf("type %d \n", icmp->type);
	//printf("type reply %d \n", ICMP_ECHOREPLY);


}

int	send_ping(int sockfd, struct sockaddr_in *ping_addr)
{
	unsigned int 	i	= 0;
	struct ping_pkt pckt;
	struct timeval	time_start;
	struct timeval	time_end;
	long double	total_time = 0;

	ft_bzero(&pckt, sizeof(pckt));
	pckt.hdr.type = ICMP_ECHO;
	pckt.hdr.code = 0;
	pckt.hdr.un.echo.id = getpid();
	while (i < sizeof(pckt.msg) - 1)
	{
		pckt.msg[i] = i;
		i++;
	}
	pckt.msg[i] = 0;
	pckt.hdr.un.echo.sequence = 1;
	pckt.hdr.checksum = checksum(&pckt, sizeof(pckt));
	gettimeofday(&time_start, NULL);

	printf("time of day %ld.%ld\n",time_start.tv_sec, time_start.tv_usec);
	if (sendto(sockfd, &pckt, sizeof(pckt), 0, (struct sockaddr*)ping_addr, sizeof(*ping_addr)) <= 0) {
		printf("Packet sending failded!\n");
		return (1);
	}
	if (rec_ping(sockfd, ping_addr) > 0) {
		printf("Packet not receive\n");
		return (1);
	}
	gettimeofday(&time_end, NULL);
	total_time += (time_end.tv_sec - time_start.tv_sec) * 1000.0 +
		(time_end.tv_usec - time_start.tv_usec) / 1000.0;
	printf("time total ping %.2Lf ms.\n", total_time);

	return (0);
}

int	main(int ac, char **av)
{
	int			sockfd;
	struct	addrinfo 	*addr;
	struct	sockaddr_in	internet_addr;

	if (ac < 2) {
		printf("ping: usage error: Destination address required\n");
		return (1);
	}

	if ((getaddrinfo(av[1], NULL, NULL, &addr)) != 0) {
		printf("ping: %s: Name or service not known\n", av[1]);
		return (1);
	}
	internet_addr = *(struct sockaddr_in*)addr->ai_addr;
  	printf("%s is at: %s\n",av[1], inet_ntoa(internet_addr.sin_addr));

	if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0
			|| set_sockopt(sockfd) == 1) {
		printf("Error Socket");
		return (1);
	}
	send_ping(sockfd, &internet_addr);

	return (0);
}
