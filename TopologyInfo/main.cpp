//
//  main.cpp
//  TopologyInfo
//
//  Created by Jingxin Wu on 8/2/17.
//  Copyright © 2017 GWU. All rights reserved.
//

#include <vector>
#include <fstream>
#include <iostream>
//#include "SmallTopo.h"
#include "NSF.h"

using namespace std;

int K = 5; //K-shortest path
int R = 0; //total number of routes
int C = 0; //total number of route pairs


vector<vector<int>> LinkList(TotalLinkNo, vector<int>(2,0));

vector< vector< vector< vector<int> > > > KPath(TotalNodeNo, vector< vector< vector<int> > >  (TotalNodeNo, vector< vector<int> >(K, vector<int> (TotalNodeNo+1)))); //stores the K shortest paths for all source destination pair
//store links of K shortest paths
//vector<vector< vector< vector<int> > > > KPathLinks(TotalNodeNo+1, vector< vector< vector<int> > > (TotalNodeNo+1, vector< vector<int> >(K, vector<int>(TotalLinkNo+1, -1))));

// *** Function Declaration *** //
vector<int> Dijkstra(double networkcost[TotalNodeNo+1][TotalNodeNo+1], const int& src, const int& dst );
vector<vector<int> > KSP( const int& src, const int& dst, const int& K );
void FindKShortestPath(void);

vector<int> KN; //KN[r] is the number of candidate paths for route r
vector<vector<vector<int> > > A(R, vector<vector<int> >(K, vector<int>(TotalLinkNo, 0))); //A[r][k][e] = 1 if link e is on the kth candidate path of route r

// Data Out
void DataIntoFile(void);

int main(int argc, const char * argv[]) {

    //calculate K shortest paths
    for(int i=0; i<TotalNodeNo; i++){
        for(int j=0; j<TotalNodeNo; j++){
            for(int z=0; z<K; z++){
                KPath[i][j][z].clear();
            }
        }
    }
    FindKShortestPath();
    
    //calculate total link number
    for(int i=1; i<TotalNodeNo; i++){
        for(int j=i+1; j<=TotalNodeNo; j++){
            if(PhysicalDistance[i][j]==100){
                TotalLinkNo++;
                vector<int> lst(2,0);
                lst[0]=i;
                lst[1]=j;
                LinkList.push_back(lst);
            }
        }
    }
    
    //update KN
    int r = 0;
    for(int i=1; i<TotalNodeNo; i++){
        for(int j=i+1; j<=TotalNodeNo; j++){
            int sum = 1;
            int min_hop = KPath[i-1][j-1][0].size();
            for(int k = 1; k < K; k++){
                if(min_hop != KPath[i-1][j-1][k].size())    break;
                sum ++;
            }
            KN.push_back(sum);
            r++;
        }
    }
    
    R = r;
    
    C = R * (R - 1)/2;
    
    r = 0;
//    //record links along the shortest path for all node pairs
//    for(int i=1; i<=TotalNodeNo; i++){
//        for(int j=1; j<=TotalNodeNo; j++){
//            KPathLinks[i][j].resize(KN[r]);
//            for(int k = 0; k < KN[r]; k++){
//                KPathLinks[i][j][k].clear();
//                for(int n=0; n<KPath[i-1][j-1][k].size()-1; n++){
//                    int src = KPath[i-1][j-1][k][n];
//                    int des = KPath[i-1][j-1][k][n+1];
//                    for(int l=0; l<TotalLinkNo; l++){
//                        if((LinkList[l][0]==src && LinkList[l][1]==des) || (LinkList[l][1]==src && LinkList[l][0]==des)){
//                            KPathLinks[i][j][k].push_back(l);
//                            break;
//                        }
//                    }
//                }
//                
//            }//for k paths
//            r++;
//        }
//    }
    A.resize(R);
    
    for(int i=1; i<TotalNodeNo; i++){
        for(int j=i+1; j<=TotalNodeNo; j++){
            A[r].resize(KN[r]);
            
            for(int k = 0; k < KN[r]; k++){
                
                A[r][k].resize(TotalLinkNo);
                for(int e = 0; e < TotalLinkNo; e++)    A[r][k][e] = 0;
                
                for(int n=0; n<KPath[i-1][j-1][k].size()-1; n++){
                    int src = KPath[i-1][j-1][k][n];
                    int des = KPath[i-1][j-1][k][n+1];
                    for(int l=0; l<TotalLinkNo; l++){
                        if((LinkList[l][0]==src && LinkList[l][1]==des) || (LinkList[l][1]==src && LinkList[l][0]==des)){
                            A[r][k][l] = 1;
                            break;
                        }
                    }
                }
                
            }//for k paths
            r++;
        }
    }
    DataIntoFile();
    return 0;
}

