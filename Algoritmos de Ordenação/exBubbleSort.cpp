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

    int fim=5, troquei,aux;

    do{
        troquei=0;
        for(int i=0; i<fim-1; i++){
            if(Atleta[i].altura>Atleta[i+1].altura){
                aux = Atleta[i].altura;
                Atleta[i].altura= Atleta[i+1].altura;
                Atleta[i+1].altura=aux;
                troquei=1;
            }
        }
        fim--;
    }while(troquei && fim>0);

    for(int i=0; i<5; i++){
        cout<<"Informações:"<<endl;
        cout<<"Nome: "<<Atleta[i].nome<<endl;
        cout<<"Altura: "<<Atleta[i].altura<<endl;
        cout<<"Peso: "<<Atleta[i].peso<<endl;
        cout<<"\n"<<endl;
    }

    return 0;
}
