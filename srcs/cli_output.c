#include "ft_p.h"

int		read_req()
{
	int		req;

	if (read(sock, (char*)&req, sizeof(req)) < 0)
		return(1);
	console_msg(0, "%i RECEIVED", req);
	return (req);
}
