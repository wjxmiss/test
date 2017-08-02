
// Modified European Topology Information: ratio 1/5

#ifndef NSFtopo_H
#define NSFtopo_H



const int TotalNodeNo = 14;
int TotalLinkNo = 0;
int NodeDegree[TotalNodeNo];
int maxNodeDegree = 0;
//const int maxdomainPaths=1;
//const int maxdomainpaths=5;
//const int TotalLinkNo = 44;
//const int TotalSubDomainNo=4;
//const int TotalDomainNo = 4;
//const int MAX_NUMBER_PATHS = 800;
//const int TotalRegeneratorNo=5;
//const long NodeNoDomain[TotalDomainNo + 1]={0,5,7,9,7};//const int TotalTrytime=8; //14*14*8
//const int KPaths=1;

//const int MaxLengthofPath=14; // 24*24
double oo = 1000000;
double one=1.0;
//const int KHQ=1;
//const int lowest=1;
//const int highest=28;

double PhysicalDistance[ TotalNodeNo + 1 ][ TotalNodeNo + 1 ] = {

//                  "0"		"1"		"2"		"3"		"4"		"5"		"6"		"7"		"8"		"9"		"10"        "11"	    "12"	   "13"	   "14"
	/* "0"  */  {    0,		oo,		oo,		oo,		oo,		oo,		oo,		oo,		oo,		oo,		 oo,	     oo,	     oo,	    oo,	    oo},
	/* "1"  */	{	oo,      0,	   100,    100,     oo, 	oo,		oo,     oo,     100,	oo,	 	 oo,	     oo,	     oo,        oo,	    oo},
	/* "2"  */	{   oo,     100,	 0,	   100,     100,    oo,	    oo,	    oo,		 oo,	oo,	 	 oo,	     oo,	     oo,        oo,	    oo},
	/* "3"  */	{   oo,     100,    100, 	 0,	     oo,	oo,	    100,	oo,      oo,	oo,	 	 oo,	     oo,	     oo,        oo,	    oo},
	/* "4"  */	{	oo,     oo, 	100,	oo,	     0,		100,	oo,		oo,      oo, 	oo,      oo,        100,         oo,        oo,	    oo},
	/* "5"  */	{	oo,     oo, 	oo,	    oo,		100,	0,      100,	100, 	 oo,    oo,		 oo,         oo,         oo,        oo,	    oo},
	/* "6"  */	{	oo,     oo, 	oo,		100,	 oo,	100,     0,		oo,	     oo,    oo,     100,	     oo,         oo,        oo,	   100},
	/* "7"  */	{	oo,     oo, 	oo,	    oo,      oo,	100,    oo,	     0,		100,    oo,	     100,        oo,	     oo,	    oo,     oo},
	/* "8"  */	{	oo,     100,    oo,	    oo,		oo,	    oo,	    oo,	    100,      0,    100,      oo,	     oo,	     oo,        oo,	    oo},
	/* "9"  */	{	oo,     oo, 	oo,		oo,	    oo,		oo,		oo,	     oo,	100,	  0,     100,	     oo,	    100,	   100,     oo},
	/* "10" */	{	oo,     oo, 	oo,		oo,		oo,	    oo,		100,    100,	 oo,	100,	   0,	     oo,	     oo,        oo,	    oo},
	/* "11" */	{   oo, 	oo,     oo,	    oo,	    100,	oo,	    oo,	    oo,		oo,		oo,	     oo,	      0,        100,	   100,     oo},
	/* "12" */	{   oo, 	oo,     oo,		oo,     oo,		oo,  	oo,		oo,		oo,	    100,     oo,        100,	      0,	    oo,    100},
	/* "13" */	{   oo, 	oo,     oo,	    oo,	    oo,	    oo,		oo,		oo,		oo,	    100,     oo,	    100,	     oo,	     0,    100},
	/* "14" */	{   oo, 	oo,     oo,	    oo,		oo,	    oo,		100,	oo,		oo,		oo,		 oo,	     oo,        100,       100,      0}


};
	
#endif
