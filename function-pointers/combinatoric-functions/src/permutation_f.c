unsigned long factorial(unsigned int n)
{
	return (n == 0) ? 1 : factorial(n-1) * n;
}

unsigned long permutation_f(unsigned int n, unsigned int k)
{
	return factorial(n)/factorial(n-k);
}
