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
	pckt->hdr.checksum = checksum(pckt, 64);
}

int rec_ping(int sockfd, t_ping *ping)
{
	ssize_t ret;
	char	control[1000];
	char    receive_packet[84];

	struct iovec io = 
	{                    
        .iov_base = receive_packet,		/* Adresse de début */
    	.iov_len = 84					/* Nombre d'octets à transférer */
    };

    struct msghdr msg =
	{
        .msg_name		= ping->raw_host,			/* adresse optionnelle */
        .msg_namelen	= sizeof(ping->raw_host),	/* taille de l'adresse */
        .msg_iov		= &io, 						/* tableau scatter/gather */
        .msg_iovlen		= 1,						/* # éléments dans msg_iov */
        .msg_control	= &control,					/* métadonnées, voir ci‐dessous */
        .msg_controllen	= sizeof(control)			/* taille du tampon de métadonnées */
        //.msg_flags		= 0;      /* attributs du message reçu */
    };

	ft_memset(receive_packet, 0, sizeof(receive_packet));
	ret = recvmsg(sockfd, &msg, 0);
	printf ("ret = %zu \n", ret);

	return (0);
}

int	send_ping(t_ping *ping)
{
	t_ping_pkt pckt;

	//set packet ping
	fill_pck(&pckt, ping);
	// send packet
	if (sendto(ping->sockfd, &pckt, sizeof(pckt), 0, (struct sockaddr*)&ping->internet_addr,
															sizeof(ping->internet_addr)) <= 0) {
		dprintf(2, "Packet sending fail!\n");
		return (-1);
	}
	//rec packet
	if (rec_ping(ping->sockfd, ping) > 0) {
		dprintf(2, "Packet not receive\n");
		return (1);
	}
	printf("Packet send! \n");
	return (0);
}

int	init_pck(t_ping *ping)
{
	// Init socket
	if ((init_sock(ping)) < 0)
		return (-1);

	if ((send_ping(ping)) < 0)
		return (-1);
	return (0);
}
