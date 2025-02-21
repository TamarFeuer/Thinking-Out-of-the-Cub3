/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   lexer_parser.h                                      :+:    :+:           */
/*                                                      +:+                   */
/*   By: rtorrent <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/18 14:27:10 by rtorrent       #+#    #+#                */
/*   Updated: 2025/02/21 12:36:04 by rtorrent       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_PARSER_H
# define LEXER_PARSER_H

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

// lexical tokens
struct s_token
{
	enum e_category	name;
	char			*value;
	unsigned int	line;
	unsigned int	pos;
};

// non-terminating symbols
enum e_ntsymbols
{

};

#endif
