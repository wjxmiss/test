//
//  SmallTopo.h
//  
//
//  Created by Jingxin Wu on 9/23/16.
//
//

#ifndef SmallTopo_h
#define SmallTopo_h

const int TotalNodeNo = 5;
int TotalLinkNo = 0;
int NodeDegree[TotalNodeNo];
int maxNodeDegree = 0;
double oo = 100000;
double one=1.0;

double PhysicalDistance[ TotalNodeNo + 1 ][ TotalNodeNo + 1 ] = {
    
    //              "0"		"1"		"2"		"3"		"4"     “5”
    /* "0"  */  {    0,		oo,		oo,		oo,		oo,     oo},
    /* "1"  */	{	oo,	     0,	   100,    100,     oo,     oo},
    /* "2"  */	{   oo,	   100,	     0,	    oo,    100,    100},
    /* "3"  */	{   oo,    100,	    oo, 	 0,	   100,    100},
    /* "4"  */	{	oo,     oo,    100,	   100,      0,     oo},
    /* "5"  */	{	oo,     oo,    100,    100,     oo,      0}
};

//double PhysicalDistance[ TotalNodeNo + 1 ][ TotalNodeNo + 1 ] = {
    
    //              "0"		"1"		"2"		"3"		"4"     “5”
//    /* "0"  */  {    0,		oo,		oo,		oo,		oo,     oo},
//    /* "1"  */	{	oo,	     0,	   100,    100,     100,      oo},
//    /* "2"  */	{   oo,	   100,	     0,	    oo,    100,      oo},
//    /* "3"  */	{   oo,    100,	    oo, 	 0,	    oo,     100},
//    /* "4"  */	{	oo,    100,    100,	    oo,	     0,      oo},
//    /* "5"  */	{	oo,     oo,     oo,	    100,	 oo,      0},
//};

//const int TotalNodeNo = 4;
//int NodeDegree[TotalNodeNo];
//int maxNodeDegree = 0;
//double oo = 1000000;
//double one=1.0;
//
//double PhysicalDistance[ TotalNodeNo + 1 ][ TotalNodeNo + 1 ] = {
//    
//    //              "0"		"1"		"2"		"3"		"4"
//    /* "0"  */  {    0,		oo,		oo,		oo,		oo},
//    /* "1"  */	{	oo,	    0,	   100,    100,    100},
//    /* "2"  */	{   oo,	   100,	     0,	    oo,  	oo},
//    /* "3"  */	{   oo,    100,	    oo, 	 0,	    oo},
//    /* "4"  */	{	oo,    100, 	oo,	    oo,	     0}
//};
#endif /* SmallTopo_h */
