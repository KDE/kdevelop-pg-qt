%token A ("A"), B ("B"), C ("C") ;;
   C
-> r1 ;;
%< r1
%pre A 1
%bin B 1 %left
%> r2 ;;
   C | r1*
-> r3 ;;
   (A | B | C | r2)
-> r4 ;;

