/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:53:17 by edawood           #+#    #+#             */
/*   Updated: 2022/11/16 12:30:05 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

char	*get_path(char *all_paths, char **cmd)
{
	char	*temp;
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	paths = ft_split(all_paths, ':');
	if (!paths)
		return (NULL);
	if (access(*cmd, X_OK) == 0)
		return (*cmd);
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, cmd[0]);
		free(temp);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		free(paths[i++]);
	}
	free(paths);
	return (NULL);
}

void	first_child(char **envp, t_pipex *pipex)
{
	char	**cmds1;

	pipex->infilefd = open(pipex->infile, O_RDONLY);
	if (pipex->infilefd == -1)
		ft_err_child_one(pipex->infile, NULL, true, false);
	if (pipex->cmd1[0] == '\0' && pipex->infilefd != -1)
		ft_putendl_fd("Error: permission denied: ", 2);
	cmds1 = ft_split(pipex->cmd1, ' ');
	dup2(pipex->fd[1], STDOUT_FILENO);
	close(pipex->fd[0]);
	dup2(pipex->infilefd, STDIN_FILENO);
	pipex->path = get_path(pipex->all_paths, cmds1);
	if (ft_isspace(pipex->cmd1[0]))
		second_child_errors(127, true);
	execve(pipex->path, cmds1, envp);
	if (!ft_strchr(*cmds1, '/') && !pipex->path)
	{
		ft_putstr_fd("Error: command not found: ", 2);
		ft_putendl_fd(cmds1[0], 2);
	}
	else
		ft_err_child_one(NULL, cmds1[0], false, true);
}

void	second_child(char **envp, t_pipex *pipex)
{
	char	**cmds2;

	cmds2 = ft_split(pipex->cmd2, ' ');
	pipex->outfilefd = open(pipex->outfile, O_CREAT | O_TRUNC | O_RDWR, 0700);
	if (pipex->outfilefd < 0 || access(pipex->outfile, 0) != 0)
		ft_err_child_two(&pipex->outfile, NULL, 1, true);
	dup2(pipex->fd[0], STDIN_FILENO);
	close(pipex->fd[1]);
	dup2(pipex->outfilefd, STDOUT_FILENO);
	pipex->path = get_path(pipex->all_paths, cmds2);
	if (ft_isspace(pipex->cmd2[0]))
		second_child_errors(127, true);
	if (pipex->cmd2[0] == '\0')
		second_child_errors(126, false);
	execve(pipex->path, cmds2, envp);
	if (!ft_strchr(*cmds2, '/') && !pipex->path)
	{
		ft_putstr_fd("Error: command not found: ", 2);
		ft_putendl_fd(cmds2[0], 2);
		exit(127);
	}
	else
		ft_err_child_two(NULL, cmds2[0], 127, false);
}
