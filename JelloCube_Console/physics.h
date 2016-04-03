/*

  Assignment 2 starter code

*/

#ifndef _PHYSICS_H_
#define _PHYSICS_H_
void computeAcceleration(struct world * jello, struct point a[8][8][8]);

// perform one step of Euler and Runge-Kutta-4th-order integrators
// updates the jello structure accordingly
void Euler(struct world * jello);
void RK4(struct world * jello);
//struct Force{
//	double Fx;
//	double Fy;
//	double Fz;
//	Force():Fx(0.0),Fy(0.0),Fz(0.0){}
//};
void HandleStructureNeighbor(struct world * jello,point f_total[8][8][8],int x,int y,int z);
void HandleNeighbor(struct world * jello,point f_total[8][8][8],int x,int y,int z);
void HandleBendNeighbor(struct world * jello,point f_total[8][8][8],int x,int y,int z);
#endif

