#include "funcdependency.h"

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

    /** Reflexive rules **/
    SetAttrs partsX = generateSubsets(X.begin(), X.end());
    for(auto &Y : partsX){
        SetAttrs partsY = generateSubsets(Y.begin(), Y.end());
        for(auto &Z : partsY)
            res[Y].insert(Z);
    }

    for(int sz = -1; sz != countDependencies(res); ){
        sz = countDependencies(res);

        /** Augmentative rules **/
        for(auto &f : res) for(auto &attrs : f.second){ // f.first -> attrs
            for(auto &Y : partsX){
                Attrs alpha = f.first, beta = attrs;
                res[alpha + Y].insert(beta + Y);
            }
        }

        /** Transivity rules **/
        for(auto &f1 : res) for(auto &attrs1 : f1.second) // f1.first -> attrs1
        for(auto &f2 : res) for(auto &attrs2 : f2.second) // f2.first -> attrs2
            if(attrs1 == f2.first)
                res[f1.first].insert(attrs2);
    }

    return res;
}
