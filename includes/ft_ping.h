#ifndef FT_PING_H
# define FT_PING_H

# include "../libft/includes/libft.h"
# include <netinet/in.h>
# include <sys/socket.h>
# include <sys/time.h>
# include <sys/types.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <signal.h>
# include <netinet/ip_icmp.h>

#define TRUE 1
#define FALSE 0

#define RECV_TIMEOUT 1
#define TTL_VAL 64
#define PING_PKT_S 64

typedef struct	s_ping {
	unsigned int		opt_h;
	unsigned int		opt_v;
	int			sockfd;
	char			*raw_host;
	struct	sockaddr_in	internet_addr;
}				t_ping;

int	init_pck(t_ping *ping);

#endif
