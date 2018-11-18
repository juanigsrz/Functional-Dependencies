#include <iostream>
#include <map>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp>
#include <set>
#include <algorithm>

struct Attr;
typedef std::set<Attr> Attrs; //Defined as a set so we don't repeat elements
typedef std::set<Attrs> SetAttrs; //Defined as a set so we don't repeat elements
struct Attr {
    char name;
    operator Attrs () const { return Attrs{*this}; } // An attribute is a set of itself
};

typedef std::map<Attrs, std::set<Attrs> > AttrDependencies; // Set of dependencies A -> B
typedef AttrDependencies::value_type AttrDependency;

inline bool operator == (const Attr& a, const Attr& b){ return a.name == b.name; }
inline bool operator < (const Attr& a, const Attr& b){ return a.name < b.name; }

inline bool operator == (const Attrs& a, const Attrs& b){
    if(a.size() != b.size()) return false;
    for(auto ita = a.begin(), itb = b.begin(); ita != a.end() and itb != b.end(); ita++, itb++)
        if(not (*ita == *itb)) return false;

    return true;
}
inline void operator += (Attrs& a, const Attr& b){ a.insert(b); } // set += elem modifies the set, adding elem
inline void operator -= (Attrs& a, const Attr& b){ a.erase(b); } // set -= elem modifies the set, removing elem

inline Attrs operator + (const Attrs& a, const Attrs& b){
    // set A + set B returns a new set A UNION B
    auto c = a;
    for(auto &e : b) c.insert(e);
    return c;
}

inline std::ostream& operator << (std::ostream& stream, const Attrs& attrs){
    // Prints a set
    for(const auto& a: attrs) std::cout << a.name;
    return stream;
}


inline bool isSubset(const Attrs& a, const Attrs& b){
    // Checks if every element of a is in b
    for(auto &attr : a)
        if( b.find(attr) == b.end() )
            return false;

    return true;
}

int countDependencies(const AttrDependencies& F){
    // Returns how many different dependencies are on F
    int sz = 0;
    for(auto &f : F) sz += f.second.size();
    return sz;
}




/****************************************************************************************/
/****************************************************************************************/
/****************************************************************************************/
/****************************************************************************************/
/****************************************************************************************/




Attrs attr_closure(const Attrs& a, const AttrDependencies& F){
    // Returns the attribute closure of the set a on F
    /*
        result = a
        while there are changes in result:
            for each b->c in F:
                if b is contained into result:
                    result := result UNION c
        return result
    */
    Attrs res = a;
    for(int sz = -1; sz != res.size(); ){
        sz = res.size();
        for(auto &dep : F){
            if( isSubset(dep.first, res) )
                for(auto &attrs : dep.second)
                    res = res + attrs;
        }
    }

    return res;
}



/****************************************************************************************/
/****************************************************************************************/
/****************************************************************************************/
/****************************************************************************************/
/****************************************************************************************/



Attrs currentSet = {}, subCurrentSet = {}, augmentSet = {};

void subprocessSubsets(Attrs::iterator it, Attrs::iterator last, AttrDependencies& R, const AttrDependencies& F){
    if(it == last) return;

    subCurrentSet += *it;
    subprocessSubsets(next(it,1), last, R, F);

    R[currentSet].insert(subCurrentSet);

    subCurrentSet -= *it;
    subprocessSubsets(next(it,1), last, R, F);
}

void processAttrsSubsets(Attrs::iterator it, Attrs::iterator last, AttrDependencies& R, const AttrDependencies& F){
    if(it == last) return;

    currentSet += *it;
    processAttrsSubsets(next(it,1), last, R, F); // The current element 'it' is in the set

    subprocessSubsets(currentSet.begin(), currentSet.end(), R, F);

    currentSet -= *it;
    processAttrsSubsets(next(it,1), last, R, F); // 'it' is NOT in the set
}

