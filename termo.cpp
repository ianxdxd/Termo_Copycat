#include <iostream>
using namespace std;
#include <stdlib.h>
#include <time.h>
#include "dicionario.hpp"


// Controle dos itens do menu
// Linha 155

int askPlayer(string question, int min, int max){ 
    
    // recebe uma string com as perguntas e 
    // retorna um inteiro com a respectiva escolha do jogador
    int answer = 0;
    cout << question;
    cin >> answer;
    while(answer < min || answer > max){
        if(!cin.good()){
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "Opcao invalida! Digite novamente: ";
        cin >> answer;
    }
    cout << endl;
    return answer;
}

void sobre(){
    
    cout << "Sobre" << endl;
    cout << "Alunos: Ian C. Aragao e Lucas Losekann Rosa" << endl;
    cout << "Professor: Marcos Carrard" << endl;
    cout << "Disciplina: Algoritmos II" << endl;
    cout << "Instituicao: Universidade do Vale do Itajai" << endl;
    cout << "Data: 08.09.2023" << endl;
    system("pause");
    
}



void getWords(string words[], int size){ 


    // words[0] = "AARAO";
    // return;
    // desabilitar para testar somente uma palavra 
    // caso queira testar mais palavras cria outras words[i]

    for(int i = 0; i < size; i++){
        bool isWordOk = true;
        do{
            // randomiza a palavra e checa se ela ja foi sorteada 
            // caso foi uma nova palavra sera randomizada ate que todas as palavras
            // do array de strings words sejam diferentes
            words[i] = lista[rand() % TAM_LISTA];
            for(int j = 0; j < size; j++){
                if(words[i] == words[j] && i != j){
                    isWordOk = false;
                    break;
                }
            }
        }while(!isWordOk);
        
    }
    
    
}

int findLetter(char letter, string word){ 
    // retorna o indice da letra na palavra
    for(int i = 0; i < 5; i++){
        if(letter == word[i]){
            return i;
        }
    }
    return -1;
}


string checkWord(string attempt, string answer){ 
    // 0 para verde
    // 1 para amarelo
    // 2 para vermelho

    // string do resultado assumindo todos os valores nulos(ou vermelhos)
    string result = "22222";
    char occurrencesIndexes[5] = {}; //vetor com as letras que aparecem na palavra, sem repeticao
    int occurrences[5] = {0, 0, 0, 0, 0}; //vetor com a quantidade de ocorrencias de cada letra, na mesma ordem que o vetor acima

    for(int i = 0; i < 5; i++){
        int idx = findLetter(answer[i], occurrencesIndexes);
        if(idx != -1){ //Se ja foi mapeada, só incrementa a quantidade de ocorrencias
            occurrences[idx]++;
            continue;
        }
        //Se nao foi mapeada, mapeia e incrementa a quantidade de ocorrencias
        occurrencesIndexes[i] = answer[i];
        occurrences[i]++;
    }
    
    //Green check
    for(int i = 0; i < 5; ++i){
        char letter = attempt[i];
        if(letter == answer[i]){
            result[i] = '0'; //torna a letra verde
            int idx = findLetter(letter, occurrencesIndexes); 
            if(idx != -1){
                occurrences[idx]--; //decrementa a quantidade de ocorrencias da letra
            }
        }
    }

    for(int i = 0; i < 5; ++i){
        if(result[i] == '0') continue; //se ja for verde, nao precisa checar
        
        char letter = attempt[i];

        //checagem para saber se a letra vai ser amarela
        int idx = findLetter(letter, occurrencesIndexes);
        if(idx != -1 && occurrences[idx] > 0){ //Se a letra aparece na palavra e ainda nao foi usada
            result[i] = '1'; //torna a letra amarela
            occurrences[idx]--; //decrementa a quantidade de ocorrencias da letra
        }
    }


    return result;
    
}

void displayStructure(string attempts[7], int size, string words[]){ 

    // attempts e um vetor de strings com as tentativas
    // attempt e uma string com a tentativa atual
    // words e um vetor de strings com as palavras a serem descobertas
    // word e uma string com a palavra atual

    // display da estrutura do jogo
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < size; j++){
            string word = words[j];
            string attempt = attempts[i];

            // checar ja a palavra digitada era a correta 
            // e parar de aceitar mais tentativas naquela lacuna
            // checa se as letras do array de strings attempts diferentes da palavra sorteada 
            // caso nao forem (l == 4) ==> a attempt(atual) e substituida por "_____"
            if(attempt != "_____"){
                for(int k = 0; k < i; k++){
                    for(int l = 0; l < 5; l++){
                        if(attempts[k][l] != word[l]){
                            break;
                        }
                        if(l == 4){
                            attempt = "_____";
                        }
                    }
                }
            }

            // print das letras (coloridas)
            // verde para Pos certa
            // amarelo para letra certa, Pos errada
            // normal para letra errada
            for(int i = 0; i < 5; ++i){
                string wordColor = checkWord(attempt, word);
                if(wordColor[i] == '0'){
                    cout << "\033[1;32m" << attempt[i] << "\033[0m";
                }else if(wordColor[i] == '1'){
                    cout << "\033[1;33m" << attempt[i] << "\033[0m";
                }else{
                    cout <<  attempt[i];
                }
                cout << " ";
            }

            cout << "         ";
        }
        cout << endl;
    }


    cout << endl;

    // teclado
    for(int i = 0; i < size; i++){
        string word = words[i];
        for(int j = 0; j < 26; j++){
            char letter = 'A' + j;
            bool foundYellow = false;
            bool foundGreen = false;
            bool foundRed = false;
            for(int k = 0; k < 7; k++){
                if(attempts[k] == "_____"){
                    continue;
                }
                for(int l = 0; l < 5; l++){
                    // checa em qual posicao a letra esta em attemps
                    // se a letra estiver na mesma posicao em word => verde
                    // caso ao contrario itera novamente pela palavra sorteada para
                    // checar se a letra esta na palavra, se esta => amarelo
                    // se todos os outros casos forem falos => vermelho
                    if(letter == attempts[k][l]){
                        if(letter == word[l]){
                            foundGreen = true;
                            break;
                        }
                        for(int l = 0; l < 5; l++){
                            if(letter == word[l]){
                                foundYellow = true;
                                break;
                            }
                        }
                        if(!foundYellow){
                            foundRed = true;
                        }
                    }
                }
            }
            if(foundGreen){
                cout << "\033[1;32m" << letter << "\033[0m";
            }else if(foundYellow){
                cout << "\033[1;33m" << letter << "\033[0m";
            }else if(foundRed){
                cout << "\033[1;31m" << letter << "\033[0m";
            }else{
                cout << letter;
            }
            cout << " ";
        }
        cout << endl;
    }

    cout << endl;
}


