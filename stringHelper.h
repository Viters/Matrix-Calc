#ifndef STRINGHELPER_H
#define STRINGHELPER_H

#include <iostream>

using namespace std;

/// \brief function that returns union of characters' collections
///
/// \param a - string that represents a collection of characters
/// \param b - string that represents a collection of characters
/// \return string that represents a union of those collections
string combineCollections(const string &a, const string &b);


/// \brief function that returns intersection of characters' collections
///
/// \param a - string that represents the first collection of characters
/// \param b - string that represents the second collection of characters
/// \return string that represents a intersection of those collections
string intersectCollections(const string &a, const string &b);

#endif
