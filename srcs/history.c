/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 02:16:33 by rfabre            #+#    #+#             */
/*   Updated: 2018/01/25 23:19:24 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void ft_arrow_up(t_edit *line)
{
  int cnt;

  cnt = 0;

  if (!line->hstr || line->cursor_pos < line->max_size)
    return ;
  else if (line->curr == NULL)
    line->curr = line->hstr;
  else if (line->curr->up)
    line->curr = line->curr->up;
  while (cnt < line->max_size - 2)
  {
    ft_putstr("\b \b");
    cnt++;
  }
  ft_putstr(line->curr->cmd);
  free(line->line);
  line->line = ft_strdup(line->curr->cmd);
  line->max_size = ft_strlen(line->curr->cmd) + 2;
  line->cursor_pos = line->max_size;
}

void ft_arrow_down(t_edit *line)
{
  int cnt;

  cnt = 0;
  if (line->cursor_pos == line->max_size && line->curr)
  {
    while (cnt < line->max_size - 2)
    {
      ft_putstr("\b \b");
      cnt++;
    }
    if (line->curr->down)
    {
      line->curr = line->curr->down;
      ft_putstr(line->curr->cmd);
      free(line->line);
      line->line = ft_strdup(line->curr->cmd);
      line->max_size = ft_strlen(line->curr->cmd) + 2;
      line->cursor_pos = line->max_size;
    }
    else
      ft_line_reset(line);
  }
}


void ft_add_history(t_edit *line)
{
  t_hstr  *tmp;
  t_hstr  *new;

  if (line->line[0] == '\0')
      return ;
  new = ft_memalloc(sizeof(t_hstr));
  new->cmd = ft_strdup(line->line);
  new->up = NULL;
  new->down = NULL;

  if (!line->hstr)
    line->hstr = new;
  else if (ft_strcmp(line->line, line->hstr->cmd) != 0) //(line->curr != line->hstr) //avoid add in history last saved element
  {
    tmp = line->hstr;
    tmp->down = new;
    new->up = tmp;
    line->hstr = new;
  }
  else
  {
    free(new->cmd);
    free(new);
  }
}