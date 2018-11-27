#include "funcdependency.h"

SetAttrs candidate_keys(const Attrs& R, const AttrDependencies& F){
    // Returns a set of all the possible sets of candidate keys
    // A candidate key is a set X of attributes in R such that
    // X+ includes all the attributes in R and there is
    // no proper subset Y of X such that Y+ includes all the attributes in R

    SetAttrs res = {}, partsR = generateSubsets(R.begin(), R.end());
    for(auto &X : partsR){
        if(attr_closure(X, F) != R) continue; // We require X to be a superkey

        SetAttrs partsY = generateSubsets(X.begin(), X.end());
        bool isCandidate = true;
        for(auto &Y : partsY){
            if(Y.size() == X.size()) continue; // We require Y to be a proper subset

            if(attr_closure(Y, F) == R){
                isCandidate = false;
                break;
            }
        }

        if(isCandidate) res.insert(X);
    }

    return res;
}
