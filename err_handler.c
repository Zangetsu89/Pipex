/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:32:44 by edawood           #+#    #+#             */
/*   Updated: 2022/11/10 15:33:35 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_err_child_one(char *input, char *cmd, bool input_file, bool path)
{
	if (input_file == true)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(input, 2);
	}
	if (path == true)
	{
		if (cmd != NULL)
		{
			ft_putstr_fd("Error: no such file or directory: ", 2);
			ft_putendl_fd(cmd, 2);
		}
	}
	exit(errno);
}

void	ft_err_child_two(char **input, char *cmd, int code, bool value)
{
	if (value == true)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(*input, 2);
	}
	else
	{
		ft_putstr_fd("Error: no such file or directory: ", 2);
		ft_putendl_fd(cmd, 2);
	}
	exit(code);
}

void	second_child_errors(int code, bool spaces)
{
	if (spaces == true)
		ft_putendl_fd("Error: command not found:", 2);
	if (code == 126)
		ft_putendl_fd("Error: permission denied:", 2);
	exit(code);
}

void	ft_error(void)
{
	perror("Error");
	exit(errno);
}
