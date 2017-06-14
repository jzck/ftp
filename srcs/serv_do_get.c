#include "ft_p.h"

int		serv_do_get(int sock)
{
	char 	fname[MAXLINE];
	int		req;
	int		rep;
	int		fd;
	struct stat	stat;
	char	*file;
	int		num_blks;
	int		num_last_blk;
	int		i;

	DG("%i file requested", REQUEST_FILE);
	ft_bzero(&fname, MAXLINE);
	rep = htons(FILENAME_OK);
	file = NULL;
	if (read(sock, fname, MAXLINE) < 0)
		rep = htons(ERR_READ);
	else if ((fd = open(fname, O_RDONLY)) < 0)
		rep = htons(NO_SUCH_FILE);
	else if ((fstat(fd, &stat)) < 0)
		rep = htons(ERR_STAT);
	else if ((file = mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
			== MAP_FAILED)
		rep = htons(ERR_MMAP);
	write(sock, (char*)&rep, sizeof(rep));

	if (ntohs(rep) != FILENAME_OK)
		return (1);
	if (read(sock, (char*)&req, sizeof(req)) < 0)
		rep = htons(ERR_READ);
	DG("start transfer command, %d, received", ntohs(req));

	num_blks = htons(stat.st_size / MAXSIZE + 1);
	num_last_blk = htons(stat.st_size % MAXSIZE);
	DG("telling client file has [%i] blocks", ntohs(num_blks));
	if (net_send(sock, (char*)&num_blks, sizeof(num_blks)))
		DG("ACK not received on num_blks");
	DG("telling client last block has [%i] bytes", ntohs(num_last_blk));
	if (net_send(sock, (char*)&num_last_blk, sizeof(num_blks)))
		DG("ACK not received on size of last block");

	num_blks = ntohs(num_blks);
	num_last_blk = ntohs(num_last_blk);
	i = -1;	
	while (++i < num_blks - 1)
		net_send(sock, file + i * MAXSIZE, MAXSIZE);
	if (num_last_blk)
		net_send(sock, file + i * MAXSIZE, MAXSIZE);

	if (file && munmap(file, stat.st_size) < 0)
		rep = htons(ERR_MMAP);
	return (0);
}
