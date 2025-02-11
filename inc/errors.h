#ifndef ERRORS_H
# define ERRORS_H

typedef enum e_code
{
	ECODE_SUCCESS,
	ECODE_FAILURE,
	ECODE_CHECK_FILE_EXTENSION,
	ECODE_CHECK_FILE_FORMAT,
	ECODE_COPY_FILE_CONTENTS,
	ECODE_COPY_LINE_BY_LINE,
	ECODE_PARSE_IDENTIFIERS,
	ECODE_PARSE_MAP,
	ECODE_CHECK_MAP_VALIDITY,
	ECODE_INIT_MINIMAP_STRUCT,
	ECODE_MALLOC,
	ECODE_INV_LEN,
	ECODE_WRG_EXT,
	ECODE_IS_DIR,
	ECODE_OPEN,
	ECODE_TXT_REP,
	ECODE_INV_TXT,
	ECODE_TXT_PATH,
	ECODE_NULL_MAP,
	ECODE_REP_IDE,
	ECODE_INV_IDE,
	ECODE_NL_MAP
}	t_ecode;

//PARSING
# define ERR_MALLOC "There was an error allocating memory."
# define ERR_INV_LEN "The file has an invalid length."
# define ERR_WRG_EXT "The file does not have .cub extension."
# define ERR_IS_DIR "The file is a directory."
# define ERR_OPEN "There was an error opening the file."
# define ERR_TXT_REP "There's a texture that's repeated in the file."
# define ERR_INV_TXT "There's an invalid texture element in the map."
# define ERR_TXT_PATH "There's a texture that doesn't have a filepath."
# define ERR_IDE_OVL "There's more information than it's neccessary for one of the identifiers."
# define ERR_NULL_MAP "There was no parsed map to work with!"
# define ERR_REP_IDE "There's a repeated identifier in the file."
# define ERR_INV_IDE "There's an invalid identifier in the file."
# define ERR_NL_MAP "There's an empty line splitting the map."

//SYSTEM CALL FAILURES
# define ERR_MEM_ALL "There was an error allocating memory."

#endif