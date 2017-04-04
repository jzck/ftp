#include "ft_p.h"

int		req_init(int sock, int req, char *name)
{
	int		rep;
	int		net_req;

	net_req = htons(req);
	write(sock, (char*)&net_req, sizeof(net_req));
	read(sock, (char*)&rep, sizeof(rep));
	rep = ntohs(rep);
	if (rep == CMD_SUPPORTED)
		cli_output(req, name, "command succesful");
	else if (rep == CMD_NOT_SUPPORTED)
		cli_output(req, name, "command not supported");
	else
		cli_output(req, name, "unexpected response");
	return (rep == CMD_SUPPORTED ? 0 : 1);
}
