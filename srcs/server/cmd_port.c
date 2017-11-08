/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_port.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 18:42:50 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/08 17:17:44 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		cmd_port(t_ftp *ftp, char **av)
{
	char	**hostport;
	char	buf[INET_ADDRSTRLEN];

	if (!av[1])
		return (ftp_ret(ftp, "501 syntax error in parameter"));
	if (ftp->data_state == DATA_PASV)
		close(ftp->dconn.sock);
	hostport = ft_strsplit(av[1], ',');
	ftp->dconn.sin.sin_family = AF_INET;
	ftp->dconn.sin.sin_port = htons(256 * ft_atoi(hostport[4])
			+ ft_atoi(hostport[5]));
	ftp->dconn.sin.sin_addr.s_addr = 
		htonl(
		256 * 256 * 256 * ft_atoi(hostport[0])
		+ 256 * 256 * ft_atoi(hostport[1])
		+ 256 * ft_atoi(hostport[2])
		+ ft_atoi(hostport[3]));
	ftp->data_state = DATA_ACTV;
	console_msg(1, "remote dconn @ %s:%i",
			inet_ntop(AF_INET, &ftp->dconn.sin.sin_addr, buf, sizeof(struct sockaddr_in)),
			ntohs(ftp->dconn.sin.sin_port));
	return (ftp_ret(ftp, "200 ip/port ok"));
}
