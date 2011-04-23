class  KDevPG::TokenStream : public KDevPG::TokenStream, public QUtf8ToUcs4Iterator {typedef QUtf8ToUcs4Iterator Iterator; public: inline KDevPG::Token& next() { 
#define CURR_POS Iterator::plain()
#define NEXT_CHR __extension__( { if(!Iterator::hasNext()) goto _end; Iterator::next(); } )
const Iterator::InputInt *lpos = Iterator::plain();
Iterator::Int chr = 0;
int lstate = 0;

_state_0: chr = NEXT_CHR; if(chr < 98) {if(chr < 32) {if(chr == 9 || chr == 10){/*1 action */lpos = CURR_POS; lstate = 1; goto _state_37;
} else goto _end;
} else {if(chr < 48) {if(chr == 32){/*1 action */lpos = CURR_POS; lstate = 1; goto _state_37;
} else goto _end;
} else {if(chr < 58){/*2 action */lpos = CURR_POS; lstate = 2; goto _state_36;
} else goto _end;
}}} else {if(chr < 102) {if(chr == 98){goto _state_31;} else goto _end;
} else {if(chr < 228) {if(chr == 102){goto _state_34;} else goto _end;
} else {if(chr == 228){goto _state_23;} else goto _end;
}}}
_state_1: chr = NEXT_CHR; if(chr == 115){/*9 action */lpos = CURR_POS; lstate = 9; goto _state_38;
} else goto _end;

_state_2: chr = NEXT_CHR; if(chr == 167){goto _state_1;} else goto _end;

_state_3: chr = NEXT_CHR; if(chr == 32){goto _state_2;} else goto _end;

_state_4: chr = NEXT_CHR; if(chr == 101){goto _state_3;} else goto _end;

_state_5: chr = NEXT_CHR; if(chr == 107){goto _state_4;} else goto _end;

_state_6: chr = NEXT_CHR; if(chr == 105){goto _state_5;} else goto _end;

_state_7: chr = NEXT_CHR; if(chr == 108){goto _state_6;} else goto _end;

_state_8: chr = NEXT_CHR; if(chr == 32){goto _state_7;} else goto _end;

_state_9: chr = NEXT_CHR; if(chr == 116){goto _state_8;} else goto _end;

_state_10: chr = NEXT_CHR; if(chr == 111){goto _state_9;} else goto _end;

_state_11: chr = NEXT_CHR; if(chr == 110){goto _state_10;} else goto _end;

_state_12: chr = NEXT_CHR; if(chr == 32){goto _state_11;} else goto _end;

_state_13: chr = NEXT_CHR; if(chr == 111){goto _state_12;} else goto _end;

_state_14: chr = NEXT_CHR; if(chr == 100){goto _state_13;} else goto _end;

_state_15: chr = NEXT_CHR; if(chr == 32){goto _state_14;} else goto _end;

_state_16: chr = NEXT_CHR; if(chr == 73){goto _state_15;} else goto _end;

_state_17: chr = NEXT_CHR; if(chr == 32){goto _state_16;} else goto _end;

_state_18: chr = NEXT_CHR; if(chr == 44){goto _state_17;} else goto _end;

_state_19: chr = NEXT_CHR; if(chr == 104){goto _state_18;} else goto _end;

_state_20: chr = NEXT_CHR; if(chr == 104){goto _state_19;} else goto _end;

_state_21: chr = NEXT_CHR; goto _end;
_state_22: chr = NEXT_CHR; if(chr == 252){/*8 action */lpos = CURR_POS; lstate = 8; goto _state_21;
} else goto _end;

_state_23: chr = NEXT_CHR; if(chr == 246){goto _state_22;} else goto _end;

_state_24: chr = NEXT_CHR; goto _end;
_state_25: chr = NEXT_CHR; goto _end;
_state_26: chr = NEXT_CHR; if(chr == 114){/*6 action */lpos = CURR_POS; lstate = 6; goto _state_25;
} else goto _end;

_state_27: chr = NEXT_CHR; if(chr == 97){goto _state_26;} else goto _end;

_state_28: chr = NEXT_CHR; goto _end;
_state_29: chr = NEXT_CHR; goto _end;
_state_30: chr = NEXT_CHR; if(chr < 122) {if(chr == 114){/*4 action */lpos = CURR_POS; lstate = 4; goto _state_29;
} else goto _end;
} else {if(chr == 122){/*5 action */lpos = CURR_POS; lstate = 5; goto _state_28;
} else goto _end;
}
_state_31: chr = NEXT_CHR; if(chr < 228) {if(chr == 97){goto _state_30;} else goto _end;
} else {if(chr == 228){goto _state_20;} else goto _end;
}
_state_32: chr = NEXT_CHR; if(chr == 98){goto _state_27;} else goto _end;

_state_33: chr = NEXT_CHR; if(chr < 114) {if(chr == 111){/*3 action */lpos = CURR_POS; lstate = 3; goto _state_32;
} else goto _end;
} else {if(chr == 114){/*7 action */lpos = CURR_POS; lstate = 7; goto _state_24;
} else goto _end;
}
_state_34: chr = NEXT_CHR; if(chr == 111){goto _state_33;} else goto _end;

_state_35: chr = NEXT_CHR; if(chr >= 48 && chr < 58){/*2 action */lpos = CURR_POS; lstate = 2; goto _state_35;
} else goto _end;

_state_36: chr = NEXT_CHR; if(chr < 48) {if(chr == 46){/*2 action */lpos = CURR_POS; lstate = 2; goto _state_35;
} else goto _end;
} else {if(chr < 58){/*2 action */lpos = CURR_POS; lstate = 2; goto _state_36;
} else goto _end;
}
_state_37: chr = NEXT_CHR; if(chr < 32) {if(chr == 9 || chr == 10){/*1 action */lpos = CURR_POS; lstate = 1; goto _state_37;
} else goto _end;
} else {if(chr == 32){/*1 action */lpos = CURR_POS; lstate = 1; goto _state_37;
} else goto _end;
}
_state_38: chr = NEXT_CHR; goto _end;_end:
plain() = lpos;
switch(lstate) {
case 0: _fail: 
case 1: 
case 2: 
case 3: 
case 4: 
case 5: 
case 6: 
case 7: 
case 8: 
case 9: 
}
}
};
