#include "../includes/ft_ping.h"

//Timout delay fo receiving packets
#define RECV_TIMEOUT 1

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

int	send_ping(int sockfd, struct sockaddr_in *ping_addr)
{
	unsigned int i	= 0;
	int	ttl_val = 64;
	struct	timeval  tv_out;
	struct	ping_pkt pckt;

	tv_out.tv_sec = RECV_TIMEOUT;
	tv_out.tv_usec = 0;
	if (setsockopt(sockfd, SOL_IP, IP_TTL, &ttl_val, sizeof(ttl_val)) != 0)
	{
		printf("error set option ttl socket\n");
		return (1);
	}
	if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv_out, sizeof(tv_out)) != 0)
	{
		printf("error set option ttl socket\n");
		return (1);
	}

	ft_bzero(&pckt, sizeof(pckt));
	pckt.hdr.type = ICMP_ECHO;
	pckt.hdr.un.echo.id = getpid();
	while (i < sizeof(pckt.msg) - 1)
	{
		pckt.msg[i] = i+'0';
		i++;
	}
	pckt.msg[i] = 0;
	pckt.hdr.un.echo.sequence = 1; //nb ping
	pckt.hdr.checksum = checksum(&pckt, sizeof(pckt));

	if (sendto(sockfd, &pckt, sizeof(pckt), 0, (struct sockaddr*)ping_addr, sizeof(*ping_addr)) <= 0)
		printf("Packet sending failded!\n");
	return (0);
}

int	main(int ac, char **av)
{
	int	sockfd;
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

	if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0) {
		printf("Error Socket");
		return (1);
	}

	send_ping(sockfd, &internet_addr);
	return (0);
}
