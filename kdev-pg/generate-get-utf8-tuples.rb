#!/usr/bin/env ruby
puts <<-code
template<template<CharEncoding> class CharSet>
NFA<CharSet<Latin1> > getUtf8Tuples(typename Codec2Int<Latin1>::Result from0, typename Codec2Int<Latin1>::Result to0)
{
  return NFA<CharSet<Latin1> >(CharSet<Latin1>::range(from0, to0));
}
code

for numranges in 2..4
  puts <<-code
template<template<CharEncoding> class CharSet>
NFA<CharSet<Latin1> > getUtf8Tuples(typename Codec2Int<Latin1>::Result from0, typename Codec2Int<Latin1>::Result to0
code
  for i in 1..(numranges-1)
    print ", typename Codec2Int<Latin1>::Result from#{i}, typename Codec2Int<Latin1>::Result to#{i}"
  end
  puts <<-code
)
{
    typedef typename Codec2Int<Latin1>::Result Int;
    if(from0 == to0)
    {
      auto tuples = NFA<CharSet<Latin1> >(CharSet<Latin1>(from0));
      tuples <<= getUtf8Tuples<CharSet>(from1, to1
code
      for i in 2..(numranges-1)
        print ", from#{i}, to#{i}"
      end
      puts <<-code
      );
      return tuples;
    }
    else
    {
      NFA<CharSet<Latin1> > tuples;
      auto firstTuples = NFA<CharSet<Latin1> >(CharSet<Latin1>(from0));
      firstTuples <<= getUtf8Tuples<CharSet>(from1, Int(0x80 + (1<<6))
code
      for i in 2..(numranges-1)
        print ", from#{i}, to#{i}"
      end
      puts <<-code
      );
      tuples |= firstTuples;
      auto midTuples = NFA<CharSet<Latin1> >(CharSet<Latin1>::range(from0 + 1, to0));
      midTuples <<= getUtf8Tuples<CharSet>(Int(0x80), Int(0x80 + (1<<6))
code
      for i in 2..(numranges-1)
        print ", from#{i}, to#{i}"
      end
      puts <<-code
      );
      tuples |= midTuples;
      auto lastTuples = NFA<CharSet<Latin1> >(CharSet<Latin1>(to0));
      lastTuples <<= getUtf8Tuples<CharSet>(Int(0x80), to1
code
      for i in 2..(numranges-1)
        print ", from#{i}, to#{i}"
      end
      puts <<-code
      );
      tuples |= lastTuples;
      return tuples;
    }
}
code
end