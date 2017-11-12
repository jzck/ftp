/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_retr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:32:28 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/12 14:50:38 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

static int	retr_internal(t_ftp *ftp, struct stat buf, int fd)
{
	char		*file;

	if ((file = mmap(NULL, buf.st_size, PROT_READ | PROT_WRITE,
					MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		close(fd);
		return (FTP_RET(ftp, "550 mmap failed"));
	}
	close(fd);
	if (dconn_open(ftp) < 0)
	{
		munmap(file, buf.st_size);
		return (-1);
	}
	send(ftp->d_sock, file, buf.st_size, 0);
	dconn_close(ftp);
	munmap(file, buf.st_size);
	return (0);
}

int			cmd_retr(t_ftp *ftp, char **av)
{
	int			fd;
	struct stat	buf;

	if ((fd = open(av[1], O_RDONLY)) < 0 || fstat(fd, &buf) < 0)
		return (FTP_RET(ftp, "550 file not found / no access"));
	if (buf.st_size)
		return (retr_internal(ftp, buf, fd));
	close(fd);
	if (dconn_open(ftp) < 0)
		return (-1);
	dconn_close(ftp);
	return (0);
}
