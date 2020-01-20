/*
	Author: Matt Anderson
	Brief: A program to calculate the number of servers (N) required to satisfy 
		   the performance requirement, maximum probability of queueing, in a 
		   server-job system. Applies the erlang-C formula expanded in log-
		   space to compute N for values of lambda/mew <= 707. 
*/
#include <iostream>
#include <cmath>

double erlangC_log_space(int N, double lambda, double mew);
double ln_factorial(int n);

/*
	Given a lambda, mew, and desired maximum probability of queueing, 
	calculates the required number of servers using the Erlang-C formula.

	Iterates Erlang-C formula for incrementing values of N until probability
	condition is satisfied. 
*/
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

/*
	Calculates the value of the erlang-C formula for a given lambda, mew, and 
	number of servers (N).

	Performs the calculation in log-space to avoid temporaries that are too
	large to fit in a 64-bit number.

	Notes on temporaries:
	PQ - probability of queueing (sum of states where jobs > N)
	pi0 - initial state, jobs = 0;
*/
double erlangC_log_space(int N, double lambda, double mew) {
	double pi0 = 1.0;
	double lnPQ;
	double utilityXN = lambda / mew;
	double utility = utilityXN / static_cast<double>(N);
	
	//compute pi0 and add -ln(pi0) to PQ
	for (int i = 1; i < N; i++) {
		pi0 += std::exp(i * std::log(utilityXN) - ln_factorial(i));
	}
	pi0 += std::exp((N * std::log(utilityXN)) - ln_factorial(N) 
	                  - std::log(1 - utility) );
	lnPQ = -std::log(pi0);

	//compute remaining terms and return PQ = exp(lnPQ)
	lnPQ -= ln_factorial(N);
	lnPQ += N * std::log(utilityXN);
	lnPQ -= std::log(1.0 - utility);
	return std::exp(lnPQ);
}

/*
	Computes the logarithm of a factorial. (i.e.  ln(n!) )
*/
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
