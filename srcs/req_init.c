#include "ft_p.h"

int		req_init(int sock, int req)
{
	int		rep;
	int		net_req;

	net_req = htons(req);
	tcflush(sock, TCIFLUSH);
	write(sock, (char*)&net_req, sizeof(net_req));
	rep = read_req(sock);
	return (rep != CMD_SUPPORTED);
}
