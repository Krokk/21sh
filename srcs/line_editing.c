/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 01:34:48 by rfabre            #+#    #+#             */
/*   Updated: 2018/01/25 01:34:48 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void ft_insert(char *buf, t_edit *line)
{
	char *tmp;
	char *tmp2;
	char *tmp3;
	int i;

	i = 0;
	tmp = ft_strndup(line->line, line->cursor_pos - 3);
	tmp2 = ft_strsub(line->line, line->cursor_pos - 3 , line->max_size);
	ft_putchar(buf[0]);
	tmp3 = ft_freejoinstr(tmp, buf);
	free (line->line);
	line->line = ft_freejoinstr(tmp3, tmp2);
	tmp2 = ft_strsub(line->line, line->cursor_pos - 2 , line->max_size);
	ft_move_it(i, line, buf, 1);
	while ((size_t)i < ft_strlen(tmp2))
	{
		buf[2] = 68;
		ft_left_arrow(buf, line);
		i++;
	}
}

void ft_delete(char *buf, t_edit *line)
{
	char *tmp;
	char *tmp2;
	int i;

	i = 0;
	if ((line->cursor_pos == line->max_size) && (line->cursor_pos > 2))
	{
		i = 0;
		tmp = ft_strndup(line->line, ft_strlen(line->line) - 1);
		free (line->line);
		line->line = tmp;
		ft_move_it(i, line, buf, 0);
	}
	else if ((line->cursor_pos != line->max_size) && (line->cursor_pos > 2))
	{
		tmp = ft_strndup(line->line, (line->cursor_pos - 3));
		tmp2 = ft_strsub(line->line, (line->cursor_pos - 2),
				(ft_strlen(line->line) - line->cursor_pos) + 3);
		free (line->line);
		line->line = ft_freejoinstr(tmp, tmp2);
		ft_move_it(i, line, buf, 0);
		while ((size_t)i < ft_strlen(tmp2))
		{
			buf[2] = 68;
			ft_left_arrow(buf, line);
			i++;
		}
	}
}

void ft_move_it(int i, t_edit *line, char *buf, int check)
{
	while (i < line->max_size)
	{
		buf[2] = 68;
		ft_left_arrow(buf, line);
		i++;
	}
	if (check == 1)
		i = 0;
	if (check == 0)
	{
		line->cursor_pos--;
		line->max_size--;
	}
	tputs(tgetstr("cd", NULL), 1, ft_pointchar);
	ft_putstr(line->line);
	line->cursor_pos = ft_strlen(line->line) + 2;
}

void			ft_line_reset(t_edit *line)
{
	free (line->line);
	line->cursor_pos = 2;
	line->max_size = 2;
	line->line = ft_memalloc(sizeof(char));
}
