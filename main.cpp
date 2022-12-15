#include <iostream>
#include <string>
#include "hash.h"
#include "bin.h"
#include "bin_hash.h"

using namespace std;

int main()
{
	int x;
	cin >> x;
	switch (x) {
		case 1:
			test_hash();
			break;
		case 2:
			test_bin();
			break;
		case 3:
			test_bin_hash();
			break;
	}
	return 0;
}