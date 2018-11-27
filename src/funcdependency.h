#ifndef __FUNCDEPENDENCY_H__
#define __FUNCDEPENDENCY_H__

/** Libraries **/
#include <iostream>
#include <map>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp>
#include <set>

/** Basic definitions/operators **/
struct Attr {
    char name;
    operator std::set<Attr> () const { return std::set<Attr>{*this}; } // An attribute is a set of itself
};
typedef std::set<Attr> Attrs;
typedef std::set<Attrs> SetAttrs;
typedef std::map<Attrs, std::set<Attrs> > AttrDependencies; // Set of dependencies A -> B
typedef AttrDependencies::value_type AttrDependency;

bool operator < (const Attr& a, const Attr& b);
std::ostream& operator << (std::ostream& stream, const Attrs& attrs);

/** Extra operators **/
bool operator == (const Attr& a, const Attr& b);
bool operator == (const Attrs& a, const Attrs& b);
void operator += (Attrs& a, const Attr& b); // set += elem modifies the set, adding elem
void operator -= (Attrs& a, const Attr& b); // set -= elem modifies the set, removing elem
Attrs operator + (const Attrs& a, const Attrs& b);

/** Utilities **/
int countDependencies(const AttrDependencies& F);
SetAttrs generateSubsets(Attrs::iterator it, Attrs::iterator last);

/** Functions **/
Attrs attr_closure(const Attrs& a, const AttrDependencies& F);
AttrDependencies set_closure(const Attrs& X, const AttrDependencies& F);
SetAttrs candidate_keys(const Attrs& R, const AttrDependencies& F);

#endif // __FUNCDEPENDENCY_H__
