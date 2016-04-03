/*

  Assignment 2 starter code

*/

#include "jello.h"
#include "physics.h"
#include <iostream>
using namespace std;

point operator-(const point& p1,const point& p2)
{
	point result;
	result.x = p1.x - p2.x;
	result.y = p1.y - p2.y;
	result.z = p1.z - p2.z;
	return result;
}

point operator*(const point& p1,const point& p2)
{
	point result;
	result.x = p1.x * p2.x;
	result.y = p1.y * p2.y;
	result.z = p1.z * p2.z;
	return result;
}

point operator/(const point& p1,const point& p2)
{
	point result;
	result.x = p1.x / p2.x;
	result.y = p1.y / p2.y;
	result.z = p1.z / p2.z;
	return result;
}

point operator/(const point& p1,const double& p2)
{
	point result;
	result.x = p1.x / p2;
	result.y = p1.y / p2;
	result.z = p1.z / p2;
	return result;
}

point operator*(const double& p1,const point& p2)
{
	point result;
	result.x = p1*p2.x;
	result.y = p1*p2.y;
	result.z = p1*p2.z;
	return result;
}

void HandleStructureNeighbor(struct world* jello,point f_total[8][8][8],int x,int y,int z)
{
	if(x>0)
	{
		point L = jello->p[x][y][z] - jello->p[x-1][y][z];
		point v = jello->v[x][y][z] - jello->v[x-1][y][z];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;
	}
	if(x<7)
	{
		point L = jello->p[x][y][z] - jello->p[x+1][y][z];
		point v = jello->v[x][y][z] - jello->v[x+1][y][z];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;

	}
	if(y>0)
	{
		point L = jello->p[x][y][z] - jello->p[x][y-1][z];
		point v = jello->v[x][y][z] - jello->v[x][y-1][z];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;

	}
	if(y<7)
	{
		point L = jello->p[x][y][z] - jello->p[x][y+1][z];
		point v = jello->v[x][y][z] - jello->v[x][y+1][z];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;
	}
	if(z>0)
	{
		point L = jello->p[x][y][z] - jello->p[x][y][z-1];
		point v = jello->v[x][y][z] - jello->v[x][y][z-1];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;
	}
	if(z<7)
	{
		point L = jello->p[x][y][z] - jello->p[x][y][z+1];
		point v = jello->v[x][y][z] - jello->v[x][y][z+1];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;
	}
	//cout<<f_total[x][y][z].x<<" "<<f_total[x][y][z].y<<" "<<f_total[x][y][z].z<<endl;
}

