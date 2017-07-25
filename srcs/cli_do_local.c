#include "ft_p.h"

char	**environ;

int		cli_do_local(int sock, char **av)
{
	char	*command;

	(void)sock;
	command = ft_strsepjoin(av + 1, ' ');
	system(command);
	return (-1);
}