vector<int> Dijkstra(double networkcost[TotalNodeNo+1][TotalNodeNo+1], const int& src, const int& dst )
{
    
    vector< vector<double> >  DijkstraLinkWeight(TotalNodeNo+1, vector<double> (TotalNodeNo + 1, oo));
    for(int ix=0; ix<=TotalNodeNo; ix++)
    {
        for(int iy=0; iy<=TotalNodeNo; iy++)
        {
            DijkstraLinkWeight[ix][iy] = networkcost[ix][iy];
        }
    }
    
    vector <int> SPath( TotalNodeNo, 0 );
    vector <bool> visited  ( ( TotalNodeNo+1 ), false);
    vector <double> Dist ( ( TotalNodeNo+1 ), oo );
    
    vector <int> Predecessor( (TotalNodeNo+1 ), 0 );
    //fill( Predecessor.begin(), Predecessor.end(), 0 );
    
    Dist[src] = 0;
    
    for(int i = 1; i<=TotalNodeNo; i++){
        vector <double> temp ( ( TotalNodeNo+1 ), 0 );
        temp.clear();
        temp.push_back(oo);
        for(int k=1; k<=TotalNodeNo; k++){
            if(visited[k]==false){
                temp.push_back(Dist[k]);
            }else{
                temp.push_back(oo);
            }
        }
        int t=oo;
        int u=0;
        for(int k=1; k<=TotalNodeNo; k++){
            if(temp[k]<t){
                t = temp[k]; u=k;
            }
        }
        visited[u]=true;//find the node with shortest distance to the source and mark it as visited
        for(int k=1; k<=TotalNodeNo; k++){
            if(Dist[u]+DijkstraLinkWeight[u][k]<Dist[k]){
                Dist[k] = Dist[u]+DijkstraLinkWeight[u][k];
                Predecessor[k]=u;
            }
        }
    }
    //vector <int> Path(TotalNodeNo);
    SPath.clear();
    vector <int> DPath( TotalNodeNo, 0 );
    DPath.clear();
    // SPath.push_back(3);
    
    if(Predecessor[dst]!=0){
        int t = dst;
        DPath.push_back(t);
        while(t!=src){
            int p = Predecessor[t];
            DPath.push_back(p);
            t = p;
        }
    }
    int ss=(int) DPath.size();
    for(int i=ss-1; i>=0; i--){
        SPath.push_back(DPath[i]);
    }
    return SPath;
}

