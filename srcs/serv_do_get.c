#include "ft_p.h"

int		serv_do_get(int sock)
{
	char 	fname[MAXLINE];
	int		req;
	int		rep;
	int		fd;
	struct stat	stat;
	char	*file;

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
		return (CMD_FAIL);

	DG("GOING TO READ_REQ");
	req = read_req(sock);
	if (req != TRANSFER_START)
		return (CMD_FAIL);

	net_send_large(sock, file, stat.st_size);

	if (file && munmap(file, stat.st_size) < 0)
		rep = htons(ERR_MMAP);
	return (CMD_SUCCESS);
}
