#include "ft_p.h"

int		read_req(int sock)
{
	int		req;

	if (read(sock, (char*)&req, sizeof(req)) < 0)
		return(0);
	req = ntohs(req);
	console_msg(0, "%i RECEIVED", req);
	return (req);
}
