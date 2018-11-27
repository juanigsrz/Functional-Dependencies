#include "funcdependency.h"

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
            auto B = dep.first;
            if( includes(res.begin(), res.end(), B.begin(), B.end()) ){
                // B is contained into res
                for(auto &C : dep.second)
                    res.insert(C.begin(), C.end());
            }
        }
    }

    return res;
}
