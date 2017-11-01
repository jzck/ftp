/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 19:18:58 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/01 19:14:28 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_H
# define FTP_H

# define MAXLINE		256

enum	e_ftp
{
	REQUEST_FILE = 100,
	REQUEST_PUT,
	REQUEST_SH,
	REQUEST_CD,
	CMD_NOT_SUPPORTED = 150,
	CMD_SUPPORTED = 160,
	FILENAME_OK = 700,
	NO_SUCH_FILE,
	TRANSFER_START,
	CD_DIR_NOT_FOUND,
	CD_RESTRICTED_DIR,
	ABORT = 800,
	ERR_READ,
	ERR_STAT,
	ERR_MMAP,
	CMD_SUCCESS = 900,
	CMD_FAIL,
};

#include "ftp_server.h"


#endif