void HandleShearNeighbor(struct world* jello,point f_total[8][8][8],int x,int y,int z)
{
	if(x>0&&y<7)
	{
		point L = jello->p[x][y][z]-jello->p[x-1][y+1][z];
		point v = jello->v[x][y][z] - jello->v[x-1][y+1][z];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-1.414*1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;
	}
	if(x>0&&y>0)
	{
		point L = jello->p[x][y][z] - jello->p[x-1][y-1][z];
		point v = jello->v[x][y][z] - jello->v[x-1][y-1][z];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-1.414*1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;

	}
	if(x<7&&y>0)
	{
		point L = jello->p[x][y][z] - jello->p[x+1][y-1][z];
		point v = jello->v[x][y][z] - jello->v[x+1][y-1][z];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-1.414*1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;
	}
	if(x<7&&y<7)
	{
		point L = jello->p[x][y][z] - jello->p[x+1][y+1][z];
		point v = jello->v[x][y][z] - jello->v[x+1][y+1][z];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-1.414*1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;

	}
	if(y>0&&z<7)
	{
		point L = jello->p[x][y][z] - jello->p[x][y-1][z+1];
		point v = jello->v[x][y][z] - jello->v[x][y-1][z+1];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-1.414*1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;
	}
	if(y>0&&z>0)
	{
		point L = jello->p[x][y][z] - jello->p[x][y-1][z-1];
		point v = jello->v[x][y][z] - jello->v[x][y-1][z-1];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-1.414*1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;
	}
	if(y<7&&z>0)
	{
		point L = jello->p[x][y][z] - jello->p[x][y+1][z-1];
		point v = jello->v[x][y][z] - jello->v[x][y+1][z-1];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-1.414*1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;
	}
	if(y<7&&z<7)
	{
		point L = jello->p[x][y][z] - jello->p[x][y+1][z+1];
		point v = jello->v[x][y][z] - jello->v[x][y+1][z+1];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-1.414*1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;
	}
	if(z>0&&x<7)
	{
		point L = jello->p[x][y][z] - jello->p[x+1][y][z-1];
		point v = jello->v[x][y][z] - jello->v[x+1][y][z-1];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-1.414*1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;
	}
	if(z>0&&x>0)
	{
		point L = jello->p[x][y][z] - jello->p[x-1][y][z-1];
		point v = jello->v[x][y][z] - jello->v[x-1][y][z-1];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-1.414*1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;
	}
	if(z<7&&x>0)
	{
		point L = jello->p[x][y][z] - jello->p[x-1][y][z+1];
		point v = jello->v[x][y][z] - jello->v[x-1][y][z+1];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-1.414*1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;
	}
	if(z<7&&x<7)
	{
		point L = jello->p[x][y][z] - jello->p[x+1][y][z+1];
		point v = jello->v[x][y][z] - jello->v[x+1][y][z+1];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-1.414*1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;
	}
	if(x<7&&y<7&&z<7)
	{
		point L = jello->p[x][y][z] - jello->p[x+1][y+1][z+1];
		point v = jello->v[x][y][z] - jello->v[x+1][y+1][z+1];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-1.732*1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;
	}
	if(x<7&&y<7&&z>0)
	{
		point L = jello->p[x][y][z] - jello->p[x+1][y+1][z-1];
		point v = jello->v[x][y][z] - jello->v[x+1][y+1][z-1];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-1.732*1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;
	}
	if(x<7&&y>0&&z<7)
	{
		point L = jello->p[x][y][z] - jello->p[x+1][y-1][z+1];
		point v = jello->v[x][y][z] - jello->v[x+1][y-1][z+1];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-1.732*1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;
	}
	if(x>0&&y<7&&z<7)
	{
		point L = jello->p[x][y][z] - jello->p[x-1][y+1][z+1];
		point v = jello->v[x][y][z] - jello->v[x-1][y+1][z+1];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-1.732*1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;
	}
	if(x<7&&y>0&&z>0)
	{
		point L = jello->p[x][y][z] - jello->p[x+1][y-1][z-1];
		point v = jello->v[x][y][z] - jello->v[x+1][y-1][z-1];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-1.732*1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;
	}
	if(x>0&&y<7&&z>0)
	{
		point L = jello->p[x][y][z] - jello->p[x-1][y+1][z-1];
		point v = jello->v[x][y][z] - jello->v[x-1][y+1][z-1];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-1.732*1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;
	}
	if(x>0&&y>0&&z<7)
	{
		point L = jello->p[x][y][z] - jello->p[x-1][y-1][z+1];
		point v = jello->v[x][y][z] - jello->v[x-1][y-1][z+1];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-1.732*1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;
	}
	if(x>0&&y>0&&z>0)
	{
		point L = jello->p[x][y][z] - jello->p[x-1][y-1][z-1];
		point v = jello->v[x][y][z] - jello->v[x-1][y-1][z-1];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-1.732*1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;
	}
}

