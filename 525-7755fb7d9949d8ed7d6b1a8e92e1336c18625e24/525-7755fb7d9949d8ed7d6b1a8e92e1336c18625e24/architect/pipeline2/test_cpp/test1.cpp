#include<iostream>
#include<fstream>
#include<cstdlib>
#include <cstring>
#include<string>
#include<vector>
#include "simulator.h"
using namespace std;
extern "C"
{
	#include"instruction.h"
}
int main(int argc, char const* argv[]){
	ifstream fp;
	fp.open(argv[1]);
	char a[50][128];
	int i = 0;
	while(fp.getline(a[i], 128)){
		i++;
	}
	ST if1,id1;
	if1.fetch_ins(a[0]);
	if1.show_st();
	if1.fetch_ins(a[6]);
	if1.show_st();
	return 0;
}


