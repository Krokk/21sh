
#include "../includes/sh.h"

struct winsize		ft_init(t_edit *line)
{
	struct winsize sz;
	struct termios attributes;
	char			*name_term;

	if ((name_term = getenv("TERM")) == NULL)
		ft_putendl("<TERM> VARIABLE NOT FOUND");
	if (tgetent(NULL, name_term) == ERR)
		ft_putendl("VARIABLE NOT VALID");
	ioctl(STDERR_FILENO, TIOCGWINSZ, &sz);
	tcgetattr(0, &attributes);
	attributes.c_lflag &= ~(ICANON);
	attributes.c_lflag &= ~(ECHO);
	attributes.c_cc[VMIN] = 1;
	attributes.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &attributes);
  line->select_mode = 0;
	line->start_select = 0;
	line->end_select = 0;
	line->is_highlight = ft_strnew(0);
	return (sz);
}

int				ft_pointchar(int c)
{
	write(STDIN_FILENO, &c, 1);
	return (0);
}

void			ft_prompt(void)
{
	ft_putstr_fd(TURQUOISE, STDOUT_FILENO);
	ft_putstr_fd("$>", STDOUT_FILENO);
	ft_putstr_fd(DEFAULT, STDOUT_FILENO);
}
