#include "includes/raylib/raylib.h"
#include <stdlib.h>
#include <cstdio>
#include <ctype.h>
#include <cstring>
#include <time.h>
#include <stdbool.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_TITLE "QUEM É ESTE POKÉMON?"

// Variável que indica qual cena está sendo exibida
int menu;

// Variavies ligadas somente ao jogo em si
int score;
int lives;
char pokemonName[90];
Texture2D pokemonImage;

// variaveis de coordenadas
const int imageWidth = SCREEN_WIDTH/ 1.3;
const int imageHeight = SCREEN_HEIGHT / 2.5;
const int imageX = SCREEN_WIDTH / 2.2 - imageWidth / 2;
const int imageY = SCREEN_HEIGHT / 2 - imageHeight / 2;
Rectangle playRetangulo = { imageX, imageY, imageWidth, imageHeight };

typedef struct node
{
    char *name;
    char *type;
    //char *image;
    struct node *left;
    struct node *right;
} Node;

typedef struct node1
{
    char *name;
    char *type;
    struct node1 *left;
    struct node1 *right;
} Node1;

Node *create_node(char *name, char *type)
{
    Node *node1 = (Node *)malloc(sizeof(Node));
    node1->name = name;
    node1->type = type;
    //node1->image = image;
    node1->left = NULL;
    node1->right = NULL;
    return node1;
}

Node1 *create_node1(char *name, char *type)
{
    Node1 *node1 = (Node1 *)malloc(sizeof(Node1));
    node1->name = name;
    node1->type = type;
    node1->left = NULL;
    node1->right = NULL;
    return node1;
}

void insert_node(Node *root, Node *node)
{
    if (strcmp(node->name, root->name) < 0)
    {
        if (root->left == NULL)
        {
            root->left = node;
        }
        else
        {
            insert_node(root->left, node);
        }
    }
    else
    {
        if (root->right == NULL)
        {
            root->right = node;
        }
        else
        {
            insert_node(root->right, node);
        }
    }
}

void insert_node1(Node1 **root, Node1 *node1)
{
    if (*root == NULL)
    {
        *root = node1;
        return;
    }
    if (strcmp(node1->name, (*root)->name) < 0)
    {
        insert_node1(&(*root)->left, node1);
    }
    else
    {
        insert_node1(&(*root)->right, node1);
    }
}
//imprime em in ordm
void print_pokedex(Node1 *root)
{
    if (root == NULL)
    {
        return;
    }
    print_pokedex(root->left);
    printf("%s\n", root->name);
    print_pokedex(root->right);
}

//conta o numero de nos da arvore
int count_nodes(Node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

// embaralha os nós aleatoriamente usando o algoritmo de Fisher-Yates
void fisher_yates_shuffle(Node **nodes, int num_nodes) {
    for (int i = num_nodes - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Node *temp = nodes[i];
        nodes[i] = nodes[j];
        nodes[j] = temp;
    }
}

// seleciona um nó aleatório da árvore, sem repetição
Node *select_random_node(Node *root, Node **selected_nodes, int num_selected) {
    int tree_size = count_nodes(root);
    int remaining_nodes = tree_size - num_selected;

    // criar vetor para armazenar os nós da árvore
    Node **nodes = (Node **) malloc(tree_size * sizeof(Node *));
    int i = 0;
    void add_nodes_to_array(Node *node) {
        if (node == NULL) return;
        nodes[i++] = node;
        add_nodes_to_array(node->left);
        add_nodes_to_array(node->right);
    }
    add_nodes_to_array(root);

    // embaralhar os nós aleatoriamente
    fisher_yates_shuffle(nodes, tree_size);
    // selecionar o nó aleatório que ainda não foi selecionado
    for (i = 0; i < remaining_nodes; i++) {
        if (selected_nodes[i] == NULL) {
            selected_nodes[i] = nodes[i];
            return nodes[i];
        }
    }

    return NULL;
}


void InputText(char* buf, int buf_size) {
    int c, pos = 0;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (pos < buf_size - 1) {
            buf[pos++] = (char)c;
        }
    }
    buf[pos] = '\0';
}


