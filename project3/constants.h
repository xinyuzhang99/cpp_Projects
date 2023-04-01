#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

const int ENCODE_MESSAGE_OPTION = 1;
const int DECODE_OPTION = 2;
const int WRITE_IMAGE_OPTION = 3;
const int EXIT_PROGRAM_OPTION = 4;
const int CORRECT_NUMBER_ARGUMENTS = 2;
const int WRONG_NUMBER_ARGUMENTS_ERROR = 2;
const int WRONG_PPM_FORMAT_ERROR = 3;
const string MAGIC_NUMBER = "P3";
const int MAXIMUM_SIZE = 2000;
const int MINIMUM_SIZE = 1;

// Constants needed for ColorClass and RowColumnClass
const int MAXIMUM_ALLOWED_COLOR = 255;
const int MINIMUM_ALLOWED_COLOR = 0;
const int COLOR_COMPONENT_NUMBER = 3;
const int RED_INDEX = 0;
const int GREEN_INDEX = 1;
const int BLUE_INDEX = 2;
const int DEFAULT_INDEX = -99999;
const int MINIMUM_BOUND = 0;

// Encoding value
const int ENCODING_BLACK = 0;
const int ENCODING_RED = 1;
const int ENCODING_GREEN = 2;
const int ENCODING_BLUE = 3;
const int ENCODING_WHITE = 4;
const int ENCODING_YELLOW = 5;
const int ENCODING_MAGENTA = 6;
const int ENCODING_CYAN = 7;

#endif
