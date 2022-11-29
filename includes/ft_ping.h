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

typedef struct	s_ping {
	unsigned int		opt_h;
	unsigned int		opt_v;
	int			sockfd;
	struct	sockaddr_in	internet_addr;
}				t_ping;

#endif
