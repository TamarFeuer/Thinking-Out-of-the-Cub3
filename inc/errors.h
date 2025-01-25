#ifndef ERRORS_H
# define ERRORS_H

//PARSING
# define ERR_WRG_EXT "The file does not have .cub extension."
# define ERR_IS_DIR "The file is a directory."
# define ERR_OPEN "There was an error opening the file."
# define ERR_TXT_REP "There's a texture that's repeated in the file."
# define ERR_INV_TXT "There's an invalid texture element in the map."
# define ERR_TXT_PATH "There's a texture that doesn't have a filepath."
# define ERR_IDE_OVL "There's more information than it's neccessary for one of the identifiers."
# define ERR_NULL_MAP "There was no parsed map to work with!"


//SYSTEM CALL FAILURES
# define ERR_MEM_ALL "There was an error allocating memory."

#endif