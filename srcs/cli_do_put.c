#include "ft_p.h"

int		cli_do_put(int sock, char **av)
{
	int		req;
	int		fd;
	struct stat	stat;
	char	*file;

	if (!av[1] || av[2])
		return (console_msg(-1, "usage: put <file>"));
	else if ((fd = open(av[1], O_RDONLY)) < 0)
		return (console_msg(-1, "no such file"));
	else if ((fstat(fd, &stat)) < 0)
		return (console_msg(-1, "fstat error"));
	else if ((file = mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
			== MAP_FAILED)
		return (console_msg(-1, "mmap error"));

	if (req_init(sock, REQUEST_PUT))
		return (1);

	write(sock, av[1], ft_strlen(av[1]));

	req = read_req(sock);
	if (req != TRANSFER_START)
		return (1);

	net_send_large(sock, file, stat.st_size);
	return (0);
}
