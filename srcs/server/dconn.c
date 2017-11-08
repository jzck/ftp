/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dconn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:55:15 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/08 17:30:21 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

static int	dconn_open_actv(t_ftp *ftp)
{
	int		sock;

	ftp_ret(ftp, "150 about to open data connection");
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(sock, (struct sockaddr*)&ftp->dconn.sin,
				sizeof(struct sockaddr_in)) < 0)
	{
		ftp_ret(ftp, "425 can't open data conn");
		return(-1);
	}
	ftp->d_sock = sock;
	return (0);
}

static int	dconn_open_pasv(t_ftp *ftp)
{
	int		sock;

	ftp_ret(ftp, "150 about to accept");
	if ((sock = accept(ftp->dconn.sock, NULL, NULL)) < 0)
	{
		ftp_ret(ftp, "425 can't open data conn");
		return(-1);
	}
	ftp->d_sock = sock;
	return (0);
}

int			dconn_open(t_ftp *ftp)
{
	if (ftp->d_sock)
	{
		ftp_ret(ftp, "125 data connection already open; transfer starting");
		return (0);
	}
	else if (ftp->data_state == DATA_ACTV)
		return (dconn_open_actv(ftp));
	else if (ftp->data_state == DATA_PASV)
		return (dconn_open_pasv(ftp));
	else
	{
		console_msg(1, "dconn_open() called but no dconn available");
		return (-1);
	}
}

int			dconn_close(t_ftp *ftp)
{
	ftp_ret(ftp, "226 closing dataconn");
	close(ftp->d_sock);
	ftp->d_sock = 0;
	return (0);
}
