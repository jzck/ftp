/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_do_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 12:09:37 by jhalford          #+#    #+#             */
/*   Updated: 2017/10/08 12:25:05 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		serv_get_fname(int sock, char **file, struct stat *stat)
{
	int		rep;
	int		fd;
	char	fname[MAXLINE];

	ft_bzero(&fname, MAXLINE);
	rep = htons(FILENAME_OK);
	if (read(sock, fname, MAXLINE) < 0)
		rep = htons(ERR_READ);
	else if ((fd = open(fname, O_RDONLY)) < 0)
		rep = htons(NO_SUCH_FILE);
	else if ((fstat(fd, stat)) < 0)
		rep = htons(ERR_STAT);
	else if ((*file = mmap(NULL, stat->st_size, PROT_READ, MAP_PRIVATE, fd, 0))
			== MAP_FAILED)
		rep = htons(ERR_MMAP);
	write(sock, (char*)&rep, sizeof(rep));
	return (rep);
}

int		serv_do_get(int sock)
{
	int			req;
	struct stat	stat;
	char		*file;

	file = NULL;
	if (serv_get_fname(sock, &file, &stat))
		return (CMD_FAIL);
	DG("GOING TO READ_REQ");
	req = read_req(sock);
	if (req != TRANSFER_START)
		return (CMD_FAIL);
	net_send_large(sock, file, stat.st_size);
	if (file)
		munmap(file, stat.st_size);
	return (CMD_SUCCESS);
}