void HandleBendNeighbor(struct world* jello,point f_total[8][8][8],int x,int y,int z)
{
	if(x>1)
	{
		point L = jello->p[x][y][z] - jello->p[x-2][y][z];
		point v = jello->v[x][y][z] - jello->v[x-2][y][z];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-2.0*1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;
	}
	if(x<6)
	{
		point L = jello->p[x][y][z] - jello->p[x+2][y][z];
		point v = jello->v[x][y][z] - jello->v[x+2][y][z];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-2.0*1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;
	}
	if(y>1)
	{
		point L = jello->p[x][y][z] - jello->p[x][y-2][z];
		point v = jello->v[x][y][z] - jello->v[x][y-2][z];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-2.0*1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;
	}
	if(y<6)
	{
		point L = jello->p[x][y][z] - jello->p[x][y+2][z];
		point v = jello->v[x][y][z] - jello->v[x][y+2][z];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-2.0*1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;
	}
	if(z>1)
	{
		point L = jello->p[x][y][z] - jello->p[x][y][z-2];
		point v = jello->v[x][y][z] - jello->v[x][y][z-2];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-2.0*1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;
	}
	if(z<6)
	{
		point L = jello->p[x][y][z] - jello->p[x][y][z+2];
		point v = jello->v[x][y][z] - jello->v[x][y][z+2];
		f_total[x][y][z] += -jello->kElastic*(L.GetMod()-2.0*1.0/7.0)*L/L.GetMod();
		f_total[x][y][z] += -jello->dElastic/L.GetMod()/L.GetMod()*v*L*L;
	}
}

/* Computes acceleration to every control point of the jello cube, 
   which is in state given by 'jello'.
   Returns result in array 'a'. */
void computeAcceleration(struct world * jello, struct point a[8][8][8])
{
	/* for you to implement ... */

	//compute the Hook's point
	point f_total[8][8][8];
	for(int x = 0;x!=8;x++)
	{
		for(int y = 0; y != 8; y++)
		{
			for(int z = 0; z !=8; z++)
			{
				f_total[x][y][z].x =  f_total[x][y][z].y = f_total[x][y][z].z = 0.0;
				a[x][y][z].x = a[x][y][z].y = a[x][y][z].z = 0.0;
			}
		}
	}
	//compute the spring's point
	for(int x = 0; x != 8; x++)
	{
		for(int y = 0; y != 8; y++)
		{
			for(int z = 0; z != 8; z++)
			{
				HandleStructureNeighbor(jello,f_total,x,y,z);
				HandleShearNeighbor(jello,f_total,x,y,z);
				HandleBendNeighbor(jello,f_total,x,y,z);
			}
		}
	}

	//compute the extra force
	if(jello->resolution > 0)
	{
		for(int x = 0; x != 8; x++)
		{
			for(int y = 0; y != 8; y++)
			{
				for(int z = 0; z !=8; z++)
				{
					int i,j,k;
					i = (jello->p[x][y][z].x - (-2.0))/4.0 * (jello->resolution-1);
					j = (jello->p[x][y][z].y - (-2.0))/4.0 * (jello->resolution-1);
					k = (jello->p[x][y][z].z - (-2.0))/4.0 * (jello->resolution-1);

					if(i>=0&&i<jello->resolution&&j>=0&&j<jello->resolution&&k>=0&&k<jello->resolution)
					{
						f_total[x][y][z] += jello->forceField[i*jello->resolution*jello->resolution+j*jello->resolution+k];
					}
				}
			}
		}
	}

	//collision detection
	if(jello->incPlanePresent == 1)
	{	
		double M = jello->a*jello->a+jello->b*jello->b+jello->c*jello->c;
		for(int x = 0; x != 8; x++)
		{
			for(int y = 0; y != 8; y++)
			{
				for(int z = 0; z != 8; z++)
				{
					double dis = abs(jello->a*jello->p[x][y][z].x + jello->b*jello->p[x][y][z].y +
						jello->c*jello->p[x][y][z].z + jello->d)/sqrt(M);
					if(dis < 1.0/7.0)//说明当前点到斜面的另外一端了
					{
						point col;
						col.x = ((jello->b*jello->b+jello->c*jello->c)*jello->p[x][y][z].x-jello->a*(jello->b*jello->p[x][y][z].y+jello->c*jello->p[x][y][z].z+jello->d))/M;
						col.y = ((jello->a*jello->a+jello->c*jello->c)*jello->p[x][y][z].y-jello->b*(jello->a*jello->p[x][y][z].x+jello->c*jello->p[x][y][z].z+jello->d))/M;
						col.z = ((jello->b*jello->b+jello->a*jello->a)*jello->p[x][y][z].z-jello->c*(jello->a*jello->p[x][y][z].x+jello->b*jello->p[x][y][z].y+jello->d))/M;

						point v;
						v.x = 0.0;
						v.y = 0.0;
						v.z = 0.0;
						point L = jello->p[x][y][z] - col;
						f_total[x][y][z] += -jello->kCollision*(L.GetMod() - 1.0/7.0)*L/L.GetMod();
						f_total[x][y][z] += -jello->dCollision/L.GetMod()/L.GetMod()*L*L*(jello->v[x][y][z]-v);
					}
				}
			}
		}
	}

	//bounding box
	for(int x = 0; x != 8; x++)
	{
		for(int y = 0; y != 8; y++)
		{
			for(int z = 0; z != 8; z++)
			{
				point col;
				col.x = jello->p[x][y][z].x;
				col.y = jello->p[x][y][z].y;
				col.z = jello->p[x][y][z].z;
				point v;
				v.x = 0.0;
				v.y = 0.0;
				v.z = 0.0;
				bool out =false;

				if(abs(jello->p[x][y][z].x)>2-1.0/7.0)//the collision happens
				{
					out = true;
					if(jello->p[x][y][z].x <= 0)
						col.x = -2.0;
					else
						col.x = 2.0;
				}
				if(abs(jello->p[x][y][z].y)>2-1.0/7.0)//the collision happens
				{
					out = true;
					if(jello->p[x][y][z].y <= 0)		
						col.y = -2.0;
					else
						col.y = 2.0;
				}
				if(abs(jello->p[x][y][z].z)>2-1.0/7.0)//the collision happens
				{
					out = true;
					if(jello->p[x][y][z].z <= 0)		
						col.z = -2.0;
					else
						col.z = 2.0;
				}
				point L = jello->p[x][y][z] - col;
				if(out)
				{
					f_total[x][y][z] += -jello->kCollision*(L.GetMod() - 1.0/7.0)*L/L.GetMod();
					f_total[x][y][z] += -jello->dCollision/L.GetMod()/L.GetMod()*L*L*(jello->v[x][y][z]-v);
				}
			}
		}
	}
	//compute the acceleration
	for(int x = 0; x != 8; x++)
	{
		for(int y = 0; y != 8; y++)
		{
			for(int z = 0; z !=8; z++)
			{
				a[x][y][z]= f_total[x][y][z]/jello->mass;
				//cout<<a[x][y][z].x<<" "<<a[x][y][z].y<<" "<<a[x][y][z].z<<endl;
			}
		}
	}

}

