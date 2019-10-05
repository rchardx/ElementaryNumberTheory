/*

Farey Sequence ¨C solution 
Mihai Patrascu, MIT 


Several less-than-optimal solutions exist. Using a priority queue, one can iterate through the fractions (generating them one by one) in O(KlgN) time. Using a fancier Math relation, this can be reduced to O(K). However, neither of these solution obtains more than 40 points, because the number of fractions (and thus K) is quadratic in N. 


The ¡°good¡± solution is based on meta-binary search. To construct this solution, we need the following subroutine: given a fraction A/B (which is not necessarily irreducible), find how many fractions from the Farey sequence are less than this fraction. Suppose we had this subroutine; then the algorithm works as follows: 

1. determine a number X such that the answer is between X/N and (X+1)/N; such a number can be determined by binary searching the range 1..N, thus calling the subroutine O(lgN) times. 

2. make a list of all fractions A/B in the range X/N..(X+1)/N. For any given B, there is at most one A in this range, and it can be determined trivially in O(1). 

3. determine the appropriate order statistic in this list (doing this in O(NlgN) by sorting is good enough). 


It remains to show how we can construct the desired subroutine. We will show how it can be implemented in O(NlgN), thus giving a O(Nlg2N) algorithm overall. Let us denote by C[j] the number of irreducible fractions i/j which are less than X/N. The algorithm is based on the following observation: C[j]=floor(X*B/N)¨CSum(C[D], where D divides j). A direct implementation, which tests whether any D is a divisor, yields a quadratic algorithm. A better approach, inspired by Eratosthene¡¯s sieve, is the following: at step j, we know C[j], and we subtract it from all multiples of j. The running time of the subroutine becomes O(NlgN). 


Two improvements (not needed for this contest) have been discovered by the author: the time can be reduced to O(NlgN) overall, or the space can be reduced to O(sqrt(N)). A direction for future research is reducing the space to O(poly(lgN)), while keeping the time O(Npoly(lgN)). 

TEST IDEAS
Test	N		M		Fracs		Comment
0	10004	49823		30423977	small M
1	16384	32714		81599337	small M
2	32768	270189200	326387383
3	39999	101329715	486329715
4	38946	331054666	461055001
5	10093	7742375		30969497	prime N; 1/4 of the way
6	35069	36800		373843415	prime N; small M
7	21187	68228094	136456189	answer: 1/2
8	29418	220062481	263062481
9	37777	49921		433803941	small M

*/

#include <stdio.h>
#include <stdlib.h>

#define PRINT_OUT(a, b) fprintf(fopen("farey.out", "w"), "%d %d\n", a, b)

struct frac {
	int p, q;
};

int cmp_frac(const void *p1, const void *p2)
{
	const struct frac *f1 = (const struct frac *) p1;
	const struct frac *f2 = (const struct frac *) p2;

	return(f1->p * f2->q - f1->q * f2->p);
}

int gcd(int a, int b)
{
	while(a && b) {
		a %= b;
		if(a)
			b %= a;
	}
	return(a + b);
}

/* --- a simple O(N*(lgN)^2) algorithm, using O(N) memory */

int count_below_3(int n, int p, int cnt[])
{
	int i, j, tot = 0;

	for(i = 2; i <= n; i++)
		cnt[i] = p * i / n;
	for(i = 2; i <= n; i++) {
		tot += cnt[i];
		for(j = i; (j += i) <= n; cnt[j] -= cnt[i]) ;
	}
	return(tot - 1);
}

void find_frac_3(int n, int lo, int k)
{
	int i;
	struct frac *a, *p, f;

	f.p = lo, f.q = n;
	
	p = a = (struct frac*)malloc(sizeof(*a) * n);
	for(i = 2; i <= n; i++) {
		p->p = ((lo + 1) * i - 1) / n;
		p->q = i;
		if((gcd(p->p, p->q) == 1) && (cmp_frac(p, &f) >= 0))
			p++;
	}

		/* of course, this could use a linear time algorithm
		 * to find the order statistic, but I didn't implement it
		 */
	qsort(a, p - a, sizeof(*a), cmp_frac);
	p = a + k;
	PRINT_OUT(p->p, p->q);
	free(a);
}

void farey3(int n, int k)
{
	int *cnt, lo, skip;

	cnt = (int*)malloc(sizeof(*cnt) * (n + 1));

		/* binary search */
	for(skip = 1; skip < n - 2; skip <<= 1) ;
	for(lo = 1; (skip >>= 1); )
		if(count_below_3(n, lo + skip, cnt) <= k)
			lo += skip;	
	k -= count_below_3(n, lo, cnt);
	free(cnt);

	find_frac_3(n, lo, k);
}

int main(int argc, char **argv)
{
	int k, n, max, alg;

	fscanf(fopen("farey.in", "r"), "%d%d", &n, &k);
	farey3(n, k-1);
	return(0);
}
