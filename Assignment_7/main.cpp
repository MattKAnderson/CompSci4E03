#include <iostream>
#include <cmath>
double erlangC_log_space(int N, double lambda, double mew);
double ln_factorial(int n);
int main() {
	int lambda = 400;
	int mew = 1;
	int N = lambda;
	double desired_p = 0.2;
	double inv_actual_p = 0.0;
	double actual_p = 1.0;
	
	//using Erlang-C formula transformed into log-space
	while (actual_p >= desired_p) {
		N++;
		actual_p = erlangC_log_space(N, lambda, mew);
		std::cout << "N is: \t" << N << std::endl;
		std::cout << "P{queueing} = " << actual_p << std::endl << std::endl;
	}
}
double erlangC_log_space(int N, double lambda, double mew) {
	double pi0 = 1.0;
	double lnPQ;
	double utiltimesN = lambda / mew;
	double util = lambda / (mew * static_cast<double>(N));
	
	//compute pi0 and add -ln(pi0) to PQ
	for (int i = 1; i < N; i++) {
		pi0 += std::exp(i * std::log(utiltimesN) - ln_factorial(i));
	}
	pi0 += std::exp(N * std::log(utiltimesN) - ln_factorial(N) - std::log(1 - util));
	lnPQ = -std::log(pi0);

	//compute remaining terms and return PQ = exp(lnPQ)
	lnPQ -= ln_factorial(N);
	lnPQ += N * std::log(utiltimesN);
	lnPQ -= std::log(1.0 - util);
	return std::exp(lnPQ);
}
double ln_factorial(int n) {
	if (n == 0) {
		return 0.0;
	}
	double lnFact = 0.0;
	for (int i = 2; i <= n; i++) {
		lnFact += std::log(i);
	}
	return lnFact;
}