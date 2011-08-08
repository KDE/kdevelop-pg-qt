template<template<CharEncoding> class CharSet>
NFA<CharSet<Latin1> > getUtf8Tuples(typename Codec2Int<Latin1>::Result from0, typename Codec2Int<Latin1>::Result to0)
{
  return NFA<CharSet<Latin1> >(CharSet<Latin1>::range(from0, to0));
}
template<template<CharEncoding> class CharSet>
NFA<CharSet<Latin1> > getUtf8Tuples(typename Codec2Int<Latin1>::Result from0, typename Codec2Int<Latin1>::Result to0
, typename Codec2Int<Latin1>::Result from1, typename Codec2Int<Latin1>::Result to1)
{
    typedef typename Codec2Int<Latin1>::Result Int;
    if(from0 == to0)
    {
      auto tuples = NFA<CharSet<Latin1> >(CharSet<Latin1>(from0));
      tuples <<= getUtf8Tuples<CharSet>(from1, to1
      );
      return tuples;
    }
    else
    {
      NFA<CharSet<Latin1> > tuples;
      auto firstTuples = NFA<CharSet<Latin1> >(CharSet<Latin1>(from0));
      firstTuples <<= getUtf8Tuples<CharSet>(from1, Int(0x80 + (1<<6))
      );
      tuples |= firstTuples;
      auto midTuples = NFA<CharSet<Latin1> >(CharSet<Latin1>::range(from0 + 1, to0));
      midTuples <<= getUtf8Tuples<CharSet>(Int(0x80), Int(0x80 + (1<<6))
      );
      tuples |= midTuples;
      auto lastTuples = NFA<CharSet<Latin1> >(CharSet<Latin1>(to0));
      lastTuples <<= getUtf8Tuples<CharSet>(Int(0x80), to1
      );
      tuples |= lastTuples;
      return tuples;
    }
}
template<template<CharEncoding> class CharSet>
NFA<CharSet<Latin1> > getUtf8Tuples(typename Codec2Int<Latin1>::Result from0, typename Codec2Int<Latin1>::Result to0
, typename Codec2Int<Latin1>::Result from1, typename Codec2Int<Latin1>::Result to1, typename Codec2Int<Latin1>::Result from2, typename Codec2Int<Latin1>::Result to2)
{
    typedef typename Codec2Int<Latin1>::Result Int;
    if(from0 == to0)
    {
      auto tuples = NFA<CharSet<Latin1> >(CharSet<Latin1>(from0));
      tuples <<= getUtf8Tuples<CharSet>(from1, to1
, from2, to2      );
      return tuples;
    }
    else
    {
      NFA<CharSet<Latin1> > tuples;
      auto firstTuples = NFA<CharSet<Latin1> >(CharSet<Latin1>(from0));
      firstTuples <<= getUtf8Tuples<CharSet>(from1, Int(0x80 + (1<<6))
, from2, to2      );
      tuples |= firstTuples;
      auto midTuples = NFA<CharSet<Latin1> >(CharSet<Latin1>::range(from0 + 1, to0));
      midTuples <<= getUtf8Tuples<CharSet>(Int(0x80), Int(0x80 + (1<<6))
, from2, to2      );
      tuples |= midTuples;
      auto lastTuples = NFA<CharSet<Latin1> >(CharSet<Latin1>(to0));
      lastTuples <<= getUtf8Tuples<CharSet>(Int(0x80), to1
, from2, to2      );
      tuples |= lastTuples;
      return tuples;
    }
}
template<template<CharEncoding> class CharSet>
NFA<CharSet<Latin1> > getUtf8Tuples(typename Codec2Int<Latin1>::Result from0, typename Codec2Int<Latin1>::Result to0
, typename Codec2Int<Latin1>::Result from1, typename Codec2Int<Latin1>::Result to1, typename Codec2Int<Latin1>::Result from2, typename Codec2Int<Latin1>::Result to2, typename Codec2Int<Latin1>::Result from3, typename Codec2Int<Latin1>::Result to3)
{
    typedef typename Codec2Int<Latin1>::Result Int;
    if(from0 == to0)
    {
      auto tuples = NFA<CharSet<Latin1> >(CharSet<Latin1>(from0));
      tuples <<= getUtf8Tuples<CharSet>(from1, to1
, from2, to2, from3, to3      );
      return tuples;
    }
    else
    {
      NFA<CharSet<Latin1> > tuples;
      auto firstTuples = NFA<CharSet<Latin1> >(CharSet<Latin1>(from0));
      firstTuples <<= getUtf8Tuples<CharSet>(from1, Int(0x80 + (1<<6))
, from2, to2, from3, to3      );
      tuples |= firstTuples;
      auto midTuples = NFA<CharSet<Latin1> >(CharSet<Latin1>::range(from0 + 1, to0));
      midTuples <<= getUtf8Tuples<CharSet>(Int(0x80), Int(0x80 + (1<<6))
, from2, to2, from3, to3      );
      tuples |= midTuples;
      auto lastTuples = NFA<CharSet<Latin1> >(CharSet<Latin1>(to0));
      lastTuples <<= getUtf8Tuples<CharSet>(Int(0x80), to1
, from2, to2, from3, to3      );
      tuples |= lastTuples;
      return tuples;
    }
}
