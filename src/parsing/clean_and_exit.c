#include "../../inc/game.h"

void	clean_and_exit(t_data *data, t_ecode ecode)
{
	free(data);
	exit(ecode);
}
