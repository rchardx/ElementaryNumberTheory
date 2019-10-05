import java.util.*;
import java.util.regex.*;
import java.text.*;
import java.math.*;
 
 
public class StairsColoring
{
  static long mod = 1000000123L;
  static long modp = 1000000122L;
  
  static long modPow(long x, long pow) {
    long r = 1;
    while (pow > 0) {
      if (pow % 2 == 1) {
        r = (r * x) % mod;
      }
      x = (x * x) % mod;
      pow /= 2;
    }
    return r;
  }
  
  static long[] factors = new long[] {2, 3, 11, 2089, 7253};
  
  static class Number {
    long[] mod;
    int[] pow;
    
    Number() {
      mod = new long[factors.length];
      pow = new int[factors.length];
    }
    
    Number mul(Number b) {
      Number r = new Number();
      for (int i = 0; i < factors.length; ++i) {
        r.mod[i] = (mod[i] * b.mod[i]) % factors[i];
        r.pow[i] = pow[i] + b.pow[i];
      }
      return r;
    }
    
    static long modInverse(long x, long p) {
      return BigInteger.valueOf(x).modInverse(BigInteger.valueOf(p)).longValue();
    }
    
    Number div(Number b) {
      Number r = new Number();
      for (int i = 0; i < factors.length; ++i) {
        r.mod[i] = (mod[i] * modInverse(b.mod[i], factors[i])) % factors[i];
        r.pow[i] = pow[i] - b.pow[i];
      }
      return r;
    }
    
    static Number valueOf(long x) {
      Number r = new Number();
      for (int i = 0; i < factors.length; ++i) {
        long xx = x;
        while (xx % factors[i] == 0) {
          r.pow[i]++;
          xx /= factors[i];
        }
        r.mod[i] = xx % factors[i];
      }
      return r;
    }
    
    long longValue() {
      long mul = 1;
      long x = 0;
      for (int i = 0; i < factors.length; ++i) {
        if (pow[i] < 0) {
          throw new AssertionError();
        }
        long m = pow[i] == 0 ? mod[i] : 0;
        long p = factors[i];
        long newMul = mul * p;
        long newx = (x * p * modInverse(p, mul) + m * mul * modInverse(mul, p)) % newMul;
        mul = newMul;
        x = newx;
      }
      if (mul != modp) {
        throw new AssertionError();
      }
      return x;
    }
  }
  
  static Number fact(long x) {
    Number r = new Number();
    for (int i = 0; i < factors.length; ++i) {
      r.mod[i] = 1;
      setFact(r, i, x);
    }
    return r;
  }
  
  static void setFact(Number r, int i, long x) {
    if (x == 0) {
      return;
    }
    long p = factors[i];
    long a = x / p;
    long b = x % p;
    if (a % 2 == 1) {
      r.mod[i] = (p - r.mod[i]) % p;
    }
    for (int t = 1; t <= b; ++t) {
      r.mod[i] = (r.mod[i] * t) % p;
    }
    r.pow[i] += a;
    setFact(r, i, a);
  }
  
  public int coloringCount(int N, int K)
  {
    long mod = fact(2 * N).div(fact(N)).div(fact(N)).div(Number.valueOf(N + 1)).longValue();
    System.out.println(mod);
    return (int)modPow(K, mod);
  }
  
 
}