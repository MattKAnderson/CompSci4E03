Code to calculate the Erlang C formula for big numbers 

The Erlang-C formula involves divisions of large exponents by large factorials that result in temporaries too large for a 64 bit number representation. By expanding the formula in log space (i.e. taking exp( ln( ... ) ) of troublesome terms) large temporaries in the calculation are compressed to numbers small enough to fit inside a 64-bit representation. 

When testing the limits of the code, the code can compute the Erlang-C formula for a (lambda / mew) of 707.  
