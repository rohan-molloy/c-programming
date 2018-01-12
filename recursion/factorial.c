unsigned long factorial(unsigned int n)
{
	return (n == 0) ? 1 : factorial(n-1) * n;
}

