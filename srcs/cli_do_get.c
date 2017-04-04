#include "ft_p.h"

int		cli_do_get(int sock, char **av)
{
	int		rep;
	int		num_blks;
	int		num_last_blk;
	int		i;
	int		fd;

	(void)av;
	if (!av[1] || av[2])
		return (console_msg(-1, "usage: get <file>"));
	if (req_init(sock, REQUEST_FILE, "PORT"))
		return (1);
	write(sock, av[1], ft_strlen(av[1]));
	read(sock, (char*)&rep, sizeof(rep));
	if (ntohs(rep) != FILENAME_OK)
	{
		cli_output(REQUEST_FILE, "PORT", "no such file");
		return (1);
	}
	rep = htons(TRANSFER_START);
	if ((fd = open_new(av[1], O_WRONLY | O_TRUNC | O_APPEND)) < 0)
		rep = htons(ABORT);
	write(sock, (char*)&rep, sizeof(rep));
	if (rep != htons(TRANSFER_START))
		return (1);
	net_get(sock, (char*)&num_blks, sizeof(num_blks));
	net_get(sock, (char*)&num_last_blk, sizeof(num_last_blk));
	num_blks = ntohs(num_blks);
	num_last_blk = ntohs(num_last_blk);
	if (g_debug > 3)
	{
		console_msg(3, "received num_blks=[%i]", num_blks);
		console_msg(3, "received num_last_blk=[%i]", num_last_blk);
	}
	i = -1;
	while (++i < num_blks)
		net_get_fd(sock, fd, MAXSIZE);
	if (num_last_blk)
		net_get_fd(sock, fd, MAXSIZE);
	return (0);
}
