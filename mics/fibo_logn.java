import java.util.*;
import java.io.PrintWriter;
import java.math.*;

class Main {
	BigInteger[] matrixMult(BigInteger[] a, BigInteger[] b) {
		BigInteger[] c = new BigInteger[4];
		c[0] = a[0].multiply(b[0]).add(a[1].multiply(b[2]));
		c[1] = a[0].multiply(b[1]).add(a[1].multiply(b[3]));
		c[2] = a[2].multiply(b[0]).add(a[3].multiply(b[2]));
		c[3] = a[2].multiply(b[1]).add(a[3].multiply(b[3]));
		return c;
	}
	
	BigInteger[] matrixPow(BigInteger[] a, int n) {
		if (n <= 1)
			return a;
		else {
			BigInteger[] c = matrixPow(a, n / 2);
			if (n % 2 == 0)
				return matrixMult(c, c);
			else
				return matrixMult(matrixMult(c, c), a);			 
		}
	}
	
	BigInteger fibo(int n) {
		return matrixPow(fBase, n)[1];
	}
	
	
	public void start() {
	}
	
	public static void main(String[] args) throws Exception {
		Main begin = new Main();
		begin.start();
	}
	
	BigInteger[] fBase = { 
			BigInteger.ONE, BigInteger.ONE, 
			BigInteger.ONE, BigInteger.ZERO 
	};
}

 
