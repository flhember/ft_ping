#ifndef FT_PING_H
# define FT_PING_H

# include <netinet/in.h>
# include <sys/socket.h>
# include <sys/time.h>
# include <sys/types.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <signal.h>
# include <netinet/ip_icmp.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <math.h>

#define TRUE 1
#define FALSE 0

#define RECV_TIMEOUT 1
#define TTL_VAL 64
#define PING_PKT_S 64
#define	PING_SLEEP 1000000

// Main struct with opt and info 
extern struct			s_ping {
	unsigned int		opt_h;
	unsigned int		opt_v;
	unsigned int		cur_pid;
	int					sockfd;
	char				*hostname;
	char				hostname_addr[INET_ADDRSTRLEN];
	unsigned int		seq;
	unsigned int		rec;
	struct				sockaddr_in	internet_addr;
	suseconds_t			rtt_min;
	suseconds_t			rtt_max;
	suseconds_t			rtt_avg;
	suseconds_t			rtt_mul;
	unsigned int		ttl_rec;
}						t_ping;

// Ping packet struct
typedef struct			s_ping_pkt {
	struct				icmphdr hdr;
    char				msg[PING_PKT_S - sizeof(struct icmphdr)];
}						t_ping_pkt;

// ft_ping:
int			parsing(int ac, char **av);
int			init_pck();
int			init_sock();
int 		rec_ping(int sockfd);
uint16_t 	checksum(void *b, size_t len);
void		print_help();
char		*return_addr(char *buf);
void		print_error_rec(struct icmphdr *rec_ping_icmp, struct iphdr	*rec_ping_ip, ssize_t bytes_rec);

// libft:
void    ft_bzero(void *s, size_t n);
void    *ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);

#endif