void initGame() {
    score = 0;
    lives = 3;
    playRetangulo = (Rectangle){ imageX, imageY, imageWidth, imageHeight };
    srand(time(NULL));    
}

void jogar(Node* root){
 // Cria arvore binaria 1 com alguns Pokemon
    Node *root = create_node("Bulbasaur", "Grama/Veneno");
    insert_node(root, create_node("Charmander", "Fogo"));
    insert_node(root, create_node("Squirtle", "Agua"));
    insert_node(root, create_node("Pikachu", "Eletrico"));
    insert_node(root, create_node("Jigglypuff", "Normal"));
    insert_node(root, create_node("Mewtwo", "Psiquico"));
    insert_node(root, create_node("Mew", "Psiquico"));
    insert_node(root, create_node("Eevee", "Normal"));
    // insert_node(root, create_node("Vaporeon", "Agua", "image_vaporeon.png"));
    // insert_node(root, create_node("Jolteon", "Eletrico", "image_jolteon.png"));
    // insert_node(root, create_node("Flareon", "Fogo", "image_flareon.png"));
    // insert_node(root, create_node("Gastly", "Fantasma", "image_gastly.png"));
    // insert_node(root, create_node("Haunter", "Fantasma", "image_haunter.png"));
    // insert_node(root, create_node("Gengar", "Fantasma", "image_gengar.png"));
    // insert_node(root, create_node("Pidgey", "Normal/Voador", "image_pidgey.png"));
    // insert_node(root, create_node("Articuno", "Gelo/Voador", "image_articuno.png"));
    // insert_node(root, create_node("Zapdos", "Eletrico/Voador", "image_zapdos.png"));
    // insert_node(root, create_node("Moltres", "Fogo/Voador", "image_moltres.png"));
    // insert_node(root, create_node("Pidgeot", "Normal/Voador", "image_pidgeot.png"));
    // insert_node(root, create_node("Rattata", "Normal", "image_rattata.png"));
    // insert_node(root, create_node("Venussaur", "Grama/Veneno", "image_venussaur.png"));
    // insert_node(root, create_node("Charizard", "Fogo/Voador", "image_charizard.png"));
    // insert_node(root, create_node("Blastoise", "Agua", "image_blastoise.png"));
    // insert_node(root, create_node("Snorlax", "Normal", "image_snorlax.png"));
    // insert_node(root, create_node("Zubat", "Veneno/Voador", "image_zubat.png"));
    // insert_node(root, create_node("Oddish", "Grama/Veneno", "image_oddish.png"));
    // insert_node(root, create_node("Ivyssaur", "Grama/Veneno", "image_ivyssaur.png"));
    // insert_node(root, create_node("Charmeleon", "Fogo", "image_charmeleon.png"));
    // insert_node(root, create_node("Wartortle", "Agua", "image_wartortle.png"));
    // insert_node(root, create_node("GeoDude", "Pedra/Terra", "image_geodude.png"));
    // insert_node(root, create_node("Onix", "Pedra/Terra", "image_onix.png"));
    // insert_node(root, create_node("Gyarados", "Agua/Voador", "image_gyarados.png"));
    // insert_node(root, create_node("Dragonite", "Dragao/Voador", "image_dragonite.png"));
    // insert_node(root, create_node("Machop", "Lutador", "image_machop.png"));
    // insert_node(root, create_node("Alakazam", "Psiquico", "image_alakazam.png"));

    // Cria arvore binaria para a Pokedex
    Node1 *pokedex = NULL;

    srand(time(NULL)); // Inicializa semente aleatoria

        DrawText("Imprimir Pokedex", 50,50,30);
        DrawText("Gerar Pokemon Aleatório", 20,30,30);
        DrawText("Sair", 90,50,30);

        switch (option)
        {
        case 1:
            printf("Pokedex:\n");
            print_pokedex(pokedex);
            break;
        case 2:
        {
            Node *selected_nodes[34] = {NULL};
            Node *random_pokemon = select_random_node(root, selected_nodes, 0);
            printf("Quem eh esse pokemon? %s\n", random_pokemon->name);
            char input_name[50];
            scanf("%s", input_name);
            if (strcmp(input_name, random_pokemon->name) == 0)
            {
                printf("EHHHH O %s!\n", random_pokemon->name);
                printf("Deseja adicionar %s a sua Pokedex? (S/N) ", random_pokemon->name);
                char input_choice;
                do
                {
                    scanf(" %c", &input_choice);
                    if (input_choice == 'S' || input_choice == 's')
                    {
                        Node1 *new_pokemon = create_node1(random_pokemon->name, random_pokemon->type);
                        insert_node1(&pokedex, new_pokemon);
                        printf("%s adicionado a Pokedex!\n", random_pokemon->name);
                        break; // sai do loop quando o usuario digita "S" ou "s"
                    }
                    else if (input_choice == 'N' || input_choice == 'n')
                    {
                        break; // sai do loop quando o usuario digita "N" ou "n"
                    }
                    else
                    {
                        printf("Opcao invalida! Digite S ou N: ");
                    }
                } while (1); // loop infinito que só termina quando o usuario digita "S" ou "N"
            }
            else
            {
                printf("Errou! O Pokemon era %s.\n", random_pokemon->name);
            }
            break;
        }
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }


}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    //ToggleFullscreen(); // Tela cheia
    SetTargetFPS(60);
    Texture2D background;
    Texture2D background2;
    Texture2D gameOver;
    Texture2D button;
    background = LoadTexture("src/background.png");
    background2 = LoadTexture("src/background2.png");
    
    button = LoadTexture("src/button1.png");
    gameOver = LoadTexture("src/gameOver.png");
    Vector2 mousePos = {0, 0}; // posição do mouse
    
    // Crie a arvore binaria com alguns Pokemon
    Node* root = create_node("Bulbasaur", "Grass/Poison");
    insert_node(root, create_node("Charmander", "Fire"));
    insert_node(root, create_node("Squirtle", "Water"));
    insert_node(root, create_node("Pikachu", "Electric"));
    insert_node(root, create_node("Jigglypuff", "Normal/Fairy"));

    // Main game loop
    while (!WindowShouldClose())    // Detect window apertando ESC FECHA TUDO -- TECLA DE ESCAPE
    {
        // Update // variaveis de atualização
        //----------------------------------------------------------------------------------
        mousePos = GetMousePosition(); // atualiza a posição do mouse a cada iteração

        // Draw
        //----------------------------------------------------------------------------------
        switch(menu) {
        case 0: // case de menu -- apertando SPACE começa o jogo
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexture(background, 0, 0, WHITE);
            DrawTexture(button, imageX, imageY, WHITE);
            
            if(IsKeyPressed(KEY_SPACE) || (CheckCollisionPointRec(mousePos, playRetangulo) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))){
                menu++;
            }

            EndDrawing();
            break;

        case 1: // case de jogo -- implementar botão de voltar ao menu
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexture(background2, 0, 0, WHITE);
            if(IsKeyPressed(KEY_SPACE)){
                menu++;
            }
            initGame();
            jogar(root);
            EndDrawing();
            break;

        case 2: //case com a cena de fim de jogo -- Implementar botão de voltar ao menu
            BeginDrawing();
            ClearBackground(BLACK);
            DrawTexture(gameOver, 0, 0, WHITE);

            EndDrawing();
            break;
        }
    }
    UnloadTexture(gameOver);
    UnloadTexture(background2);
    UnloadTexture(background);
    UnloadTexture(button);
    CloseWindow();

    return 0;
}
