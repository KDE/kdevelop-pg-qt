%token A ("A"), B ("B"), C ("C") ;;
r1 A -> r2 ;;
r2 B -> r1 ;;
r3+ C -> r3 ;;
%< r4
%bin A 1 %left
%post B 2 %left
%> r5 ;;
r5+ -> r4 ;;
