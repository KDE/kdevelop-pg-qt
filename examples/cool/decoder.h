#ifndef COOL_DECODER_H
#define COOL_DECODER_H

#include "coolparser.h"

#include <string>
#include <cstdlib>

namespace cool
{

class decoder
{
  KDevPG::TokenStream *_M_token_stream;
  Parser * p;
public:
  decoder(KDevPG::TokenStream *token_stream, Parser * parser)
    : _M_token_stream(token_stream), p(parser) {}

  int decode_op(std::size_t index) const
  {
    Parser::Token const &tk = _M_token_stream->at(index);
    return tk.kind;
  }

  QString decode_id(std::size_t index) const
  {
    Parser::Token const &tk = _M_token_stream->at(index);
    return p->tokenText(tk.begin,tk.end);
  }

  long decode_number(std::size_t index) const
  {
    Parser::Token const &tk = _M_token_stream->at(index);
    return p->tokenText(tk.begin,tk.end).toLong();    
  }
};

} // end of namespace cool

#endif // COOL_DECODER_H
