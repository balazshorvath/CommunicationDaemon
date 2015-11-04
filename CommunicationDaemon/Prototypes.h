#ifndef PROTOTYPES_H
#define PROTOTYPES_H

/* ! The file requres nothing atm */
/* ! Be aware of include order */

int validateInput(int, char**);
void initializeProgram(int, char**);
void outputThread();
void inputThread();

/* converions between hex and actual values */
/* out size can be calculated easily... */
void toHex(char* in, char* outStr, int inSize);
/*
* input is a string, dont need sizes
* ret -1 if the hex string is invalid 0 everythings fine
*/
int fromHex(char* inStr, char* out);

#endif
