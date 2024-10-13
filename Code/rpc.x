struct inputData {
	int X<>;
	int Y<>;
	double r;
};

struct avgArray {
	double arr[2];
};

struct productVector {
	double vec<>;
};

program MENU_PROG {
		version MENU_VER {
			int INNERPRODUCT(inputData) = 1;
			avgArray AVERAGES(inputData) = 2;
			productVector PRODUCT(inputData) = 3;		
		} = 1;
} = 0x23451111;


