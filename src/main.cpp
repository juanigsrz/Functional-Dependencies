#include <iostream>
#include "funcdependency.cpp"

int main() {
    /** Set 1 **/
    /*
    Attr a{'A'}, b{'B'}, c{'C'}, d{'D'};
    AttrDependencies F;
    F[a].insert(b);
    F[b].insert(Attrs{a,d});
    F[Attrs{b,c}].insert(a);

    Attrs a_closure = {};
    AttrDependencies s_closure = set_closure(Attrs{a,b,c,d}, F); // = 137
    SetAttrs cand_keys = {};
    */

    /** Set 2 **/
    /*
    Attr a{'A'}, b{'B'}, c{'C'}, d{'D'}, e{'E'}, f{'F'};
    AttrDependencies F;
    F[Attrs{a,b}].insert(c);
    F[Attrs{b,d}].insert(Attrs{e,f});

    Attrs a_closure = {};
    AttrDependencies s_closure = set_closure(Attrs{a,b,c,d,e,f}, F); // = 1081
    SetAttrs cand_keys = {};
    */

    /** Set 3 **/
    /*
    Attr a{'A'}, b{'B'}, c{'C'}, d{'D'}, e{'E'}, f{'F'}, g{'G'}, h{'H'}, i{'I'}, j{'J'};
    AttrDependencies F;
    F[a].insert(i);
    F[Attrs{a,b}].insert(c);
    F[Attrs{a,d}].insert(Attrs{g,h});
    F[Attrs{b,d}].insert(Attrs{e,f});
    F[h].insert(j);

    Attrs a_closure = attr_closure(Attrs{b,d}, F); // = {B, D, E, F}
    AttrDependencies s_closure = {};
    SetAttrs cand_keys = candidate_keys(Attrs{a,b,c,d,e,f,g,h,i,j}, F); // = { A, B, D }
    */

    /** Set 4 **/
    /*
    Attr a{'A'}, b{'B'}, c{'C'}, d{'D'}, e{'E'}, f{'F'}, g{'G'}, h{'H'};
    AttrDependencies F;
    F[a].insert(Attrs{b,c});
    F[c].insert(d);
    F[d].insert(g);
    F[e].insert(a);
    F[e].insert(h);
    F[h].insert(e);

    Attrs a_closure = attr_closure(Attrs{a,c}, F); // = {A, B, C, D, G}
    AttrDependencies s_closure = {};
    SetAttrs cand_keys = candidate_keys(Attrs{a,b,c,d,e,f,g,h}, F); // = {E, F}{F, H}
    */

    /** Set 5 **/

    Attr a{'A'}, b{'B'}, c{'C'}, d{'D'}, e{'E'}, f{'F'}, g{'G'};
    AttrDependencies F;
    F[a].insert(f);
    F[a].insert(g);
    F[b].insert(e);
    F[c].insert(d);
    F[d].insert(b);
    F[e].insert(a);
    F[Attrs{f,g}].insert(c);

    Attrs a_closure = attr_closure(Attrs{f,g}, F); // = {A, B, C, D, E, F, G}
    AttrDependencies s_closure = {}; //set_closure(Attrs{a,b,c,d,e,f,g}, F);
    SetAttrs cand_keys = candidate_keys(Attrs{a,b,c,d,e,f,g}, F); // = {A}{B}...{E}{F, G}


    /** Set TEST1 **/
    /*
    Attr a{'A'}, b{'B'}, c{'C'}, d{'D'};
    AttrDependencies F;
    F[a].insert(b);
    F[b].insert(c);

    Attrs a_closure = {};
    AttrDependencies s_closure = set_closure(Attrs{a,b,c,d}, F);
    SetAttrs cand_keys = {};
    */


    std::cout << "A+ closure: ";
    for(auto &elem : a_closure) std::cout << elem << ' ';
    std::cout << std::endl;

    std::cout << "F+ size: " << countDependencies(s_closure) << std::endl;
    /*for(auto &f : s_closure){
        std::cout << f.first << " -> ";
        for(auto &e : f.second) std::cout << e << ' ';
        std::cout << '\n';
    }*/

    std::cout << "Candidate keys: \n";
    for(auto &attrs : cand_keys){
        for(auto &e : attrs)
            std::cout << e << ' ';
        std::cout << '\n';
    }

    std::cout << std::endl;

    return 0;
}
