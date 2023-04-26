// Code by Jorge Buenestado, Ising Problem
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;
#define MAX 1000000


const int total = 1; //cuantas veces quieres ejecutarlo
const int N = 16; //tamaño matrix
const int PMC = 10000; //pasos montecarlo
const bool randomStart = true;
const bool mostrar = false;
const double tk = 1.5;   //temperatura del sistema



int main(){
    int i, j, k, n;
    int x0, y0, x1, x2, y1, y2;
    int cp, cn, check1, check2, pasos;
    double red[N][N], energia, p, xhi, copia[N][N], funcion[N];
    double promedioMagnetizacion, promedioEnergia, calculoMagnetizacion, calculoEnergia, calor;
    srand(time(0));
    
    cout<<endl<<"-------------------Start of Program------------------"<<endl;
    cp = 0;
    cn = 0;
    for(k = 0; k < total; k++){
        if(randomStart){
            for(i = 0; i < N; i++){
                for(j = 0; j< N;j++){
                    red[i][j] = pow(-1,rand()%(MAX));
                    copia[i][j] = red[i][j];
                }
            }
        }
        else{
        for(i = 0; i < N; i++){
            for(j = 0; j< N;j++){
                red[i][j] = 1;
                copia[i][j] = red[i][j];
            }
        }   
        }

        promedioMagnetizacion = 0;
        promedioEnergia = 0;
        calculoEnergia = 0;
        for(n = 0; n < N*N*PMC; n++){

            x0 = rand()%N;
            y0 = rand()%N;
            x1 = x0;
            y1 = y0;
            x2 = x0;
            y2 = y0;
            if(x0 == 0  ){x2 = N ;}
            if(x0 == N-1){x1 = -1;}
            if(y0 == 0  ){y2 = N ;}
            if(y0 == N-1){y1 = -1;}
            energia = 2*red[x0][y0]*(red[x1+1][y0]+red[x2-1][y0]+red[x0][y1+1]+red[x0][y2-1]); 
            xhi = (rand()%MAX);///MAX;
            p = min(1.0, exp(-2*energia/tk));

            if(p >= xhi/MAX){
                red[x0][y0] = -red[x0][y0];
            }

            if(n%(N*N*PMC/100) == 0){
                calculoMagnetizacion = 0;
                for(i = 0; i < N; i++){
                    for(j = 0; j< N;j++){
                        calculoMagnetizacion += red[i][j];
                        for(k = 0; k < N; k++){
                            x1 = i+k;
                            if(i+k >= N){x1 = x1%N;}
                            funcion[k] += red[i][j]*red[x1][j];
                        }
                    }
                }
                promedioMagnetizacion += abs(calculoMagnetizacion)/N*N;
                calculoEnergia += energia;
            }
        }

        promedioMagnetizacion = promedioMagnetizacion/(PMC/100);
        calor = (((pow(calculoEnergia,2))/(PMC/100))-pow(calculoEnergia/(PMC/100),2))/(N*N*tk);

        promedioEnergia = calculoEnergia/(2*N*PMC/100);

        if((total ==1 )&&(mostrar)){
            cout<<endl<<"Red inicial                                            Red final"<<endl;
            for(i = 0; i < N; i++){
                for(j = 0; j< N; j++){
                    if(copia[i][j] == 1){cout<<"+";}
                    cout<<copia[i][j]<<" ";
                }
                cout <<"                 ";
                for(j = 0; j< N; j++){
                    if(red[i][j] == 1){cout<<"+";}
                    cout<<red[i][j]<< " ";
                }
                cout<<endl;
            }

            cout<<endl<<"Valores Cambiados "<<endl;
            for(i = 0; i < N; i++){
                for(j = 0; j< N; j++){
                    if(red[i][j]+copia[i][j] == 2){cout<<"+";}
                    if(red[i][j]+copia[i][j] == 0){cout<<" ";}
                    cout<<(red[i][j]+copia[i][j])/2<<" ";
                }
                cout<<endl;
            }
            cout<<endl;
        }
        if(total != 1){
        check1 = 0;
        check2 = 0;
        for(i = 0; i < N; i++){
            for(j = 0; j < N; j++){
                if(red[i][j] != 1){
                    check1 = -1;
                }
                if(red[i][j] != -1){
                    check2 = 1;
                }

            }
        }
        if(check1 == 0){cp += 1;}
        if(check2 == 0){cn += 1;}
        }

    }
        
    if(total != 1){
    cout<<"Combinaciones distintas = "<< total- cp - cn <<endl;
    cout<<"Contador todo positivo = "<< cp <<endl;
    cout<<"Contador todo negativo = "<< cn <<endl;
    }
    cout<<"Magnetización Promedio  = "<< promedioMagnetizacion <<endl;
    cout<<"Energia Media           = "<< promedioEnergia <<endl;
    cout<<"Calor específico        = "<< calor <<endl;
    cout<<"------------------End of Program------------------"<<endl<<endl;
    return 0;
}