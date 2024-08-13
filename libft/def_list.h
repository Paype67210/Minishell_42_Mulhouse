/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_list.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeter <jpeter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:40:13 by pdeson            #+#    #+#             */
/*   Updated: 2024/04/19 11:50:48 by jpeter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEF_LIST_H
# define DEF_LIST_H

typedef struct s_list{
	void			*content;
	char			*execve_path;
	int				type;
	size_t			size;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

#endif
