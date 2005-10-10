
/*
 * an example
 */

class Fact inherits Object {
  fact(n: Int): Int {
    if n = 0 then 1
             else n * fact(n - 1)
  };

  test(): String { 10.toString() };
  main(): Int  { fact(1000) };
};

