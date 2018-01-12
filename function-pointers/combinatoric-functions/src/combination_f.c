unsigned long combination_f(unsigned int n, unsigned int k)
{
	return (k !=0 && k != n) ? combination_f(n-1, k-1) + combination_f(n-1, k) : 1;
}