vector<vector<int>> KSP( const int& src, const int& dst, const int& K )
{
    vector <vector <int> > SKShortestP(K, vector <int> (TotalNodeNo, 0 ) );
    for(int i=0; i<K; i++){
        SKShortestP[i].clear();
    }
    //SKShortestP.clear();
    int k=1;
    vector<int> ph (TotalNodeNo);   ph.clear();
    ph = Dijkstra(PhysicalDistance, src,dst);
    //P is a cell array that holds all the paths found so far
    vector <vector <int> > P( TotalNodeNo*K, vector <int> (TotalNodeNo, 0 ) );
    for(int i = 0; i< TotalNodeNo*K; i++){
        P[i].clear();
    }
    
    if(ph.size()==0){
        SKShortestP.clear();
    }else{
        int path_number = 1;
        P[path_number-1] = ph;
        int current_P = path_number;
        vector< vector<int> > Xx( TotalNodeNo*K, vector<int> (TotalNodeNo+2, 0));//X is a cell array of a subset of P
        Xx.clear();
        int size_X=1;
        vector<int> x(TotalNodeNo+2,0);x.clear();
        x.push_back(path_number);
        x.insert(x.end(),ph.begin(),ph.end());
        int costp = 0;
        for(int i=0; i<ph.size()-1; i++){
            costp = costp + PhysicalDistance[ph[i]][ph[i+1]];
        }
        x.push_back(costp);
        Xx.push_back(x);
        vector<int> S(TotalNodeNo*K,0);
        S[path_number-1] = ph[0];//deviation vertex is the first node initially
        SKShortestP[k-1]=ph;
        while((k<K)&&(size_X!=0)){
            //remove P from X
            for(int i=0; i<Xx.size(); i++){
                if(Xx[i][0]==(current_P)){
                    size_X = size_X-1;
                    //Xx[i].clear();
                    Xx.erase(Xx.begin()+i);
                    break;
                }
            }
            vector<int> P_ (TotalNodeNo); P_.clear();
            P_ = P[current_P-1];//P_ is current P
            
            int w = S[current_P-1];//Find w in (P_,w) in set S, w was the dev vertex used to found P_
            int w_index_in_path=0;
            for(int i=0; i<P_.size();i++){
                if(w==P_[i]){
                    w_index_in_path=i;
                    break;
                }
            }
            
            for(int index_dev_vertex = w_index_in_path; index_dev_vertex<(P_.size()-1); index_dev_vertex++){
                //index_dev_vertex is index in P_ of deviation vertex
                double TempPhysicalDistance[ TotalNodeNo + 1 ][ TotalNodeNo + 1 ];
                for(int i=0; i<=TotalNodeNo; i++){
                    for(int j=0; j<=TotalNodeNo; j++){
                        TempPhysicalDistance[i][j] = PhysicalDistance[i][j];
                    }
                }
                for(int i=0; i<index_dev_vertex; i++){
                    int v = P_[i];
                    for(int j=0; j<=TotalNodeNo; j++){
                        TempPhysicalDistance[v][j] = oo;
                        TempPhysicalDistance[j][v] = oo;
                    }
                }//remove vertices in P before index_dev_vertex and their incident edges
                vector <vector <int> > SP_sameSubPath( K, vector <int> (TotalNodeNo, 0 ) );
                SP_sameSubPath.clear();
                //int index = 1;
                SP_sameSubPath.push_back(P_);
                for(int i=0; i<SKShortestP.size(); i++){
                    if(SKShortestP[i].size()>=(index_dev_vertex+1)){
                        bool testsub = true;
                        for(int j= 0; j<=index_dev_vertex; j++){
                            if(P_[j]!=SKShortestP[i][j]){
                                testsub=false;
                                break;
                            }
                        }
                        if(testsub==true){
                            //index = index+1;
                            SP_sameSubPath.push_back(SKShortestP[i]);
                        }
                    }
                }//remove incident edge of v if v is in shortestPaths (K) U P_  with similar sub_path to P_
                int v_ = P_[index_dev_vertex];
                for(int j=0; j<SP_sameSubPath.size(); j++){
                    int next = SP_sameSubPath[j][index_dev_vertex+1];
                    TempPhysicalDistance[v_][next]=oo;
                }
                
                //call dijkstra between deviation vertex to destination node
                vector<int> dev_p (TotalNodeNo);   dev_p.clear();
                dev_p = Dijkstra(TempPhysicalDistance, v_,dst);
                bool testdevp = true;
                for(int i=0; i<SKShortestP.size(); i++){
                    if(dev_p.size()==SKShortestP[i].size()){
                        bool testp=false;
                        for(int j=0; j<dev_p.size(); j++){
                            if(dev_p[j]!=SKShortestP[i][j]){
                                testp=true;
                                break;
                            }
                        }
                        if(testp==false)    {testdevp = false;break;}
                    }
                }
                if(testdevp==false) continue;
                if(dev_p.size()!=0){
                    path_number++;
                    vector<int> pp(TotalNodeNo); pp.clear();
                    for(int i=0; i<index_dev_vertex; i++){
                        pp.push_back(P_[i]);
                    }
                    pp.insert(pp.end(), dev_p.begin(), dev_p.end());
                    P[path_number-1] = pp;
                    S[path_number-1] = P_[index_dev_vertex];
                    size_X++;
                    x.clear();
                    x.push_back(path_number);
                    x.insert(x.end(),pp.begin(),pp.end());
                    int costpp = 0;
                    //get the cost of the sub path before deviation vertex v
                    for(int i=0; i<index_dev_vertex; i++){
                        costpp = costpp + PhysicalDistance[P_[i]][P_[i+1]];
                    }
                    
                    for(int i=0; i<dev_p.size()-1; i++){
                        costpp = costpp + TempPhysicalDistance[dev_p[i]][dev_p[i+1]];
                    }
                    x.push_back(costpp);
                    Xx.push_back(x);
                }
            }//end for index_dev_vertex
            if(size_X>0){
                int shortestXCost = oo;
                int shortestX = 0;
                for(int i=0; i<Xx.size(); i++){
                    if((Xx[i][Xx[i].size()-1]<shortestXCost)&&(Xx[i][Xx[i].size()-1]>0)&&(Xx[i][Xx[i].size()-1]<oo)){
                        shortestXCost = Xx[i][Xx[i].size()-1];
                        shortestX = Xx[i][0];
                    }
                }
                current_P = shortestX;
                k++;
                SKShortestP[k-1]=P[(current_P-1)];
            }//end if
        }//end while
    }
    return SKShortestP;
}
void FindKShortestPath(void){
    //call K-Shortest Path
    vector <vector <int> > KShP( K, vector <int> (TotalNodeNo, 0 ) );
    KShP = KSP(1,2,K);
    for(int i=1; i<TotalNodeNo; i++){
        for (int j=i+1; j<=TotalNodeNo; j++){
            KPath[i-1][j-1] = KSP(i,j,K);
            vector <vector <int> > RKShortestP(K, vector <int> (TotalNodeNo, 0 ) );//reverse shortest path
            for(int z=0; z<KPath[i-1][j-1].size(); z++){
                KPath[j-1][i-1][z].clear();
                for(int t=(int) (KPath[i-1][j-1][z].size()-1); t>=0; t--){
                    KPath[j-1][i-1][z].push_back(KPath[i-1][j-1][z][t]);
                }
            }
        }
    }
}
void DataIntoFile(void)
{
    char BlockDataFileName[100];
    strcpy( BlockDataFileName, "NSFinfo" );
    //strcpy( BlockDataFileName, "SNetinfo" );
    strcat( BlockDataFileName, ".dat" );
    ofstream blockfile_handle( BlockDataFileName, ios::app );
    
    blockfile_handle.setf( ios::left );
    
    blockfile_handle << R <<endl;
    blockfile_handle << C <<endl;
    blockfile_handle << TotalLinkNo << endl;
    
    blockfile_handle << "[";
    for(int r = 0; r < R-1; r++){
        blockfile_handle << KN[r] << ",";
    }
    blockfile_handle << KN[R-1] << "]" << endl;
    
    for(int r = 0; r < R; r++){
        blockfile_handle << "[";
        for(int k = 0; k < KN[r] - 1; k++){
            blockfile_handle << "[";
            for(int e = 0; e < TotalLinkNo - 1; e++){
                blockfile_handle << A[r][k][e] << ",";
            }
            blockfile_handle << A[r][k][TotalLinkNo - 1] << "]," << endl;
        }
        blockfile_handle << "[";
        for(int e = 0; e < TotalLinkNo - 1; e++){
            blockfile_handle << A[r][KN[r] - 1][e] << ",";
        }
        blockfile_handle << A[r][KN[r] - 1][TotalLinkNo - 1] << "]]" << endl;
    }

    blockfile_handle.close();
}
