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
