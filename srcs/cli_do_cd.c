#include "ft_p.h"

int		cli_do_cd(int sock, char **av)
{
	if (!av[1] || av[2])
		return (console_msg(-1, "usage: cd <path>"));
	if (req_init(sock, REQUEST_CD))
		return (1);
	write(sock, av[1], ft_strlen(av[1]));
	return (0);
}
