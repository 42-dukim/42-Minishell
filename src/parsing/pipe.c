/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkwak <junkwak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:03:50 by junkwak           #+#    #+#             */
/*   Updated: 2024/12/13 16:36:27 by junkwak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../inc/minishell.h"

// int     ft_pipe(char *split, t_pipe *pipe, int i)
// {       
//         int     err_1;
//         int     err_2;
        
//         err_1 = 0;
//         err_2 = 0;
//         if (!split)
//                 return (-1);
//         while (i <= pipe->p_count)
//         {
//                 if (i < pipe->p_count)//처음
//                         err_1 = dup2(pipe->fd[1], STDOUT_FILENO);
//                         //close(pipe->fd[1]);
//                 else if (i > 0 && i < pipe->p_count)
//                 {
//                    err_2 = dup2(pipe->fd[i - 1], STDIN_FILENO);
//                    err_1 = dup2(pipe->fd[1], STDOUT_FILENO);
//                    close(pipe->fd[i - 1]);
//                 }
//                 if (err_1 == -1 || err_2 == -1)
//                         exit(1);
//                 i++;
//                 close(pipe->fd[0]);
//                 close(pipe->fd[1]);
//                 //close(pipe->fd[1]);
//         }
//         return (0);
// }
// void    ft_fork(char *line, t_pipe *pipe, int **result)
// {
//         int     i;

//         i = 0;
//         while (i < pipe->p_count)
//         {
//                 pipe->pid = fork();
//                 if (pipe->pid == 0)
//                 {
//                         if (pipe->p_count > 0)
//                                 ft_pipe(line, pipe, i);
//                 }
//                 i++;
//         }
// }
// // void    pipe_inst(char *line)
// // void    pipe_inst(t_list *token_list)
// {
//         t_pipe  *pipe;
//         int    **result;

//         result = malloc(sizeof(int *) * (pipe->p_count - 1));
//         if (!result)
//                 return ;
//         pipe->p_count = 0;
//         pipe->pid = 0;
//         ft_fork(line, pipe,result);
// }
