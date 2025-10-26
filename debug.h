#include "rs232.h"

// Need to initialize in .cpp to SerialCommunication to be able to use debug

//#define DEBUG // à mettre en commentaire ou non au besoin

#ifdef DEBUG

# define DEBUG_PRINT(x) SerialCommunication::readFlash(x) // ou par RS-232

#else

# define DEBUG_PRINT(x) do {} while (0) // code mort

#endif