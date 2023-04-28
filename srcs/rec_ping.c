#include "../includes/ft_ping.h"

static const char       *error_icmp[] = {
    "",
    "",
    "",
    "Destination Net Unreachable"
};

void            print_error_rec(struct icmphdr *rec_ping_icmp, struct iphdr	*rec_ping_ip, ssize_t bytes_rec)
{
    char buf[256];
    struct sockaddr_in tmp_addr;

    tmp_addr.sin_family = AF_INET;
    tmp_addr.sin_addr.s_addr = rec_ping_ip->saddr;
    getnameinfo((struct sockaddr *)&tmp_addr, sizeof(struct sockaddr_in), buf, sizeof(buf), NULL, 0, NI_NAMEREQD);
    printf("%zu bytes from %s (", bytes_rec - sizeof(struct iphdr), buf);
    return_addr(buf);
    printf("): %s\n", error_icmp[rec_ping_icmp->type]);

	//printf("Error Packet received with ICMP type %d\n", rec_ping_icmp->type);
}

// When packet return is error, we have to verif id in echo part
int            check_echo_reply(struct icmphdr *rec_ping_icmp)
{
    struct iphdr	*ip_echo = (struct iphdr*) rec_ping_icmp + 1;
	struct icmphdr *icmp_echo = (struct icmphdr*) ip_echo + 1;

    if (htons(icmp_echo->un.echo.id) == t_ping.cur_pid)
        return (1);
    return (-1);
}

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
	struct icmphdr  *rec_ping_icmp = (void *)receive_packet + sizeof(struct iphdr);
	struct iphdr	*rec_ping_ip = (void *)receive_packet;
	
	//check valid icmp reply code
	if (rec_ping_icmp->type != ICMP_ECHOREPLY)
	{
        //check if packet is for me
	    if (!check_echo_reply(rec_ping_icmp)) {
    		return (-1);
        }
        print_error_rec(rec_ping_icmp, rec_ping_ip, bytes_rec);
		return (-1);
	} else {
        //check if packet is for me
	    if (htons(rec_ping_icmp->un.echo.id) != t_ping.cur_pid) {
    		return (-1);
        }
		rtt = get_rtt_ping((void *)receive_packet + sizeof(struct iphdr) + sizeof(struct icmphdr));
		printf("%lu bytes from %s: icmp_seq=%d ttl=%d time=%ld.%03ld ms\n",
			bytes_rec - sizeof(struct iphdr), /*t_ping.hostname,*/ t_ping.hostname_addr, t_ping.seq, rec_ping_ip->ttl, rtt / 1000l, rtt % 1000l);
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
		return (0);
	}
	return (0);
}