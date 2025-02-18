/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   tokenizer.h                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: rtorrent <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/18 14:27:10 by rtorrent       #+#    #+#                */
/*   Updated: 2025/02/18 14:33:06 by rtorrent       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

enum e_category
{
	IDENTIFIER,
	LITERAL,
	SEPARATOR
};

struct s_token
{
	enum e_category	name;
	char			*value;
	int				line;
};

#endif
