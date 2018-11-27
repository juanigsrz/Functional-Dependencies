#include <iostream>
#include <string>
#include <cstring>
#include "funcdependency.h"

int main(int argc, char* argv[]) {
    if(argc < 2){
        std::cout << "Use: fd file [-countFD]" << std::endl;
        return 0;
    }

    freopen(argv[1], "r", stdin);

    std::string inp, inpaux;
    char holder;
    int status = 0;

    Attrs R{}, A{};
    AttrDependencies F{};

    /** Read Input **/
    while( std::cin >> holder ){
        switch(holder){
            case 'R':
                if( status&1 ){
                    std::cout << "R is defined twice" << std::endl;
                    return 0;
                }
                std::cin >> holder >> holder >> inp;
                if(inp != "empty")
                    for(auto &c : inp) R.insert(Attr {c});

                status |= 1;
                break;

            case 'A':
                if( status&2 ){
                    std::cout << "A is defined twice" << std::endl;
                    return 0;
                }
                std::cin >> holder >> holder >> inp;
                if(inp != "empty")
                    for(auto &c : inp) A.insert(Attr {c});

                status |= 2;
                break;

            case 'F':
                if( status&4 ){
                    std::cout << "F is defined twice" << std::endl;
                    return 0;
                }
                std::cin >> holder >> holder >> inp;
                if(inp != "empty"){
                    int ndep = stoi(inp);
                    for(int i=0; i<ndep; i++){
                        std::cin >> inp >> holder >> holder >> inpaux;
                        Attrs left{}, right{};
                        for(auto &c : inp) left.insert(Attr {c});
                        for(auto &c : inpaux) right.insert(Attr {c});
                        F[left].insert(right);
                    }
                }

                status |= 4;
                break;
        }
    }


    /** Attribute closure **/
    Attrs a_closure = attr_closure(A, F);
    std::cout << "A+ closure: ";
    if(a_closure.empty()) std::cout << "empty" << std::endl;
    else {
        for(auto &elem : a_closure) std::cout << elem;
        std::cout << std::endl;
    }


    /** Set closure **/
    if((argc >= 3) and (strcmp(argv[2], "-countFD") == 0)){
        AttrDependencies s_closure = set_closure(R,F);
        std::cout << "F+ size: " << countDependencies(s_closure) << std::endl;
    }


    /** Candidate keys **/
    SetAttrs cand_keys = candidate_keys(R, F);
    std::cout << "Candidate keys: \n";
    for(auto &attrs : cand_keys){
        for(auto &c : attrs) std::cout << c;
        std::cout << '\n';
    }

    std::cout << std::endl;

    return 0;
}
