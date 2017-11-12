/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 16:20:14 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/12 19:19:47 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

static char	*fname(char *path)
{
	char	*bs;
	
	bs = ft_strrchr(path, '/');
	if (bs)
		return (bs + 1);
	else
		return (path);
}

int		cli_put(t_ftp *ftp, char **av)
{
	struct stat	buf;
	char		*file;
	int			fd;

	if (!av[1] || av[2])
		return (console_msg(-1, "usage: put <filename>"));
	if ((fd = open(av[1], O_RDONLY)) < 0 || fstat(fd, &buf) < 0)
	{
		console_msg(0, "no such file or directory");
		return (-1);
	}
	if (!buf.st_size || (file = mmap(NULL, buf.st_size, PROT_READ,
					MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (close(fd));
	close(fd);
	if (dconn_init(ftp) < 0)
		return (munmap(file, buf.st_size));
	FTP_CMD(ftp, "STOR %s", fname(av[1]));
	if (dconn_open(ftp) < 0)
		return (munmap(file, buf.st_size));
	console_msg(0, "Upload in progess, please wait... %i", buf.st_size);
	/* ftp_sendraw(ftp->d_sock, file, buf.st_size); */
	send(ftp->d_sock, file, buf.st_size, 0);
	close(ftp->d_sock);
	ftp->d_sock = 0;
	dconn_close(ftp);
	munmap(file, buf.st_size);
	return (0);
}