/* performs one step of Euler Integration */
/* as a result, updates the jello structure */
void Euler(struct world * jello)
{
  int i,j,k;
  point a[8][8][8];

  computeAcceleration(jello, a);
  
  for (i=0; i<=7; i++)
    for (j=0; j<=7; j++)
      for (k=0; k<=7; k++)
      {
        jello->p[i][j][k].x += jello->dt * jello->v[i][j][k].x;
        jello->p[i][j][k].y += jello->dt * jello->v[i][j][k].y;
        jello->p[i][j][k].z += jello->dt * jello->v[i][j][k].z;
        jello->v[i][j][k].x += jello->dt * a[i][j][k].x;
        jello->v[i][j][k].y += jello->dt * a[i][j][k].y;
        jello->v[i][j][k].z += jello->dt * a[i][j][k].z;

      }
}

/* performs one step of RK4 Integration */
/* as a result, updates the jello structure */
void RK4(struct world * jello)
{
  point F1p[8][8][8], F1v[8][8][8], 
        F2p[8][8][8], F2v[8][8][8],
        F3p[8][8][8], F3v[8][8][8],
        F4p[8][8][8], F4v[8][8][8];

  point a[8][8][8];


  struct world buffer;

  int i,j,k;

  buffer = *jello; // make a copy of jello

  computeAcceleration(jello, a);

  for (i=0; i<=7; i++)
    for (j=0; j<=7; j++)
      for (k=0; k<=7; k++)
      {
         pMULTIPLY(jello->v[i][j][k],jello->dt,F1p[i][j][k]);
         pMULTIPLY(a[i][j][k],jello->dt,F1v[i][j][k]);
         pMULTIPLY(F1p[i][j][k],0.5,buffer.p[i][j][k]);
         pMULTIPLY(F1v[i][j][k],0.5,buffer.v[i][j][k]);
         pSUM(jello->p[i][j][k],buffer.p[i][j][k],buffer.p[i][j][k]);
         pSUM(jello->v[i][j][k],buffer.v[i][j][k],buffer.v[i][j][k]);
      }

  computeAcceleration(&buffer, a);

  for (i=0; i<=7; i++)
    for (j=0; j<=7; j++)
      for (k=0; k<=7; k++)
      {
         // F2p = dt * buffer.v;
         pMULTIPLY(buffer.v[i][j][k],jello->dt,F2p[i][j][k]);
         // F2v = dt * a(buffer.p,buffer.v);     
         pMULTIPLY(a[i][j][k],jello->dt,F2v[i][j][k]);
         pMULTIPLY(F2p[i][j][k],0.5,buffer.p[i][j][k]);
         pMULTIPLY(F2v[i][j][k],0.5,buffer.v[i][j][k]);
         pSUM(jello->p[i][j][k],buffer.p[i][j][k],buffer.p[i][j][k]);
         pSUM(jello->v[i][j][k],buffer.v[i][j][k],buffer.v[i][j][k]);
      }

  computeAcceleration(&buffer, a);

  for (i=0; i<=7; i++)
    for (j=0; j<=7; j++)
      for (k=0; k<=7; k++)
      {
         // F3p = dt * buffer.v;
         pMULTIPLY(buffer.v[i][j][k],jello->dt,F3p[i][j][k]);
         // F3v = dt * a(buffer.p,buffer.v);     
         pMULTIPLY(a[i][j][k],jello->dt,F3v[i][j][k]);
         pMULTIPLY(F3p[i][j][k],0.5,buffer.p[i][j][k]);
         pMULTIPLY(F3v[i][j][k],0.5,buffer.v[i][j][k]);
         pSUM(jello->p[i][j][k],buffer.p[i][j][k],buffer.p[i][j][k]);
         pSUM(jello->v[i][j][k],buffer.v[i][j][k],buffer.v[i][j][k]);
      }
         
  computeAcceleration(&buffer, a);


  for (i=0; i<=7; i++)
    for (j=0; j<=7; j++)
      for (k=0; k<=7; k++)
      {
         // F3p = dt * buffer.v;
         pMULTIPLY(buffer.v[i][j][k],jello->dt,F4p[i][j][k]);
         // F3v = dt * a(buffer.p,buffer.v);     
         pMULTIPLY(a[i][j][k],jello->dt,F4v[i][j][k]);

         pMULTIPLY(F2p[i][j][k],2,buffer.p[i][j][k]);
         pMULTIPLY(F3p[i][j][k],2,buffer.v[i][j][k]);
         pSUM(buffer.p[i][j][k],buffer.v[i][j][k],buffer.p[i][j][k]);
         pSUM(buffer.p[i][j][k],F1p[i][j][k],buffer.p[i][j][k]);
         pSUM(buffer.p[i][j][k],F4p[i][j][k],buffer.p[i][j][k]);
         pMULTIPLY(buffer.p[i][j][k],1.0 / 6,buffer.p[i][j][k]);
         pSUM(buffer.p[i][j][k],jello->p[i][j][k],jello->p[i][j][k]);

         pMULTIPLY(F2v[i][j][k],2,buffer.p[i][j][k]);
         pMULTIPLY(F3v[i][j][k],2,buffer.v[i][j][k]);
         pSUM(buffer.p[i][j][k],buffer.v[i][j][k],buffer.p[i][j][k]);
         pSUM(buffer.p[i][j][k],F1v[i][j][k],buffer.p[i][j][k]);
         pSUM(buffer.p[i][j][k],F4v[i][j][k],buffer.p[i][j][k]);
         pMULTIPLY(buffer.p[i][j][k],1.0 / 6,buffer.p[i][j][k]);
         pSUM(buffer.p[i][j][k],jello->v[i][j][k],jello->v[i][j][k]);
      }

  return;  
}
