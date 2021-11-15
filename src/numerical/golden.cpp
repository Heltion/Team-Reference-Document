constexpr LD Phi = (sqrt(5) - 1) / 2;
LD ternary_search(LD f(LD), LD L, LD R){
	LD mL = Phi * L + (1 - Phi) * R;
	LD mR = Phi * R + (1 - Phi) * L;
	LD fmL = f(mL), fmR = f(mR);
	for(int i = 0; i < step; i += 1)
		if(fmL > fmR){
			L = mL;
			mL = mR;
			fmL = fmR;
			fmR = f(mR = Phi * R + (1 - Phi) * L);
		}
		else{
			R = mR;
			mR = mL;
			fmR = fmL;
			fmL = f(mL = Phi * L + (1 - Phi) * R);	
		}
    return (mL + mR) / 2;
}