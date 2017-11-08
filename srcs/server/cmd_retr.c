/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_retr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:32:28 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/08 15:12:28 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		cmd_retr(t_ftp *ftp, char **av)
{
	int		sock;
	int		fd;
	struct stat	buf;
	char	*file;
	int		i;
	char	**split;

	sock = dconn_open(ftp);
	if ((fd = open(av[1], O_RDONLY)) < 0 || fstat(fd, &buf) < 0)
		return (ftp_ret(ftp, "550 file not found / no access"));
	if (buf.st_size)
	{
		if ((file = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
				== MAP_FAILED)
			return (ftp_ret(ftp, "550 mmap failed"));
		split = ft_strsplit(file, '\n');
		i = -1;
		while (split[++i])
			ftp_send(sock, split[i]);
		ft_sstrfree(split);
		munmap(file, buf.st_size);
	}
	ftp_ret(ftp, "226 closing dataconn");
	close(sock);
	return (0);
}
