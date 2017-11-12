/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dconn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:55:15 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/12 14:44:50 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

static int	dconn_open_actv(t_ftp *ftp)
{
	int		sock;

	FTP_RET(ftp, "150 about to open data connection");
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(sock, (struct sockaddr*)&ftp->dconn.sin,
				sizeof(struct sockaddr_in)) < 0)
	{
		FTP_RET(ftp, "425 can't open data conn");
		return (-1);
	}
	ftp->d_sock = sock;
	return (0);
}

static int	dconn_open_pasv(t_ftp *ftp)
{
	int		sock;

	FTP_RET(ftp, "150 about to accept");
	if ((sock = accept(ftp->dconn.sock, NULL, NULL)) < 0)
	{
		FTP_RET(ftp, "425 can't open data conn");
		return (-1);
	}
	ftp->d_sock = sock;
	return (0);
}

int			dconn_open(t_ftp *ftp)
{
	if (ftp->d_sock)
	{
		FTP_RET(ftp, "125 data connection already open; transfer starting");
		return (0);
	}
	else if (ftp->data_state == DATA_ACTV)
		return (dconn_open_actv(ftp));
	else if (ftp->data_state == DATA_PASV || ftp->data_state == DATA_EPSV)
		return (dconn_open_pasv(ftp));
	else
	{
		FTP_RET(ftp, "425 can't establish data connection");
		console_msg(1, "dconn_open() called but no dconn available");
		return (-1);
	}
}

int			dconn_close(t_ftp *ftp)
{
	FTP_RET(ftp, "226 closing dataconn");
	if (ftp->data_state == DATA_PASV)
	{
		close(ftp->dconn.sock);
		ftp->data_state = DATA_NONE;
	}
	close(ftp->d_sock);
	ftp->d_sock = 0;
	return (0);
}
