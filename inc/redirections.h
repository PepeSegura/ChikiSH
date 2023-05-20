/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepe <pepe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 21:17:49 by pepe              #+#    #+#             */
/*   Updated: 2023/05/18 00:16:29 by pepe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "minishell.h"

# define TEMP_FILE ".here_doc"

/*__HERE_DOC__*/
void	here_doc(char *limit, int fd);
int		open_files(int identifier, char *filename);

#endif
