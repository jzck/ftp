#include "ft_p.h"

int		cli_output(int req, char *name, char *msg)
{
	ft_printf("%i %s %s\n", req, name, msg);
	return (0);
}
