/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:15:10 by edawood           #+#    #+#             */
/*   Updated: 2022/11/10 15:31:59 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <stdbool.h>

typedef struct t_pipex {
	char	*infile;
	int		infilefd;
	char	*outfile;
	int		outfilefd;
	char	*cmd1;
	char	*cmd2;
	char	*all_paths;
	char	*path;
	int		fd[2];
	int		pid1;
	int		pid2;
	int		exit_code;
}	t_pipex;

int		main(int argc, char **argv, char **envp);
void	ft_error(void);
char	*all_paths(char **envp);
int		ft_isspace(int c);
char	*get_path(char *all_paths, char **cmd);
void	first_child(char **envp, t_pipex *pipex);
void	second_child(char **envp, t_pipex *pipex);
void	ft_err_child_one(char *input, char *cmd, bool input_file, bool path);
void	ft_err_child_two(char **input, char *cmd, int code, bool input_file);
void	second_child_errors(int code, bool spaces);

#endif