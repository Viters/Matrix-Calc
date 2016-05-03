#include "stringHelper.h"

string combineCollections(const string &a, const string &b){
    string tmp;
    tmp=a+b;
    int charPos;
    for(int i=0; i<tmp.length(); i++){
        charPos=tmp.rfind(tmp[i]);
        while(charPos!=i){
            tmp.erase(charPos, 1);
            charPos=tmp.rfind(tmp[i]);
        }
    }
    return tmp;
}

string intersectCollections(const string &a, const string &b) {
    string res="";
    for(int i=0; i<a.length(); i++){
        if( b.rfind(a[i]) != string::npos && res.rfind(a[i]) == string::npos)
            res=res+a[i];
    }
    return res;
}
