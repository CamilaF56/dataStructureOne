#include <iostream>
#include <locale>

using namespace std;

typedef struct atleta{
char nome[30];
float altura;
float peso;
} Atle;
Atle Atleta[5];

int main()
{
    setlocale(LC_ALL,"Portuguese");

    for(int i=0; i<5; i++){
        cout<< "Digite o seu nome"<<endl;
        cin>>Atleta[i].nome;

        cout<< "Digite a sua altura"<<endl;
        cin>>Atleta[i].altura;

        cout<< "Digite o seu peso"<<endl;
        cin>>Atleta[i].peso;

        cout<<"\n"<<endl;
    }

    int iMenor, aux, fim = 5;

        for(int i=0; i<fim-1; i++){
                iMenor=i;
                for(int k=i+1; k<5; k++){
                    if(Atleta[k].altura < Atleta[iMenor].altura){
                        iMenor=k;
                    }
                }
            if(iMenor!=i){
                aux = Atleta[iMenor].altura;
                Atleta[iMenor].altura= Atleta[i].altura;
                Atleta[i].altura=aux;
            }
        }
        fim--;

    for(int i=0; i<5; i++){
        cout<<"Informações:"<<endl;
        cout<<"Nome: "<<Atleta[i].nome<<endl;
        cout<<"Altura: "<<Atleta[i].altura<<endl;
        cout<<"Peso: "<<Atleta[i].peso<<endl;
        cout<<"\n"<<endl;
    }

    return 0;
}
