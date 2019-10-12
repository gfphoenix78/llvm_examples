#include <stdio.h>
#include <stdint.h>

extern int64_t foobarbaz;
int gcd(int,int);

int main()
{
	printf ("foobar = %ld, gcd(3,4)=%d\n", foobarbaz, gcd(3,4));

	return 0;
}
