#include "../includes/ft_ping.h"

uint16_t checksum(void *b, size_t len)
{
	unsigned short *buf = b;
	unsigned int sum = 0;
	unsigned short result;

	while (len > 1)
	{
		sum += *buf++;
		len = len -2;
	}
	if (len == 1 )
		sum += *(unsigned char*)buf;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	result = ~sum;
	return (result);
}

void    ft_bzero(void *s, size_t n)
{
    char    *cpy;
    size_t  i;

    i = 0;
    cpy = s;
    while (i < n)
    {
        cpy[i] = '\0';
        i++;
    }
}

void    *ft_memset(void *s, int c, size_t n)
{
    size_t  i;
    char    *cpy;

    cpy = s;
    i = 0;
    while (i < n)
    {
        cpy[i] = (unsigned char)c;
        i++;
    }
    return (cpy);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char*)dest)[i] = ((char*)src)[i];
		i++;
	}
	return (dest);
}

void	print_help()
{
	printf("Usage: sudo ./ft_ping [OPTION...] HOST\n");
	printf("Send ICMP ECHO_REQUEST packets to network hosts.\n");
	printf("Options valid :\n");
	printf("  -v    verbose output\n");
	printf("  -h    give this help list\n");
}

char            *return_addr(char *buf)
{
    char				tmp_addr[INET_ADDRSTRLEN];
	struct addrinfo		*addr = NULL;
	struct addrinfo		hint = {.ai_family = AF_INET, .ai_socktype = SOCK_RAW, .ai_protocol = IPPROTO_ICMP};

	if (getaddrinfo(buf, NULL, &hint, &addr) < 0) {
        return (NULL);
    }
	inet_ntop(addr->ai_family, &((struct sockaddr_in *)addr->ai_addr)->sin_addr, tmp_addr, INET_ADDRSTRLEN);
    printf("%s", tmp_addr);
	freeaddrinfo(addr);
	return (0);
}