void applyAugmentRule(Attrs::iterator it, Attrs::iterator last, AttrDependencies& R, const Attrs& alfa, const Attrs& beta){
    if(it == last) return;

    augmentSet += *it;
    applyAugmentRule(next(it,1), last, R, alfa, beta);

    Attrs alfa_ext = alfa + augmentSet, beta_ext = beta + augmentSet;
    R[alfa_ext].insert(beta_ext);

    augmentSet -= *it;
    applyAugmentRule(next(it,1), last, R, alfa, beta);
}

AttrDependencies set_closure(const Attrs& X, const AttrDependencies& F){
    // Returns the closure of a set of Functional Dependencies (FD)
    // based on some initial set X
    /*
        result = F
        for each possible set X' of X:
            apply reflexive rules to X'
            add new FDs to result
        while there are changes in result:
            for each FD f in result:
                apply augmentative rules to f
                add new FDs to result
            for each FD f1 in result:
                for each FD f2 in result:
                    if f1 and f2 can be combined by transitivity rules:
                        add the new FD to result
        return result
    */
    AttrDependencies res = F;
    processAttrsSubsets(X.begin(), X.end(), res, F);

    for(int sz = -1; sz != countDependencies(res); ){
        sz = countDependencies(res);

        for(auto &f : res) for(auto &attrs : f.second) // f.first -> attrs
            applyAugmentRule(X.begin(), X.end(), res, f.first, attrs);

        for(auto &f1 : res) for(auto &attrs1 : f1.second) // f1.first -> attrs1
        for(auto &f2 : res) for(auto &attrs2 : f2.second) // f2.first -> attrs2
            if(attrs1 == f2.first)
                res[f1.first].insert(attrs2);
    }

    return res;
}



/****************************************************************************************/
/****************************************************************************************/
/****************************************************************************************/
/****************************************************************************************/
/****************************************************************************************/


std::map<Attrs, bool> spawnsR;
Attrs candidateSet = {}, candidateSubset = {};

bool processCandidateSubsets(Attrs::iterator it, Attrs::iterator last, const Attrs& R, const AttrDependencies& F){
    // Returns true if there is no proper subset that can "spawn" R
    // returns false otherwise
    if(it == last) return true;

    candidateSubset += *it;
    bool checkWith = processCandidateSubsets(next(it,1), last, R, F); // The current element 'it' is in the set

    if( candidateSubset.size() != candidateSet.size() ){ // A proper subset
        if( spawnsR.find(candidateSubset) == spawnsR.end() )
            spawnsR[candidateSubset] = attr_closure(candidateSubset, F) == R;

        if( spawnsR[candidateSubset] ){
            // Skip the next check since we already know we spawn R
            candidateSubset -= *it;
            return false;
        }
    }

    candidateSubset -= *it;
    bool checkWithout = processCandidateSubsets(next(it,1), last, R, F); // 'it' is NOT in the set

    return checkWith and checkWithout;
}

void processCandidateSets(Attrs::iterator it, Attrs::iterator last, const Attrs& R, SetAttrs& res, const AttrDependencies& F){
    if(it == last) return;

    candidateSet += *it;
    processCandidateSets(next(it,1), last, R, res, F); // The current element 'it' is in the set

    if( spawnsR.find(candidateSet) == spawnsR.end() )
        spawnsR[candidateSet] = attr_closure(candidateSet, F) == R;

    if( spawnsR[candidateSet] ){
        bool isCandidate = processCandidateSubsets(candidateSet.begin(), candidateSet.end(), R, F);

        if( isCandidate )
            res.insert(candidateSet);
    }

    candidateSet -= *it;
    processCandidateSets(next(it,1), last, R, res, F); // 'it' is NOT in the set

}

SetAttrs candidate_keys(const Attrs& R, const AttrDependencies& F){
    // Returns a set of all the possible sets of candidate keys
    // A candidate key is a set X of attributes in R such that
    // X+ includes all the attributes in R and there is
    // no proper subset Y of X such that Y+ includes all the attributes in R

    SetAttrs res = {};
    spawnsR.clear();
    processCandidateSets(R.begin(), R.end(), R, res, F);

    return res;
}

