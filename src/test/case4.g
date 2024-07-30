%token A ("A"), B ("B"), C ("C") ;;
? A -> r1 ;;
%< r1
%bin B 1 %left
%post C 2 %left
%> r2 ;;

