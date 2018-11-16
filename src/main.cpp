#include <iostream>
#include "funcdependency.cpp"

int main() {
    /** Set 1 **/
    /*
    Attr a{'A'}, b{'B'}, c{'C'}, d{'D'};
    AttrDependencies F;
    F.insert(a >> b);
    F.insert(b >> Attrs{a,d});
    F.insert(Attrs{b,c} >> a);

    Attrs a_closure = {};
    SetAttrs cand_keys = {};
    AttrDependencies s_closure = set_closure(Attrs{a,b,c,d}, F);
    */

    /** Set 2 **/
    /*
    Attr a{'A'}, b{'B'}, c{'C'}, d{'D'}, e{'E'}, f{'F'};
    AttrDependencies F;
    F.insert(Attrs{a,b} >> c);
    F.insert(Attrs{b,d} >> Attrs{e,f});

    Attrs a_closure = {};
    AttrDependencies s_closure = set_closure(Attrs{a,b,c,d,e,f}, F);
    SetAttrs cand_keys = {};
    */

    /** Set 3 **/
    /*
    Attr a{'A'}, b{'B'}, c{'C'}, d{'D'}, e{'E'}, f{'F'}, g{'G'}, h{'H'}, i{'I'}, j{'J'};
    AttrDependencies F;
    F.insert(a >> i);
    F.insert(Attrs{a,b} >> c);
    F.insert(Attrs{a,d} >> Attrs{g,h});
    F.insert(Attrs{b,d} >> Attrs{e,f});
    F.insert(h >> j);

    Attrs a_closure = attr_closure(Attrs{b,d}, F); // = {B, D, E, F}
    AttrDependencies s_closure = {};
    SetAttrs cand_keys = candidate_keys(Attrs{a,b,c,d,e,f,g,h,i,j}, F); // = { A, B, D }
    */

    /** Set 4 **/
    /*
    Attr a{'A'}, b{'B'}, c{'C'}, d{'D'}, e{'E'}, f{'F'}, g{'G'}, h{'H'};
    AttrDependencies F;
    F.insert(a >> Attrs{b,c});
    F.insert(c >> d);
    F.insert(d >> g);
    F.insert(e >> a);
    F.insert(e >> h);
    F.insert(h >> e);

    Attrs a_closure = attr_closure(Attrs{a,c}, F); // = {A, B, C, D, G}
    AttrDependencies s_closure = {};
    SetAttrs cand_keys = candidate_keys(Attrs{a,b,c,d,e,f,g,h}, F); // = {F, H} -- TODO: Check this
    */

    /** Set 5 **/
    /*
    Attr a{'A'}, b{'B'}, c{'C'}, d{'D'}, e{'E'}, f{'F'}, g{'G'};
    AttrDependencies F;
    F.insert(a >> f);
    F.insert(a >> g);
    F.insert(b >> e);
    F.insert(c >> d);
    F.insert(d >> b);
    F.insert(e >> a);
    F.insert(Attrs{f,g} >> c);

    Attrs a_closure = attr_closure(Attrs{f,g}, F); // = {A, B, C, D, E, F, G}
    AttrDependencies s_closure = {};
    SetAttrs cand_keys = candidate_keys(Attrs{a,b,c,d,e,f,g}, F); // = {A, G}{B, G}...{F, G} -- TODO: Check this
    */

    /** Set TEST1 **/
    /*
    Attr a{'A'}, b{'B'}, c{'C'}, d{'D'};
    AttrDependencies F;
    F.insert(a >> b);
    F.insert(b >> c);

    Attrs a_closure = {};
    AttrDependencies s_closure = set_closure(Attrs{a,b,c,d}, F);
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
