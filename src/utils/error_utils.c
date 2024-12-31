#include "../../inc/minishell.h"

void	print_stderr(const char *str1, const char *str2)
{
	char	*str;

	str = ft_strjoin(str1, str2);
	perror(str);
	free(str);
}
