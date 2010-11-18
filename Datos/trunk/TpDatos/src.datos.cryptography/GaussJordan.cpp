/*
 * GaussJordan.cpp
 *
 *  Created on: 18/11/2010
 *      Author: richy
 */

#include "GaussJordan.h"
#include <math.h>

using namespace std;
GaussJordan::GaussJordan(int n, double** matriz, double** inversa) {
	this->N = n;
	this->matriz = matriz;
	this->identidad = inversa;
}

GaussJordan::~GaussJordan() {
}
void GaussJordan::hallar_inversa(void)
{
	int cont,cont2, flag=0;

	escalonar_matriz();
	generar_matriz_identidad(); //rellena la matriz identidad


	for(cont=0;cont<N;cont++) //recorre filas
	{
		for(cont2=0;cont2<N;cont2++) //recorre columnas
		{
			if(matriz[cont][cont2]!=0) //busca pivote (elemento ditinto de 0)
			{
				if(matriz[cont][cont2]!=1) //si pivote no es 1, se lo multiplica
				{
					multip_fila(cont,pow(matriz[cont][cont2],-1));
				}

				ceros_arriba(cont,cont2); // se hacen 0's por arriba
				ceros_abajo(cont,cont2); // y por debajo del pivote

				break;
			}
		}
	}

/*--------------------------------------------------------------*/
/* Una vez terminada esta operacion, la matriz identidad estara */
/* transformada en la inversa */
/* */
/* Ahora se comprueba que la matriz original este transformada */
/* en la matriz identidad, de no ser asi la inversa obtenida */
/* no es valida y la matriz no tiena inversa */
/*--------------------------------------------------------------*/


for(cont=0;cont<N;cont++)
{
	for(cont2=0;cont2<N;cont2++)
	{
		if(cont==cont2)
		{
			if(matriz[cont][cont2]!=1) flag=1;
		}
		else
		{
			if(matriz[cont][cont2]!=0) flag=1;
		}
	}
}



if(flag==1)
{
	cout<<"La matriz no tiene inversa"<<endl;
}
else
{
	cout<<"La Matriz Inversa es :"<<endl;

	for(cont=0;cont<N;cont++)
	{
		for(cont2=0;cont2<N;cont2++)
		{
			cout<<identidad[cont][cont2]<<" ";

		}
		cout<<endl;
	}
}

}

/*-----------------------------------------------------------------------*/
/* */
/* Ordena la matriz de forma que quede en su forma escalonada por */
/* renglones */
/* */
/*-----------------------------------------------------------------------*/

void GaussJordan::escalonar_matriz(void)
{
	int cont, col, ceros, vec[10];
	int flag, aux;

	for(cont=0;cont<N;cont++)
	{
		col=0,ceros=0;

		if(matriz[cont][col]==0)
		{
			do{
				ceros++;
				col++;
			}while(matriz[cont][col]==0);
		}
		vec[cont]=ceros;
	}


	do
	{
		flag=0;
		for(cont=0;cont<N-1;cont++)
		{
			if(vec[cont]>vec[cont+1])
			{
				aux=vec[cont];
				vec[cont]=vec[cont+1];
				vec[cont+1]=aux;

				permutar_filas(cont,cont+1);

				flag=1;
			}
		}
	}while(flag==1);

}

/*----------------------------------------------------------------------*/
/* SE DEFINEN LAS 3 OPERACIONES ELEMENTALES DE FILA */
/* */
/* Las operaciones que se le realizen a la matriz para reducirla */
/* tambien deberan realizarsele a la matriz identidad para obtener */
/* la matriz inversa */
/*----------------------------------------------------------------------*/


void GaussJordan::permutar_filas(int fila1,int fila2)
{
	float auxval;
	int cont;

	for(cont=0;cont<N;cont++)
	{
		auxval=matriz[fila1][cont];
		matriz[fila1][cont]=matriz[fila2][cont];
		matriz[fila2][cont]=auxval;

		auxval=identidad[fila1][cont];
		identidad[fila1][cont]=identidad[fila2][cont];
		identidad[fila2][cont]=auxval;
	}
}

/*----------------------------------------------------------------------*/

void GaussJordan::multip_fila(int fila,double factor)
{
	int cont;

	for(cont=0;cont<N;cont++)
	{
		matriz[fila][cont]=(matriz[fila][cont])*factor;
		identidad[fila][cont]=(identidad[fila][cont])*factor;
	}
}

/*----------------------------------------------------------------------*/

void GaussJordan::sumar_fila_multip(int fila1,int fila2, double factor)
{
	int cont;
	for(cont=0;cont<N;cont++)
	{
		matriz[fila1][cont]=(matriz[fila1][cont])+((matriz[fila2][cont])*factor);
		identidad[fila1][cont]=(identidad[fila1][cont])+((identidad[fila2][cont])*factor);
	}
}


void GaussJordan::ceros_arriba(int fila_pivote, int columna_pivote)
{
	int cont;

	for(cont=0;cont<fila_pivote;cont++)
	{
		sumar_fila_multip(cont,fila_pivote,((matriz[cont][columna_pivote])*(-1)));

	}
}

/*-------------------------------------------------------------------------*/
void GaussJordan::ceros_abajo(int fila_pivote, int columna_pivote)
{
	int cont;

	for(cont=columna_pivote+1;cont<N;cont++)
	{
		sumar_fila_multip(cont,fila_pivote,((matriz[cont][columna_pivote])*(-1)));
	}

}
/*-------------------------------------------------------------------------*/
void GaussJordan::generar_matriz_identidad(void)
{
	int i,j;
	for(i=0;i<this->N;i++)
	{
		for(j=0;j<this->N;j++)
		{
			if(i==j) identidad[i][j]=1;
			else identidad[i][j]=0;
		}
	}
}
