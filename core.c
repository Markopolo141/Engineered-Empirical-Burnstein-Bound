inline double hoeffding_1(double sox, double tox, int n, double replacement) {
	if (sox<0 || tox<0) {
		printf("ERR1\n");
		return NAN;
	}
	if (tox>=1)
		return replacement;
	double aa = sox+tox;
	double a = sox/aa;
	double bb = 1-tox;
	double b = 1/bb;
	double e = (n*1.0)/(sox+1);
	aa = aa*e;
	bb = bb*e;
	return pow(a,aa)*pow(b,bb);
}
inline double forx0q(double q, double xb, double xa, double x0) {
	if (x0<xa){
		printf("ERR2\n");
		return NAN;
	}
	return (xa-xb)*(2*q*x0*(x0-xa)*(x0-xb)+2*x0-xa-xb)*exp(-q*x0*x0)+(x0-xa)*(x0-xa)*exp(-q*xb*xb)-(x0-xb)*(x0-xb)*exp(-q*xa*xa);
}
inline double numeric_find_zeroq(double q, double xb, double xa) {
	if (xb<-xa) {
		printf("ERR3\n");
		return NAN;
	}
	double x0 = 0.0;
	for (int i = 1; i < 15; i++) {
		double pi = xa/pow(2,i);
		if ((x0+pi>xa) && (forx0q(q,xb,xa,x0+pi)>0))
			x0 += pi;
	}
	return x0;
}
inline double obj(double s,double y,double q,double xb,double xa,double x0) {
	return (((s+x0*xb)*(2*q*x0*xb-2*q*x0*x0-1)+xb*(xb-x0))*exp(-q*x0*x0)+(s+x0*x0)*exp(-q*xb*xb))*exp(q*(s-y))/((x0-xb)*(x0-xb));
}

double run_f(double s,double y,double D,double d,int n) {
	double ws = ((n-1)*y+s)*1.0/n;
	double min_inner_val2 = 1.0;
	for (double phi=0.0; phi<=1.0001; phi+=0.009999) {
		double min_inner_val = 1.0;
		for (double q=0.0; q<10; q+=0.01) {
			double nfzq = numeric_find_zeroq(q,D*(1-d),-d*D);
			for (double x0=0; x0>=nfzq; x0+=nfzq*0.0999-0.0000001) {
				double v = obj(s,(1-phi)*ws,q,D*(1-d),-d*D,x0);
				if (v<min_inner_val)
					min_inner_val = v;
			}
		}
		min_inner_val = pow(min_inner_val,n);
		min_inner_val += hoeffding_1(s/((D*(1-d))*(D*(1-d))),sqrt(phi*ws)/(D*(1-d)),n,0.0);
		min_inner_val += hoeffding_1(s/((d*D)*(d*D)),sqrt(phi*ws)/(d*D),n,0.0);
		if (min_inner_val<min_inner_val2)
			min_inner_val2 = min_inner_val;
	}
	return min_inner_val2;
}