void play(){ 
    system("cls");
    int gameType = askPlayer("Que tipo gostaria de jogar?\n1 - Termo\n2 - Dueto\n3 - Trio\n4 - Quarteto\n5 - Voltar\nEscolha uma opcao: ", 1, 5);
    if(gameType == 5){
        return;
    }
    string words[gameType] = {};
    getWords(words, gameType);
    string attempts[7];
    for(int j = 0; j < 7; j++){
        attempts[j] = "_____";
    }
    


    system("cls");
    displayStructure(attempts, gameType, words);

    string attempt;
    for(int i = 0; i < 7; i++){
        cout << "Digite a palavra " << i + 1 << ": ";
        cin >> attempt;
        bool valid = true;


        // checar se a palavra existe dentro da lista
        // compara cada letra da palavra com as letras das palavras da lista 
        // se a palavra existir entao (p == 4)
        bool foundWord = false;
        for(int t = 0; t < TAM_LISTA; t++){
            for(int p = 0; p < 5; p++){
                if(toupper(attempt[p]) != lista[t][p]){
                    break;
                }
                if(p == 4){
                    foundWord = true;
                }
            }
            if(foundWord)break;
        }

        if(!foundWord)valid = false;
        

        // Caso a palavra for menor do que 5 ou valid == false
        // ele limpa o buffer com a palavra errada e pede para digitar novamente
        // e testa os dois itens acima novamente 
        while(attempt.length() != 5 || !valid){
            if(!cin.good()){
                cin.clear();
                cin.ignore(10000, '\n');
            }
            system("cls");
            displayStructure(attempts, gameType, words);

            
            cout << "\nPalavra não existente ou não contém 5 letras! Digite novamente: ";
            cin >> attempt;

            valid = true;

            for(int t = 0; t < TAM_LISTA; t++){
            for(int p = 0; p < 5; p++){
                if(toupper(attempt[p]) != lista[t][p]){
                    break;
                }
                if(p == 4){
                    foundWord = true;
                }
            }
            if(foundWord)break;
        }

        if(!foundWord)valid = false;
        }

        //itera pela tentiva e coloca todas as letras em maiusculo
        for(int j = 0; j < 5; j++){
            attempts[i][j] = toupper(attempt[j]); 
        }
        system("cls");
        displayStructure(attempts, gameType, words);

        // checagem da vitoria
        // checa se as tentivas condizem com as palavras sorteadas
        bool won = true;
        for(int j = 0; j < gameType; j++){
            bool found = false;
            for(int k = 0; k < i + 1; k++){
                if(attempts[k] == words[j]){
                    found = true;
                    break;
                }
            }
            if(!found){
                won = false;
                break;
            }
        }
        if(won){
            cout << "Parabens! Voce venceu!" << endl;
            system("pause");
            return;
        }
    }

    cout << "Voce perdeu! :(" << endl;
    int wantToSee = askPlayer("Deseja ver as palavras?\n1 - Sim\n2 - Nao\nEscolha sua opcao: ", 1, 2);
    system("cls");
    if(wantToSee == 2){
        cout << "Ok! Ate a proxima!\n";
        system("pause");
        return;
    }
    cout << "As palavras eram: \n";
    for(int i = 0; i < gameType; i++){
        cout << words[i] << endl;
    }
    system("pause");

}



int main(){
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));
    bool sair = false;

    while(!sair){

        int menuChoice = askPlayer("Bem vindo ao termo\n1 - Jogar\n2 - Sobre\n3 - Sair\nEscolha uma opcao: ", 1, 3);
        switch(menuChoice){
            case 1:
                play();
                break;
            case 2:
                sobre();
                break; 
            case 3:
                sair = true;
                break;
        }
        system("cls");
    }


    cout << "Fim do programa" << endl;
    return 0;
}


