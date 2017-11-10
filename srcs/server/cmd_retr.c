/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_retr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:32:28 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/10 18:54:04 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		cmd_retr(t_ftp *ftp, char **av)
{
	int			fd;
	struct stat	buf;
	char		*file;

	if ((fd = open(av[1], O_RDONLY)) < 0 || fstat(fd, &buf) < 0)
		return (ftp_ret(ftp, "550 file not found / no access"));
	if (buf.st_size)
	{
		if ((file = mmap(NULL, buf.st_size, PROT_READ | PROT_WRITE,
						MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		{
			close(fd);
			return (ftp_ret(ftp, "550 mmap failed"));
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
	}
	else
	{
		if (dconn_open(ftp) < 0)
			return (-1);
		dconn_close(ftp);
	}
	return (0);
}
