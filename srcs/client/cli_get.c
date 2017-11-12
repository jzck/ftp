/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 13:00:28 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/12 15:02:03 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

static int	cleanup(int fd, char *filename)
{
	close(fd);
	unlink(filename);
	return (-1);
}

int			cli_get(t_ftp *ftp, char **av)
{
	char	*msg;
	int		fd;
	int		size;

	if (!av[1] || av[2])
		return (console_msg(-1, "usage: get <filename>"));
	if ((fd = open(av[1], O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
		return (-1);
	if (dconn_init(ftp) < 0)
		return (cleanup(fd, av[1]));
	FTP_CMD(ftp, "RETR %s", av[1]);
	if (dconn_open(ftp) < 0)
		return (cleanup(fd, av[1]));
	size = ftp_recvraw(ftp->d_sock, &msg);
	write(fd, msg, size);
	ft_strdel(&msg);
	close(fd);
	dconn_close(ftp);
	return (0);
}
