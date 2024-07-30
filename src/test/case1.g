%token A ("A"), B ("B"), C ("C") ;;
(r2 | 0) r3 -> rr;;
r1 (A r1)* -> r2 ;;
C -> r1 ;;
A -> r3 ;;
%< r1
%post B 1
%bin A 1 %left
%> r4 ;;
r4* (A | B | C) -> r5 ;;
