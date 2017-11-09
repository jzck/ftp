/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_retr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:32:28 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/09 15:14:57 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		cmd_retr(t_ftp *ftp, char **av)
{
	int		fd;
	struct stat	buf;
	char	*file;
	int		i;
	char	**split;

	if (dconn_open(ftp) < 0)
		return (-1);
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
			ftp_send(ftp->d_sock, split[i]);
		ft_sstrfree(split);
		munmap(file, buf.st_size);
	}
	dconn_close(ftp);
	return (0);
}
