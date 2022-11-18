#include "../includes/ft_ping.h"

int	main(int ac, char **av)
{
	int	sockfd;
	struct	addrinfo 	*addr;
	struct	sockaddr_in	*internet_addr;

	if (ac < 2) {
		printf("ping: usage error: Destination address required\n");
		return (1);
	}
	if ((getaddrinfo(av[1], NULL, NULL, &addr)) != 0) {
		printf("ping: %s: Name or service not known\n", av[1]);
		return (1);
	}
	internet_addr = (struct sockaddr_in*)addr->ai_addr;
  	printf("%s is at: %s\n",av[1], inet_ntoa(internet_addr->sin_addr));
	if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0) {
		printf("Error Socket");
		return (1);
	}
	return (0);
}
