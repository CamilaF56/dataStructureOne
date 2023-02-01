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

    int i, j, aux, fim=5;

    for(int i=0; i<fim; i++){
        cout<< "Digite o seu nome["<<i+1<<"]"<<endl;
        cin>>Atleta[i].nome;

        cout<< "Digite a sua altura["<<i+1<<"]"<<endl;
        cin>>Atleta[i].altura;

        cout<< "Digite o seu peso["<<i+1<<"]"<<endl;
        cin>>Atleta[i].peso;

        system("cls");
    }

    for(int i=0; i<fim-1; i++){
        for(int j=i+1; j<fim; j++){
            if(Atleta[i].altura > Atleta[j].altura){
                aux = Atleta[i].altura;
                Atleta[i].altura= Atleta[j].altura;
                Atleta[j].altura=aux;
            }
        }
            //fim--;
    }

    for(int i=0; i<fim; i++){
        cout<<"Informações:"<<endl;
        cout<<"Nome: "<<Atleta[i].nome<<endl;
        cout<<"Altura: "<<Atleta[i].altura<<endl;
        cout<<"Peso: "<<Atleta[i].peso<<endl;
        cout<<"\n"<<endl;
    }

    return 0;
}
