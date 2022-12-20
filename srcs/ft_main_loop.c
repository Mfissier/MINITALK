/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achretie <achretie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:08:32 by achretie          #+#    #+#             */
/*   Updated: 2022/12/20 09:32:03 by achretie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_init_data(t_data *data, char **envp)
{
	int		i;
	t_env	*head;

	head = NULL;
	i = 0;
	while (envp[i])
		i++;
	head = ft_fill_list(head, envp, i);
	data->envp = head;
	data->input = NULL;
	data->cd_str = NULL;
	data->ret_value = 0;
	data->exit = 0;
	data->cmd = NULL;
	data->full_cmd = NULL;
	data->pid = 0;
	data->idoc = 0;
	data->in = -1;
	data->out = -1;
	data->bug = 0;
}

void    ft_main_loop(t_pex *p, t_data *data, t_args *args)
{
    int i;
    char    **envp;
	char	**cmd_sep_by_pipes;
	char	*clean_cmd;

    envp = ft_env_to_tab(data);
    p->nb_cmd = ft_get_nb_cmd(args, p);
	p->solo_pid = 0;
	i = 0;
	if (p->nb_cmd == 1)
	{
		clean_cmd = ft_redir_parse(data, data->input);
		if (ft_isbuiltin(args, data))
			return ;
		else
		{
			p->full_cmd = ft_split(clean_cmd, ' ');
        	p->cmd = ft_execve_path(p->full_cmd, envp);
			if (!data->bug)
				ft_exec_cmd(p, envp, data);
		}
	}	else if (p->nb_cmd > 1)
	{
		cmd_sep_by_pipes =  ft_split(data->input, '|');
    	while (i < p->nb_cmd)
    	{
			clean_cmd = ft_redir_parse(data, cmd_sep_by_pipes[i]);
			//ft_isbuiltin(args, data);                            cat < lol | grep 1 | wc -c > output
	    	p->full_cmd = ft_split(clean_cmd, ' ');
        	p->cmd = ft_execve_path(p->full_cmd, envp);
			ft_exec_pipe(p, i, envp, data);
			ft_free_path(p->full_cmd);
			free(p->cmd);
			free(clean_cmd);
			data->out = -1; 
			data->in = -1;
			data->bug = 0;
        	i++;
		}
		ft_free_path(cmd_sep_by_pipes);
	}
}

void	ft_reset(t_data *data)
{
	dup2(1, 1);
	dup2(0, 0);
	data->out = -1; 
	data->in = -1;
	data->bug = 0;
}

int	ft_start_commands(t_data *data, t_args *args)
{
	t_pex	p;

    ft_main_loop(&p, data, args);
	waitpid(p.solo_pid, NULL, 0);
	ft_end_pipes(&p);
	ft_reset(data);
	return (0);
}