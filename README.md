# Functional-Dependencies
C++ implementation of functional dependencies

How to use:
1. Compile: g++ -O3 *.cpp -o fd
2. Use: fd file [-countFD]

• -countFD is optional, prints the cardinality of F+
• Format of the input file:
    Each attribute will be represented as a character
    ○ R := S, where S is the set of all attributes
    ○ A := S, where S is the set from which we want to calculate A+
    ○ F := N
        S1 -> S2
        ...
        Si -> Sj

        where N and integer and each one of the following N lines represent each one a functional dependency

    Refer to the examples if needed