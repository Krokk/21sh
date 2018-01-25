/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 01:34:50 by rfabre            #+#    #+#             */
/*   Updated: 2018/01/25 01:34:51 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void ft_left_arrow(char *buf, t_edit *line)
{
	if (buf[2] == 68)
	{
		if (line->cursor_pos >= 3)
		{
			line->cursor_pos--;
			ft_putstr("\033[1D");
		}
	}
}

void ft_right_arrow(char *buf, t_edit *line)
{
	if (buf[2] == 67)
	{
		if (line->cursor_pos < line->max_size)
		{
			line->cursor_pos++;
			ft_putstr("\033[1C");
		}
		if (((line->cursor_pos) % line->sz.ws_col) == 0)
		{
			tputs(tgetstr("do", NULL), 1, ft_pointchar);
			tputs(tgetstr("cr", NULL), 1, ft_pointchar);
		}
	}
}

void ft_go_start(t_edit *line, char *buf)
{
	int i;

	i = 0;
	while (i < line->max_size)
	{
		buf[2] = 68;
		ft_left_arrow(buf, line);
		i++;
	}
	tputs(tgetstr("cd", NULL), 1, ft_pointchar);
	// line->cursor_pos = ft_strlen(line->line) + 2;
}

static void ft_highlight(t_edit *line, char *buf)
{
	int i;
	char *tmp;
	char *tmp2;

	i = 0;
	tmp = ft_strndup(line->line, line->start_select);
	ft_putstr(tmp);
	ft_putstr(tgetstr("mr", NULL));
	tmp2 = ft_strsub(line->line, line->start_select , (line->end_select - line->start_select));
	ft_putstr(tmp2);
	free(tmp);
	ft_putstr(tgetstr("me", NULL));
	tmp = ft_strsub(line->line, line->end_select , (line->max_size - 3));
	ft_putstr(tmp);
	line->cursor_pos = line->max_size;
	while ((size_t)++i <= ft_strlen(tmp))
	{
		buf[0] = 27;
		buf[1] = 91;
		buf[2] = 68;
		ft_left_arrow(buf, line);
	}
	free(tmp);
	free(line->is_highlight);
	line->is_highlight = tmp2;
}

void ft_isarrow(char *buf, t_edit *line)
{
	if (buf[2] == 68)
		ft_left_arrow(buf, line);
	else
		ft_right_arrow(buf, line);
	if (line->select_mode)
	{
		line->end_select = line->cursor_pos - 2;
		ft_go_start(line, buf);
		ft_highlight(line, buf);
	}

}

void ft_endkey(char *buf, t_edit *line)
{
	while (line->cursor_pos < line->max_size)
	{
		buf[0] = 27;
		buf[1] = 91;
		buf[2] = 67;
		ft_right_arrow(buf, line);
	}
}

void ft_homekey(char *buf, t_edit *line)
{
	while (line->cursor_pos > 2)
	{
		buf[0] = 27;
		buf[1] = 91;
		buf[2] = 68;
		ft_left_arrow(buf, line);
	}
}
