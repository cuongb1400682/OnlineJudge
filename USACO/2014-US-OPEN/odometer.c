#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef long long int int64;

int64 begin(int64 a) {
	int64 retval = 1;
	while (a > 99) {
		retval = retval * 10 + 1;
		a /= 10;
	}
	return retval * 10;
}

int64 end(int64 a) {
	int64 retval = 9;
	while (a > 9) {
		retval = retval * 10 + 8;
		a /= 10;
	}
	return retval;
}

int64 next(int64 a) {
	int64 retval, i, ndigits;
	int digits[16];
	int count[10] = {0};
	int prev, ne;

	if (a == end(a))
		return begin(a * 10);

	ndigits = 0;
	for (i = a; i > 0; i /= 10) {
		digits[ndigits++] = i % 10;
		count[i % 10]++;
	}

	for (i = 0; i < ndigits && count[digits[i]] != 1; ++i)
		;

	prev = digits[i];
	ne = (i == 0) ? digits[1] : digits[i - 1];

	if ((prev == 0 && i < ndigits - 2) || (prev != 0 && i < ndigits - 1)) {
		retval = digits[i];
		digits[i] = digits[i+1];
		digits[i+1] = retval;
	} else {
		if (ne == 9) {
			++prev;
			ne = 0;
		}
		++ne;
		if (ne == prev)
			++ne;
		digits[0] = prev;
		for (i = 1; i < ndigits; ++i)
			digits[i] = ne;
	}

	retval = digits[ndigits - 1];
	for (i = ndigits - 2; i >= 0; --i)
		retval = retval * 10 + digits[i];

	return retval;
}

int count(int64 a, int64 b) {
	int64 retval = 0;
	int64 i, j, k, pow10;

	for (i = 110L; i <= 9999999999999999L; i = next(i))
		if (i >= a && i <= b)
			++retval;

	for (i = 2, pow10 = 100; i <= 16; ++i, pow10 *= 10)
		for (j = 1; j <= 9; ++j) {
			k = j * pow10;
			if (k >= a && k <= b)
				++retval;
		}

	return retval;
}

int main(void) {
	freopen("odometer.in", "r", stdin);
	freopen("odometer.out", "w", stdout);

	int64 X, Y;
	scanf("%Ld%Ld", &X, &Y);
	printf("%d", count(X, Y));
	return 0;
}
