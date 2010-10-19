#include "kdev-pg-char-sets.h"

int next(QUtf8ToUcs4Iterator& i)
{
#define CURR_POS i
#define NEXT_CHR __extension__({ if(!i.hasNext()) goto fail; i.next(); })
int lstate = -1;
quint32 chr;
QUtf8ToUcs4Iterator lpos = i;
_state_0: chr = NEXT_CHR; if(chr < 98) {if(chr < 32) {if(chr == 9 || chr == 10){/*1 action */lpos = CURR_POS; lstate = 1; goto _state_37;
} else goto fail;
} else {if(chr < 48) {if(chr == 32){/*1 action */lpos = CURR_POS; lstate = 1; goto _state_37;
} else goto fail;
} else {if(chr < 58){/*2 action */lpos = CURR_POS; lstate = 2; goto _state_36;
} else goto fail;
}}} else {if(chr < 102) {if(chr == 98){goto _state_31;} else goto fail;
} else {if(chr < 228) {if(chr == 102){goto _state_34;} else goto fail;
} else {if(chr == 228){goto _state_23;} else goto fail;
}}}_state_1: chr = NEXT_CHR; if(chr == 115){/*9 action */lpos = CURR_POS; lstate = 9; goto _state_38;
} else goto fail;
_state_2: chr = NEXT_CHR; if(chr == 167){goto _state_1;} else goto fail;
_state_3: chr = NEXT_CHR; if(chr == 32){goto _state_2;} else goto fail;
_state_4: chr = NEXT_CHR; if(chr == 101){goto _state_3;} else goto fail;
_state_5: chr = NEXT_CHR; if(chr == 107){goto _state_4;} else goto fail;
_state_6: chr = NEXT_CHR; if(chr == 105){goto _state_5;} else goto fail;
_state_7: chr = NEXT_CHR; if(chr == 108){goto _state_6;} else goto fail;
_state_8: chr = NEXT_CHR; if(chr == 32){goto _state_7;} else goto fail;
_state_9: chr = NEXT_CHR; if(chr == 116){goto _state_8;} else goto fail;
_state_10: chr = NEXT_CHR; if(chr == 111){goto _state_9;} else goto fail;
_state_11: chr = NEXT_CHR; if(chr == 110){goto _state_10;} else goto fail;
_state_12: chr = NEXT_CHR; if(chr == 32){goto _state_11;} else goto fail;
_state_13: chr = NEXT_CHR; if(chr == 111){goto _state_12;} else goto fail;
_state_14: chr = NEXT_CHR; if(chr == 100){goto _state_13;} else goto fail;
_state_15: chr = NEXT_CHR; if(chr == 32){goto _state_14;} else goto fail;
_state_16: chr = NEXT_CHR; if(chr == 73){goto _state_15;} else goto fail;
_state_17: chr = NEXT_CHR; if(chr == 32){goto _state_16;} else goto fail;
_state_18: chr = NEXT_CHR; if(chr == 44){goto _state_17;} else goto fail;
_state_19: chr = NEXT_CHR; if(chr == 104){goto _state_18;} else goto fail;
_state_20: chr = NEXT_CHR; if(chr == 104){goto _state_19;} else goto fail;
_state_21: chr = NEXT_CHR; goto fail;_state_22: chr = NEXT_CHR; if(chr == 252){/*8 action */lpos = CURR_POS; lstate = 8; goto _state_21;
} else goto fail;
_state_23: chr = NEXT_CHR; if(chr == 246){goto _state_22;} else goto fail;
_state_24: chr = NEXT_CHR; goto fail;_state_25: chr = NEXT_CHR; goto fail;_state_26: chr = NEXT_CHR; if(chr == 114){/*6 action */lpos = CURR_POS; lstate = 6; goto _state_25;
} else goto fail;
_state_27: chr = NEXT_CHR; if(chr == 97){goto _state_26;} else goto fail;
_state_28: chr = NEXT_CHR; goto fail;_state_29: chr = NEXT_CHR; goto fail;_state_30: chr = NEXT_CHR; if(chr < 122) {if(chr == 114){/*4 action */lpos = CURR_POS; lstate = 4; goto _state_29;
} else goto fail;
} else {if(chr == 122){/*5 action */lpos = CURR_POS; lstate = 5; goto _state_28;
} else goto fail;
}_state_31: chr = NEXT_CHR; if(chr < 228) {if(chr == 97){goto _state_30;} else goto fail;
} else {if(chr == 228){goto _state_20;} else goto fail;
}_state_32: chr = NEXT_CHR; if(chr == 98){goto _state_27;} else goto fail;
_state_33: chr = NEXT_CHR; if(chr < 114) {if(chr == 111){/*3 action */lpos = CURR_POS; lstate = 3; goto _state_32;
} else goto fail;
} else {if(chr == 114){/*7 action */lpos = CURR_POS; lstate = 7; goto _state_24;
} else goto fail;
}_state_34: chr = NEXT_CHR; if(chr == 111){goto _state_33;} else goto fail;
_state_35: chr = NEXT_CHR; if(chr >= 48 && chr < 58){/*2 action */lpos = CURR_POS; lstate = 2; goto _state_35;
} else goto fail;
_state_36: chr = NEXT_CHR; if(chr < 48) {if(chr == 46){/*2 action */lpos = CURR_POS; lstate = 2; goto _state_35;
} else goto fail;
} else {if(chr < 58){/*2 action */lpos = CURR_POS; lstate = 2; goto _state_36;
} else goto fail;
}_state_37: chr = NEXT_CHR; if(chr < 32) {if(chr == 9 || chr == 10){/*1 action */lpos = CURR_POS; lstate = 1; goto _state_37;
} else goto fail;
} else {if(chr == 32){/*1 action */lpos = CURR_POS; lstate = 1; goto _state_37;
} else goto fail;
}_state_38: chr = NEXT_CHR; goto fail;
fail:
i = lpos;
return lstate;
}

int main()
{
    string str;
    getline(cin, str);
    QByteArray qba(str.c_str(), str.size());
    QUtf8ToUcs4Iterator iter(qba);
    QUtf8ToUcs4Iterator begin = iter;
    const char* names[] = {"ERROR", "whitespace", "dec-number", "foo", "bar", "baz", "foobar", "for", "umlauts", "anti-law"};
    int last;
    while(iter.hasNext())
    {
      QUtf8ToUcs4Iterator llast = iter;
      last = next(iter);
      if(last == -1)
      {
        cout << "ERROR" << endl;
        break;
      }
      cout << names[last] << ": " << str.substr(llast - begin, iter - llast) << endl;
    }
}
