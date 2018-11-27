#include "funcdependency.h"

/** Essential operators **/
bool operator < (const Attr& a, const Attr& b){ return a.name < b.name; }
std::ostream& operator << (std::ostream& stream, const Attrs& attrs){
    // Prints a set
    for(const auto& a: attrs) std::cout << a.name;
    return stream;
}

/** Extra operators **/
bool operator == (const Attr& a, const Attr& b){ return a.name == b.name; }
bool operator == (const Attrs& a, const Attrs& b){
    if(a.size() != b.size()) return false;
    for(auto ita = a.begin(), itb = b.begin(); ita != a.end() and itb != b.end(); ita++, itb++)
        if(not (*ita == *itb)) return false;

    return true;
}
void operator += (Attrs& a, const Attr& b){ a.insert(b); }
void operator -= (Attrs& a, const Attr& b){ a.erase(b); }
Attrs operator + (const Attrs& a, const Attrs& b){
    // set A + set B returns a new set A UNION B
    auto c = a;
    for(auto &e : b) c.insert(e);
    return c;
}

/** Utilities **/
int countDependencies(const AttrDependencies& F){
    // Returns how many different dependencies are on F
    int sz = 0;
    for(auto &f : F) sz += f.second.size();
    return sz;
}

void auxGenerateSubsets(Attrs::iterator it, Attrs::iterator last, SetAttrs& res, Attrs& temp){
    if(it == last) return;
    temp.insert(*it);
    auxGenerateSubsets(next(it,1), last, res, temp);
    res.insert(temp);
    temp.erase(*it);
    auxGenerateSubsets(next(it,1), last, res, temp);
}

SetAttrs generateSubsets(Attrs::iterator it, Attrs::iterator last){
    SetAttrs res = {};
    Attrs temp = {};
    auxGenerateSubsets(it, last, res, temp);
    return res;
}
