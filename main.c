/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:53:29 by edawood           #+#    #+#             */
/*   Updated: 2022/11/24 18:37:19 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*all_paths(char **envp)
{
	while (*envp != '\0')
	{		
		if (!ft_strncmp("PATH=", *envp, 5))
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

void	pipexx(char **envp, t_pipex *pipex)
{
	int	wstatus;

	if (pipe(pipex->fd) < 0)
		ft_error();
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		ft_error();
	if (pipex->pid1 == 0)
		first_child(envp, pipex);
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
		ft_error();
	if (pipex->pid2 == 0)
		second_child(envp, pipex);
	close(pipex->fd[1]);
	close(pipex->fd[0]);
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, &wstatus, 0);
	if (WIFEXITED(wstatus))
		pipex->exit_code = WEXITSTATUS(wstatus);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
	{
		ft_putendl_fd("Error: wrong number of args", 2);
		exit(1);
	}
	pipex.infile = argv[1];
	pipex.cmd1 = argv[2];
	pipex.cmd2 = argv[3];
	pipex.outfile = argv[4];
	pipex.all_paths = all_paths(envp);
	if (!pipex.all_paths)
		ft_error();
	pipexx(envp, &pipex);
	close(pipex.infilefd);
	close(pipex.outfilefd);
	return (pipex.exit_code);
}
