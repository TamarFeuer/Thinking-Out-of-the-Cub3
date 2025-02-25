/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   lexer_parser.h                                      :+:    :+:           */
/*                                                      +:+                   */
/*   By: rtorrent <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/18 14:27:10 by rtorrent       #+#    #+#                */
/*   Updated: 2025/02/25 15:56:18 by rtorrent       ########   odam.nl        */
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

enum e_id
{
	EA,
	NO,
	WE,
	SO,
	F,
	C
};

/* literal flags
 *
 * tentatively valid as a numerical decimal: TVALID_NUM
 * tentatively valid as a map portion      : TVALID_MAP
 */

# define TVALID_NUM 01
# define TVALID_MAP 02

// lexical tokens
struct s_token
{
	enum e_category	name;
	char			*value;
	size_t			len;
	unsigned int	line;
	unsigned int	pos;
	union
	{
		enum e_id		id;
		unsigned int	lflags;
	};
};

#endif
