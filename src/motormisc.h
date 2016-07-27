#ifndef __MOTORMISC_H__
#define __MOTORMISC_H__

#include "motorcommon.h"
#include "motorproject.h"

#define BOOL_TO_STR(a)          (a ? _("yes") : _("no"))
//#define MAKEMODE_TO_STR(a)      (a == motorproject::automake ? _("automake") : _("manual"))

inline char* MAKEMODE_TO_STR(motorproject::makemodekind a) {

    if (a == motorproject::automake) {
	 return (char*)"automake";
    }
    if (a == motorproject::manual) {
	return (char*)"manual";
    }
    if (a == motorproject::cmake) {
	return (char*)"cmake";
    }
    return (char*)"automake";
}

string findprogram(const string &progname);
string getparsed(motorproject &pf, const string &placefrom);

#endif
