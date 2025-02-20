/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   lexer.h                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: rtorrent <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/18 14:27:10 by rtorrent       #+#    #+#                */
/*   Updated: 2025/02/20 17:16:12 by rtorrent       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/* token categories
 * 
 * separator : "," or "\n"
 * identifier: "NO", "SO", "WE", "EA", "F", or "C"
 * literal   : everything else
*/

enum e_category
{
	SEPARATOR,
	IDENTIFIER,
	LITERAL
};

struct s_token
{
	enum e_category	name;
	char			*value;
	unsigned int	line;
	unsigned int	pos;
};

#endif
