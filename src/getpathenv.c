/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpathenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 20:32:42 by troberts          #+#    #+#             */
/*   Updated: 2022/08/06 11:32:48 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*generate_cmd_path(char *path_env, char *cmd)
{
	char	*path_cmd;
	char	*path_cmd_tmp;

	path_cmd_tmp = ft_strjoin(ft_strchr(path_env, '/'), "/");
	if (path_cmd_tmp == NULL)
	{
		perror("Error");
		return (NULL);
	}
	path_cmd = ft_strjoin(path_cmd_tmp, cmd);
	free(path_cmd_tmp);
	return (path_cmd);
}

static void	clean_error(char **array, char *str)
{
	free_double_ptr_char(array);
	if (str)
		exit_print(str);
	exit(EXIT_FAILURE);
}

char	*get_path_of_cmd(char **envp, char *cmd)
{
	int		i;
	char	**path_env;
	char	*path_cmd;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	path_env = ft_split(envp[i], ':');
	i = 0;
	path_cmd = generate_cmd_path(path_env[i], cmd);
	if (path_cmd == NULL)
		clean_error(path_env, NULL);
	i++;
	while (access(path_cmd, F_OK | X_OK) != 0)
	{
		free(path_cmd);
		i++;
		if (path_env[i] == NULL)
			clean_error(path_env, "No valid path found for command.");
		path_cmd = generate_cmd_path(path_env[i], cmd);
		if (path_cmd == NULL)
			clean_error(path_env, NULL);
	}
	return (path_cmd);
}