
#include "../includes/sh.h"

void			ft_freetab(char **table)
{
	int			i;

	i = 0;
	if (!table)
		return ;
	while (table[i])
	{
		ft_strdel((&table[i]));
		i++;
	}
	if (table)
		ft_memdel((void **)&table);
}

void			ft_line_reset(t_edit *line)
{
	ft_strdel(&line->line);
	free(line->line);
	line->cursor_pos = 2;
	line->max_size = 2;
	line->line = ft_memalloc(sizeof(char));
	line->select_mode = 0;
	line->curr = NULL;
}
