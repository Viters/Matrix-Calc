#include "intersectCollections.h"

string intersectCollections(const string &a, const string &b) {
    string res="";
    for(int i=0; i<a.length(); i++){
        if( b.rfind(a[i]) != string::npos && res.rfind(a[i]) == string::npos)
            res=res+a[i];
    }
    return res;
}
