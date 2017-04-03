/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 19:18:58 by jhalford          #+#    #+#             */
/*   Updated: 2017/04/03 17:12:59 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_H
# define FT_P_H

# define FTP_SERVER_USAGE	"%s <port>"
# define FTP_CLIENT_USAGE	"%s <addr> <port>"
# define FTP_BUF			1024
# define FTP_REPLY_BUF		1024

#include "libft.h"
#include "sys/socket.h"
#include "netdb.h"
#include "netinet/in.h"
#include "arpa/inet.h"

typedef struct s_ftp_reply	t_ftp_reply;

struct		s_ftp_reply
{
	int		code;
	char	*data;
};

extern char		**g_av;

int		ftp_daemon(int sock);
int		ftp_spawn(int cs);
int		ftp_cmd(char *cmd, t_ftp_reply *reply);

#endif
