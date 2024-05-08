#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum main_char{Jack, the_Detective};

enum characters{Sherlock_Holmes, John_Watson, John_Smith, Inspector_Lestrade, Miss_Stealthy, Sergeant_Goodley, Sir_William_Gull, Jeremy_Bert, nobody};
enum characters JacksCharacter;

enum hex_type{Street, Building1, Building2, Police_cordon, Open_manhole, Covered_manhole, Shut_off_gaslight, Lit_gaslight};

enum lit_area{lit_hex, unlit_hex};

typedef struct{
    enum hex_type HexType;
    enum characters HexCharacter;
    enum lit_area LitArea;
}hex;
//hex board[9][13];

struct characters_cards{
    enum characters cards;
    struct characters_cards* next;
};
struct characters_cards* head = NULL;
struct characters_cards* head1 = NULL;
struct characters_cards* head2 = NULL;

typedef struct{
    char name[50];
}Characters;
Characters characters[8]={
    {"Sherlock Holmes"},
    {"John Watson"},
    {"John Smith"},
    {"Inspector Lestrade"},
    {"Miss Stealthy"},
    {"Sergeant Goodley"},
    {"Sir William Gull"},
    {"Jeremy Bert"},
};

typedef struct{
    char name[50];
    enum main_char role;
}player;
player Player_1, Player_2;

typedef struct{
    int x;
    int y;
}coordinate;
coordinate sherlock = {5, 6};
coordinate jeremy = {3, 8};
coordinate smith = {2, 6};
coordinate watson = {4, 0};
coordinate william = {0, 4};
coordinate lestrade = {4, 4};
coordinate stealthy = {7, 8};
coordinate goodley = {3, 12};

int round_counter = 1;

int MainMenu(void);
void NewGame(void);
void shuffle_alibi_cards(void);
void shuffle_characters_cards(void);
void game_rounds(void);
hex** initialize_board();
void Print_Board(hex**);
hex** Sherlock(hex**);
hex** Jeremy__Bert(hex**);
hex** Smith(hex**);
hex** William(hex**);
hex** Lestrade(hex**);
hex** Stealthy(hex**);
hex** Watson(hex**);
hex** Goodley(hex**);


int main(){
    
    while(1){
        
        switch(MainMenu()){
            case 1:
                NewGame();
                getchar();
                printf("\n\n\nPress Enter");
                getchar();
                break;
            case 2:
                printf("2");
                getchar();
                printf("\n\n\nPress Enter");
                getchar();
                break;
            case 3:
                printf("3");
                getchar();
                printf("\n\n\nPress Enter");
                getchar();
                break;
            default:
                printf("Please Enter Valid Number");
                getchar();
                printf("\n\n\nPress Enter");
                getchar();
                break;
        }
        
    }

    return 0;
}

int MainMenu(){
    int choice;
    while(1){
        system("cls");
        printf("Select one of the following\n\n");
        printf("1. New Game\n");
        printf("2. Load previous Game\n");
        printf("3. Save & Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        system("cls");

        return choice;
    }
}
void NewGame(){
    system("cls");
    printf("1. Start Game");
    printf("\n2. back to main menu");
    printf("\n\nEnter your choice: ");
    int choice;
    scanf("%d", &choice);
    switch(choice){
        case 1:
            system("cls");
            printf("\nEnter the name of the first player: ");
            getchar();
            gets(Player_1.name);
            printf("\nEnter the name of the second player: ");
            gets(Player_2.name);
            system("cls");
            printf("%s take your role", Player_1.name);
            printf("\n\n1. Jack");
            printf("\n2. the Detective");
            printf("\n\nEnter your choice: ");
            int choice2;
            scanf("%d", &choice2);
            system("cls");
            if(choice2==1){
                printf("\n%s! you play as Jack", Player_1.name);
                printf("\n%s! you play as the Detective", Player_2.name);
                getchar();
                printf("\n\nPress Enter");
                getchar();
                Player_1.role = Jack;
                Player_2.role = the_Detective;
            }else{
                printf("\n%s! you play as the Detective", Player_1.name);
                printf("\n%s! you play as Jack", Player_2.name);
                getchar();
                printf("\n\nPress Enter");
                getchar();
                Player_2.role = Jack;
                Player_1.role = the_Detective;
            }
            system("cls");
            printf("Detective! could you please close your eyes\n");
            getchar();
            printf("\nJack! press Enter");
            getchar();
            system("cls");
            shuffle_alibi_cards();
            printf("\n\nGood Luck,Have Fun :)");
            printf("\npress Enter to start game");
            getchar();
            game_rounds();
            break;


        case 2:
            return;
    }
}
void shuffle_alibi_cards(){       
    srand(time(NULL));
    JacksCharacter = (rand()%8)+0;     //Character impersonated by jack
    printf("Jack you are going to impersonating '%s' during this game", characters[JacksCharacter].name);
    
    return;
}
void shuffle_characters_cards(){ 
    int i;
    if (head == NULL) { 
    for(i=0;i<8;i++){     //create a linked list of 8 nodes for characters cards 
        struct characters_cards* temp =(struct characters_cards*) malloc(sizeof(struct characters_cards)); 
        temp->cards = i; 
        temp->next = NULL; 
        if(head==NULL){ 
            head = temp; 
        }else{ 
            struct characters_cards* temp1 = head; 
            while(temp1->next != NULL){ 
                temp1 = temp1->next; 
            } 
            temp1->next = temp; 
        } 
    }
} 
    srand(time(0));   //shuffle the first linked list 
    int randnum[4]; 
    for(i=0;i<4;i++){ 
    randnum[i]=-1; 
    } 
    for(i=0;i<4;i++){    //create 4 unique random number 
        randnum[i] = (rand()%8)+0; 
        for(int j=0;j<4;j++){ 
            if(randnum[i]==randnum[j] && i!=j){ 
                randnum[i]=(rand()%8)+0; 
                j=-1; 
            } 
        } 
    } 
    
    head1 = head2 = NULL; 
    struct characters_cards* temp = head; 
    while(temp != NULL){
         int israndom = 0;
          for (i = 0; i < 4; i++) {
               if(temp->cards == randnum[i]){
                    israndom = 1;
                    break;
               }
          } 
        if (israndom) {  //create a linked list of 4 nodes for odd rounds  
            struct characters_cards* temp1 =(struct characters_cards*) malloc(sizeof(struct characters_cards)); 
            temp1->cards = temp->cards; 
            temp1->next = NULL; 
            if(head1==NULL){ 
                head1 = temp1; 
            }else{ 
                struct characters_cards* temp2 = head1; 
                while(temp2->next != NULL){ 
                    temp2 = temp2->next; 
                } 
                temp2->next = temp1; 
            } 
                 
        }else{                      //create a new linked list of 4 for even rounds 
            struct characters_cards* temp5 =(struct characters_cards*) malloc(sizeof(struct characters_cards)); 
            temp5->cards = temp->cards; 
            temp5->next = NULL; 
            if(head2==NULL){ 
                head2 = temp5; 
            }else{ 
                struct characters_cards* temp6 = head2; 
                while(temp6->next != NULL){ 
                    temp6 = temp6->next; 
                } 
                temp6->next = temp5; 
            } 
        } 
        temp = temp->next; 
    } 
    return;     
} 
void game_rounds(){ 
    while(round_counter<=8){
    if(round_counter%2 != 0){ 
        shuffle_characters_cards(); 
        struct characters_cards* tmp = head1; 
        system("cls"); 
        hex** board1 = initialize_board();
        hex** board2;
        hex** board3;
        Print_Board(board1);
        printf("\nDetective! Choose one of these characters please: \n"); 
        int i=1; 
        int arr[4];
        while(tmp!=NULL){ 
            printf("%d. %s\n", i, characters[tmp->cards].name); 
            arr[i-1]=tmp->cards;
            tmp = tmp->next; 
            i++; 
        } 
        int choice; 
        printf("Enter your choice: "); 
        scanf("%d", &choice); 
        printf("\nYou are going to play with %s\n\n", characters[arr[choice-1]].name);
        getchar();
        printf("Press Enter");
        getchar();
        system("cls");
        if(arr[choice-1]==0){
            board1 = initialize_board();
            Print_Board(board1);
            board2 = Sherlock(board1);
            system("cls");
            Print_Board(board2);
        }else if(arr[choice-1]==7){
            board1 = initialize_board();
            Print_Board(board1);
            board2 = Jeremy__Bert(board1);
            system("cls");
            Print_Board(board2);
        }else if(arr[choice-1]==2){
            board1 = initialize_board();
            Print_Board(board1);
            board2 = Smith(board1);
            system("cls");
            Print_Board(board2);
        }else if(arr[choice-1]==6){
            board1 = initialize_board();
            Print_Board(board1);
            board2 = William(board1);
            system("cls");
            Print_Board(board2);
        }else if(arr[choice-1]==3){
            board1 = initialize_board();
            Print_Board(board1);
            board2 = Lestrade(board1);
            system("cls");
            Print_Board(board2);
        }else if(arr[choice-1]==4){
            board1 = initialize_board();
            Print_Board(board1);
            board2 = Stealthy(board1);
            system("cls");
            Print_Board(board2);
        }else if(arr[choice-1]==1){
            board1 = initialize_board();
            Print_Board(board1);
            board2 = Watson(board1);
            system("cls");
            Print_Board(board2);
        }else if(arr[choice-1]==5){
            board1 = initialize_board();
            Print_Board(board1);
            board2 = Goodley(board1);
            system("cls");
            Print_Board(board2);
        }
        struct characters_cards* tmp1 = head1;
        if(choice-1==0){
            head1=tmp1->next;
        }else{
            for(i=0;i<choice-2 && tmp1!=NULL;i++){
                tmp1=tmp1->next;
            }
            struct characters_cards* tmp2 = tmp1->next;
            tmp1->next = tmp2->next;
            head1=tmp1;
        }
        system("cls");
        Print_Board(board2);
        printf("\nMr.Jack choose one of these characters please\n");
        i=1; 
        int arr2[3];
        struct characters_cards* tmp3 = head1;
        while(tmp3!=NULL){ 
            printf("%d. %s\n", i, characters[tmp3->cards].name); 
            arr2[i-1]=tmp3->cards;
            tmp3 = tmp3->next; 
            i++; 
        } 
        int choice2;
        scanf("%d", &choice2);
        printf("\nYou are going to play with %s\n\n", characters[arr2[choice2-1]].name);
        getchar();
        printf("Press Enter");
        getchar();
        system("cls");
        if(arr2[choice2-1]==0){
            Print_Board(board2);
            board3 = Sherlock(board2);
            system("cls");
            Print_Board(board3);
        }else if(arr2[choice2-1]==7){
            Print_Board(board2);
            board3 = Jeremy__Bert(board2);
            system("cls");
            Print_Board(board3);
        }else if(arr2[choice2-1]==2){
            Print_Board(board2);
            board3 = Smith(board2);
            system("cls");
            Print_Board(board3);
        }else if(arr2[choice2-1]==6){
            Print_Board(board2);
            board3 = William(board2);
            system("cls");
            Print_Board(board3);
        }else if(arr2[choice2-1]==3){
            Print_Board(board2);
            board3 = Lestrade(board2);
            system("cls");
            Print_Board(board3);
        }else if(arr2[choice2-1]==4){
            Print_Board(board2);
            board3 = Stealthy(board2);
            system("cls");
            Print_Board(board3);
        }else if(arr2[choice2-1]==1){
            Print_Board(board2);
            board3 = Watson(board2);
            system("cls");
            Print_Board(board3);
        }else if(arr2[choice2-1]==5){
            Print_Board(board2);
            board3 = Goodley(board2);
            system("cls");
            Print_Board(board3);
        }

        
    }
 
    } 
    return; 
}
hex** initialize_board(){
    int i, j;
    hex **board;
    board = (hex **) malloc(9 * sizeof(hex *));
    for(i=0;i<9;i++){
        board[i] = (hex *) malloc(13 * sizeof(hex));
    }
    for(i=0;i<9;i++){
        for(j=0;j<13;j++){
            if(i==0){
                if(j==0 || j==1 || j==2 || j==3){
                    board[i][j].HexType = 1;
                    board[i][j].HexCharacter = 8;
                }else if(j==4){
                    board[i][j].HexType = 0;
                    board[i][j].HexCharacter = 6;
                }else if(j==6){
                    board[i][j].HexType = 0;
                    board[i][j].HexCharacter = 8;
                }else if(j==5){
                    board[i][j].HexType = 4;
                    board[i][j].HexCharacter = 8;
                }else if(j==7 || j==8 || j==9 || j==10){
                    board[i][j].HexType = 1;
                    board[i][j].HexCharacter = 8;
                }else if(j==11 || j==12){
                    board[i][j].HexType = 3;
                    board[i][j].HexCharacter = 8;
                }
            }else if(i==1){
                if(j==0 || j==9){
                    board[i][j].HexType = 1;
                    board[i][j].HexCharacter = 8;
                }else if(j==2){
                    board[i][j].HexType = 7;
                    board[i][j].HexCharacter = 8;
                }else if(j==3){
                    board[i][j].HexType = 2;
                    board[i][j].HexCharacter = 8;
                }else if(j==5){
                    board[i][j].HexType = 6;
                    board[i][j].HexCharacter = 8;
                }else if(j==11){
                    board[i][j].HexType = 5;
                    board[i][j].HexCharacter = 8;
                }else if(j==1 || j==4 || j==6 || j==7 || j==8 || j==10 || j==12){
                    board[i][j].HexType = 0;
                    board[i][j].HexCharacter = 8;
                }
            }else if(i==2){
                if(j==0){
                    board[i][j].HexType = 4;
                    board[i][j].HexCharacter = 8;
                }else if(j==5 || j==7){
                    board[i][j].HexType = 2;
                    board[i][j].HexCharacter = 8;
                }else if(j==11){
                    board[i][j].HexType = 7;
                    board[i][j].HexCharacter = 8;
                }else if(j==6){
                    board[i][j].HexType = 0;
                    board[i][j].HexCharacter = 2;
                }else if(j==1 || j==2 || j==3 || j==4 || j==8 || j==9 || j==10 || j==12){
                    board[i][j].HexType = 0;
                    board[i][j].HexCharacter = 8;
                }
            }else if(i==3){
                if(j==1 || j==2 || j==3 || j==9){
                    board[i][j].HexType = 2;
                    board[i][j].HexCharacter = 8;
                }else if(j==7){
                    board[i][j].HexType = 7;
                    board[i][j].HexCharacter = 8;
                }else if(j==5){
                    board[i][j].HexType = 4;
                    board[i][j].HexCharacter = 8;
                }else if(j==8){
                    board[i][j].HexType = 0;
                    board[i][j].HexCharacter = 7;
                }else if(j==12){
                    board[i][j].HexType = 0;
                    board[i][j].HexCharacter = 5;
                }else if(j==0 || j==4 || j==6 || j==10 ||j==11){
                    board[i][j].HexType = 0;
                    board[i][j].HexCharacter = 8;
                }
            }else if(i==4){
                if(j==1 || j==5 || j==7 || j==10 || j==11){
                    board[i][j].HexType = 2;
                    board[i][j].HexCharacter = 8;
                }else if(j==12){
                    board[i][j].HexType = 4;
                    board[i][j].HexCharacter = 8;
                }else if(j==0){
                    board[i][j].HexType = 0;
                    board[i][j].HexCharacter = 1;
                }else if(j==4){
                    board[i][j].HexType = 0;
                    board[i][j].HexCharacter = 3;
                }else if(j==2 || j==3 || j==6 || j==8 || j==9){
                    board[i][j].HexType = 0;
                    board[i][j].HexCharacter = 8;
                }
            }else if(i==5){
                if(j==3 || j==9 || j==11){
                    board[i][j].HexType = 2;
                    board[i][j].HexCharacter = 8;
                }else if(j==5){
                    board[i][j].HexType = 7;
                    board[i][j].HexCharacter = 8;
                }else if(j==7){
                    board[i][j].HexType = 4;
                    board[i][j].HexCharacter = 8;
                }else if(j==6){
                    board[i][j].HexType = 0;
                    board[i][j].HexCharacter = 0;
                }else if(j==0 || j==1 || j==2 || j==4 || j==8 || j==10 || j==12){
                    board[i][j].HexType = 0;
                    board[i][j].HexCharacter = 8;
                }
            }else if(i==6){
                if(j==1 || j==10){
                    board[i][j].HexType = 7;
                    board[i][j].HexCharacter = 8;
                }else if(j==5 || j==7){
                    board[i][j].HexType = 2;
                    board[i][j].HexCharacter = 8;
                }else if(j==2){
                    board[i][j].HexType = 5;
                    board[i][j].HexCharacter = 8;
                }else if(j==12){
                    board[i][j].HexType = 1;
                    board[i][j].HexCharacter = 8;
                }else if(j==0 || j==3 || j==4 || j==6 || j==8 || j==9 || j==11){
                    board[i][j].HexType = 0;
                    board[i][j].HexCharacter = 8;
                }
            }else if(i==7){
                if(j==0){
                    board[i][j].HexType = 3;
                    board[i][j].HexCharacter = 8;
                }else if(j==2 || j==3 || j==4 || j==10 || j==12){
                    board[i][j].HexType = 1;
                    board[i][j].HexCharacter = 8;
                }else if(j==7){
                    board[i][j].HexType = 6;
                    board[i][j].HexCharacter = 8;
                }else if(j==9){
                    board[i][j].HexType = 2;
                    board[i][j].HexCharacter = 8;
                }else if(j==8){
                    board[i][j].HexType = 0;
                    board[i][j].HexCharacter = 4;
                }else if(j==1 || j==5 || j==6 || j==11){
                    board[i][j].HexType = 0;
                    board[i][j].HexCharacter = 8;
                }
            }else if(i==8){
                if(j==7){
                    board[i][j].HexType = 4;
                    board[i][j].HexCharacter = 8;
                }else if(j==1){
                    board[i][j].HexType = 3;
                    board[i][j].HexCharacter = 8;
                }else if(j!=7 && j!=1){
                    board[i][j].HexType = 1;
                    board[i][j].HexCharacter = 8;
                }
            }
        }
    }
    return board;
}
void Print_Board(hex** board1){
    int i, j;
    for(i=0;i<9;i++){
        if(i==0){
            for(j=0;j<13;j++){
                if(j%2==0){
                    printf("    ");
                }else{
                    printf(" ___");
                }
            }
            printf("\n ");
            for(j=0;j<13;j++){
                if(j%2==0){
                    printf("___");
                }else{
                    if(board1[i][j].HexCharacter == 0 && board1[i][j].HexType == 0){
                        printf("/🔎*\\");
                    }else if((board1[i][j].HexCharacter == 0 && board1[i][j].HexType == 4) || (board1[i][j].HexCharacter == 0 && board1[i][j].HexType == 5)){
                        printf("/🔎*\\");
                    }else if((board1[i][j].HexCharacter == 1 && board1[i][j].HexType == 0)||(board1[i][j].HexCharacter == 1 && board1[i][j].HexType == 4)||(board1[i][j].HexCharacter == 1 && board1[i][j].HexType == 5)){
                        printf("/🔦*\\");
                    }else if((board1[i][j].HexCharacter == 2 && board1[i][j].HexType == 0)||(board1[i][j].HexCharacter == 2 && board1[i][j].HexType == 4)||(board1[i][j].HexCharacter == 2 && board1[i][j].HexType == 5)){
                        printf("/🔌*\\");
                    }else if((board1[i][j].HexCharacter == 3 && board1[i][j].HexType == 0)||(board1[i][j].HexCharacter == 3 && board1[i][j].HexType == 4)||(board1[i][j].HexCharacter == 3 && board1[i][j].HexType == 5)){
                        printf("/🧔*\\");
                    }else if((board1[i][j].HexCharacter == 4 && board1[i][j].HexType == 0)||(board1[i][j].HexCharacter == 4 && board1[i][j].HexType == 4)||(board1[i][j].HexCharacter == 4 && board1[i][j].HexType == 5)){
                        printf("/🧝*\\");
                    }else if((board1[i][j].HexCharacter == 5 && board1[i][j].HexType == 0)||(board1[i][j].HexCharacter == 5 && board1[i][j].HexType == 4)||(board1[i][j].HexCharacter == 5 && board1[i][j].HexType == 5)){
                        printf("/📯*\\");
                    }else if((board1[i][j].HexCharacter == 6 && board1[i][j].HexType == 0)||(board1[i][j].HexCharacter == 6 && board1[i][j].HexType == 4)||(board1[i][j].HexCharacter == 6 && board1[i][j].HexType == 5)){
                        printf("/🧓*\\");
                    }else if((board1[i][j].HexCharacter == 7 && board1[i][j].HexType == 0)||(board1[i][j].HexCharacter == 7 && board1[i][j].HexType == 4)||(board1[i][j].HexCharacter == 7 && board1[i][j].HexType == 5)){
                        printf("/💂*\\");
                    }else if(board1[i][j].HexType == 0){
                        printf("/   \\");
                    }else if(board1[i][j].HexType == 1){
                        printf("/🏠 \\");
                    }else if(board1[i][j].HexType == 2){
                        printf("/🏡 \\");
                    }else if(board1[i][j].HexType == 3){
                        printf("/🚧 \\");
                    }else if(board1[i][j].HexType == 4){
                        printf("/⭕ \\");
                    }else if(board1[i][j].HexType == 5){
                        printf("/⛔ \\");
                    }else if(board1[i][j].HexType == 6){
                        printf("/!💡\\");
                    }else if(board1[i][j].HexType == 7){
                        printf("/💡 \\");
                    }else{
                        printf("/   \\");
                    }
                }
            }
        }
        printf("\n");
        for(j=0;j<13;j++){
            if(j%2==0){
                if(board1[i][j].HexCharacter == 0 && board1[i][j].HexType == 0){
                        printf("/🔎*\\");
                }else if((board1[i][j].HexCharacter == 0 && board1[i][j].HexType == 4) || (board1[i][j].HexCharacter == 0 && board1[i][j].HexType == 5)){
                        printf("/🔎*\\");
                }else if((board1[i][j].HexCharacter == 1 && board1[i][j].HexType == 0)||(board1[i][j].HexCharacter == 1 && board1[i][j].HexType == 4)||(board1[i][j].HexCharacter == 1 && board1[i][j].HexType == 5)){
                        printf("/🔦*\\");
                }else if((board1[i][j].HexCharacter == 2 && board1[i][j].HexType == 0)||(board1[i][j].HexCharacter == 2 && board1[i][j].HexType == 4)||(board1[i][j].HexCharacter == 2 && board1[i][j].HexType == 5)){
                        printf("/🔌*\\");
                }else if((board1[i][j].HexCharacter == 3 && board1[i][j].HexType == 0)||(board1[i][j].HexCharacter == 3 && board1[i][j].HexType == 4)||(board1[i][j].HexCharacter == 3 && board1[i][j].HexType == 5)){
                        printf("/🧔*\\");
                }else if((board1[i][j].HexCharacter == 4 && board1[i][j].HexType == 0)||(board1[i][j].HexCharacter == 4 && board1[i][j].HexType == 4)||(board1[i][j].HexCharacter == 4 && board1[i][j].HexType == 5)){
                        printf("/🧝*\\");
                }else if((board1[i][j].HexCharacter == 5 && board1[i][j].HexType == 0)||(board1[i][j].HexCharacter == 5 && board1[i][j].HexType == 4)||(board1[i][j].HexCharacter == 5 && board1[i][j].HexType == 5)){
                        printf("/📯*\\");
                }else if((board1[i][j].HexCharacter == 6 && board1[i][j].HexType == 0)||(board1[i][j].HexCharacter == 6 && board1[i][j].HexType == 4)||(board1[i][j].HexCharacter == 6 && board1[i][j].HexType == 5)){
                        printf("/🧓*\\");
                }else if((board1[i][j].HexCharacter == 7 && board1[i][j].HexType == 0)||(board1[i][j].HexCharacter == 7 && board1[i][j].HexType == 4)||(board1[i][j].HexCharacter == 7 && board1[i][j].HexType == 5)){
                        printf("/💂*\\");
                }else if(board1[i][j].HexType == 0){
                    printf("/   \\");
                }else if(board1[i][j].HexType == 1){
                    printf("/🏠 \\");
                }else if(board1[i][j].HexType == 2){
                    printf("/🏡 \\");
                }else if(board1[i][j].HexType == 3){
                    printf("/🚧 \\");
                }else if(board1[i][j].HexType == 4){
                    printf("/⭕ \\");
                }else if(board1[i][j].HexType == 5){
                    printf("/⛔ \\");
                }else if(board1[i][j].HexType == 6){
                    printf("/!💡\\");
                }else if(board1[i][j].HexType == 7){
                    printf("/💡 \\");
                }
            }else{
                printf("___");
            }
        }
        printf("\n");
        for(j=0;j<13;j++){
            if(j%2==0){
                printf("\\___/");
            }else{
                if (i == 8) {
                printf("   ");
                } else if(board1[i+1][j].HexCharacter == 0 && board1[i+1][j].HexType == 0){
                    printf("🔎*");
                }else if((board1[i+1][j].HexCharacter == 0 && board1[i+1][j].HexType == 4)|| (board1[i+1][j].HexCharacter == 0 && board1[i+1][j].HexType == 5)){
                    printf("🔎*");
                }else if((board1[i+1][j].HexCharacter == 1 && board1[i+1][j].HexType == 0)||(board1[i+1][j].HexCharacter == 1 && board1[i+1][j].HexType == 4)||(board1[i+1][j].HexCharacter == 1 && board1[i+1][j].HexType == 5)){
                    printf("🔦*");
                }else if((board1[i+1][j].HexCharacter == 2 && board1[i+1][j].HexType == 0)||(board1[i+1][j].HexCharacter == 2 && board1[i+1][j].HexType == 4)||(board1[i+1][j].HexCharacter == 2 && board1[i+1][j].HexType == 5)){
                    printf("🔌*");
                }else if((board1[i+1][j].HexCharacter == 3 && board1[i+1][j].HexType == 0)||(board1[i+1][j].HexCharacter == 3 && board1[i+1][j].HexType == 4)||(board1[i+1][j].HexCharacter == 3 && board1[i+1][j].HexType == 5)){
                    printf("🧔*");
                }else if((board1[i+1][j].HexCharacter == 4 && board1[i+1][j].HexType == 0)||(board1[i+1][j].HexCharacter == 4 && board1[i+1][j].HexType == 4)||(board1[i+1][j].HexCharacter == 4 && board1[i+1][j].HexType == 5)){
                    printf("🧝*");
                }else if((board1[i+1][j].HexCharacter == 5 && board1[i+1][j].HexType == 0)||(board1[i+1][j].HexCharacter == 5 && board1[i+1][j].HexType == 4)||(board1[i+1][j].HexCharacter == 5 && board1[i+1][j].HexType == 5)){
                    printf("📯*");
                }else if((board1[i+1][j].HexCharacter == 6 && board1[i+1][j].HexType == 0)||(board1[i+1][j].HexCharacter == 6 && board1[i+1][j].HexType == 4)||(board1[i+1][j].HexCharacter == 6 && board1[i+1][j].HexType == 5)){
                    printf("🧓*");
                }else if((board1[i+1][j].HexCharacter == 7 && board1[i+1][j].HexType == 0)||(board1[i+1][j].HexCharacter == 7 && board1[i+1][j].HexType == 4)||(board1[i+1][j].HexCharacter == 7 && board1[i+1][j].HexType == 5)){
                    printf("💂*");
                }else if(board1[i+1][j].HexType == 0){
                    printf("   ");
                }else if(board1[i+1][j].HexType == 1){
                    printf("🏠 ");
                }else if(board1[i+1][j].HexType == 2){
                    printf("🏡 ");
                }else if(board1[i+1][j].HexType == 3){
                    printf("🚧 ");
                }else if(board1[i+1][j].HexType == 4){
                    printf("⭕ ");
                }else if(board1[i+1][j].HexType == 5){
                    printf("⛔ ");
                }else if(board1[i+1][j].HexType == 6){
                    printf("!💡");
                }else if(board1[i+1][j].HexType == 7){
                    printf("💡 ");
                }else{
                    printf("   ");
                }
            }
        }

    }
    

    return ;
}
hex** Sherlock(hex** board){
    //hex** initialize board
    printf("\nYou have to move 1 to 3 hexes Then you can use your ability\n");
    printf("How many moves do you want to do?\n");
    int number_of_moves;
    scanf("%d", &number_of_moves);
    for(int i=0;i<number_of_moves;i++){
        printf("Which direction do you want to move for the %d move?\n", i+1);
        printf("1.Up   ");
        printf("2.Down   ");
        printf("3.UpRight   ");
        printf("4.DownRight   ");
        printf("5.UpLeft   ");
        printf("6.DownLeft   \n");
        if(board[sherlock.x][sherlock.y].HexType==4){
            printf("7. Pass Through The Tunnel\n");
        }
        int choice;
        scanf("%d", &choice);
        if(choice==1){
            if(board[(sherlock.x)-1][sherlock.y].HexType==0 || board[(sherlock.x)-1][sherlock.y].HexType==4 || board[(sherlock.x)-1][sherlock.y].HexType==5){
                board[sherlock.x][sherlock.y].HexCharacter=8;
                sherlock.x = (sherlock.x)-1;
                board[sherlock.x][sherlock.y].HexCharacter=0;
            }else{
                //###### try again
            }
        }else if(choice==2){
            if(board[(sherlock.x)+1][sherlock.y].HexType==0 || board[(sherlock.x)+1][sherlock.y].HexType==4 || board[(sherlock.x)+1][sherlock.y].HexType==5){
                board[sherlock.x][sherlock.y].HexCharacter=8;
                sherlock.x = (sherlock.x)+1;
                board[sherlock.x][sherlock.y].HexCharacter=0;
            }else{
                //#####
            }
        }else if(choice==3){
            if(sherlock.y%2==0){
                if(board[sherlock.x][(sherlock.y)+1].HexType==0 || board[sherlock.x][(sherlock.y)+1].HexType==4 || board[sherlock.x][(sherlock.y)+1].HexType==5){
                    board[sherlock.x][sherlock.y].HexCharacter=8;
                    sherlock.y = (sherlock.y)+1;
                    board[sherlock.x][sherlock.y].HexCharacter=0;
                }else{
                    //#####
                }
            }else{
                if(board[sherlock.x-1][sherlock.y+1].HexType==0 || board[sherlock.x-1][sherlock.y+1].HexType==4 || board[sherlock.x-1][sherlock.y+1].HexType==5){
                    board[sherlock.x][sherlock.y].HexCharacter=8;
                    sherlock.x = sherlock.x-1;
                    sherlock.y = sherlock.y+1;
                    board[sherlock.x][sherlock.y].HexCharacter=0;
                }else{
                    //#####
                }
            }
        }else if(choice==4){
            if(sherlock.y%2==0){
                if(board[(sherlock.x)+1][(sherlock.y)+1].HexType==0 || board[(sherlock.x)+1][(sherlock.y)+1].HexType==4 || board[(sherlock.x)+1][(sherlock.y)+1].HexType==5){
                    board[sherlock.x][sherlock.y].HexCharacter=8;
                    sherlock.y = (sherlock.y)+1;
                    sherlock.x = (sherlock.x)+1;
                    board[sherlock.x][sherlock.y].HexCharacter=0;
                }else{
                    //#####
                }
            }else{
                if(board[sherlock.x][(sherlock.y)+1].HexType==0 || board[sherlock.x][(sherlock.y)+1].HexType==4 || board[sherlock.x][(sherlock.y)+1].HexType==5){
                    board[sherlock.x][sherlock.y].HexCharacter=8;
                    sherlock.y = (sherlock.y)+1;
                    board[sherlock.x][sherlock.y].HexCharacter=0;
                }else{
                    //#####
                }
            }
        }else if(choice==5){
            if(sherlock.y%2==0){
                if(board[sherlock.x][(sherlock.y)-1].HexType==0 || board[sherlock.x][(sherlock.y)-1].HexType==4 || board[sherlock.x][(sherlock.y)-1].HexType==5){
                    board[sherlock.x][sherlock.y].HexCharacter=8;
                    sherlock.y = (sherlock.y)-1;
                    board[sherlock.x][sherlock.y].HexCharacter=0;
                }else{
                    //#####
                }
            }else{
                if(board[(sherlock.x)-1][(sherlock.y)-1].HexType==0 || board[(sherlock.x)-1][(sherlock.y)-1].HexType==4 || board[(sherlock.x)-1][(sherlock.y)-1].HexType==5){
                    board[sherlock.x][sherlock.y].HexCharacter=8;
                    sherlock.y = (sherlock.y)-1;
                    sherlock.x = (sherlock.x)-1;
                    board[sherlock.x][sherlock.y].HexCharacter=0;
                }else{
                    //#####
                }
            }
        }else if(choice==6){
            if(sherlock.y%2==0){
                if(board[(sherlock.x)+1][(sherlock.y)-1].HexType==0 || board[(sherlock.x)+1][(sherlock.y)-1].HexType==4 || board[(sherlock.x)+1][(sherlock.y)-1].HexType==5){
                    board[sherlock.x][sherlock.y].HexCharacter=8;
                    sherlock.y = (sherlock.y)-1;
                    sherlock.x = (sherlock.x)+1;
                    board[sherlock.x][sherlock.y].HexCharacter=0;
                }else{
                    //#####
                }
            }else{
                if(board[sherlock.x][(sherlock.y)-1].HexType==0 || board[sherlock.x][(sherlock.y)-1].HexType==4 || board[sherlock.x][(sherlock.y)-1].HexType==5){
                    board[sherlock.x][sherlock.y].HexCharacter=8;
                    sherlock.y = (sherlock.y)-1;
                    board[sherlock.x][sherlock.y].HexCharacter=0;
                }else{
                    //#####
                }
            }
        }else if(choice==7 && board[sherlock.x][sherlock.y].HexType==4){
            printf("Which manhole do you want to get out of?\n");
            if(board[0][5].HexType==4){
                printf("1.The manhole in the first row & 6th columns\n");
            }
            if(board[2][0].HexType==4){
                printf("2.The manhole in the 3th row & first column\n");
            }
            if(board[1][11].HexType==4){
                printf("3.The manhole in the 2th row & 12th column\n");
            }
            if(board[3][5].HexType==4){
                printf("4.The manhole in the 4th row & 6th column\n");
            }
            if(board[5][7].HexType==4){
                printf("5.The manhole in the 6th row & 8th column\n");
            }
            if(board[6][2].HexType==4){
                printf("6.The manhole in the 7th row & 3th column\n");
            }
            if(board[8][7].HexType==4){
                printf("7.The manhole in the 9th row & 8th column\n");
            }
            if(board[4][12].HexType==4){
                printf("8.The manhole in the 5th row & 13th column\n");
            }
            int tunnel_choice;
            scanf("%d", &tunnel_choice);
            if(tunnel_choice==1){
                board[sherlock.x][sherlock.y].HexCharacter=8;
                sherlock.x = 0;
                sherlock.y = 5;
                board[sherlock.x][sherlock.y].HexCharacter=0;
            }else if(tunnel_choice==2){
                board[sherlock.x][sherlock.y].HexCharacter=8;
                sherlock.x = 2;
                sherlock.y = 0;
                board[sherlock.x][sherlock.y].HexCharacter=0;
            }else if(tunnel_choice==3){
                board[sherlock.x][sherlock.y].HexCharacter=8;
                sherlock.x = 1;
                sherlock.y = 11;
                board[sherlock.x][sherlock.y].HexCharacter=0;
            }else if(tunnel_choice==4){
                board[sherlock.x][sherlock.y].HexCharacter=8;
                sherlock.x = 3;
                sherlock.y = 5;
                board[sherlock.x][sherlock.y].HexCharacter=0;
            }else if(tunnel_choice==5){
                board[sherlock.x][sherlock.y].HexCharacter=8;
                sherlock.x = 5;
                sherlock.y = 7;
                board[sherlock.x][sherlock.y].HexCharacter=0;
            }else if(tunnel_choice==6){
                board[sherlock.x][sherlock.y].HexCharacter=8;
                sherlock.x = 5;
                sherlock.y = 2;
                board[sherlock.x][sherlock.y].HexCharacter=0;
            }else if(tunnel_choice==7){
                board[sherlock.x][sherlock.y].HexCharacter=8;
                sherlock.x = 8;
                sherlock.y = 7;
                board[sherlock.x][sherlock.y].HexCharacter=0;
            }else if(tunnel_choice==8){
                board[sherlock.x][sherlock.y].HexCharacter=8;
                sherlock.x = 4;
                sherlock.y = 12;
                board[sherlock.x][sherlock.y].HexCharacter=0;
            }else{
                //to control user foolishness
            }
            

        }else{
            //to control user foolishness
        }

    }
    srand(time(NULL));        //Sherlock's ability
    enum characters sherlock_ability = (rand()%8)+0;
    if(sherlock_ability==JacksCharacter){
        while(sherlock_ability==JacksCharacter){
            sherlock_ability = (rand()%8)+0;
        }
    }
    printf("The other player!close your eyes please\n\n");
    getchar();
    printf("If it's safe press Enter\n");
    getchar();
    printf("%s is not Jack", characters[sherlock_ability].name);
    getchar();
    printf("Press Enter to see updated map");
    getchar();


    return board;
}
hex** Jeremy__Bert(hex** board){
    printf("\nDo you want to use your ability or move first?\n");
    printf("1.Move first\n");
    printf("Other than 1.Use my ability first\n");
    int choice;
    scanf("%d", &choice);
    if(choice==1){
        printf("You have to move 1 to 3 hexes Then you can use your ability\n");
        printf("How many moves do you want to do?\n");
        int number_of_moves;
        scanf("%d", &number_of_moves);
        for(int i=0;i<number_of_moves;i++){
        printf("Which direction do you want to move for the %dth move?\n", i+1);
        printf("1.Up   ");
        printf("2.Down   ");
        printf("3.UpRight   ");
        printf("4.DownRight   ");
        printf("5.UpLeft   ");
        printf("6.DownLeft   \n");
        if(board[jeremy.x][jeremy.y].HexType==4){
            printf("7. Pass Through The Tunnel\n");
        }
        int choice1;
        scanf("%d", &choice1);
        if(choice1==1){
            if(board[(jeremy.x)-1][jeremy.y].HexType==0 || board[(jeremy.x)-1][jeremy.y].HexType==4 || board[(jeremy.x)-1][jeremy.y].HexType==5){
                board[jeremy.x][jeremy.y].HexCharacter = 8;
                board[(jeremy.x)-1][jeremy.y].HexCharacter = 7;
                jeremy.x = (jeremy.x)-1;
            }else{
                //###### try again
            }
        }else if(choice1==2){
            if(board[(jeremy.x)+1][jeremy.y].HexType==0 || board[(jeremy.x)+1][jeremy.y].HexType==4 || board[(jeremy.x)+1][jeremy.y].HexType==5){
                board[jeremy.x][jeremy.y].HexCharacter = 8;
                board[(jeremy.x)+1][jeremy.y].HexCharacter = 7;
                jeremy.x = (jeremy.x)+1;
            }else{
                //#####
            }
        }else if(choice1==3){
            if(jeremy.y%2==0){
                if(board[jeremy.x][(jeremy.y)+1].HexType==0 || board[jeremy.x][(jeremy.y)+1].HexType==4 || board[jeremy.x][(jeremy.y)+1].HexType==5){
                    board[jeremy.x][jeremy.y].HexCharacter = 8;
                    board[jeremy.x][(jeremy.y)+1].HexCharacter = 7;
                    jeremy.y = (jeremy.y)+1;
                }else{
                    //#####
                }
            }else{
                if(board[(jeremy.x)-1][(jeremy.y)+1].HexType==0 || board[(jeremy.x)-1][(jeremy.y)+1].HexType==4 || board[(jeremy.x)-1][(jeremy.y)+1].HexType==5){
                    board[jeremy.x][jeremy.y].HexCharacter = 8;
                    board[(jeremy.x)-1][(jeremy.y)+1].HexCharacter = 7;
                    jeremy.y = (jeremy.y)+1;
                    jeremy.x = (jeremy.x)-1;
                }else{
                    //#####
                }
            }
        }else if(choice1==4){
            if(jeremy.y%2==0){
                if(board[(jeremy.x)+1][(jeremy.y)+1].HexType==0 || board[(jeremy.x)+1][(jeremy.y)+1].HexType==4 || board[(jeremy.x)+1][(jeremy.y)+1].HexType==5){
                    board[jeremy.x][jeremy.y].HexCharacter = 8;
                    board[(jeremy.x)+1][(jeremy.y)+1].HexCharacter = 7;
                    jeremy.y = (jeremy.y)+1;
                    jeremy.x = (jeremy.x)+1;
                }else{
                    //#####
                }
            }else{
                if(board[jeremy.x][(jeremy.y)+1].HexType==0 || board[jeremy.x][(jeremy.y)+1].HexType==4 || board[jeremy.x][(jeremy.y)+1].HexType==5){
                    board[jeremy.x][jeremy.y].HexCharacter = 8;
                    board[jeremy.x][(jeremy.y)+1].HexCharacter = 7;
                    jeremy.y = (jeremy.y)+1;
                }else{
                    //#####
                }
            }
        }else if(choice1==5){
            if(jeremy.y%2==0){
                if(board[jeremy.x][(jeremy.y)-1].HexType==0 || board[jeremy.x][(jeremy.y)-1].HexType==4 || board[jeremy.x][(jeremy.y)-1].HexType==5){
                    board[jeremy.x][jeremy.y].HexCharacter = 8;
                    board[jeremy.x][(jeremy.y)-1].HexCharacter = 7;
                    jeremy.y = (jeremy.y)-1;
                }else{
                    //#####
                }
            }else{
                if(board[(jeremy.x)-1][(jeremy.y)-1].HexType==0 || board[(jeremy.x)-1][(jeremy.y)-1].HexType==4 || board[(jeremy.x)-1][(jeremy.y)-1].HexType==5){
                    board[jeremy.x][jeremy.y].HexCharacter = 8;
                    board[(jeremy.x)-1][(jeremy.y)-1].HexCharacter = 7;
                    jeremy.y = (jeremy.y)-1;
                    jeremy.x = (jeremy.x)-1;
                }else{
                    //#####
                }
            }
        }else if(choice1==6){
            if(jeremy.y%2==0){
                if(board[(jeremy.x)+1][(jeremy.y)-1].HexType==0 || board[(jeremy.x)+1][(jeremy.y)-1].HexType==4 || board[(jeremy.x)+1][(jeremy.y)-1].HexType==5){
                    board[jeremy.x][jeremy.y].HexCharacter = 8;
                    board[(jeremy.x)+1][(jeremy.y)-1].HexCharacter = 7;
                    jeremy.y = (jeremy.y)-1;
                    jeremy.x = (jeremy.x)+1;
                }else{
                    //#####
                }
            }else{
                if(board[jeremy.x][(jeremy.y)-1].HexType==0 || board[jeremy.x][(jeremy.y)-1].HexType==4 || board[jeremy.x][(jeremy.y)-1].HexType==5){
                    board[jeremy.x][jeremy.y].HexCharacter = 8;
                    board[jeremy.x][(jeremy.y)-1].HexCharacter = 7;
                    jeremy.y = (jeremy.y)-1;
                }else{
                    //#####
                }
            }
        }else if(choice1==7 && board[jeremy.x][jeremy.y].HexType==4){
            printf("Which manhole do you want to get out of?\n");
            if(board[0][5].HexType==4){
                printf("1.The manhole in the first row & 6th columns\n");
            }
            if(board[2][0].HexType==4){
                printf("2.The manhole in the 3th row & first column\n");
            }
            if(board[1][11].HexType==4){
                printf("3.The manhole in the 2th row & 12th column\n");
            }
            if(board[3][5].HexType==4){
                printf("4.The manhole in the 4th row & 6th column\n");
            }
            if(board[5][7].HexType==4){
                printf("5.The manhole in the 6th row & 8th column\n");
            }
            if(board[6][2].HexType==4){
                printf("6.The manhole in the 7th row & 3th column\n");
            }
            if(board[8][7].HexType==4){
                printf("7.The manhole in the 9th row & 8th column\n");
            }
            if(board[4][12].HexType==4){
                printf("8.The manhole in the 5th row & 13th column\n");
            }
            int tunnel_choice;
            scanf("%d", &tunnel_choice);
            if(tunnel_choice==1){
                board[jeremy.x][jeremy.y].HexCharacter = 8;
                jeremy.x = 0;
                jeremy.y = 5;
                board[jeremy.x][jeremy.y].HexCharacter = 7;
            }else if(tunnel_choice==2){
                board[jeremy.x][jeremy.y].HexCharacter = 8;
                jeremy.x = 2;
                jeremy.y = 0;
                board[jeremy.x][jeremy.y].HexCharacter = 7;
            }else if(tunnel_choice==3){
                board[jeremy.x][jeremy.y].HexCharacter = 8;
                jeremy.x = 1;
                jeremy.y = 11;
                board[jeremy.x][jeremy.y].HexCharacter = 7;
            }else if(tunnel_choice==4){
                board[jeremy.x][jeremy.y].HexCharacter = 8;
                jeremy.x = 3;
                jeremy.y = 5;
                board[jeremy.x][jeremy.y].HexCharacter = 7;
            }else if(tunnel_choice==5){
                board[jeremy.x][jeremy.y].HexCharacter = 8;
                jeremy.x = 5;
                jeremy.y = 7;
                board[jeremy.x][jeremy.y].HexCharacter = 7;
            }else if(tunnel_choice==6){
                board[jeremy.x][jeremy.y].HexCharacter = 8;
                jeremy.x = 5;
                jeremy.y = 2;
                board[jeremy.x][jeremy.y].HexCharacter = 7;
            }else if(tunnel_choice==7){
                board[jeremy.x][jeremy.y].HexCharacter = 8;
                jeremy.x = 8;
                jeremy.y = 7;
                board[jeremy.x][jeremy.y].HexCharacter = 7;
            }else if(tunnel_choice==8){
                board[jeremy.x][jeremy.y].HexCharacter = 8;
                jeremy.x = 4;
                jeremy.y = 12;
                board[jeremy.x][jeremy.y].HexCharacter = 7;
            }else{
                //to control user foolishness
            }
            

        }else{
            //to control user foolishness
        }
        printf("\n");
        printf("Now you have to use your ability\n");
        printf("which open manhole do you want to close?\n");
        if(board[0][5].HexType==4){
            printf("1.The manhole in the first row & 6th columns\n");
        }
        if(board[2][0].HexType==4){
            printf("2.The manhole in the 3th row & first column\n");
        }
        if(board[1][11].HexType==4){
            printf("3.The manhole in the 2th row & 12th column\n");
        }
        if(board[3][5].HexType==4){
            printf("4.The manhole in the 4th row & 6th column\n");
        }
        if(board[5][7].HexType==4){
            printf("5.The manhole in the 6th row & 8th column\n");
        }
        if(board[6][2].HexType==4){
            printf("6.The manhole in the 7th row & 3th column\n");
        }
        if(board[8][7].HexType==4){
            printf("7.The manhole in the 9th row & 8th column\n");
        }
        if(board[4][12].HexType==4){
            printf("8.The manhole in the 5th row & 13th column\n");
        }
        int close_manhole;
        int save_i, save_j;
        scanf("%d", &close_manhole);
        if(close_manhole==1){
            board[0][5].HexType=5;
            save_i=0;
            save_j=5;
        }else if(close_manhole==2){
            board[2][0].HexType=5;
            save_i=2;
            save_j=0;
        }else if(close_manhole==3){
            board[1][11].HexType=5;
            save_i=1;
            save_j=11;
        }else if(close_manhole==4){
            board[3][5].HexType=5;
            save_i=3;
            save_j=5;
        }else if(close_manhole==5){
            board[5][7].HexType=5;
            save_i=5;
            save_j=7;
        }else if(close_manhole==6){
            board[6][2].HexType=5;
            save_i=6;
            save_j=2;
        }else if(close_manhole==7){
            board[8][7].HexType=5;
            save_i=8;
            save_j=7;
        }else if(close_manhole==8){
            board[4][12].HexType=5;
            save_i=4;
            save_j=12;
        }
        printf("which close manhole do you want to open?\n");
        if(board[0][5].HexType==5 && save_i!=0 && save_j!=5){
            printf("1.The manhole in the first row & 6th columns\n");
        }
        if(board[2][0].HexType==5 && save_i!=2 && save_j!=0){
            printf("2.The manhole in the 3th row & first column\n");
        }
        if(board[1][11].HexType==5 && save_i!=1 && save_j!=11){
            printf("3.The manhole in the 2th row & 12th column\n");
        }
        if(board[3][5].HexType==5 && save_i!=3 && save_j!=5){
            printf("4.The manhole in the 4th row & 6th column\n");
        }
        if(board[5][7].HexType==5 && save_i!=5 && save_j!=7){
            printf("5.The manhole in the 6th row & 8th column\n");
        }
        if(board[6][2].HexType==5 && save_i!=6 && save_j!=2){
            printf("6.The manhole in the 7th row & 3th column\n");
        }
        if(board[8][7].HexType==5 && save_i!=8 && save_j!=7){
            printf("7.The manhole in the 9th row & 8th column\n");
        }
        if(board[4][12].HexType==5 && save_i!=4 && save_j!=12){
            printf("8.The manhole in the 5th row & 13th column\n");
        }
        int open_manhole;
        scanf("%d", &open_manhole);
        if(open_manhole==1){
            board[0][5].HexType=4;
        }else if(open_manhole==2){
            board[2][0].HexType=4;
        }else if(open_manhole==3){
            board[1][11].HexType=4;
        }else if(open_manhole==4){
            board[3][5].HexType=4;
        }else if(open_manhole==5){
            board[5][7].HexType=4;
        }else if(open_manhole==6){
            board[6][2].HexType=4;
        }else if(open_manhole==7){
            board[8][7].HexType=4;
        }else if(open_manhole==8){
            board[4][12].HexType=4;
        }
        }


    }else{
        printf("which open manhole do you want to close?\n");
        if(board[0][5].HexType==4){
            printf("1.The manhole in the first row & 6th columns\n");
        }
        if(board[2][0].HexType==4){
            printf("2.The manhole in the 3th row & first column\n");
        }
        if(board[1][11].HexType==4){
            printf("3.The manhole in the 2th row & 12th column\n");
        }
        if(board[3][5].HexType==4){
            printf("4.The manhole in the 4th row & 6th column\n");
        }
        if(board[5][7].HexType==4){
            printf("5.The manhole in the 6th row & 8th column\n");
        }
        if(board[6][2].HexType==4){
            printf("6.The manhole in the 7th row & 3th column\n");
        }
        if(board[8][7].HexType==4){
            printf("7.The manhole in the 9th row & 8th column\n");
        }
        if(board[4][12].HexType==4){
            printf("8.The manhole in the 5th row & 13th column\n");
        }
        int close_manhole1;
        int save_i, save_j;
        scanf("%d", &close_manhole1);
        if(close_manhole1==1){
            board[0][5].HexType=5;
            save_i=0;
            save_j=5;
        }else if(close_manhole1==2){
            board[2][0].HexType=5;
            save_i=2;
            save_j=0;
        }else if(close_manhole1==3){
            board[1][11].HexType=5;
            save_i=1;
            save_j=11;
        }else if(close_manhole1==4){
            board[3][5].HexType=5;
            save_i=3;
            save_j=5;
        }else if(close_manhole1==5){
            board[5][7].HexType=5;
            save_i=5;
            save_j=7;
        }else if(close_manhole1==6){
            board[6][2].HexType=5;
            save_i=6;
            save_j=2;
        }else if(close_manhole1==7){
            board[8][7].HexType=5;
            save_i=8;
            save_j=7;
        }else if(close_manhole1==8){
            board[4][12].HexType=5;
            save_i=4;
            save_j=12;
        }
        printf("which close manhole do you want to open?\n");
        if(board[0][5].HexType==5 && save_i!=0 && save_j!=5){
            printf("1.The manhole in the first row & 6th columns\n");
        }
        if(board[2][0].HexType==5 && save_i!=2 && save_j!=0){
            printf("2.The manhole in the 3th row & first column\n");
        }
        if(board[1][11].HexType==5 && save_i!=1 && save_j!=11){
            printf("3.The manhole in the 2th row & 12th column\n");
        }
        if(board[3][5].HexType==5 && save_i!=3 && save_j!=5){
            printf("4.The manhole in the 4th row & 6th column\n");
        }
        if(board[5][7].HexType==5 && save_i!=5 && save_j!=7){
            printf("5.The manhole in the 6th row & 8th column\n");
        }
        if(board[6][2].HexType==5 && save_i!=6 && save_j!=2){
            printf("6.The manhole in the 7th row & 3th column\n");
        }
        if(board[8][7].HexType==5 && save_i!=8 && save_j!=7){
            printf("7.The manhole in the 9th row & 8th column\n");
        }
        if(board[4][12].HexType==5 && save_i!=4 && save_j!=12){
            printf("8.The manhole in the 5th row & 13th column\n");
        }
        int open_manhole1;
        scanf("%d", &open_manhole1);
        if(open_manhole1==1){
            board[0][5].HexType=4;
        }else if(open_manhole1==2){
            board[2][0].HexType=4;
        }else if(open_manhole1==3){
            board[1][11].HexType=4;
        }else if(open_manhole1==4){
            board[3][5].HexType=4;
        }else if(open_manhole1==5){
            board[5][7].HexType=4;
        }else if(open_manhole1==6){
            board[6][2].HexType=4;
        }else if(open_manhole1==7){
            board[8][7].HexType=4;
        }else if(open_manhole1==8){
            board[4][12].HexType=4;
        }
        printf("Now you have to move 1 to 3 hexes");
        printf("How many moves do you want to do?\n");
        int number_of_moves;
        scanf("%d", &number_of_moves);
        for(int i=0;i<number_of_moves;i++){
        printf("Which direction do you want to move for the %dth move?\n", i+1);
        printf("1.Up   ");
        printf("2.Down   ");
        printf("3.UpRight   ");
        printf("4.DownRight   ");
        printf("5.UpLeft   ");
        printf("6.DownLeft   \n");
        if(board[jeremy.x][jeremy.y].HexType==4){
            printf("7. Pass Through The Tunnel\n");
        }
        int choice2;
        scanf("%d", &choice2);
        if(choice2==1){
            if(board[(jeremy.x)-1][jeremy.y].HexType==0 || board[(jeremy.x)-1][jeremy.y].HexType==4 || board[(jeremy.x)-1][jeremy.y].HexType==5){
                board[jeremy.x][jeremy.y].HexCharacter = 8;
                board[(jeremy.x)-1][jeremy.y].HexCharacter = 7;
                jeremy.x = (jeremy.x)-1;
            }else{
                //###### try again
            }
        }else if(choice2==2){
            if(board[(jeremy.x)+1][jeremy.y].HexType==0 || board[(jeremy.x)+1][jeremy.y].HexType==4 || board[(jeremy.x)+1][jeremy.y].HexType==5){
                board[jeremy.x][jeremy.y].HexCharacter = 8;
                board[(jeremy.x)+1][jeremy.y].HexCharacter = 7;
                jeremy.x = (jeremy.x)+1;
            }else{
                //#####
            }
        }else if(choice2==3){
            if(jeremy.y%2==0){
                if(board[jeremy.x][(jeremy.y)+1].HexType==0 || board[jeremy.x][(jeremy.y)+1].HexType==4 || board[jeremy.x][(jeremy.y)+1].HexType==5){
                    board[jeremy.x][jeremy.y].HexCharacter = 8;
                    board[jeremy.x][(jeremy.y)+1].HexCharacter = 7;
                    jeremy.y = (jeremy.y)+1;
                }else{
                    //#####
                }
            }else{
                if(board[(jeremy.x)-1][(jeremy.y)+1].HexType==0 || board[(jeremy.x)-1][(jeremy.y)+1].HexType==4 || board[(jeremy.x)-1][(jeremy.y)+1].HexType==5){
                    board[jeremy.x][jeremy.y].HexCharacter = 8;
                    board[(jeremy.x)-1][(jeremy.y)+1].HexCharacter = 7;
                    jeremy.y = (jeremy.y)+1;
                    jeremy.x = (jeremy.x)-1;
                }else{
                    //#####
                }
            }
        }else if(choice2==4){
            if(jeremy.y%2==0){
                if(board[(jeremy.x)+1][(jeremy.y)+1].HexType==0 || board[(jeremy.x)+1][(jeremy.y)+1].HexType==4 || board[(jeremy.x)+1][(jeremy.y)+1].HexType==5){
                    board[jeremy.x][jeremy.y].HexCharacter = 8;
                    board[(jeremy.x)+1][(jeremy.y)+1].HexCharacter = 7;
                    jeremy.y = (jeremy.y)+1;
                    jeremy.x = (jeremy.x)+1;
                }else{
                    //#####
                }
            }else{
                if(board[jeremy.x][(jeremy.y)+1].HexType==0 || board[jeremy.x][(jeremy.y)+1].HexType==4 || board[jeremy.x][(jeremy.y)+1].HexType==5){
                    board[jeremy.x][jeremy.y].HexCharacter = 8;
                    board[jeremy.x][(jeremy.y)+1].HexCharacter = 7;
                    jeremy.y = (jeremy.y)+1;
                }else{
                    //#####
                }
            }
        }else if(choice2==5){
            if(jeremy.y%2==0){
                if(board[jeremy.x][(jeremy.y)-1].HexType==0 || board[jeremy.x][(jeremy.y)-1].HexType==4 || board[jeremy.x][(jeremy.y)-1].HexType==5){
                    board[jeremy.x][jeremy.y].HexCharacter = 8;
                    board[jeremy.x][(jeremy.y)-1].HexCharacter = 7;
                    jeremy.y = (jeremy.y)-1;
                }else{
                    //#####
                }
            }else{
                if(board[(jeremy.x)-1][(jeremy.y)-1].HexType==0 || board[(jeremy.x)-1][(jeremy.y)-1].HexType==4 || board[(jeremy.x)-1][(jeremy.y)-1].HexType==5){
                    board[jeremy.x][jeremy.y].HexCharacter = 8;
                    board[(jeremy.x)-1][(jeremy.y)-1].HexCharacter = 7;
                    jeremy.y = (jeremy.y)-1;
                    jeremy.x = (jeremy.x)-1;
                }else{
                    //#####
                }
            }
        }else if(choice2==6){
            if(jeremy.y%2==0){
                if(board[(jeremy.x)+1][(jeremy.y)-1].HexType==0 || board[(jeremy.x)+1][(jeremy.y)-1].HexType==4 || board[(jeremy.x)+1][(jeremy.y)-1].HexType==5){
                    board[jeremy.x][jeremy.y].HexCharacter = 8;
                    board[(jeremy.x)+1][(jeremy.y)-1].HexCharacter = 7;
                    jeremy.y = (jeremy.y)-1;
                    jeremy.x = (jeremy.x)+1;
                }else{
                    //#####
                }
            }else{
                if(board[jeremy.x][(jeremy.y)-1].HexType==0 || board[jeremy.x][(jeremy.y)-1].HexType==4 || board[jeremy.x][(jeremy.y)-1].HexType==5){
                    board[jeremy.x][jeremy.y].HexCharacter = 8;
                    board[jeremy.x][(jeremy.y)-1].HexCharacter = 7;
                    jeremy.y = (jeremy.y)-1;
                }else{
                    //#####
                }
            }
        }else if(choice2==7 && board[jeremy.x][jeremy.y].HexType==4){
            printf("Which manhole do you want to get out of?\n");
            if(board[0][5].HexType==4){
                printf("1.The manhole in the first row & 6th columns\n");
            }
            if(board[2][0].HexType==4){
                printf("2.The manhole in the 3th row & first column\n");
            }
            if(board[1][11].HexType==4){
                printf("3.The manhole in the 2th row & 12th column\n");
            }
            if(board[3][5].HexType==4){
                printf("4.The manhole in the 4th row & 6th column\n");
            }
            if(board[5][7].HexType==4){
                printf("5.The manhole in the 6th row & 8th column\n");
            }
            if(board[6][2].HexType==4){
                printf("6.The manhole in the 7th row & 3th column\n");
            }
            if(board[8][7].HexType==4){
                printf("7.The manhole in the 9th row & 8th column\n");
            }
            if(board[4][12].HexType==4){
                printf("8.The manhole in the 5th row & 13th column\n");
            }
            int tunnel_choice1;
            scanf("%d", &tunnel_choice1);
            if(tunnel_choice1==1){
                board[jeremy.x][jeremy.y].HexCharacter = 8;
                jeremy.x = 0;
                jeremy.y = 5;
                board[jeremy.x][jeremy.y].HexCharacter = 7;
            }else if(tunnel_choice1==2){
                board[jeremy.x][jeremy.y].HexCharacter = 8;
                jeremy.x = 2;
                jeremy.y = 0;
                board[jeremy.x][jeremy.y].HexCharacter = 7;
            }else if(tunnel_choice1==3){
                board[jeremy.x][jeremy.y].HexCharacter = 8;
                jeremy.x = 1;
                jeremy.y = 11;
                board[jeremy.x][jeremy.y].HexCharacter = 7;
            }else if(tunnel_choice1==4){
                board[jeremy.x][jeremy.y].HexCharacter = 8;
                jeremy.x = 3;
                jeremy.y = 5;
                board[jeremy.x][jeremy.y].HexCharacter = 7;
            }else if(tunnel_choice1==5){
                board[jeremy.x][jeremy.y].HexCharacter = 8;
                jeremy.x = 5;
                jeremy.y = 7;
                board[jeremy.x][jeremy.y].HexCharacter = 7;
            }else if(tunnel_choice1==6){
                board[jeremy.x][jeremy.y].HexCharacter = 8;
                jeremy.x = 5;
                jeremy.y = 2;
                board[jeremy.x][jeremy.y].HexCharacter = 7;
            }else if(tunnel_choice1==7){
                board[jeremy.x][jeremy.y].HexCharacter = 8;
                jeremy.x = 8;
                jeremy.y = 7;
                board[jeremy.x][jeremy.y].HexCharacter = 7;
            }else if(tunnel_choice1==8){
                board[jeremy.x][jeremy.y].HexCharacter = 8;
                jeremy.x = 4;
                jeremy.y = 12;
                board[jeremy.x][jeremy.y].HexCharacter = 7;
            }else{
                //to control user foolishness
            }
            

        }else{
            //to control user foolishness
        }
        }
    }
    return board;
}
hex** Smith(hex** board){
    printf("\nDo you want to use your ability or move first?\n");
    printf("1.Move first\n");
    printf("Other than 1.Use my ability first\n");
    int choice;
    scanf("%d", &choice);
    if(choice==1){
        //system("cls");
        printf("You have to move 1 to 3 hexes Then you can use your ability\n");
        printf("How many moves do you want to do?\n");
        int number_of_moves;
        scanf("%d", &number_of_moves);
        for(int i=0;i<number_of_moves;i++){
        //system("cls");
            printf("Which direction do you want to move for the %dth move?\n", i+1);
            printf("1.Up   ");
            printf("2.Down   ");
            printf("3.UpRight   ");
            printf("4.DownRight   ");
            printf("5.UpLeft   ");
            printf("6.DownLeft   \n");
            if(board[smith.x][smith.y].HexType==4){
                printf("7. Pass Through The Tunnel\n");
            }
        int choice1;
        scanf("%d", &choice1);
        if(choice1==1){
            if(board[(smith.x)-1][smith.y].HexType==0 || board[(smith.x)-1][smith.y].HexType==4 || board[(smith.x)-1][smith.y].HexType==5){
                board[smith.x][smith.y].HexCharacter = 8;
                board[(smith.x)-1][smith.y].HexCharacter = 2;
                smith.x = (smith.x)-1;
            }else{
                //###### try again
            }
        }else if(choice1==2){
            if(board[(smith.x)+1][smith.y].HexType==0 || board[(smith.x)+1][smith.y].HexType==4 || board[(smith.x)+1][smith.y].HexType==5){
                board[smith.x][smith.y].HexCharacter = 8;
                board[(smith.x)+1][smith.y].HexCharacter = 2;
                smith.x = (smith.x)+1;
            }else{
                //#####
            }
        }else if(choice1==3){
            if(smith.y%2==0){
                if(board[smith.x][(smith.y)+1].HexType==0 || board[smith.x][(smith.y)+1].HexType==4 || board[smith.x][(smith.y)+1].HexType==5){
                    board[smith.x][smith.y].HexCharacter = 8;
                    board[smith.x][(smith.y)+1].HexCharacter = 2;
                    smith.y = (smith.y)+1;
                }else{
                    //#####
                }
            }else{
                if(board[(smith.x)-1][(smith.y)+1].HexType==0 || board[(smith.x)-1][(smith.y)+1].HexType==4 || board[(smith.x)-1][(smith.y)+1].HexType==5){
                    board[smith.x][smith.y].HexCharacter = 8;
                    board[(smith.x)-1][(smith.y)+1].HexCharacter = 2;
                    smith.y = (smith.y)+1;
                    smith.x = (smith.x)-1;
                }else{
                    //#####
                }
            }
        }else if(choice1==4){
            if(smith.y%2==0){
                if(board[(smith.x)+1][(smith.y)+1].HexType==0 || board[(smith.x)+1][(smith.y)+1].HexType==4 || board[(smith.x)+1][(smith.y)+1].HexType==5){
                    board[smith.x][smith.y].HexCharacter = 8;
                    board[(smith.x)+1][(smith.y)+1].HexCharacter = 2;
                    smith.y = (smith.y)+1;
                    smith.x = (smith.x)+1;
                }else{
                    //#####
                }
            }else{
                if(board[smith.x][(smith.y)+1].HexType==0 || board[smith.x][(smith.y)+1].HexType==4 || board[smith.x][(smith.y)+1].HexType==5){
                    board[smith.x][smith.y].HexCharacter = 8;
                    board[smith.x][(smith.y)+1].HexCharacter = 2;
                    smith.y = (smith.y)+1;
                }else{
                    //#####
                }
            }
        }else if(choice1==5){
            if(smith.y%2==0){
                if(board[smith.x][(smith.y)-1].HexType==0 || board[smith.x][(smith.y)-1].HexType==4 || board[smith.x][(smith.y)-1].HexType==5){
                    board[smith.x][smith.y].HexCharacter = 8;
                    board[smith.x][(smith.y)-1].HexCharacter = 2;
                    smith.y = (smith.y)-1;
                }else{
                    //#####
                }
            }else{
                if(board[(smith.x)-1][(smith.y)-1].HexType==0 || board[(smith.x)-1][(smith.y)-1].HexType==4 || board[(smith.x)-1][(smith.y)-1].HexType==5){
                    board[smith.x][smith.y].HexCharacter = 8;
                    board[(smith.x)-1][(smith.y)-1].HexCharacter = 2;
                    smith.y = (smith.y)-1;
                    smith.x = (smith.x)-1;
                }else{
                    //#####
                }
            }
        }else if(choice1==6){
            if(smith.y%2==0){
                if(board[(smith.x)+1][(smith.y)-1].HexType==0 || board[(smith.x)+1][(smith.y)-1].HexType==4 || board[(smith.x)+1][(smith.y)-1].HexType==5){
                    board[smith.x][smith.y].HexCharacter = 8;
                    board[(smith.x)+1][(smith.y)-1].HexCharacter = 2;
                    smith.y = (smith.y)-1;
                    smith.x = (smith.x)+1;
                }else{
                    //#####
                }
            }else{
                if(board[smith.x][(smith.y)-1].HexType==0 || board[smith.x][(smith.y)-1].HexType==4 || board[smith.x][(smith.y)-1].HexType==5){
                    board[smith.x][smith.y].HexCharacter = 8;
                    board[smith.x][(smith.y)-1].HexCharacter = 2;
                    smith.y = (smith.y)-1;
                }else{
                    //#####
                }
            }
        }else if(choice1==7 && board[smith.x][smith.y].HexType==4){
            printf("Which manhole do you want to get out of?\n");
            if(board[0][5].HexType==4){
                printf("1.The manhole in the first row & 6th columns\n");
            }
            if(board[2][0].HexType==4){
                printf("2.The manhole in the 3th row & first column\n");
            }
            if(board[1][11].HexType==4){
                printf("3.The manhole in the 2th row & 12th column\n");
            }
            if(board[3][5].HexType==4){
                printf("4.The manhole in the 4th row & 6th column\n");
            }
            if(board[5][7].HexType==4){
                printf("5.The manhole in the 6th row & 8th column\n");
            }
            if(board[6][2].HexType==4){
                printf("6.The manhole in the 7th row & 3th column\n");
            }
            if(board[8][7].HexType==4){
                printf("7.The manhole in the 9th row & 8th column\n");
            }
            if(board[4][12].HexType==4){
                printf("8.The manhole in the 5th row & 13th column\n");
            }
            int tunnel_choice;
            scanf("%d", &tunnel_choice);
            if(tunnel_choice==1){
                board[smith.x][smith.y].HexCharacter = 8;
                jeremy.x = 0;
                jeremy.y = 5;
                board[smith.x][smith.y].HexCharacter = 2;
            }else if(tunnel_choice==2){
                board[smith.x][smith.y].HexCharacter = 8;
                smith.x = 2;
                smith.y = 0;
                board[smith.x][smith.y].HexCharacter = 2;
            }else if(tunnel_choice==3){
                board[smith.x][smith.y].HexCharacter = 8;
                smith.x = 1;
                smith.y = 11;
                board[smith.x][smith.y].HexCharacter = 2;
            }else if(tunnel_choice==4){
                board[smith.x][smith.y].HexCharacter = 8;
                smith.x = 3;
                smith.y = 5;
                board[smith.x][smith.y].HexCharacter = 2;
            }else if(tunnel_choice==5){
                board[smith.x][smith.y].HexCharacter = 8;
                smith.x = 5;
                smith.y = 7;
                board[smith.x][smith.y].HexCharacter = 2;
            }else if(tunnel_choice==6){
                board[smith.x][smith.y].HexCharacter = 8;
                smith.x = 5;
                smith.y = 2;
                board[smith.x][smith.y].HexCharacter = 2;
            }else if(tunnel_choice==7){
                board[smith.x][smith.y].HexCharacter = 8;
                smith.x = 8;
                smith.y = 7;
                board[smith.x][smith.y].HexCharacter = 2;
            }else if(tunnel_choice==8){
                board[smith.x][smith.y].HexCharacter = 8;
                smith.x = 4;
                smith.y = 12;
                board[smith.x][smith.y].HexCharacter = 2;
            }else{
                //to control user foolishness
            }
            

        }else{
            //to control user foolishness
        }
        }
    
        //system("cls");
        printf("Now you have to use your ability\n");
        printf("which lit gaslight do you want to shut off?\n");
        if(board[1][2].HexType==7){
            printf("1.The gaslight in the second row & 3th columns\n");
        }
        if(board[1][5].HexType==7){
            printf("2.The gaslight in the second row & 6th column\n");
        }
        if(board[2][11].HexType==7){
            printf("3.The gaslight in the 3th row & 12th column\n");
        }
        if(board[3][7].HexType==7){
            printf("4.The gaslight in the 4th row & 8th column\n");
        }
        if(board[5][5].HexType==7){
            printf("5.The gaslight in the 6th row & 6th column\n");
        }
        if(board[6][1].HexType==7){
            printf("6.The gaslight in the 7th row & 2th column\n");
        }
        if(board[6][10].HexType==7){
            printf("7.The gaslight in the 7th row & 11th column\n");
        }
        if(board[7][7].HexType==7){
            printf("8.The gaslight in the 8th row & 8th column\n");
        }
        int shut_off_gaslight;
        int save_i, save_j;
        scanf("%d", &shut_off_gaslight);
        if(shut_off_gaslight==1){
            board[1][2].HexType=6;
            save_i=1;
            save_j=2;
        }else if(shut_off_gaslight==2){
            board[1][5].HexType=6;
            save_i=1;
            save_j=5;
        }else if(shut_off_gaslight==3){
            board[2][11].HexType=6;
            save_i=2;
            save_j=11;
        }else if(shut_off_gaslight==4){
            board[3][7].HexType=6;
            save_i=3;
            save_j=7;
        }else if(shut_off_gaslight==5){
            board[5][5].HexType=6;
            save_i=5;
            save_j=5;
        }else if(shut_off_gaslight==6){
            board[6][1].HexType=6;
            save_i=6;
            save_j=1;
        }else if(shut_off_gaslight==7){
            board[6][10].HexType=6;
            save_i=6;
            save_j=10;
        }else if(shut_off_gaslight==8){
            board[7][7].HexType=6;
            save_i=7;
            save_j=7;
        }
        //system("cls");
        printf("which shut off gaslight do you want to lit?\n");
        if(board[1][2].HexType==6 && save_i!=1 && save_j!=2){
            printf("1.The gaslight in the second row & 3th columns\n");
        }
        if(board[1][5].HexType==6 && save_i!=1 && save_j!=5){
            printf("2.The gaslight in the second row & 6th column\n");
        }
        if(board[2][11].HexType==6 && save_i!=2 && save_j!=11){
            printf("3.The gaslight in the 3th row & 12th column\n");
        }
        if(board[3][7].HexType==6 && save_i!=3 && save_j!=7){
            printf("4.The gaslight in the 4th row & 8th column\n");
        }
        if(board[5][5].HexType==6 && save_i!=5 && save_j!=5){
            printf("5.The gaslight in the 6th row & 6th column\n");
        }
        if(board[6][1].HexType==6 && save_i!=6 && save_j!=1){
            printf("6.The gaslight in the 7th row & 2th column\n");
        }
        if(board[6][10].HexType==6 && save_i!=6 && save_j!=10){
            printf("7.The gaslight in the 7th row & 11th column\n");
        }
        if(board[7][7].HexType==6 && save_i!=7 && save_j!=7){
            printf("8.The gaslight in the 8th row & 8th column\n");
        }
        int lit_gaslight;
        scanf("%d", &lit_gaslight);
        if(lit_gaslight==1){
            board[1][2].HexType=7;
        }else if(lit_gaslight==2){
            board[1][5].HexType=7;
        }else if(lit_gaslight==3){
            board[2][11].HexType=7;
        }else if(lit_gaslight==4){
            board[3][7].HexType=7;
        }else if(lit_gaslight==5){
            board[5][5].HexType=7;
        }else if(lit_gaslight==6){
            board[6][1].HexType=7;
        }else if(lit_gaslight==7){
            board[6][10].HexType=7;
        }else if(lit_gaslight==8){
            board[7][7].HexType=7;
        }
        


    }else{     //use ability first
        //system("cls");
        printf("\nwhich lit gaslight do you want to shut off?\n");
        if(board[1][2].HexType==7){
            printf("1.The gaslight in the second row & 3th columns\n");
        }
        if(board[1][5].HexType==7){
            printf("2.The gaslight in the second row & 6th column\n");
        }
        if(board[2][11].HexType==7){
            printf("3.The gaslight in the 3th row & 12th column\n");
        }
        if(board[3][7].HexType==7){
            printf("4.The gaslight in the 4th row & 8th column\n");
        }
        if(board[5][5].HexType==7){
            printf("5.The gaslight in the 6th row & 6th column\n");
        }
        if(board[6][1].HexType==7){
            printf("6.The gaslight in the 7th row & 2th column\n");
        }
        if(board[6][10].HexType==7){
            printf("7.The gaslight in the 7th row & 11th column\n");
        }
        if(board[7][7].HexType==7){
            printf("8.The gaslight in the 8th row & 8th column\n");
        }
        int shut_off_gaslight1;
        int save_i, save_j;
        scanf("%d", &shut_off_gaslight1);
        if(shut_off_gaslight1==1){
            board[1][2].HexType=6;
            save_i=1;
            save_j=2;
        }else if(shut_off_gaslight1==2){
            board[1][5].HexType=6;
            save_i=1;
            save_j=5;
        }else if(shut_off_gaslight1==3){
            board[2][11].HexType=6;
            save_i=2;
            save_j=11;
        }else if(shut_off_gaslight1==4){
            board[3][7].HexType=6;
            save_i=3;
            save_j=7;
        }else if(shut_off_gaslight1==5){
            board[5][5].HexType=6;
            save_i=5;
            save_j=5;
        }else if(shut_off_gaslight1==6){
            board[6][1].HexType=6;
            save_i=6;
            save_j=1;
        }else if(shut_off_gaslight1==7){
            board[6][10].HexType=6;
            save_i=6;
            save_j=10;
        }else if(shut_off_gaslight1==8){
            board[7][7].HexType=6;
            save_i=7;
            save_j=7;
        }
        //system("cls");
        printf("which shut off gaslight do you want to lit?\n");
        if(board[1][2].HexType==6 && save_i!=1 && save_j!=2){
            printf("1.The gaslight in the second row & 3th columns\n");
        }
        if(board[1][5].HexType==6 && save_i!=1 && save_j!=5){
            printf("2.The gaslight in the second row & 6th column\n");
        }
        if(board[2][11].HexType==6 && save_i!=2 && save_j!=11){
            printf("3.The gaslight in the 3th row & 12th column\n");
        }
        if(board[3][7].HexType==6 && save_i!=3 && save_j!=7){
            printf("4.The gaslight in the 4th row & 8th column\n");
        }
        if(board[5][5].HexType==6 && save_i!=5 && save_j!=5){
            printf("5.The gaslight in the 6th row & 6th column\n");
        }
        if(board[6][1].HexType==6 && save_i!=6 && save_j!=1){
            printf("6.The gaslight in the 7th row & 2th column\n");
        }
        if(board[6][10].HexType==6 && save_i!=6 && save_j!=10){
            printf("7.The gaslight in the 7th row & 11th column\n");
        }
        if(board[7][7].HexType==6 && save_i!=7 && save_j!=7){
            printf("8.The gaslight in the 8th row & 8th column\n");
        }
        int lit_gaslight1;
        scanf("%d", &lit_gaslight1);
        if(lit_gaslight1==1){
            board[1][2].HexType=7;
        }else if(lit_gaslight1==2){
            board[1][5].HexType=7;
        }else if(lit_gaslight1==3){
            board[2][11].HexType=7;
        }else if(lit_gaslight1==4){
            board[3][7].HexType=7;
        }else if(lit_gaslight1==5){
            board[5][5].HexType=7;
        }else if(lit_gaslight1==6){
            board[6][1].HexType=7;
        }else if(lit_gaslight1==7){
            board[6][10].HexType=7;
        }else if(lit_gaslight1==8){
            board[7][7].HexType=7;
        }
        //system("cls");
        printf("Now you have to move 1 to 3 hexes");
        printf("How many moves do you want to do?\n");
        int number_of_moves;
        scanf("%d", &number_of_moves);
        for(int i=0;i<number_of_moves;i++){
            //system("cls");
        printf("Which direction do you want to move for the %dth move?\n", i+1);
        printf("1.Up   ");
        printf("2.Down   ");
        printf("3.UpRight   ");
        printf("4.DownRight   ");
        printf("5.UpLeft   ");
        printf("6.DownLeft   \n");
        if(board[smith.x][smith.y].HexType==4){
            printf("7. Pass Through The Tunnel\n");
        }
        int choice2;
        scanf("%d", &choice2);
        if(choice2==1){
            if(board[(smith.x)-1][smith.y].HexType==0 || board[(smith.x)-1][smith.y].HexType==4 || board[(smith.x)-1][smith.y].HexType==5){
                board[smith.x][smith.y].HexCharacter = 8;
                board[(smith.x)-1][smith.y].HexCharacter = 2;
                smith.x = (smith.x)-1;
            }else{
                //###### try again
            }
        }else if(choice2==2){
            if(board[(smith.x)+1][smith.y].HexType==0 || board[(smith.x)+1][smith.y].HexType==4 || board[(smith.x)+1][smith.y].HexType==5){
                board[smith.x][smith.y].HexCharacter = 8;
                board[(smith.x)+1][smith.y].HexCharacter = 2;
                smith.x = (smith.x)+1;
            }else{
                //#####
            }
        }else if(choice2==3){
            if(smith.y%2==0){
                if(board[smith.x][(smith.y)+1].HexType==0 || board[smith.x][(smith.y)+1].HexType==4 || board[smith.x][(smith.y)+1].HexType==5){
                    board[smith.x][smith.y].HexCharacter = 8;
                    board[smith.x][(smith.y)+1].HexCharacter = 2;
                    smith.y = (smith.y)+1;
                }else{
                    //#####
                }
            }else{
                if(board[(smith.x)-1][(smith.y)+1].HexType==0 || board[(smith.x)-1][(smith.y)+1].HexType==4 || board[(smith.x)-1][(smith.y)+1].HexType==5){
                    board[smith.x][smith.y].HexCharacter = 8;
                    board[(smith.x)-1][(smith.y)+1].HexCharacter = 2;
                    smith.y = (smith.y)+1;
                    smith.x = (smith.x)-1;
                }else{
                    //#####
                }
            }
        }else if(choice2==4){
            if(smith.y%2==0){
                if(board[(smith.x)+1][(smith.y)+1].HexType==0 || board[(smith.x)+1][(smith.y)+1].HexType==4 || board[(smith.x)+1][(smith.y)+1].HexType==5){
                    board[smith.x][smith.y].HexCharacter = 8;
                    board[(smith.x)+1][(smith.y)+1].HexCharacter = 2;
                    smith.y = (smith.y)+1;
                    smith.x = (smith.x)+1;
                }else{
                    //#####
                }
            }else{
                if(board[smith.x][(smith.y)+1].HexType==0 || board[smith.x][(smith.y)+1].HexType==4 || board[smith.x][(smith.y)+1].HexType==5){
                    board[smith.x][smith.y].HexCharacter = 8;
                    board[smith.x][(smith.y)+1].HexCharacter = 2;
                    smith.y = (smith.y)+1;
                }else{
                    //#####
                }
            }
        }else if(choice2==5){
            if(smith.y%2==0){
                if(board[smith.x][(smith.y)-1].HexType==0 || board[smith.x][(smith.y)-1].HexType==4 || board[smith.x][(smith.y)-1].HexType==5){
                    board[smith.x][smith.y].HexCharacter = 8;
                    board[smith.x][(smith.y)-1].HexCharacter = 2;
                    smith.y = (smith.y)-1;
                }else{
                    //#####
                }
            }else{
                if(board[(smith.x)-1][(smith.y)-1].HexType==0 || board[(smith.x)-1][(smith.y)-1].HexType==4 || board[(smith.x)-1][(smith.y)-1].HexType==5){
                    board[smith.x][smith.y].HexCharacter = 8;
                    board[(smith.x)-1][(smith.y)-1].HexCharacter = 2;
                    smith.y = (smith.y)-1;
                    smith.x = (smith.x)-1;
                }else{
                    //#####
                }
            }
        }else if(choice2==6){
            if(smith.y%2==0){
                if(board[(smith.x)+1][(smith.y)-1].HexType==0 || board[(smith.x)+1][(smith.y)-1].HexType==4 || board[(smith.x)+1][(smith.y)-1].HexType==5){
                    board[smith.x][smith.y].HexCharacter = 8;
                    board[(smith.x)+1][(smith.y)-1].HexCharacter = 2;
                    smith.y = (smith.y)-1;
                    smith.x = (smith.x)+1;
                }else{
                    //#####
                }
            }else{
                if(board[smith.x][(smith.y)-1].HexType==0 || board[smith.x][(smith.y)-1].HexType==4 || board[smith.x][(smith.y)-1].HexType==5){
                    board[smith.x][smith.y].HexCharacter = 8;
                    board[smith.x][(smith.y)-1].HexCharacter = 2;
                    smith.y = (smith.y)-1;
                }else{
                    //#####
                }
            }
        }else if(choice2==7 && board[smith.x][smith.y].HexType==4){
            printf("Which manhole do you want to get out of?\n");
            if(board[0][5].HexType==4){
                printf("1.The manhole in the first row & 6th columns\n");
            }
            if(board[2][0].HexType==4){
                printf("2.The manhole in the 3th row & first column\n");
            }
            if(board[1][11].HexType==4){
                printf("3.The manhole in the 2th row & 12th column\n");
            }
            if(board[3][5].HexType==4){
                printf("4.The manhole in the 4th row & 6th column\n");
            }
            if(board[5][7].HexType==4){
                printf("5.The manhole in the 6th row & 8th column\n");
            }
            if(board[6][2].HexType==4){
                printf("6.The manhole in the 7th row & 3th column\n");
            }
            if(board[8][7].HexType==4){
                printf("7.The manhole in the 9th row & 8th column\n");
            }
            if(board[4][12].HexType==4){
                printf("8.The manhole in the 5th row & 13th column\n");
            }
            int tunnel_choice1;
            scanf("%d", &tunnel_choice1);
            if(tunnel_choice1==1){
                board[smith.x][smith.y].HexCharacter = 8;
                smith.x = 0;
                smith.y = 5;
                board[smith.x][smith.y].HexCharacter = 2;
            }else if(tunnel_choice1==2){
                board[smith.x][smith.y].HexCharacter = 8;
                smith.x = 2;
                smith.y = 0;
                board[smith.x][smith.y].HexCharacter = 2;
            }else if(tunnel_choice1==3){
                board[smith.x][smith.y].HexCharacter = 8;
                smith.x = 1;
                smith.y = 11;
                board[smith.x][smith.y].HexCharacter = 2;
            }else if(tunnel_choice1==4){
                board[smith.x][smith.y].HexCharacter = 8;
                smith.x = 3;
                smith.y = 5;
                board[smith.x][smith.y].HexCharacter = 2;
            }else if(tunnel_choice1==5){
                board[smith.x][smith.y].HexCharacter = 8;
                smith.x = 5;
                smith.y = 7;
                board[smith.x][smith.y].HexCharacter = 2;
            }else if(tunnel_choice1==6){
                board[smith.x][smith.y].HexCharacter = 8;
                smith.x = 5;
                smith.y = 2;
                board[smith.x][smith.y].HexCharacter = 2;
            }else if(tunnel_choice1==7){
                board[smith.x][smith.y].HexCharacter = 8;
                smith.x = 8;
                smith.y = 7;
                board[smith.x][smith.y].HexCharacter = 2;
            }else if(tunnel_choice1==8){
                board[smith.x][smith.y].HexCharacter = 8;
                smith.x = 4;
                smith.y = 12;
                board[smith.x][smith.y].HexCharacter = 2;
            }else{
                //to control user foolishness
            }
            

        }else{
            //to control user foolishness
        }
        }
    }
    return board;
}
hex** William(hex** board){
    printf("\nDo you want to use your ability or Do you want to move?");
    printf("\n1.Move");
    printf("\nOther than 1.Use your ability\n");
    int choice;
    scanf("%d", &choice);
    if(choice==1){
        printf("You have to move 1 to 3 hexes\n");
        printf("How many moves do you want to do?");
        int number_of_moves;
        scanf("%d", &number_of_moves);
        for(int i=0;i<number_of_moves;i++){
            //system("cls");
            printf("Which direction do you want to move for the %dth move?\n", i+1);
            printf("1.Up   ");
            printf("2.Down   ");
            printf("3.UpRight   ");
            printf("4.DownRight   ");
            printf("5.UpLeft   ");
            printf("6.DownLeft   \n");
            if(board[william.x][william.y].HexType==4){
                printf("7. Pass Through The Tunnel\n");
            }
        int choice1;
        scanf("%d", &choice1);
        if(choice1==1){
            if(board[(william.x)-1][william.y].HexType==0 || board[(william.x)-1][william.y].HexType==4 || board[(william.x)-1][william.y].HexType==5){
                board[william.x][william.y].HexCharacter = 8;
                board[(william.x)-1][william.y].HexCharacter = 6;
                william.x = (william.x)-1;
            }else{
                //###### try again
            }
        }else if(choice1==2){
            if(board[(william.x)+1][william.y].HexType==0 || board[(william.x)+1][william.y].HexType==4 || board[(william.x)+1][william.y].HexType==5){
                board[william.x][william.y].HexCharacter = 8;
                board[(william.x)+1][william.y].HexCharacter = 6;
                william.x = (william.x)+1;
            }else{
                //#####
            }
        }else if(choice1==3){
            if(william.y%2==0){
                if(board[william.x][(william.y)+1].HexType==0 || board[william.x][(william.y)+1].HexType==4 || board[william.x][(william.y)+1].HexType==5){
                    board[william.x][william.y].HexCharacter = 8;
                    board[william.x][(william.y)+1].HexCharacter = 6;
                    william.y = (william.y)+1;
                }else{
                    //#####
                }
            }else{
                if(board[(william.x)-1][(william.y)+1].HexType==0 || board[(william.x)-1][(william.y)+1].HexType==4 || board[(william.x)-1][(william.y)+1].HexType==5){
                    board[william.x][william.y].HexCharacter = 8;
                    board[(william.x)-1][(william.y)+1].HexCharacter = 6;
                    william.y = (william.y)+1;
                    william.x = (william.x)-1;
                }else{
                    //#####
                }
            }
        }else if(choice1==4){
            if(william.y%2==0){
                if(board[(william.x)+1][(william.y)+1].HexType==0 || board[(william.x)+1][(william.y)+1].HexType==4 || board[(william.x)+1][(william.y)+1].HexType==5){
                    board[william.x][william.y].HexCharacter = 8;
                    board[(william.x)+1][(william.y)+1].HexCharacter = 6;
                    william.y = (william.y)+1;
                    william.x = (william.x)+1;
                }else{
                    //#####
                }
            }else{
                if(board[william.x][(william.y)+1].HexType==0 || board[william.x][(william.y)+1].HexType==4 || board[william.x][(william.y)+1].HexType==5){
                    board[william.x][william.y].HexCharacter = 8;
                    board[william.x][(william.y)+1].HexCharacter = 6;
                    william.y = (william.y)+1;
                }else{
                    //#####
                }
            }
        }else if(choice1==5){
            if(william.y%2==0){
                if(board[william.x][(william.y)-1].HexType==0 || board[william.x][(william.y)-1].HexType==4 || board[william.x][(william.y)-1].HexType==5){
                    board[william.x][william.y].HexCharacter = 8;
                    board[william.x][(william.y)-1].HexCharacter = 6;
                    william.y = (william.y)-1;
                }else{
                    //#####
                }
            }else{
                if(board[(william.x)-1][(william.y)-1].HexType==0 || board[(william.x)-1][(william.y)-1].HexType==4 || board[(william.x)-1][(william.y)-1].HexType==5){
                    board[william.x][william.y].HexCharacter = 8;
                    board[(william.x)-1][(william.y)-1].HexCharacter = 6;
                    william.y = (william.y)-1;
                    william.x = (william.x)-1;
                }else{
                    //#####
                }
            }
        }else if(choice1==6){
            if(william.y%2==0){
                if(board[(william.x)+1][(william.y)-1].HexType==0 || board[(william.x)+1][(william.y)-1].HexType==4 || board[(william.x)+1][(william.y)-1].HexType==5){
                    board[william.x][william.y].HexCharacter = 8;
                    board[(william.x)+1][(william.y)-1].HexCharacter = 6;
                    william.y = (william.y)-1;
                    william.x = (william.x)+1;
                }else{
                    //#####
                }
            }else{
                if(board[william.x][(william.y)-1].HexType==0 || board[william.x][(william.y)-1].HexType==4 || board[william.x][(william.y)-1].HexType==5){
                    board[william.x][william.y].HexCharacter = 8;
                    board[william.x][(william.y)-1].HexCharacter = 6;
                    william.y = (william.y)-1;
                }else{
                    //#####
                }
            }
        }else if(choice1==7 && board[william.x][william.y].HexType==4){
            printf("Which manhole do you want to get out of?\n");
            if(board[0][5].HexType==4){
                printf("1.The manhole in the first row & 6th columns\n");
            }
            if(board[2][0].HexType==4){
                printf("2.The manhole in the 3th row & first column\n");
            }
            if(board[1][11].HexType==4){
                printf("3.The manhole in the 2th row & 12th column\n");
            }
            if(board[3][5].HexType==4){
                printf("4.The manhole in the 4th row & 6th column\n");
            }
            if(board[5][7].HexType==4){
                printf("5.The manhole in the 6th row & 8th column\n");
            }
            if(board[6][2].HexType==4){
                printf("6.The manhole in the 7th row & 3th column\n");
            }
            if(board[8][7].HexType==4){
                printf("7.The manhole in the 9th row & 8th column\n");
            }
            if(board[4][12].HexType==4){
                printf("8.The manhole in the 5th row & 13th column\n");
            }
            int tunnel_choice;
            scanf("%d", &tunnel_choice);
            if(tunnel_choice==1){
                board[william.x][william.y].HexCharacter = 8;
                jeremy.x = 0;
                jeremy.y = 5;
                board[william.x][william.y].HexCharacter = 6;
            }else if(tunnel_choice==2){
                board[william.x][william.y].HexCharacter = 8;
                william.x = 2;
                william.y = 0;
                board[william.x][william.y].HexCharacter = 6;
            }else if(tunnel_choice==3){
                board[william.x][william.y].HexCharacter = 8;
                william.x = 1;
                william.y = 11;
                board[william.x][william.y].HexCharacter = 6;
            }else if(tunnel_choice==4){
                board[william.x][william.y].HexCharacter = 8;
                william.x = 3;
                william.y = 5;
                board[william.x][william.y].HexCharacter = 6;
            }else if(tunnel_choice==5){
                board[william.x][william.y].HexCharacter = 8;
                william.x = 5;
                william.y = 7;
                board[william.x][william.y].HexCharacter = 6;
            }else if(tunnel_choice==6){
                board[william.x][william.y].HexCharacter = 8;
                william.x = 5;
                william.y = 2;
                board[william.x][william.y].HexCharacter = 6;
            }else if(tunnel_choice==7){
                board[william.x][william.y].HexCharacter = 8;
                william.x = 8;
                william.y = 7;
                board[william.x][william.y].HexCharacter = 6;
            }else if(tunnel_choice==8){
                board[william.x][william.y].HexCharacter = 8;
                william.x = 4;
                william.y = 12;
                board[william.x][william.y].HexCharacter = 6;
            }else{
                //to control user foolishness
            }
            

        }else{
            //to control user foolishness
        }
        
        }
    }else{
        printf("\nWho do you want to exchange your location with?\n");
        printf("1.Sherlock Holmes   ");
        printf("2.John H. Watson   ");
        printf("3.John Smith   ");
        printf("4.Inspector Lestrade   ");
        printf("\n5.Miss Stealthy   ");
        printf("6.Sergeant Goodley   ");
        printf("Other than this.Jeremy Bert\n");
        int choice;
        scanf("%d", &choice);
        if(choice==1){
            board[william.x][william.y].HexCharacter = 0;
            board[sherlock.x][sherlock.y].HexCharacter = 6;
        }else if(choice==2){
            board[william.x][william.y].HexCharacter = 1;
            board[watson.x][watson.y].HexCharacter = 6;
        }else if(choice==3){
            board[william.x][william.y].HexCharacter = 2;
            board[smith.x][smith.y].HexCharacter = 6;
        }else if(choice==4){
            board[william.x][william.y].HexCharacter = 3;
            board[lestrade.x][lestrade.y].HexCharacter = 6;
        }else if(choice==5){
            board[william.x][william.y].HexCharacter = 4;
            board[stealthy.x][stealthy.y].HexCharacter = 6;
        }else if(choice==6){
            board[william.x][william.y].HexCharacter = 5;
            board[goodley.x][goodley.y].HexCharacter = 6;
        }else{
            board[william.x][william.y].HexCharacter = 7;
            board[jeremy.x][jeremy.y].HexCharacter = 6;
        }
    }
    return board;
}
hex** Lestrade(hex** board){
    printf("\nDo you want to use your ability or move first?\n");
    printf("1.Move first\n");
    printf("Other than 1.Use my ability first\n");
    int choice;
    scanf("%d", &choice);
    if(choice==1){
        //system("cls");
        printf("You have to move 1 to 3 hexes Then you can use your ability\n");
        printf("How many moves do you want to do?\n");
        int number_of_moves;
        scanf("%d", &number_of_moves);
        for(int i=0;i<number_of_moves;i++){
        //system("cls");
            printf("Which direction do you want to move for the %dth move?\n", i+1);
            printf("1.Up   ");
            printf("2.Down   ");
            printf("3.UpRight   ");
            printf("4.DownRight   ");
            printf("5.UpLeft   ");
            printf("6.DownLeft   \n");
            if(board[lestrade.x][lestrade.y].HexType==4){
                printf("7. Pass Through The Tunnel\n");
            }
        int choice1;
        scanf("%d", &choice1);
        if(choice1==1){
            if(board[(lestrade.x)-1][lestrade.y].HexType==0 || board[(lestrade.x)-1][lestrade.y].HexType==4 || board[(lestrade.x)-1][lestrade.y].HexType==5){
                board[lestrade.x][lestrade.y].HexCharacter = 8;
                board[(lestrade.x)-1][lestrade.y].HexCharacter = 3;
                lestrade.x = (lestrade.x)-1;
            }else{
                //###### try again
            }
        }else if(choice1==2){
            if(board[(lestrade.x)+1][lestrade.y].HexType==0 || board[(lestrade.x)+1][lestrade.y].HexType==4 || board[(lestrade.x)+1][lestrade.y].HexType==5){
                board[lestrade.x][lestrade.y].HexCharacter = 8;
                board[(lestrade.x)+1][lestrade.y].HexCharacter = 3;
                lestrade.x = (lestrade.x)+1;
            }else{
                //#####
            }
        }else if(choice1==3){
            if(lestrade.y%2==0){
                if(board[lestrade.x][(lestrade.y)+1].HexType==0 || board[lestrade.x][(lestrade.y)+1].HexType==4 || board[lestrade.x][(lestrade.y)+1].HexType==5){
                    board[lestrade.x][lestrade.y].HexCharacter = 8;
                    board[lestrade.x][(lestrade.y)+1].HexCharacter = 3;
                    lestrade.y = (lestrade.y)+1;
                }else{
                    //#####
                }
            }else{
                if(board[(lestrade.x)-1][(lestrade.y)+1].HexType==0 || board[(lestrade.x)-1][(lestrade.y)+1].HexType==4 || board[(lestrade.x)-1][(lestrade.y)+1].HexType==5){
                    board[lestrade.x][lestrade.y].HexCharacter = 8;
                    board[(lestrade.x)-1][(lestrade.y)+1].HexCharacter = 3;
                    lestrade.y = (lestrade.y)+1;
                    lestrade.x = (lestrade.x)-1;
                }else{
                    //#####
                }
            }
        }else if(choice1==4){
            if(lestrade.y%2==0){
                if(board[(lestrade.x)+1][(lestrade.y)+1].HexType==0 || board[(lestrade.x)+1][(lestrade.y)+1].HexType==4 || board[(lestrade.x)+1][(lestrade.y)+1].HexType==5){
                    board[lestrade.x][lestrade.y].HexCharacter = 8;
                    board[(lestrade.x)+1][(lestrade.y)+1].HexCharacter = 3;
                    lestrade.y = (lestrade.y)+1;
                    lestrade.x = (lestrade.x)+1;
                }else{
                    //#####
                }
            }else{
                if(board[lestrade.x][(lestrade.y)+1].HexType==0 || board[lestrade.x][(lestrade.y)+1].HexType==4 || board[lestrade.x][(lestrade.y)+1].HexType==5){
                    board[lestrade.x][lestrade.y].HexCharacter = 8;
                    board[lestrade.x][(lestrade.y)+1].HexCharacter = 3;
                    lestrade.y = (lestrade.y)+1;
                }else{
                    //#####
                }
            }
        }else if(choice1==5){
            if(lestrade.y%2==0){
                if(board[lestrade.x][(lestrade.y)-1].HexType==0 || board[lestrade.x][(lestrade.y)-1].HexType==4 || board[lestrade.x][(lestrade.y)-1].HexType==5){
                    board[lestrade.x][lestrade.y].HexCharacter = 8;
                    board[lestrade.x][(lestrade.y)-1].HexCharacter = 3;
                    lestrade.y = (lestrade.y)-1;
                }else{
                    //#####
                }
            }else{
                if(board[(lestrade.x)-1][(lestrade.y)-1].HexType==0 || board[(lestrade.x)-1][(lestrade.y)-1].HexType==4 || board[(lestrade.x)-1][(lestrade.y)-1].HexType==5){
                    board[lestrade.x][lestrade.y].HexCharacter = 8;
                    board[(lestrade.x)-1][(lestrade.y)-1].HexCharacter = 3;
                    lestrade.y = (lestrade.y)-1;
                    lestrade.x = (lestrade.x)-1;
                }else{
                    //#####
                }
            }
        }else if(choice1==6){
            if(lestrade.y%2==0){
                if(board[(lestrade.x)+1][(lestrade.y)-1].HexType==0 || board[(lestrade.x)+1][(lestrade.y)-1].HexType==4 || board[(lestrade.x)+1][(lestrade.y)-1].HexType==5){
                    board[lestrade.x][lestrade.y].HexCharacter = 8;
                    board[(lestrade.x)+1][(lestrade.y)-1].HexCharacter = 3;
                    lestrade.y = (lestrade.y)-1;
                    lestrade.x = (lestrade.x)+1;
                }else{
                    //#####
                }
            }else{
                if(board[lestrade.x][(lestrade.y)-1].HexType==0 || board[lestrade.x][(lestrade.y)-1].HexType==4 || board[lestrade.x][(lestrade.y)-1].HexType==5){
                    board[lestrade.x][lestrade.y].HexCharacter = 8;
                    board[lestrade.x][(lestrade.y)-1].HexCharacter = 3;
                    lestrade.y = (lestrade.y)-1;
                }else{
                    //#####
                }
            }
        }else if(choice1==7 && board[lestrade.x][lestrade.y].HexType==4){
            printf("Which manhole do you want to get out of?\n");
            if(board[0][5].HexType==4){
                printf("1.The manhole in the first row & 6th columns\n");
            }
            if(board[2][0].HexType==4){
                printf("2.The manhole in the 3th row & first column\n");
            }
            if(board[1][11].HexType==4){
                printf("3.The manhole in the 2th row & 12th column\n");
            }
            if(board[3][5].HexType==4){
                printf("4.The manhole in the 4th row & 6th column\n");
            }
            if(board[5][7].HexType==4){
                printf("5.The manhole in the 6th row & 8th column\n");
            }
            if(board[6][2].HexType==4){
                printf("6.The manhole in the 7th row & 3th column\n");
            }
            if(board[8][7].HexType==4){
                printf("7.The manhole in the 9th row & 8th column\n");
            }
            if(board[4][12].HexType==4){
                printf("8.The manhole in the 5th row & 13th column\n");
            }
            int tunnel_choice;
            scanf("%d", &tunnel_choice);
            if(tunnel_choice==1){
                board[lestrade.x][lestrade.y].HexCharacter = 8;
                jeremy.x = 0;
                jeremy.y = 5;
                board[lestrade.x][lestrade.y].HexCharacter = 3;
            }else if(tunnel_choice==2){
                board[lestrade.x][lestrade.y].HexCharacter = 8;
                lestrade.x = 2;
                lestrade.y = 0;
                board[lestrade.x][lestrade.y].HexCharacter = 3;
            }else if(tunnel_choice==3){
                board[lestrade.x][lestrade.y].HexCharacter = 8;
                lestrade.x = 1;
                lestrade.y = 11;
                board[lestrade.x][lestrade.y].HexCharacter = 3;
            }else if(tunnel_choice==4){
                board[lestrade.x][lestrade.y].HexCharacter = 8;
                lestrade.x = 3;
                lestrade.y = 5;
                board[lestrade.x][lestrade.y].HexCharacter = 3;
            }else if(tunnel_choice==5){
                board[lestrade.x][lestrade.y].HexCharacter = 8;
                lestrade.x = 5;
                lestrade.y = 7;
                board[lestrade.x][lestrade.y].HexCharacter = 3;
            }else if(tunnel_choice==6){
                board[lestrade.x][lestrade.y].HexCharacter = 8;
                lestrade.x = 5;
                lestrade.y = 2;
                board[lestrade.x][lestrade.y].HexCharacter = 3;
            }else if(tunnel_choice==7){
                board[lestrade.x][lestrade.y].HexCharacter = 8;
                lestrade.x = 8;
                lestrade.y = 7;
                board[lestrade.x][lestrade.y].HexCharacter = 3;
            }else if(tunnel_choice==8){
                board[lestrade.x][lestrade.y].HexCharacter = 8;
                lestrade.x = 4;
                lestrade.y = 12;
                board[lestrade.x][lestrade.y].HexCharacter = 3;
            }else{
                //to control user foolishness
            }
            

        }else{
            //to control user foolishness
        }
        }
    
        //system("cls");
        printf("Now you have to use your ability\n");
        printf("Which exit do you want to block?\n");
        if(board[0][0].HexType==1 && board[0][1].HexType==1){
            printf("1.The Top Right Exit\n");
        }
        if(board[0][11].HexType==1 && board[0][12].HexType==1){
            printf("2.The Top Left Exit\n");
        }
        if(board[7][0].HexType==1 && board[8][1].HexType==1){
            printf("3.The Lower Right Exit\n");
        }
        if(board[7][12].HexType==1 && board[8][11].HexType==1){
            printf("4.The Lower Left Exit\n");
        }
        int block_exit;
        scanf("%d", &block_exit);
        if(block_exit==1){
            board[0][0].HexType=3;
            board[0][1].HexType=3;
        }else if(block_exit==2){
            board[0][11].HexType=3;
            board[0][12].HexType=3;
        }else if(block_exit==3){
            board[7][0].HexType=3;
            board[8][1].HexType=3;
        }else if(block_exit==4){
            board[7][12].HexType=3;
            board[8][11].HexType=3;
        }
        printf("\nWhich exit do you want to free?\n");
        if(board[0][0].HexType==3 && board[0][1].HexType==3){
            printf("1.The Top Right Exit\n");
        }
        if(board[0][11].HexType==3 && board[0][12].HexType==3){
            printf("2.The Top Left Exit\n");
        }
        if(board[7][0].HexType==3 && board[8][1].HexType==3){
            printf("3.The Lower Right Exit\n");
        }
        if(board[7][12].HexType==3 && board[8][11].HexType==3){
            printf("4.The Lower Left Exit\n");
        }
        int free_exit;
        scanf("%d", &free_exit);
        if(free_exit==1){
            board[0][0].HexType=1;
            board[0][1].HexType=1;
        }else if(free_exit==2){
            board[0][11].HexType=1;
            board[0][12].HexType=1;
        }else if(free_exit==3){
            board[7][0].HexType=1;
            board[8][1].HexType=1;
        }else if(free_exit==4){
            board[7][12].HexType=1;
            board[8][11].HexType=1;
        }


    }else{     //use ability first
        //system("cls");
        printf("\nWhich exit do you want to block?\n");
        if(board[0][0].HexType==1 && board[0][1].HexType==1){
            printf("1.The Top Right Exit\n");
        }
        if(board[0][11].HexType==1 && board[0][12].HexType==1){
            printf("2.The Top Left Exit\n");
        }
        if(board[7][0].HexType==1 && board[8][1].HexType==1){
            printf("3.The Lower Right Exit\n");
        }
        if(board[7][12].HexType==1 && board[8][11].HexType==1){
            printf("4.The Lower Left Exit\n");
        }
        int block_exit;
        scanf("%d", &block_exit);
        if(block_exit==1){
            board[0][0].HexType=3;
            board[0][1].HexType=3;
        }else if(block_exit==2){
            board[0][11].HexType=3;
            board[0][12].HexType=3;
        }else if(block_exit==3){
            board[7][0].HexType=3;
            board[8][1].HexType=3;
        }else if(block_exit==4){
            board[7][12].HexType=3;
            board[8][11].HexType=3;
        }
        printf("\nWhich exit do you want to free?\n");
        if(board[0][0].HexType==3 && board[0][1].HexType==3){
            printf("1.The Top Right Exit\n");
        }
        if(board[0][11].HexType==3 && board[0][12].HexType==3){
            printf("2.The Top Left Exit\n");
        }
        if(board[7][0].HexType==3 && board[8][1].HexType==3){
            printf("3.The Lower Right Exit\n");
        }
        if(board[7][12].HexType==3 && board[8][11].HexType==3){
            printf("4.The Lower Left Exit\n");
        }
        int free_exit;
        scanf("%d", &free_exit);
        if(free_exit==1){
            board[0][0].HexType=1;
            board[0][1].HexType=1;
        }else if(free_exit==2){
            board[0][11].HexType=1;
            board[0][12].HexType=1;
        }else if(free_exit==3){
            board[7][0].HexType=1;
            board[8][1].HexType=1;
        }else if(free_exit==4){
            board[7][12].HexType=1;
            board[8][11].HexType=1;
        }
        //system("cls");
        printf("\nNow you have to move 1 to 3 hexes\n");
        printf("How many moves do you want to do?\n");
        int number_of_moves;
        scanf("%d", &number_of_moves);
        for(int i=0;i<number_of_moves;i++){
            //system("cls");
        printf("Which direction do you want to move for the %dth move?\n", i+1);
        printf("1.Up   ");
        printf("2.Down   ");
        printf("3.UpRight   ");
        printf("4.DownRight   ");
        printf("5.UpLeft   ");
        printf("6.DownLeft   \n");
        if(board[lestrade.x][lestrade.y].HexType==4){
            printf("7. Pass Through The Tunnel\n");
        }
        int choice2;
        scanf("%d", &choice2);
        if(choice2==1){
            if(board[(lestrade.x)-1][lestrade.y].HexType==0 || board[(lestrade.x)-1][lestrade.y].HexType==4 || board[(lestrade.x)-1][lestrade.y].HexType==5){
                board[lestrade.x][lestrade.y].HexCharacter = 8;
                board[(lestrade.x)-1][lestrade.y].HexCharacter = 3;
                lestrade.x = (lestrade.x)-1;
            }else{
                //###### try again
            }
        }else if(choice2==2){
            if(board[(lestrade.x)+1][lestrade.y].HexType==0 || board[(lestrade.x)+1][lestrade.y].HexType==4 || board[(lestrade.x)+1][lestrade.y].HexType==5){
                board[lestrade.x][lestrade.y].HexCharacter = 8;
                board[(lestrade.x)+1][lestrade.y].HexCharacter = 3;
                lestrade.x = (lestrade.x)+1;
            }else{
                //#####
            }
        }else if(choice2==3){
            if(lestrade.y%2==0){
                if(board[lestrade.x][(lestrade.y)+1].HexType==0 || board[lestrade.x][(lestrade.y)+1].HexType==4 || board[lestrade.x][(lestrade.y)+1].HexType==5){
                    board[lestrade.x][lestrade.y].HexCharacter = 8;
                    board[lestrade.x][(lestrade.y)+1].HexCharacter = 3;
                    lestrade.y = (lestrade.y)+1;
                }else{
                    //#####
                }
            }else{
                if(board[(lestrade.x)-1][(lestrade.y)+1].HexType==0 || board[(lestrade.x)-1][(lestrade.y)+1].HexType==4 || board[(lestrade.x)-1][(lestrade.y)+1].HexType==5){
                    board[lestrade.x][lestrade.y].HexCharacter = 8;
                    board[(lestrade.x)-1][(lestrade.y)+1].HexCharacter = 3;
                    lestrade.y = (lestrade.y)+1;
                    lestrade.x = (lestrade.x)-1;
                }else{
                    //#####
                }
            }
        }else if(choice2==4){
            if(lestrade.y%2==0){
                if(board[(lestrade.x)+1][(lestrade.y)+1].HexType==0 || board[(lestrade.x)+1][(lestrade.y)+1].HexType==4 || board[(lestrade.x)+1][(lestrade.y)+1].HexType==5){
                    board[lestrade.x][lestrade.y].HexCharacter = 8;
                    board[(lestrade.x)+1][(lestrade.y)+1].HexCharacter = 3;
                    lestrade.y = (lestrade.y)+1;
                    lestrade.x = (lestrade.x)+1;
                }else{
                    //#####
                }
            }else{
                if(board[lestrade.x][(lestrade.y)+1].HexType==0 || board[lestrade.x][(lestrade.y)+1].HexType==4 || board[lestrade.x][(lestrade.y)+1].HexType==5){
                    board[lestrade.x][lestrade.y].HexCharacter = 8;
                    board[lestrade.x][(lestrade.y)+1].HexCharacter = 3;
                    lestrade.y = (lestrade.y)+1;
                }else{
                    //#####
                }
            }
        }else if(choice2==5){
            if(lestrade.y%2==0){
                if(board[lestrade.x][(lestrade.y)-1].HexType==0 || board[lestrade.x][(lestrade.y)-1].HexType==4 || board[lestrade.x][(lestrade.y)-1].HexType==5){
                    board[lestrade.x][lestrade.y].HexCharacter = 8;
                    board[lestrade.x][(lestrade.y)-1].HexCharacter = 3;
                    lestrade.y = (lestrade.y)-1;
                }else{
                    //#####
                }
            }else{
                if(board[(lestrade.x)-1][(lestrade.y)-1].HexType==0 || board[(lestrade.x)-1][(lestrade.y)-1].HexType==4 || board[(lestrade.x)-1][(lestrade.y)-1].HexType==5){
                    board[lestrade.x][lestrade.y].HexCharacter = 8;
                    board[(lestrade.x)-1][(lestrade.y)-1].HexCharacter = 3;
                    lestrade.y = (lestrade.y)-1;
                    lestrade.x = (lestrade.x)-1;
                }else{
                    //#####
                }
            }
        }else if(choice2==6){
            if(lestrade.y%2==0){
                if(board[(lestrade.x)+1][(lestrade.y)-1].HexType==0 || board[(lestrade.x)+1][(lestrade.y)-1].HexType==4 || board[(lestrade.x)+1][(lestrade.y)-1].HexType==5){
                    board[lestrade.x][lestrade.y].HexCharacter = 8;
                    board[(lestrade.x)+1][(lestrade.y)-1].HexCharacter = 3;
                    lestrade.y = (lestrade.y)-1;
                    lestrade.x = (lestrade.x)+1;
                }else{
                    //#####
                }
            }else{
                if(board[lestrade.x][(lestrade.y)-1].HexType==0 || board[lestrade.x][(lestrade.y)-1].HexType==4 || board[lestrade.x][(lestrade.y)-1].HexType==5){
                    board[lestrade.x][lestrade.y].HexCharacter = 8;
                    board[lestrade.x][(lestrade.y)-1].HexCharacter = 3;
                    lestrade.y = (lestrade.y)-1;
                }else{
                    //#####
                }
            }
        }else if(choice2==7 && board[lestrade.x][lestrade.y].HexType==4){
            printf("Which manhole do you want to get out of?\n");
            if(board[0][5].HexType==4){
                printf("1.The manhole in the first row & 6th columns\n");
            }
            if(board[2][0].HexType==4){
                printf("2.The manhole in the 3th row & first column\n");
            }
            if(board[1][11].HexType==4){
                printf("3.The manhole in the 2th row & 12th column\n");
            }
            if(board[3][5].HexType==4){
                printf("4.The manhole in the 4th row & 6th column\n");
            }
            if(board[5][7].HexType==4){
                printf("5.The manhole in the 6th row & 8th column\n");
            }
            if(board[6][2].HexType==4){
                printf("6.The manhole in the 7th row & 3th column\n");
            }
            if(board[8][7].HexType==4){
                printf("7.The manhole in the 9th row & 8th column\n");
            }
            if(board[4][12].HexType==4){
                printf("8.The manhole in the 5th row & 13th column\n");
            }
            int tunnel_choice1;
            scanf("%d", &tunnel_choice1);
            if(tunnel_choice1==1){
                board[lestrade.x][lestrade.y].HexCharacter = 8;
                lestrade.x = 0;
                lestrade.y = 5;
                board[lestrade.x][lestrade.y].HexCharacter = 3;
            }else if(tunnel_choice1==2){
                board[lestrade.x][lestrade.y].HexCharacter = 8;
                lestrade.x = 2;
                lestrade.y = 0;
                board[lestrade.x][lestrade.y].HexCharacter = 3;
            }else if(tunnel_choice1==3){
                board[lestrade.x][lestrade.y].HexCharacter = 8;
                lestrade.x = 1;
                lestrade.y = 11;
                board[lestrade.x][lestrade.y].HexCharacter = 3;
            }else if(tunnel_choice1==4){
                board[lestrade.x][lestrade.y].HexCharacter = 8;
                lestrade.x = 3;
                lestrade.y = 5;
                board[lestrade.x][lestrade.y].HexCharacter = 3;
            }else if(tunnel_choice1==5){
                board[lestrade.x][lestrade.y].HexCharacter = 8;
                lestrade.x = 5;
                lestrade.y = 7;
                board[lestrade.x][lestrade.y].HexCharacter = 3;
            }else if(tunnel_choice1==6){
                board[lestrade.x][lestrade.y].HexCharacter = 8;
                lestrade.x = 5;
                lestrade.y = 2;
                board[lestrade.x][lestrade.y].HexCharacter = 3;
            }else if(tunnel_choice1==7){
                board[lestrade.x][lestrade.y].HexCharacter = 8;
                lestrade.x = 8;
                lestrade.y = 7;
                board[lestrade.x][lestrade.y].HexCharacter = 3;
            }else if(tunnel_choice1==8){
                board[lestrade.x][lestrade.y].HexCharacter = 8;
                lestrade.x = 4;
                lestrade.y = 12;
                board[lestrade.x][lestrade.y].HexCharacter = 3;
            }else{
                //to control user foolishness
            }
            

        }else{
            //to control user foolishness
        }
        }
    }
    return board;
}
hex** Stealthy(hex** board){
    printf("\nYou have to move 1 to 4 hexes \n");
    printf("How many moves do you want to do?\n");
    int number_of_moves;
    scanf("%d", &number_of_moves);
    for(int i=0;i<number_of_moves;i++){
        printf("Which direction do you want to move for the %d move?\n", i+1);
        printf("1.Up   ");
        printf("2.Down   ");
        printf("3.UpRight   ");
        printf("4.DownRight   ");
        printf("5.UpLeft   ");
        printf("6.DownLeft   \n");
        if(board[stealthy.x][stealthy.y].HexType==4){
            printf("7. Pass Through The Tunnel\n");
        }
        int choice;
        scanf("%d", &choice);
        if(i==(number_of_moves-1)){
            if(choice==1){
                if(board[(stealthy.x)-1][stealthy.y].HexType==0 || board[(stealthy.x)-1][stealthy.y].HexType==4 || board[(stealthy.x)-1][stealthy.y].HexType==5){
                board[stealthy.x][stealthy.y].HexCharacter=8;
                stealthy.x = (stealthy.x)-1;
                board[stealthy.x][stealthy.y].HexCharacter=4;
                }else{
                //###### try again
                }
            }else if(choice==2){
            if(board[(stealthy.x)+1][stealthy.y].HexType==0 || board[(stealthy.x)+1][stealthy.y].HexType==4 || board[(stealthy.x)+1][stealthy.y].HexType==5){
                board[stealthy.x][stealthy.y].HexCharacter=8;
                stealthy.x = (stealthy.x)+1;
                board[stealthy.x][stealthy.y].HexCharacter=4;
            }else{
                //#####
            }
        }else if(choice==3){
            if(stealthy.y%2==0){
                if(board[stealthy.x][(stealthy.y)+1].HexType==0 || board[stealthy.x][(stealthy.y)+1].HexType==4 || board[stealthy.x][(stealthy.y)+1].HexType==5){
                    board[stealthy.x][stealthy.y].HexCharacter=8;
                    stealthy.y = (stealthy.y)+1;
                    board[stealthy.x][stealthy.y].HexCharacter=4;
                }else{
                    //#####
                }
            }else{
                if(board[stealthy.x-1][stealthy.y+1].HexType==0 || board[stealthy.x-1][stealthy.y+1].HexType==4 || board[stealthy.x-1][stealthy.y+1].HexType==5){
                    board[stealthy.x][stealthy.y].HexCharacter=8;
                    stealthy.x = stealthy.x-1;
                    stealthy.y = stealthy.y+1;
                    board[stealthy.x][stealthy.y].HexCharacter=4;
                }else{
                    //#####
                }
            }
        }else if(choice==4){
            if(stealthy.y%2==0){
                if(board[(stealthy.x)+1][(stealthy.y)+1].HexType==0 || board[(stealthy.x)+1][(stealthy.y)+1].HexType==4 || board[(stealthy.x)+1][(stealthy.y)+1].HexType==5){
                    board[stealthy.x][stealthy.y].HexCharacter=8;
                    stealthy.y = (stealthy.y)+1;
                    stealthy.x = (stealthy.x)+1;
                    board[stealthy.x][stealthy.y].HexCharacter=4;
                }else{
                    //#####
                }
            }else{
                if(board[stealthy.x][(stealthy.y)+1].HexType==0 || board[stealthy.x][(stealthy.y)+1].HexType==4 || board[stealthy.x][(stealthy.y)+1].HexType==5){
                    board[stealthy.x][stealthy.y].HexCharacter=8;
                    stealthy.y = (stealthy.y)+1;
                    board[stealthy.x][stealthy.y].HexCharacter=4;
                }else{
                    //#####
                }
            }
        }else if(choice==5){
            if(stealthy.y%2==0){
                if(board[stealthy.x][(stealthy.y)-1].HexType==0 || board[stealthy.x][(stealthy.y)-1].HexType==4 || board[stealthy.x][(stealthy.y)-1].HexType==5){
                    board[stealthy.x][stealthy.y].HexCharacter=8;
                    stealthy.y = (stealthy.y)-1;
                    board[stealthy.x][stealthy.y].HexCharacter=4;
                }else{
                    //#####
                }
            }else{
                if(board[(stealthy.x)-1][(stealthy.y)-1].HexType==0 || board[(stealthy.x)-1][(stealthy.y)-1].HexType==4 || board[(stealthy.x)-1][(stealthy.y)-1].HexType==5){
                    board[stealthy.x][stealthy.y].HexCharacter=8;
                    stealthy.y = (stealthy.y)-1;
                    stealthy.x = (stealthy.x)-1;
                    board[stealthy.x][stealthy.y].HexCharacter=4;
                }else{
                    //#####
                }
            }
        }else if(choice==6){
            if(stealthy.y%2==0){
                if(board[(stealthy.x)+1][(stealthy.y)-1].HexType==0 || board[(stealthy.x)+1][(stealthy.y)-1].HexType==4 || board[(stealthy.x)+1][(stealthy.y)-1].HexType==5){
                    board[stealthy.x][stealthy.y].HexCharacter=8;
                    stealthy.y = (stealthy.y)-1;
                    stealthy.x = (stealthy.x)+1;
                    board[stealthy.x][stealthy.y].HexCharacter=4;
                }else{
                    //#####
                }
            }else{
                if(board[stealthy.x][(stealthy.y)-1].HexType==0 || board[stealthy.x][(stealthy.y)-1].HexType==4 || board[stealthy.x][(stealthy.y)-1].HexType==5){
                    board[stealthy.x][stealthy.y].HexCharacter=8;
                    stealthy.y = (stealthy.y)-1;
                    board[stealthy.x][stealthy.y].HexCharacter=4;
                }else{
                    //#####
                }
            }
        }else if(choice==7 && board[stealthy.x][stealthy.y].HexType==4){
            printf("Which manhole do you want to get out of?\n");
            if(board[0][5].HexType==4){
                printf("1.The manhole in the first row & 6th columns\n");
            }
            if(board[2][0].HexType==4){
                printf("2.The manhole in the 3th row & first column\n");
            }
            if(board[1][11].HexType==4){
                printf("3.The manhole in the 2th row & 12th column\n");
            }
            if(board[3][5].HexType==4){
                printf("4.The manhole in the 4th row & 6th column\n");
            }
            if(board[5][7].HexType==4){
                printf("5.The manhole in the 6th row & 8th column\n");
            }
            if(board[6][2].HexType==4){
                printf("6.The manhole in the 7th row & 3th column\n");
            }
            if(board[8][7].HexType==4){
                printf("7.The manhole in the 9th row & 8th column\n");
            }
            if(board[4][12].HexType==4){
                printf("8.The manhole in the 5th row & 13th column\n");
            }
            int tunnel_choice;
            scanf("%d", &tunnel_choice);
            if(tunnel_choice==1){
                board[stealthy.x][stealthy.y].HexCharacter=8;
                stealthy.x = 0;
                stealthy.y = 5;
                board[stealthy.x][stealthy.y].HexCharacter=4;
            }else if(tunnel_choice==2){
                board[stealthy.x][stealthy.y].HexCharacter=8;
                stealthy.x = 2;
                stealthy.y = 0;
                board[stealthy.x][stealthy.y].HexCharacter=4;
            }else if(tunnel_choice==3){
                board[stealthy.x][stealthy.y].HexCharacter=8;
                stealthy.x = 1;
                stealthy.y = 11;
                board[stealthy.x][stealthy.y].HexCharacter=4;
            }else if(tunnel_choice==4){
                board[stealthy.x][stealthy.y].HexCharacter=8;
                stealthy.x = 3;
                stealthy.y = 5;
                board[stealthy.x][stealthy.y].HexCharacter=4;
            }else if(tunnel_choice==5){
                board[stealthy.x][stealthy.y].HexCharacter=8;
                stealthy.x = 5;
                stealthy.y = 7;
                board[stealthy.x][stealthy.y].HexCharacter=4;
            }else if(tunnel_choice==6){
                board[stealthy.x][stealthy.y].HexCharacter=8;
                stealthy.x = 5;
                stealthy.y = 2;
                board[stealthy.x][stealthy.y].HexCharacter=4;
            }else if(tunnel_choice==7){
                board[stealthy.x][stealthy.y].HexCharacter=8;
                stealthy.x = 8;
                stealthy.y = 7;
                board[stealthy.x][stealthy.y].HexCharacter=4;
            }else if(tunnel_choice==8){
                board[stealthy.x][stealthy.y].HexCharacter=8;
                stealthy.x = 4;
                stealthy.y = 12;
                board[stealthy.x][stealthy.y].HexCharacter=4;
            }else{
                //to control user foolishness
            }
            

        }else{
            //to control user foolishness
        }
        }else if(choice==1){
                board[stealthy.x][stealthy.y].HexCharacter=8;
                stealthy.x = (stealthy.x)-1;
                board[stealthy.x][stealthy.y].HexCharacter=4;
        }else if(choice==2){
                board[stealthy.x][stealthy.y].HexCharacter=8;
                stealthy.x = (stealthy.x)+1;
                board[stealthy.x][stealthy.y].HexCharacter=4;
        }else if(choice==3){
            if(stealthy.y%2==0){
                    board[stealthy.x][stealthy.y].HexCharacter=8;
                    stealthy.y = (stealthy.y)+1;
                    board[stealthy.x][stealthy.y].HexCharacter=4;
            }else{
                    board[stealthy.x][stealthy.y].HexCharacter=8;
                    stealthy.x = stealthy.x-1;
                    stealthy.y = stealthy.y+1;
                    board[stealthy.x][stealthy.y].HexCharacter=4;
            }
        }else if(choice==4){
            if(stealthy.y%2==0){
                    board[stealthy.x][stealthy.y].HexCharacter=8;
                    stealthy.y = (stealthy.y)+1;
                    stealthy.x = (stealthy.x)+1;
                    board[stealthy.x][stealthy.y].HexCharacter=4;
            }else{
                    board[stealthy.x][stealthy.y].HexCharacter=8;
                    stealthy.y = (stealthy.y)+1;
                    board[stealthy.x][stealthy.y].HexCharacter=4;
            }
        }else if(choice==5){
            if(stealthy.y%2==0){
                    board[stealthy.x][stealthy.y].HexCharacter=8;
                    stealthy.y = (stealthy.y)-1;
                    board[stealthy.x][stealthy.y].HexCharacter=4;
            }else{
                    board[stealthy.x][stealthy.y].HexCharacter=8;
                    stealthy.y = (stealthy.y)-1;
                    stealthy.x = (stealthy.x)-1;
                    board[stealthy.x][stealthy.y].HexCharacter=4;
            }
        }else if(choice==6){
            if(stealthy.y%2==0){
                    board[stealthy.x][stealthy.y].HexCharacter=8;
                    stealthy.y = (stealthy.y)-1;
                    stealthy.x = (stealthy.x)+1;
                    board[stealthy.x][stealthy.y].HexCharacter=4;
            }else{
                    board[stealthy.x][stealthy.y].HexCharacter=8;
                    stealthy.y = (stealthy.y)-1;
                    board[stealthy.x][stealthy.y].HexCharacter=4;
            }
        }else if(choice==7 && board[stealthy.x][stealthy.y].HexType==4){
            printf("Which manhole do you want to get out of?\n");
            if(board[0][5].HexType==4){
                printf("1.The manhole in the first row & 6th columns\n");
            }
            if(board[2][0].HexType==4){
                printf("2.The manhole in the 3th row & first column\n");
            }
            if(board[1][11].HexType==4){
                printf("3.The manhole in the 2th row & 12th column\n");
            }
            if(board[3][5].HexType==4){
                printf("4.The manhole in the 4th row & 6th column\n");
            }
            if(board[5][7].HexType==4){
                printf("5.The manhole in the 6th row & 8th column\n");
            }
            if(board[6][2].HexType==4){
                printf("6.The manhole in the 7th row & 3th column\n");
            }
            if(board[8][7].HexType==4){
                printf("7.The manhole in the 9th row & 8th column\n");
            }
            if(board[4][12].HexType==4){
                printf("8.The manhole in the 5th row & 13th column\n");
            }
            int tunnel_choice;
            scanf("%d", &tunnel_choice);
            if(tunnel_choice==1){
                board[stealthy.x][stealthy.y].HexCharacter=8;
                stealthy.x = 0;
                stealthy.y = 5;
                board[stealthy.x][stealthy.y].HexCharacter=4;
            }else if(tunnel_choice==2){
                board[stealthy.x][stealthy.y].HexCharacter=8;
                stealthy.x = 2;
                stealthy.y = 0;
                board[stealthy.x][stealthy.y].HexCharacter=4;
            }else if(tunnel_choice==3){
                board[stealthy.x][stealthy.y].HexCharacter=8;
                stealthy.x = 1;
                stealthy.y = 11;
                board[stealthy.x][stealthy.y].HexCharacter=4;
            }else if(tunnel_choice==4){
                board[stealthy.x][stealthy.y].HexCharacter=8;
                stealthy.x = 3;
                stealthy.y = 5;
                board[stealthy.x][stealthy.y].HexCharacter=4;
            }else if(tunnel_choice==5){
                board[stealthy.x][stealthy.y].HexCharacter=8;
                stealthy.x = 5;
                stealthy.y = 7;
                board[stealthy.x][stealthy.y].HexCharacter=4;
            }else if(tunnel_choice==6){
                board[stealthy.x][stealthy.y].HexCharacter=8;
                stealthy.x = 5;
                stealthy.y = 2;
                board[stealthy.x][stealthy.y].HexCharacter=4;
            }else if(tunnel_choice==7){
                board[stealthy.x][stealthy.y].HexCharacter=8;
                stealthy.x = 8;
                stealthy.y = 7;
                board[stealthy.x][stealthy.y].HexCharacter=4;
            }else if(tunnel_choice==8){
                board[stealthy.x][stealthy.y].HexCharacter=8;
                stealthy.x = 4;
                stealthy.y = 12;
                board[stealthy.x][stealthy.y].HexCharacter=4;
            }else{
                //to control user foolishness
            }
            

        }else{
            //to control user foolishness
        }

    }
    return board;
}
hex** Watson(hex** board){
    printf("\nYou have to move 1 to 3 hexes Then you can use your ability\n");
    printf("How many moves do you want to do?\n");
    int number_of_moves;
    scanf("%d", &number_of_moves);
    for(int i=0;i<number_of_moves;i++){
        printf("Which direction do you want to move for the %dth move?\n", i+1);
        printf("1.Up   ");
        printf("2.Down   ");
        printf("3.UpRight   ");
        printf("4.DownRight   ");
        printf("5.UpLeft   ");
        printf("6.DownLeft   ");
        if(board[watson.x][watson.y].HexType==4){
            printf("7. Pass Through The Tunnel");
        }
        int choice;
        scanf("%d", &choice);
        if(choice==1){
            if(board[(watson.x)-1][watson.y].HexType==0 || board[(watson.x)-1][watson.y].HexType==4 || board[(watson.x)-1][watson.y].HexType==5){
                board[watson.x][watson.y].HexCharacter=8;
                watson.x = (watson.x)-1;
                board[watson.x][watson.y].HexCharacter=1;
            }else{
                //###### try again
            }
        }else if(choice==2){
            if(board[(watson.x)+1][watson.y].HexType==0 || board[(watson.x)+1][watson.y].HexType==4 || board[(watson.x)+1][watson.y].HexType==5){
                board[watson.x][watson.y].HexCharacter=8;
                watson.x = (watson.x)+1;
                board[watson.x][watson.y].HexCharacter=1;
            }else{
                //#####
            }
        }else if(choice==3){
            if(watson.y%2==0){
                if(board[watson.x][(watson.y)+1].HexType==0 || board[watson.x][(watson.y)+1].HexType==4 || board[watson.x][(watson.y)+1].HexType==5){
                    board[watson.x][watson.y].HexCharacter=8;
                    watson.y = (watson.y)+1;
                    board[watson.x][watson.y].HexCharacter=1;
                }else{
                    //#####
                }
            }else{
                if(board[(watson.x)-1][(watson.y)+1].HexType==0 || board[(watson.x)-1][(watson.y)+1].HexType==4 || board[(watson.x)-1][(watson.y)+1].HexType==5){
                    board[watson.x][watson.y].HexCharacter=8;
                    watson.y = (watson.y)+1;
                    watson.x = (watson.x)-1;
                    board[watson.x][watson.y].HexCharacter=1;
                }else{
                    //#####
                }
            }
        }else if(choice==4){
            if(watson.y%2==0){
                if(board[(watson.x)+1][(watson.y)+1].HexType==0 || board[(watson.x)+1][(watson.y)+1].HexType==4 || board[(watson.x)+1][(watson.y)+1].HexType==5){
                    board[watson.x][watson.y].HexCharacter=8;
                    watson.y = (watson.y)+1;
                    watson.x = (watson.x)+1;
                    board[watson.x][watson.y].HexCharacter=1;
                }else{
                    //#####
                }
            }else{
                if(board[watson.x][(watson.y)+1].HexType==0 || board[watson.x][(watson.y)+1].HexType==4 || board[watson.x][(watson.y)+1].HexType==5){
                    board[watson.x][watson.y].HexCharacter=8;
                    watson.y = (watson.y)+1;
                    board[watson.x][watson.y].HexCharacter=1;
                }else{
                    //#####
                }
            }
        }else if(choice==5){
            if(watson.y%2==0){
                if(board[watson.x][(watson.y)-1].HexType==0 || board[watson.x][(watson.y)-1].HexType==4 || board[watson.x][(watson.y)-1].HexType==5){
                    board[watson.x][watson.y].HexCharacter=8;
                    watson.y = (watson.y)-1;
                    board[watson.x][watson.y].HexCharacter=1;
                }else{
                    //#####
                }
            }else{
                if(board[(watson.x)-1][(watson.y)-1].HexType==0 || board[(watson.x)-1][(watson.y)-1].HexType==4 || board[(watson.x)-1][(watson.y)-1].HexType==5){
                    board[watson.x][watson.y].HexCharacter=8;
                    watson.y = (watson.y)-1;
                    watson.x = (watson.x)-1;
                    board[watson.x][watson.y].HexCharacter=1;
                }else{
                    //#####
                }
            }
        }else if(choice==6){
            if(watson.y%2==0){
                if(board[(watson.x)+1][(watson.y)-1].HexType==0 || board[(watson.x)+1][(watson.y)-1].HexType==4 || board[(watson.x)+1][(watson.y)-1].HexType==5){
                    board[watson.x][watson.y].HexCharacter=8;
                    watson.y = (watson.y)-1;
                    watson.x = (watson.x)+1;
                    board[watson.x][watson.y].HexCharacter=1;
                }else{
                    //#####
                }
            }else{
                if(board[watson.x][(watson.y)-1].HexType==0 || board[watson.x][(watson.y)-1].HexType==4 || board[watson.x][(watson.y)-1].HexType==5){
                    board[watson.x][watson.y].HexCharacter=8;
                    watson.y = (watson.y)-1;
                    board[watson.x][watson.y].HexCharacter=1;
                }else{
                    //#####
                }
            }
        }else if(choice==7 && board[watson.x][watson.y].HexType==4){
            printf("Which manhole do you want to get out of?\n");
            if(board[0][5].HexType==4){
                printf("1.The manhole in the first row & 6th columns\n");
            }
            if(board[2][0].HexType==4){
                printf("2.The manhole in the 3th row & first column\n");
            }
            if(board[1][11].HexType==4){
                printf("3.The manhole in the 2th row & 12th column\n");
            }
            if(board[3][5].HexType==4){
                printf("4.The manhole in the 4th row & 6th column\n");
            }
            if(board[5][7].HexType==4){
                printf("5.The manhole in the 6th row & 8th column\n");
            }
            if(board[6][2].HexType==4){
                printf("6.The manhole in the 7th row & 3th column\n");
            }
            if(board[8][7].HexType==4){
                printf("7.The manhole in the 9th row & 8th column\n");
            }
            if(board[4][12].HexType==4){
                printf("8.The manhole in the 5th row & 13th column\n");
            }
            int tunnel_choice;
            scanf("%d", &tunnel_choice);
            if(tunnel_choice==1){
                board[watson.x][watson.y].HexCharacter=8;
                watson.x = 0;
                watson.y = 5;
                board[watson.x][watson.y].HexCharacter=1;
            }else if(tunnel_choice==2){
                board[watson.x][watson.y].HexCharacter=8;
                watson.x = 2;
                watson.y = 0;
                board[watson.x][watson.y].HexCharacter=1;
            }else if(tunnel_choice==3){
                board[watson.x][watson.y].HexCharacter=8;
                watson.x = 1;
                watson.y = 11;
                board[watson.x][watson.y].HexCharacter=1;
            }else if(tunnel_choice==4){
                board[watson.x][watson.y].HexCharacter=8;
                watson.x = 3;
                watson.y = 5;
                board[watson.x][watson.y].HexCharacter=1;
            }else if(tunnel_choice==5){
                board[watson.x][watson.y].HexCharacter=8;
                watson.x = 5;
                watson.y = 7;
                board[watson.x][watson.y].HexCharacter=1;
            }else if(tunnel_choice==6){
                board[watson.x][watson.y].HexCharacter=8;
                watson.x = 5;
                watson.y = 2;
                board[watson.x][watson.y].HexCharacter=1;
            }else if(tunnel_choice==7){
                board[watson.x][watson.y].HexCharacter=8;
                watson.x = 8;
                watson.y = 7;
                board[watson.x][watson.y].HexCharacter=1;
            }else if(tunnel_choice==8){
                board[watson.x][watson.y].HexCharacter=8;
                watson.x = 4;
                watson.y = 12;
                board[watson.x][watson.y].HexCharacter=1;
            }else{
                //to control user foolishness
            }
            

        }else{
            //to control user foolishness
        }

    }
    //system("cls");
    printf("Which way do you want to illuminate?\n");
    printf("1.Up   ");
    printf("2.Down   ");
    printf("3.UpRight   ");
    printf("4.DownRight   ");
    printf("5.UpLeft   ");
    printf("6.DownLeft   ");
    int illuminated_way;
    scanf("%d", &illuminated_way);
    if(illuminated_way==1){
        for(int k=0;k<watson.x;k++){
            board[k][watson.y].LitArea = 0;
        }
    }else if(illuminated_way==2){
        for(int k=(watson.x)+1;k<9;k++){
            board[k][watson.y].LitArea = 0;
        }
    }else if(illuminated_way==3){
        if(watson.y%2==0){
            if((watson.y+1)<13){
                board[watson.x][(watson.y)+1].LitArea = 0;
                int x = watson.x;
                int y = watson.y;
                int m=1;
                int n=1;
                while((board[x-m][y+n+1].HexType==0 || board[x-m][y+n+1].HexType==4 || board[x-m][y+n+1].HexType==5) && (x-m)>=0 && (y+n+1)<=12){
                    board[x-m][y+n+1].LitArea = 0;
                    if((board[x-m][y+n+2].HexType==0 || board[x-m][y+n+2].HexType==4 || board[x-m][y+n+2].HexType==5)&&(x-m)>=0&&(y+n+2)<=12){
                        board[x-m][y+n+2].LitArea = 0;
                        n=n+2;
                    }
                    m = m+1;
                }
            }
        }else{
            int x = watson.x;
                int y = watson.y;
                int m=1;
                int n=1;
                while((board[x-m][y+n].HexType==0 || board[x-m][y+n].HexType==4 || board[x-m][y+n].HexType==5) && (x-m)>=0 && (y+n)<=12){
                    board[x-m][y+n].LitArea = 0;
                    if((board[x-m][y+n+1].HexType==0 || board[x-m][y+n+1].HexType==4 || board[x-m][y+n+1].HexType==5)&&(x-m)>=0&&(y+n+1)<=12){
                        board[x-m][y+n+1].LitArea = 0;
                        n=n+2;
                    }
                    m = m+1;
                }
        }
    }else if(illuminated_way==4){
        if(watson.y%2==0){
            int x = watson.x;
            int y = watson.y;
            int n=1;
            int m=1;
            while((board[x+m][y+n].HexType==0 || board[x+m][y+n].HexType==4 || board[x+m][y+n].HexType==5) && (x+m)<=8 && (y+n)<=12){
                board[x+m][y+n].LitArea = 0;
                if((board[x+m][y+n+1].HexType==0 || board[x+m][y+n+1].HexType==4 || board[x+m][y+n+1].HexType==5) && (x+m)<=8 && (y+n+1)<=12){
                    board[x+m][y+n+1].LitArea = 0;
                }
            }
        }else{
            if(watson.y+1<13){
                board[watson.x][watson.y+1].LitArea=0;
            }
            int x = watson.x;
            int y = watson.y;
            int n=1;
            int m=1;
            while((board[x+m][y+n+1].HexType==0 || board[x+m][y+n+1].HexType==4 || board[x+m][y+n+1].HexType==5) && (x+m)<=8 && (y+n+1)<=12){
                    board[x+m][y+n+1].LitArea = 0;
                    if((board[x+m][y+n+2].HexType==0 || board[x+m][y+n+2].HexType==4 || board[x+m][y+n+2].HexType==5)&&(x+m)>=0&&(y+n+2)<=12){
                        board[x+m][y+n+2].LitArea = 0;
                        n=n+2;
                    }
                    m = m+1;
                }
        }
    }else if(illuminated_way==5){
        if(watson.y%2==0){
            if(watson.y-1>=0 && watson.x>=0){
                board[watson.x][watson.y-1].LitArea=0;
            }
            int x = watson.x;
            int y = watson.y;
            int n=1;
            int m=1;
            while((board[x-m][y-n-1].HexType==0 || board[x-m][y-n-1].HexType==4 || board[x-m][y-n-1].HexType==5) && (x-m)>=0 && (y-n-1)>=0){
                board[x-m][y-n-1].LitArea = 0;
                if((board[x-m][y-n-2].HexType==0 || board[x-m][y-n-2].HexType==4 || board[x-m][y-n-2].HexType==5)&&(x-m)>=0&&(y-n-2)>=0){
                    board[x-m][y-n-2].LitArea = 0;
                    n=n+2;
                }
                m = m+1;
            }
        }else{
            int x = watson.x;
            int y = watson.y;
            int n=1;
            int m=1;
            while((board[x-m][y-n].HexType==0 || board[x-m][y-n].HexType==4 || board[x-m][y-n].HexType==5) && (x-m)>=0 && (y-n)>=0){
                board[x-m][y-n].LitArea = 0;
                if((board[x-m][y-n-1].HexType==0 || board[x-m][y-n-1].HexType==4 || board[x-m][y-n-1].HexType==5) && (x-m)>=0 && (y-n-1)>=0){
                    board[x-m][y-n-1].LitArea = 0;
                }
            }
        }
    }else if(illuminated_way==6){
        if(watson.y%2==0){
            int x = watson.x;
            int y = watson.y;
            int n=1;
            int m=1;
            while((board[x+m][y+n].HexType==0 || board[x+m][y+n].HexType==4 || board[x+m][y+n].HexType==5) && (x+m)<=8 && (y+n)>=0){
                board[x+m][y+n].LitArea = 0;
                if((board[x+m][y+n+1].HexType==0 || board[x+m][y+n+1].HexType==4 || board[x+m][y+n+1].HexType==5) && (x+m)<=8 && (y+n+1)>=0){
                    board[x+m][y+n+1].LitArea = 0;
                }
            }
        }else{
            if(watson.y-1>=0 && watson.x+1<=8){
                board[watson.x+1][watson.y-1].LitArea=0;
            }
            int x = watson.x;
            int y = watson.y;
            int n=1;
            int m=1;
            while((board[x+m][y-n-1].HexType==0 || board[x+m][y-n-1].HexType==4 || board[x+m][y-n-1].HexType==5) && (x+m)<=8 && (y-n-1)>=0){
                board[x+m][y-n-1].LitArea = 0;
                if((board[x+m][y-n-2].HexType==0 || board[x+m][y-n-2].HexType==4 || board[x+m][y-n-2].HexType==5)&&(x+m)>=0&&(y-n-2)>=0){
                    board[x+m][y-n-2].LitArea = 0;
                    n=n+2;
                }
                m = m+1;
            }
        }
    }
    return board;

}
hex** Goodley(hex** board){
    printf("\nDo you want to use your ability or move first?\n");
    printf("1.Move first\n");
    printf("Other than 1.Use my ability first\n");
    int choice;
    scanf("%d", &choice);
    if(choice==1){
        //system("cls");
        printf("You have to move 1 to 3 hexes Then you can use your ability\n");
        printf("How many moves do you want to do?\n");
        int number_of_moves;
        scanf("%d", &number_of_moves);
        for(int i=0;i<number_of_moves;i++){
        //system("cls");
            printf("Which direction do you want to move for the %dth move?\n", i+1);
            printf("1.Up   ");
            printf("2.Down   ");
            printf("3.UpRight   ");
            printf("4.DownRight   ");
            printf("5.UpLeft   ");
            printf("6.DownLeft   \n");
            if(board[lestrade.x][lestrade.y].HexType==4){
                printf("7. Pass Through The Tunnel\n");
            }
        int choice1;
        scanf("%d", &choice1);
        if(choice1==1){
            if(board[(goodley.x)-1][goodley.y].HexType==0 || board[(goodley.x)-1][goodley.y].HexType==4 || board[(goodley.x)-1][goodley.y].HexType==5){
                board[goodley.x][goodley.y].HexCharacter = 8;
                board[(goodley.x)-1][goodley.y].HexCharacter = 5;
                goodley.x = (goodley.x)-1;
            }else{
                //###### try again
            }
        }else if(choice1==2){
            if(board[(goodley.x)+1][goodley.y].HexType==0 || board[(goodley.x)+1][goodley.y].HexType==4 || board[(goodley.x)+1][goodley.y].HexType==5){
                board[goodley.x][goodley.y].HexCharacter = 8;
                board[(goodley.x)+1][goodley.y].HexCharacter = 5;
                goodley.x = (goodley.x)+1;
            }else{
                //#####
            }
        }else if(choice1==3){
            if(goodley.y%2==0){
                if(board[goodley.x][(goodley.y)+1].HexType==0 || board[goodley.x][(goodley.y)+1].HexType==4 || board[goodley.x][(goodley.y)+1].HexType==5){
                    board[goodley.x][goodley.y].HexCharacter = 8;
                    board[goodley.x][(goodley.y)+1].HexCharacter = 5;
                    goodley.y = (goodley.y)+1;
                }else{
                    //#####
                }
            }else{
                if(board[(goodley.x)-1][(goodley.y)+1].HexType==0 || board[(goodley.x)-1][(goodley.y)+1].HexType==4 || board[(goodley.x)-1][(goodley.y)+1].HexType==5){
                    board[goodley.x][goodley.y].HexCharacter = 8;
                    board[(goodley.x)-1][(goodley.y)+1].HexCharacter = 5;
                    goodley.y = (goodley.y)+1;
                    goodley.x = (goodley.x)-1;
                }else{
                    //#####
                }
            }
        }else if(choice1==4){
            if(goodley.y%2==0){
                if(board[(goodley.x)+1][(goodley.y)+1].HexType==0 || board[(goodley.x)+1][(goodley.y)+1].HexType==4 || board[(goodley.x)+1][(goodley.y)+1].HexType==5){
                    board[goodley.x][goodley.y].HexCharacter = 8;
                    board[(goodley.x)+1][(goodley.y)+1].HexCharacter = 5;
                    goodley.y = (goodley.y)+1;
                    goodley.x = (goodley.x)+1;
                }else{
                    //#####
                }
            }else{
                if(board[goodley.x][(goodley.y)+1].HexType==0 || board[goodley.x][(goodley.y)+1].HexType==4 || board[goodley.x][(goodley.y)+1].HexType==5){
                    board[goodley.x][goodley.y].HexCharacter = 8;
                    board[goodley.x][(goodley.y)+1].HexCharacter = 5;
                    goodley.y = (goodley.y)+1;
                }else{
                    //#####
                }
            }
        }else if(choice1==5){
            if(goodley.y%2==0){
                if(board[goodley.x][(goodley.y)-1].HexType==0 || board[goodley.x][(goodley.y)-1].HexType==4 || board[goodley.x][(goodley.y)-1].HexType==5){
                    board[goodley.x][goodley.y].HexCharacter = 8;
                    board[goodley.x][(goodley.y)-1].HexCharacter = 5;
                    goodley.y = (goodley.y)-1;
                }else{
                    //#####
                }
            }else{
                if(board[(goodley.x)-1][(goodley.y)-1].HexType==0 || board[(goodley.x)-1][(goodley.y)-1].HexType==4 || board[(goodley.x)-1][(goodley.y)-1].HexType==5){
                    board[goodley.x][goodley.y].HexCharacter = 8;
                    board[(goodley.x)-1][(goodley.y)-1].HexCharacter = 5;
                    goodley.y = (goodley.y)-1;
                    goodley.x = (goodley.x)-1;
                }else{
                    //#####
                }
            }
        }else if(choice1==6){
            if(goodley.y%2==0){
                if(board[(goodley.x)+1][(goodley.y)-1].HexType==0 || board[(goodley.x)+1][(goodley.y)-1].HexType==4 || board[(goodley.x)+1][(goodley.y)-1].HexType==5){
                    board[goodley.x][goodley.y].HexCharacter = 8;
                    board[(goodley.x)+1][(goodley.y)-1].HexCharacter = 5;
                    goodley.y = (goodley.y)-1;
                    goodley.x = (goodley.x)+1;
                }else{
                    //#####
                }
            }else{
                if(board[goodley.x][(goodley.y)-1].HexType==0 || board[goodley.x][(goodley.y)-1].HexType==4 || board[goodley.x][(goodley.y)-1].HexType==5){
                    board[goodley.x][goodley.y].HexCharacter = 8;
                    board[goodley.x][(goodley.y)-1].HexCharacter = 5;
                    goodley.y = (goodley.y)-1;
                }else{
                    //#####
                }
            }
        }else if(choice1==7 && board[goodley.x][goodley.y].HexType==4){
            printf("Which manhole do you want to get out of?\n");
            if(board[0][5].HexType==4){
                printf("1.The manhole in the first row & 6th columns\n");
            }
            if(board[2][0].HexType==4){
                printf("2.The manhole in the 3th row & first column\n");
            }
            if(board[1][11].HexType==4){
                printf("3.The manhole in the 2th row & 12th column\n");
            }
            if(board[3][5].HexType==4){
                printf("4.The manhole in the 4th row & 6th column\n");
            }
            if(board[5][7].HexType==4){
                printf("5.The manhole in the 6th row & 8th column\n");
            }
            if(board[6][2].HexType==4){
                printf("6.The manhole in the 7th row & 3th column\n");
            }
            if(board[8][7].HexType==4){
                printf("7.The manhole in the 9th row & 8th column\n");
            }
            if(board[4][12].HexType==4){
                printf("8.The manhole in the 5th row & 13th column\n");
            }
            int tunnel_choice;
            scanf("%d", &tunnel_choice);
            if(tunnel_choice==1){
                board[goodley.x][goodley.y].HexCharacter = 8;
                jeremy.x = 0;
                jeremy.y = 5;
                board[goodley.x][goodley.y].HexCharacter = 5;
            }else if(tunnel_choice==2){
                board[goodley.x][goodley.y].HexCharacter = 8;
                goodley.x = 2;
                goodley.y = 0;
                board[goodley.x][goodley.y].HexCharacter = 5;
            }else if(tunnel_choice==3){
                board[goodley.x][goodley.y].HexCharacter = 8;
                goodley.x = 1;
                goodley.y = 11;
                board[goodley.x][goodley.y].HexCharacter = 5;
            }else if(tunnel_choice==4){
                board[goodley.x][goodley.y].HexCharacter = 8;
                goodley.x = 3;
                goodley.y = 5;
                board[goodley.x][goodley.y].HexCharacter = 5;
            }else if(tunnel_choice==5){
                board[goodley.x][goodley.y].HexCharacter = 8;
                goodley.x = 5;
                goodley.y = 7;
                board[goodley.x][goodley.y].HexCharacter = 5;
            }else if(tunnel_choice==6){
                board[goodley.x][goodley.y].HexCharacter = 8;
                goodley.x = 5;
                goodley.y = 2;
                board[goodley.x][goodley.y].HexCharacter = 5;
            }else if(tunnel_choice==7){
                board[goodley.x][goodley.y].HexCharacter = 8;
                goodley.x = 8;
                goodley.y = 7;
                board[goodley.x][goodley.y].HexCharacter = 5;
            }else if(tunnel_choice==8){
                board[goodley.x][goodley.y].HexCharacter = 8;
                goodley.x = 4;
                goodley.y = 12;
                board[goodley.x][goodley.y].HexCharacter = 5;
            }else{
                //to control user stupidity
            }
            

        }else{
            //to control user stupidity
        }
        }
    
        //system("cls");
        printf("Now you have to use your ability\n");
        printf("How many characters do you want to bring closer to Goodley?\n");
        int char_num;
        scanf("%d", &char_num);
        for(int j=0;j<char_num;j++){
            printf("Who do you want to bring closer to Goodley?\n");
            printf("1.Sherlock Holmes  ");
            printf("2.John Watson  ");
            printf("3.John Smith  ");
            printf("4.Inspector Lestrade");
            printf("\n5.Miss Stealthy  ");
            printf("6.Sir William Gull  ");
            printf("7.Jeremy Bert  ");
            int choice2;
            scanf("%d", &choice2);
            printf("\nHow many moves do you approach this character?\n");
            int move_num;
            scanf("%d", &move_num);
            if(choice2==1){
                for(int i=0;i<move_num;i++){
                    printf("Which direction do you want to move for the %d move?\n", i+1);
                    printf("1.Up   ");
                    printf("2.Down   ");
                    printf("3.UpRight   ");
                    printf("4.DownRight   ");
                    printf("5.UpLeft   ");
                    printf("6.DownLeft   \n");
                    int direction;
                    scanf("%d", &direction);
                    if(direction==1){
                        if(board[(sherlock.x)-1][sherlock.y].HexType==0 || board[(sherlock.x)-1][sherlock.y].HexType==4 || board[(sherlock.x)-1][sherlock.y].HexType==5){
                            board[sherlock.x][sherlock.y].HexCharacter=8;
                            sherlock.x = (sherlock.x)-1;
                            board[sherlock.x][sherlock.y].HexCharacter=0;
                        }else{
                            //###### try again
                        }
                    }else if(direction==2){
                        if(board[(sherlock.x)+1][sherlock.y].HexType==0 || board[(sherlock.x)+1][sherlock.y].HexType==4 || board[(sherlock.x)+1][sherlock.y].HexType==5){
                            board[sherlock.x][sherlock.y].HexCharacter=8;
                            sherlock.x = (sherlock.x)+1;
                            board[sherlock.x][sherlock.y].HexCharacter=0;
                    }else{
                            //#####
                        }
                    }else if(direction==3){
                        if(sherlock.y%2==0){
                            if(board[sherlock.x][(sherlock.y)+1].HexType==0 || board[sherlock.x][(sherlock.y)+1].HexType==4 || board[sherlock.x][(sherlock.y)+1].HexType==5){
                                board[sherlock.x][sherlock.y].HexCharacter=8;
                                sherlock.y = (sherlock.y)+1;
                                board[sherlock.x][sherlock.y].HexCharacter=0;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[sherlock.x-1][sherlock.y+1].HexType==0 || board[sherlock.x-1][sherlock.y+1].HexType==4 || board[sherlock.x-1][sherlock.y+1].HexType==5){
                                board[sherlock.x][sherlock.y].HexCharacter=8;
                                sherlock.x = sherlock.x-1;
                                sherlock.y = sherlock.y+1;
                                board[sherlock.x][sherlock.y].HexCharacter=0;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==4){
                        if(sherlock.y%2==0){
                            if(board[(sherlock.x)+1][(sherlock.y)+1].HexType==0 || board[(sherlock.x)+1][(sherlock.y)+1].HexType==4 || board[(sherlock.x)+1][(sherlock.y)+1].HexType==5){
                                board[sherlock.x][sherlock.y].HexCharacter=8;
                                sherlock.y = (sherlock.y)+1;
                                sherlock.x = (sherlock.x)+1;
                                board[sherlock.x][sherlock.y].HexCharacter=0;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[sherlock.x][(sherlock.y)+1].HexType==0 || board[sherlock.x][(sherlock.y)+1].HexType==4 || board[sherlock.x][(sherlock.y)+1].HexType==5){
                                board[sherlock.x][sherlock.y].HexCharacter=8;
                                sherlock.y = (sherlock.y)+1;
                                board[sherlock.x][sherlock.y].HexCharacter=0;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==5){
                        if(sherlock.y%2==0){
                            if(board[sherlock.x][(sherlock.y)-1].HexType==0 || board[sherlock.x][(sherlock.y)-1].HexType==4 || board[sherlock.x][(sherlock.y)-1].HexType==5){
                                board[sherlock.x][sherlock.y].HexCharacter=8;
                                sherlock.y = (sherlock.y)-1;
                                board[sherlock.x][sherlock.y].HexCharacter=0;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[(sherlock.x)-1][(sherlock.y)-1].HexType==0 || board[(sherlock.x)-1][(sherlock.y)-1].HexType==4 || board[(sherlock.x)-1][(sherlock.y)-1].HexType==5){
                                board[sherlock.x][sherlock.y].HexCharacter=8;
                                sherlock.y = (sherlock.y)-1;
                                sherlock.x = (sherlock.x)-1;
                                board[sherlock.x][sherlock.y].HexCharacter=0;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==6){
                        if(sherlock.y%2==0){
                            if(board[(sherlock.x)+1][(sherlock.y)-1].HexType==0 || board[(sherlock.x)+1][(sherlock.y)-1].HexType==4 || board[(sherlock.x)+1][(sherlock.y)-1].HexType==5){
                                board[sherlock.x][sherlock.y].HexCharacter=8;
                                sherlock.y = (sherlock.y)-1;
                                sherlock.x = (sherlock.x)+1;
                                board[sherlock.x][sherlock.y].HexCharacter=0;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[sherlock.x][(sherlock.y)-1].HexType==0 || board[sherlock.x][(sherlock.y)-1].HexType==4 || board[sherlock.x][(sherlock.y)-1].HexType==5){
                                board[sherlock.x][sherlock.y].HexCharacter=8;
                                sherlock.y = (sherlock.y)-1;
                                board[sherlock.x][sherlock.y].HexCharacter=0;
                            }else{
                            //#####
                            }
                        }
                    }
                }
            }else if(choice2==2){
                for(int i=0;i<move_num;i++){
                    printf("Which direction do you want to move for the %dth move?\n", i+1);
                    printf("1.Up   ");
                    printf("2.Down   ");
                    printf("3.UpRight   ");
                    printf("4.DownRight   ");
                    printf("5.UpLeft   ");
                    printf("6.DownLeft   ");
                    int direction;
                    scanf("%d", &direction);
                    if(direction==1){
                        if(board[(watson.x)-1][watson.y].HexType==0 || board[(watson.x)-1][watson.y].HexType==4 || board[(watson.x)-1][watson.y].HexType==5){
                            board[watson.x][watson.y].HexCharacter=8;
                            watson.x = (watson.x)-1;
                            board[watson.x][watson.y].HexCharacter=1;
                        }else{
                            //###### try again
                        }
                    }else if(direction==2){
                        if(board[(watson.x)+1][watson.y].HexType==0 || board[(watson.x)+1][watson.y].HexType==4 || board[(watson.x)+1][watson.y].HexType==5){
                            board[watson.x][watson.y].HexCharacter=8;
                            watson.x = (watson.x)+1;
                            board[watson.x][watson.y].HexCharacter=1;
                        }else{
                            //#####
                        }
                    }else if(direction==3){
                        if(watson.y%2==0){
                            if(board[watson.x][(watson.y)+1].HexType==0 || board[watson.x][(watson.y)+1].HexType==4 || board[watson.x][(watson.y)+1].HexType==5){
                                board[watson.x][watson.y].HexCharacter=8;
                                watson.y = (watson.y)+1;
                                board[watson.x][watson.y].HexCharacter=1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[(watson.x)-1][(watson.y)+1].HexType==0 || board[(watson.x)-1][(watson.y)+1].HexType==4 || board[(watson.x)-1][(watson.y)+1].HexType==5){
                                board[watson.x][watson.y].HexCharacter=8;
                                watson.y = (watson.y)+1;
                                watson.x = (watson.x)-1;
                                board[watson.x][watson.y].HexCharacter=1;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==4){
                        if(watson.y%2==0){
                            if(board[(watson.x)+1][(watson.y)+1].HexType==0 || board[(watson.x)+1][(watson.y)+1].HexType==4 || board[(watson.x)+1][(watson.y)+1].HexType==5){
                                board[watson.x][watson.y].HexCharacter=8;
                                watson.y = (watson.y)+1;
                                watson.x = (watson.x)+1;
                                board[watson.x][watson.y].HexCharacter=1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[watson.x][(watson.y)+1].HexType==0 || board[watson.x][(watson.y)+1].HexType==4 || board[watson.x][(watson.y)+1].HexType==5){
                                board[watson.x][watson.y].HexCharacter=8;
                                watson.y = (watson.y)+1;
                                board[watson.x][watson.y].HexCharacter=1;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==5){
                        if(watson.y%2==0){
                            if(board[watson.x][(watson.y)-1].HexType==0 || board[watson.x][(watson.y)-1].HexType==4 || board[watson.x][(watson.y)-1].HexType==5){
                                board[watson.x][watson.y].HexCharacter=8;
                                watson.y = (watson.y)-1;
                                board[watson.x][watson.y].HexCharacter=1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[(watson.x)-1][(watson.y)-1].HexType==0 || board[(watson.x)-1][(watson.y)-1].HexType==4 || board[(watson.x)-1][(watson.y)-1].HexType==5){
                                board[watson.x][watson.y].HexCharacter=8;
                                watson.y = (watson.y)-1;
                                watson.x = (watson.x)-1;
                                board[watson.x][watson.y].HexCharacter=1;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==6){
                        if(watson.y%2==0){
                            if(board[(watson.x)+1][(watson.y)-1].HexType==0 || board[(watson.x)+1][(watson.y)-1].HexType==4 || board[(watson.x)+1][(watson.y)-1].HexType==5){
                                board[watson.x][watson.y].HexCharacter=8;
                                watson.y = (watson.y)-1;
                                watson.x = (watson.x)+1;
                                board[watson.x][watson.y].HexCharacter=1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[watson.x][(watson.y)-1].HexType==0 || board[watson.x][(watson.y)-1].HexType==4 || board[watson.x][(watson.y)-1].HexType==5){
                                board[watson.x][watson.y].HexCharacter=8;
                                watson.y = (watson.y)-1;
                                board[watson.x][watson.y].HexCharacter=1;
                            }else{
                                //#####
                            }
                        }
                    }

                }

            }else if(choice2==3){
                for(int i=0;i<move_num;i++){
                    printf("Which direction do you want to move for the %d move?\n", i+1);
                    printf("1.Up   ");
                    printf("2.Down   ");
                    printf("3.UpRight   ");
                    printf("4.DownRight   ");
                    printf("5.UpLeft   ");
                    printf("6.DownLeft   \n");
                    int direction;
                    scanf("%d", &direction);
                    if(direction==1){
                        if(board[(smith.x)-1][smith.y].HexType==0 || board[(smith.x)-1][smith.y].HexType==4 || board[(smith.x)-1][smith.y].HexType==5){
                            board[smith.x][smith.y].HexCharacter = 8;
                            board[(smith.x)-1][smith.y].HexCharacter = 2;
                            smith.x = (smith.x)-1;
                        }else{
                            //###### try again
                        }
                    }else if(direction==2){
                        if(board[(smith.x)+1][smith.y].HexType==0 || board[(smith.x)+1][smith.y].HexType==4 || board[(smith.x)+1][smith.y].HexType==5){
                            board[smith.x][smith.y].HexCharacter = 8;
                            board[(smith.x)+1][smith.y].HexCharacter = 2;
                            smith.x = (smith.x)+1;
                        }else{
                            //#####
                        }
                    }else if(direction==3){
                        if(smith.y%2==0){
                            if(board[smith.x][(smith.y)+1].HexType==0 || board[smith.x][(smith.y)+1].HexType==4 || board[smith.x][(smith.y)+1].HexType==5){
                                board[smith.x][smith.y].HexCharacter = 8;
                                board[smith.x][(smith.y)+1].HexCharacter = 2;
                                smith.y = (smith.y)+1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[(smith.x)-1][(smith.y)+1].HexType==0 || board[(smith.x)-1][(smith.y)+1].HexType==4 || board[(smith.x)-1][(smith.y)+1].HexType==5){
                                board[smith.x][smith.y].HexCharacter = 8;
                                board[(smith.x)-1][(smith.y)+1].HexCharacter = 2;
                                smith.y = (smith.y)+1;
                                smith.x = (smith.x)-1;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==4){
                        if(smith.y%2==0){
                            if(board[(smith.x)+1][(smith.y)+1].HexType==0 || board[(smith.x)+1][(smith.y)+1].HexType==4 || board[(smith.x)+1][(smith.y)+1].HexType==5){
                                board[smith.x][smith.y].HexCharacter = 8;
                                board[(smith.x)+1][(smith.y)+1].HexCharacter = 2;
                                smith.y = (smith.y)+1;
                                smith.x = (smith.x)+1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[smith.x][(smith.y)+1].HexType==0 || board[smith.x][(smith.y)+1].HexType==4 || board[smith.x][(smith.y)+1].HexType==5){
                                board[smith.x][smith.y].HexCharacter = 8;
                                board[smith.x][(smith.y)+1].HexCharacter = 2;
                                smith.y = (smith.y)+1;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==5){
                        if(smith.y%2==0){
                            if(board[smith.x][(smith.y)-1].HexType==0 || board[smith.x][(smith.y)-1].HexType==4 || board[smith.x][(smith.y)-1].HexType==5){
                                board[smith.x][smith.y].HexCharacter = 8;
                                board[smith.x][(smith.y)-1].HexCharacter = 2;
                                smith.y = (smith.y)-1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[(smith.x)-1][(smith.y)-1].HexType==0 || board[(smith.x)-1][(smith.y)-1].HexType==4 || board[(smith.x)-1][(smith.y)-1].HexType==5){
                                board[smith.x][smith.y].HexCharacter = 8;
                                board[(smith.x)-1][(smith.y)-1].HexCharacter = 2;
                                smith.y = (smith.y)-1;
                                smith.x = (smith.x)-1;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==6){
                        if(smith.y%2==0){
                            if(board[(smith.x)+1][(smith.y)-1].HexType==0 || board[(smith.x)+1][(smith.y)-1].HexType==4 || board[(smith.x)+1][(smith.y)-1].HexType==5){
                                board[smith.x][smith.y].HexCharacter = 8;
                                board[(smith.x)+1][(smith.y)-1].HexCharacter = 2;
                                smith.y = (smith.y)-1;
                                smith.x = (smith.x)+1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[smith.x][(smith.y)-1].HexType==0 || board[smith.x][(smith.y)-1].HexType==4 || board[smith.x][(smith.y)-1].HexType==5){
                                board[smith.x][smith.y].HexCharacter = 8;
                                board[smith.x][(smith.y)-1].HexCharacter = 2;
                                smith.y = (smith.y)-1;
                            }else{
                                //#####
                            }
                        }
                    }
                }

            }else if(choice2==4){
                for(int i=0;i<move_num;i++){
                    printf("Which direction do you want to move for the %d move?\n", i+1);
                    printf("1.Up   ");
                    printf("2.Down   ");
                    printf("3.UpRight   ");
                    printf("4.DownRight   ");
                    printf("5.UpLeft   ");
                    printf("6.DownLeft   \n");
                    int direction;
                    scanf("%d", &direction);
                    if(direction==1){
                        if(board[(lestrade.x)-1][lestrade.y].HexType==0 || board[(lestrade.x)-1][lestrade.y].HexType==4 || board[(lestrade.x)-1][lestrade.y].HexType==5){
                            board[lestrade.x][lestrade.y].HexCharacter = 8;
                            board[(lestrade.x)-1][lestrade.y].HexCharacter = 3;
                            lestrade.x = (lestrade.x)-1;
                        }else{
                            //###### try again
                        }
                    }else if(direction==2){
                        if(board[(lestrade.x)+1][lestrade.y].HexType==0 || board[(lestrade.x)+1][lestrade.y].HexType==4 || board[(lestrade.x)+1][lestrade.y].HexType==5){
                            board[lestrade.x][lestrade.y].HexCharacter = 8;
                            board[(lestrade.x)+1][lestrade.y].HexCharacter = 3;
                            lestrade.x = (lestrade.x)+1;
                        }else{
                            //#####
                        }
                    }else if(direction==3){
                        if(lestrade.y%2==0){
                            if(board[lestrade.x][(lestrade.y)+1].HexType==0 || board[lestrade.x][(lestrade.y)+1].HexType==4 || board[lestrade.x][(lestrade.y)+1].HexType==5){
                                board[lestrade.x][lestrade.y].HexCharacter = 8;
                                board[lestrade.x][(lestrade.y)+1].HexCharacter = 3;
                                lestrade.y = (lestrade.y)+1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[(lestrade.x)-1][(lestrade.y)+1].HexType==0 || board[(lestrade.x)-1][(lestrade.y)+1].HexType==4 || board[(lestrade.x)-1][(lestrade.y)+1].HexType==5){
                                board[lestrade.x][lestrade.y].HexCharacter = 8;
                                board[(lestrade.x)-1][(lestrade.y)+1].HexCharacter = 3;
                                lestrade.y = (lestrade.y)+1;
                                lestrade.x = (lestrade.x)-1;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==4){
                        if(lestrade.y%2==0){
                            if(board[(lestrade.x)+1][(lestrade.y)+1].HexType==0 || board[(lestrade.x)+1][(lestrade.y)+1].HexType==4 || board[(lestrade.x)+1][(lestrade.y)+1].HexType==5){
                                board[lestrade.x][lestrade.y].HexCharacter = 8;
                                board[(lestrade.x)+1][(lestrade.y)+1].HexCharacter = 3;
                                lestrade.y = (lestrade.y)+1;
                                lestrade.x = (lestrade.x)+1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[lestrade.x][(lestrade.y)+1].HexType==0 || board[lestrade.x][(lestrade.y)+1].HexType==4 || board[lestrade.x][(lestrade.y)+1].HexType==5){
                                board[lestrade.x][lestrade.y].HexCharacter = 8;
                                board[lestrade.x][(lestrade.y)+1].HexCharacter = 3;
                                lestrade.y = (lestrade.y)+1;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==5){
                        if(lestrade.y%2==0){
                            if(board[lestrade.x][(lestrade.y)-1].HexType==0 || board[lestrade.x][(lestrade.y)-1].HexType==4 || board[lestrade.x][(lestrade.y)-1].HexType==5){
                                board[lestrade.x][lestrade.y].HexCharacter = 8;
                                board[lestrade.x][(lestrade.y)-1].HexCharacter = 3;
                                lestrade.y = (lestrade.y)-1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[(lestrade.x)-1][(lestrade.y)-1].HexType==0 || board[(lestrade.x)-1][(lestrade.y)-1].HexType==4 || board[(lestrade.x)-1][(lestrade.y)-1].HexType==5){
                                board[lestrade.x][lestrade.y].HexCharacter = 8;
                                board[(lestrade.x)-1][(lestrade.y)-1].HexCharacter = 3;
                                lestrade.y = (lestrade.y)-1;
                                lestrade.x = (lestrade.x)-1;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==6){
                        if(lestrade.y%2==0){
                            if(board[(lestrade.x)+1][(lestrade.y)-1].HexType==0 || board[(lestrade.x)+1][(lestrade.y)-1].HexType==4 || board[(lestrade.x)+1][(lestrade.y)-1].HexType==5){
                                board[lestrade.x][lestrade.y].HexCharacter = 8;
                                board[(lestrade.x)+1][(lestrade.y)-1].HexCharacter = 3;
                                lestrade.y = (lestrade.y)-1;
                                lestrade.x = (lestrade.x)+1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[lestrade.x][(lestrade.y)-1].HexType==0 || board[lestrade.x][(lestrade.y)-1].HexType==4 || board[lestrade.x][(lestrade.y)-1].HexType==5){
                                board[lestrade.x][lestrade.y].HexCharacter = 8;
                                board[lestrade.x][(lestrade.y)-1].HexCharacter = 3;
                                lestrade.y = (lestrade.y)-1;
                            }else{
                                //#####
                            }
                        }
                    }
                }
            }else if(choice2==5){
                for(int i=0;i<move_num;i++){
                    printf("Which direction do you want to move for the %d move?\n", i+1);
                    printf("1.Up   ");
                    printf("2.Down   ");
                    printf("3.UpRight   ");
                    printf("4.DownRight   ");
                    printf("5.UpLeft   ");
                    printf("6.DownLeft   \n");
                    int direction;
                    scanf("%d", &direction);
                    if(direction==1){
                        if(board[(stealthy.x)-1][stealthy.y].HexType==0 || board[(stealthy.x)-1][stealthy.y].HexType==4 || board[(stealthy.x)-1][stealthy.y].HexType==5){
                            board[stealthy.x][stealthy.y].HexCharacter=8;
                            stealthy.x = (stealthy.x)-1;
                            board[stealthy.x][stealthy.y].HexCharacter=4;
                        }else{
                            //###### try again
                        }
                    }else if(direction==2){
                        if(board[(stealthy.x)+1][stealthy.y].HexType==0 || board[(stealthy.x)+1][stealthy.y].HexType==4 || board[(stealthy.x)+1][stealthy.y].HexType==5){
                            board[stealthy.x][stealthy.y].HexCharacter=8;
                            stealthy.x = (stealthy.x)+1;
                            board[stealthy.x][stealthy.y].HexCharacter=4;
                        }else{
                            //#####
                        }
                    }else if(direction==3){
                        if(stealthy.y%2==0){
                            if(board[stealthy.x][(stealthy.y)+1].HexType==0 || board[stealthy.x][(stealthy.y)+1].HexType==4 || board[stealthy.x][(stealthy.y)+1].HexType==5){
                                board[stealthy.x][stealthy.y].HexCharacter=8;
                                stealthy.y = (stealthy.y)+1;
                                board[stealthy.x][stealthy.y].HexCharacter=4;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[stealthy.x-1][stealthy.y+1].HexType==0 || board[stealthy.x-1][stealthy.y+1].HexType==4 || board[stealthy.x-1][stealthy.y+1].HexType==5){
                                board[stealthy.x][stealthy.y].HexCharacter=8;
                                stealthy.x = stealthy.x-1;
                                stealthy.y = stealthy.y+1;
                                board[stealthy.x][stealthy.y].HexCharacter=4;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==4){
                        if(stealthy.y%2==0){
                            if(board[(stealthy.x)+1][(stealthy.y)+1].HexType==0 || board[(stealthy.x)+1][(stealthy.y)+1].HexType==4 || board[(stealthy.x)+1][(stealthy.y)+1].HexType==5){
                                board[stealthy.x][stealthy.y].HexCharacter=8;
                                stealthy.y = (stealthy.y)+1;
                                stealthy.x = (stealthy.x)+1;
                                board[stealthy.x][stealthy.y].HexCharacter=4;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[stealthy.x][(stealthy.y)+1].HexType==0 || board[stealthy.x][(stealthy.y)+1].HexType==4 || board[stealthy.x][(stealthy.y)+1].HexType==5){
                                board[stealthy.x][stealthy.y].HexCharacter=8;
                                stealthy.y = (stealthy.y)+1;
                                board[stealthy.x][stealthy.y].HexCharacter=4;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==5){
                        if(stealthy.y%2==0){
                            if(board[stealthy.x][(stealthy.y)-1].HexType==0 || board[stealthy.x][(stealthy.y)-1].HexType==4 || board[stealthy.x][(stealthy.y)-1].HexType==5){
                                board[stealthy.x][stealthy.y].HexCharacter=8;
                                stealthy.y = (stealthy.y)-1;
                                board[stealthy.x][stealthy.y].HexCharacter=4;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[(stealthy.x)-1][(stealthy.y)-1].HexType==0 || board[(stealthy.x)-1][(stealthy.y)-1].HexType==4 || board[(stealthy.x)-1][(stealthy.y)-1].HexType==5){
                                board[stealthy.x][stealthy.y].HexCharacter=8;
                                stealthy.y = (stealthy.y)-1;
                                stealthy.x = (stealthy.x)-1;
                                board[stealthy.x][stealthy.y].HexCharacter=4;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==6){
                        if(stealthy.y%2==0){
                            if(board[(stealthy.x)+1][(stealthy.y)-1].HexType==0 || board[(stealthy.x)+1][(stealthy.y)-1].HexType==4 || board[(stealthy.x)+1][(stealthy.y)-1].HexType==5){
                                board[stealthy.x][stealthy.y].HexCharacter=8;
                                stealthy.y = (stealthy.y)-1;
                                stealthy.x = (stealthy.x)+1;
                                board[stealthy.x][stealthy.y].HexCharacter=4;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[stealthy.x][(stealthy.y)-1].HexType==0 || board[stealthy.x][(stealthy.y)-1].HexType==4 || board[stealthy.x][(stealthy.y)-1].HexType==5){
                                board[stealthy.x][stealthy.y].HexCharacter=8;
                                stealthy.y = (stealthy.y)-1;
                                board[stealthy.x][stealthy.y].HexCharacter=4;
                            }else{
                                //#####
                            }
                        }
                    }
                }

            }else if(choice2==6){
                for(int i=0;i<move_num;i++){
                    printf("Which direction do you want to move for the %d move?\n", i+1);
                    printf("1.Up   ");
                    printf("2.Down   ");
                    printf("3.UpRight   ");
                    printf("4.DownRight   ");
                    printf("5.UpLeft   ");
                    printf("6.DownLeft   \n");
                    int direction;
                    scanf("%d", &direction);
                    if(direction==1){
                        if(board[(william.x)-1][william.y].HexType==0 || board[(william.x)-1][william.y].HexType==4 || board[(william.x)-1][william.y].HexType==5){
                            board[william.x][william.y].HexCharacter = 8;
                            board[(william.x)-1][william.y].HexCharacter = 6;
                            william.x = (william.x)-1;
                        }else{
                            //###### try again
                        }
                    }else if(direction==2){
                        if(board[(william.x)+1][william.y].HexType==0 || board[(william.x)+1][william.y].HexType==4 || board[(william.x)+1][william.y].HexType==5){
                            board[william.x][william.y].HexCharacter = 8;
                            board[(william.x)+1][william.y].HexCharacter = 6;
                            william.x = (william.x)+1;
                        }else{
                            //#####
                        }
                    }else if(direction==3){
                        if(william.y%2==0){
                            if(board[william.x][(william.y)+1].HexType==0 || board[william.x][(william.y)+1].HexType==4 || board[william.x][(william.y)+1].HexType==5){
                                board[william.x][william.y].HexCharacter = 8;
                                board[william.x][(william.y)+1].HexCharacter = 6;
                                william.y = (william.y)+1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[(william.x)-1][(william.y)+1].HexType==0 || board[(william.x)-1][(william.y)+1].HexType==4 || board[(william.x)-1][(william.y)+1].HexType==5){
                                board[william.x][william.y].HexCharacter = 8;
                                board[(william.x)-1][(william.y)+1].HexCharacter = 6;
                                william.y = (william.y)+1;
                                william.x = (william.x)-1;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==4){
                        if(william.y%2==0){
                            if(board[(william.x)+1][(william.y)+1].HexType==0 || board[(william.x)+1][(william.y)+1].HexType==4 || board[(william.x)+1][(william.y)+1].HexType==5){
                                board[william.x][william.y].HexCharacter = 8;
                                board[(william.x)+1][(william.y)+1].HexCharacter = 6;
                                william.y = (william.y)+1;
                                william.x = (william.x)+1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[william.x][(william.y)+1].HexType==0 || board[william.x][(william.y)+1].HexType==4 || board[william.x][(william.y)+1].HexType==5){
                                board[william.x][william.y].HexCharacter = 8;
                                board[william.x][(william.y)+1].HexCharacter = 6;
                                william.y = (william.y)+1;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==5){
                        if(william.y%2==0){
                            if(board[william.x][(william.y)-1].HexType==0 || board[william.x][(william.y)-1].HexType==4 || board[william.x][(william.y)-1].HexType==5){
                                board[william.x][william.y].HexCharacter = 8;
                                board[william.x][(william.y)-1].HexCharacter = 6;
                                william.y = (william.y)-1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[(william.x)-1][(william.y)-1].HexType==0 || board[(william.x)-1][(william.y)-1].HexType==4 || board[(william.x)-1][(william.y)-1].HexType==5){
                                board[william.x][william.y].HexCharacter = 8;
                                board[(william.x)-1][(william.y)-1].HexCharacter = 6;
                                william.y = (william.y)-1;
                                william.x = (william.x)-1;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==6){
                        if(william.y%2==0){
                            if(board[(william.x)+1][(william.y)-1].HexType==0 || board[(william.x)+1][(william.y)-1].HexType==4 || board[(william.x)+1][(william.y)-1].HexType==5){
                                board[william.x][william.y].HexCharacter = 8;
                                board[(william.x)+1][(william.y)-1].HexCharacter = 6;
                                william.y = (william.y)-1;
                                william.x = (william.x)+1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[william.x][(william.y)-1].HexType==0 || board[william.x][(william.y)-1].HexType==4 || board[william.x][(william.y)-1].HexType==5){
                                board[william.x][william.y].HexCharacter = 8;
                                board[william.x][(william.y)-1].HexCharacter = 6;
                                william.y = (william.y)-1;
                            }else{
                                //#####
                            }
                        }
                    }
                }
            }else if(choice2==7){
                for(int i=0;i<move_num;i++){
                    printf("Which direction do you want to move for the %d move?\n", i+1);
                    printf("1.Up   ");
                    printf("2.Down   ");
                    printf("3.UpRight   ");
                    printf("4.DownRight   ");
                    printf("5.UpLeft   ");
                    printf("6.DownLeft   \n");
                    int direction;
                    scanf("%d", &direction);
                    if(direction==1){
                        if(board[(jeremy.x)-1][jeremy.y].HexType==0 || board[(jeremy.x)-1][jeremy.y].HexType==4 || board[(jeremy.x)-1][jeremy.y].HexType==5){
                            board[jeremy.x][jeremy.y].HexCharacter = 8;
                            board[(jeremy.x)-1][jeremy.y].HexCharacter = 7;
                            jeremy.x = (jeremy.x)-1;
                        }else{
                            //###### try again
                        }
                    }else if(direction==2){
                        if(board[(jeremy.x)+1][jeremy.y].HexType==0 || board[(jeremy.x)+1][jeremy.y].HexType==4 || board[(jeremy.x)+1][jeremy.y].HexType==5){
                            board[jeremy.x][jeremy.y].HexCharacter = 8;
                            board[(jeremy.x)+1][jeremy.y].HexCharacter = 7;
                            jeremy.x = (jeremy.x)+1;
                        }else{
                            //#####
                        }
                    }else if(direction==3){
                        if(jeremy.y%2==0){
                            if(board[jeremy.x][(jeremy.y)+1].HexType==0 || board[jeremy.x][(jeremy.y)+1].HexType==4 || board[jeremy.x][(jeremy.y)+1].HexType==5){
                                board[jeremy.x][jeremy.y].HexCharacter = 8;
                                board[jeremy.x][(jeremy.y)+1].HexCharacter = 7;
                                jeremy.y = (jeremy.y)+1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[(jeremy.x)-1][(jeremy.y)+1].HexType==0 || board[(jeremy.x)-1][(jeremy.y)+1].HexType==4 || board[(jeremy.x)-1][(jeremy.y)+1].HexType==5){
                                board[jeremy.x][jeremy.y].HexCharacter = 8;
                                board[(jeremy.x)-1][(jeremy.y)+1].HexCharacter = 7;
                                jeremy.y = (jeremy.y)+1;
                                jeremy.x = (jeremy.x)-1;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==4){
                        if(jeremy.y%2==0){
                            if(board[(jeremy.x)+1][(jeremy.y)+1].HexType==0 || board[(jeremy.x)+1][(jeremy.y)+1].HexType==4 || board[(jeremy.x)+1][(jeremy.y)+1].HexType==5){
                                board[jeremy.x][jeremy.y].HexCharacter = 8;
                                board[(jeremy.x)+1][(jeremy.y)+1].HexCharacter = 7;
                                jeremy.y = (jeremy.y)+1;
                                jeremy.x = (jeremy.x)+1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[jeremy.x][(jeremy.y)+1].HexType==0 || board[jeremy.x][(jeremy.y)+1].HexType==4 || board[jeremy.x][(jeremy.y)+1].HexType==5){
                                board[jeremy.x][jeremy.y].HexCharacter = 8;
                                board[jeremy.x][(jeremy.y)+1].HexCharacter = 7;
                                jeremy.y = (jeremy.y)+1;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==5){
                        if(jeremy.y%2==0){
                            if(board[jeremy.x][(jeremy.y)-1].HexType==0 || board[jeremy.x][(jeremy.y)-1].HexType==4 || board[jeremy.x][(jeremy.y)-1].HexType==5){
                                board[jeremy.x][jeremy.y].HexCharacter = 8;
                                board[jeremy.x][(jeremy.y)-1].HexCharacter = 7;
                                jeremy.y = (jeremy.y)-1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[(jeremy.x)-1][(jeremy.y)-1].HexType==0 || board[(jeremy.x)-1][(jeremy.y)-1].HexType==4 || board[(jeremy.x)-1][(jeremy.y)-1].HexType==5){
                                board[jeremy.x][jeremy.y].HexCharacter = 8;
                                board[(jeremy.x)-1][(jeremy.y)-1].HexCharacter = 7;
                                jeremy.y = (jeremy.y)-1;
                                jeremy.x = (jeremy.x)-1;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==6){
                        if(jeremy.y%2==0){
                            if(board[(jeremy.x)+1][(jeremy.y)-1].HexType==0 || board[(jeremy.x)+1][(jeremy.y)-1].HexType==4 || board[(jeremy.x)+1][(jeremy.y)-1].HexType==5){
                                board[jeremy.x][jeremy.y].HexCharacter = 8;
                                board[(jeremy.x)+1][(jeremy.y)-1].HexCharacter = 7;
                                jeremy.y = (jeremy.y)-1;
                                jeremy.x = (jeremy.x)+1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[jeremy.x][(jeremy.y)-1].HexType==0 || board[jeremy.x][(jeremy.y)-1].HexType==4 || board[jeremy.x][(jeremy.y)-1].HexType==5){
                                board[jeremy.x][jeremy.y].HexCharacter = 8;
                                board[jeremy.x][(jeremy.y)-1].HexCharacter = 7;
                                jeremy.y = (jeremy.y)-1;
                            }else{
                                //#####
                            }
                        }
                    }
                }
            }else{
                //####
            }
        }

    }else{        //use ability first
        //system("cls");
        printf("How many characters do you want to bring closer to Goodley?\n");
        int char_num;
        scanf("%d", &char_num);
        for(int j=0;j<char_num;j++){
            printf("Who do you want to bring closer to Goodley?\n");
            printf("1.Sherlock Holmes  ");
            printf("2.John Watson  ");
            printf("3.John Smith  ");
            printf("4.Inspector Lestrade");
            printf("\n5.Miss Stealthy  ");
            printf("6.Sir William Gull  ");
            printf("7.Jeremy Bert  ");
            int choice2;
            scanf("%d", &choice2);
            printf("\nHow many moves do you approach this character?\n");
            int move_num;
            scanf("%d", &move_num);
            if(choice2==1){
                for(int i=0;i<move_num;i++){
                    printf("Which direction do you want to move for the %d move?\n", i+1);
                    printf("1.Up   ");
                    printf("2.Down   ");
                    printf("3.UpRight   ");
                    printf("4.DownRight   ");
                    printf("5.UpLeft   ");
                    printf("6.DownLeft   \n");
                    int direction;
                    scanf("%d", &direction);
                    if(direction==1){
                        if(board[(sherlock.x)-1][sherlock.y].HexType==0 || board[(sherlock.x)-1][sherlock.y].HexType==4 || board[(sherlock.x)-1][sherlock.y].HexType==5){
                            board[sherlock.x][sherlock.y].HexCharacter=8;
                            sherlock.x = (sherlock.x)-1;
                            board[sherlock.x][sherlock.y].HexCharacter=0;
                        }else{
                            //###### try again
                        }
                    }else if(direction==2){
                        if(board[(sherlock.x)+1][sherlock.y].HexType==0 || board[(sherlock.x)+1][sherlock.y].HexType==4 || board[(sherlock.x)+1][sherlock.y].HexType==5){
                            board[sherlock.x][sherlock.y].HexCharacter=8;
                            sherlock.x = (sherlock.x)+1;
                            board[sherlock.x][sherlock.y].HexCharacter=0;
                    }else{
                            //#####
                        }
                    }else if(direction==3){
                        if(sherlock.y%2==0){
                            if(board[sherlock.x][(sherlock.y)+1].HexType==0 || board[sherlock.x][(sherlock.y)+1].HexType==4 || board[sherlock.x][(sherlock.y)+1].HexType==5){
                                board[sherlock.x][sherlock.y].HexCharacter=8;
                                sherlock.y = (sherlock.y)+1;
                                board[sherlock.x][sherlock.y].HexCharacter=0;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[sherlock.x-1][sherlock.y+1].HexType==0 || board[sherlock.x-1][sherlock.y+1].HexType==4 || board[sherlock.x-1][sherlock.y+1].HexType==5){
                                board[sherlock.x][sherlock.y].HexCharacter=8;
                                sherlock.x = sherlock.x-1;
                                sherlock.y = sherlock.y+1;
                                board[sherlock.x][sherlock.y].HexCharacter=0;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==4){
                        if(sherlock.y%2==0){
                            if(board[(sherlock.x)+1][(sherlock.y)+1].HexType==0 || board[(sherlock.x)+1][(sherlock.y)+1].HexType==4 || board[(sherlock.x)+1][(sherlock.y)+1].HexType==5){
                                board[sherlock.x][sherlock.y].HexCharacter=8;
                                sherlock.y = (sherlock.y)+1;
                                sherlock.x = (sherlock.x)+1;
                                board[sherlock.x][sherlock.y].HexCharacter=0;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[sherlock.x][(sherlock.y)+1].HexType==0 || board[sherlock.x][(sherlock.y)+1].HexType==4 || board[sherlock.x][(sherlock.y)+1].HexType==5){
                                board[sherlock.x][sherlock.y].HexCharacter=8;
                                sherlock.y = (sherlock.y)+1;
                                board[sherlock.x][sherlock.y].HexCharacter=0;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==5){
                        if(sherlock.y%2==0){
                            if(board[sherlock.x][(sherlock.y)-1].HexType==0 || board[sherlock.x][(sherlock.y)-1].HexType==4 || board[sherlock.x][(sherlock.y)-1].HexType==5){
                                board[sherlock.x][sherlock.y].HexCharacter=8;
                                sherlock.y = (sherlock.y)-1;
                                board[sherlock.x][sherlock.y].HexCharacter=0;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[(sherlock.x)-1][(sherlock.y)-1].HexType==0 || board[(sherlock.x)-1][(sherlock.y)-1].HexType==4 || board[(sherlock.x)-1][(sherlock.y)-1].HexType==5){
                                board[sherlock.x][sherlock.y].HexCharacter=8;
                                sherlock.y = (sherlock.y)-1;
                                sherlock.x = (sherlock.x)-1;
                                board[sherlock.x][sherlock.y].HexCharacter=0;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==6){
                        if(sherlock.y%2==0){
                            if(board[(sherlock.x)+1][(sherlock.y)-1].HexType==0 || board[(sherlock.x)+1][(sherlock.y)-1].HexType==4 || board[(sherlock.x)+1][(sherlock.y)-1].HexType==5){
                                board[sherlock.x][sherlock.y].HexCharacter=8;
                                sherlock.y = (sherlock.y)-1;
                                sherlock.x = (sherlock.x)+1;
                                board[sherlock.x][sherlock.y].HexCharacter=0;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[sherlock.x][(sherlock.y)-1].HexType==0 || board[sherlock.x][(sherlock.y)-1].HexType==4 || board[sherlock.x][(sherlock.y)-1].HexType==5){
                                board[sherlock.x][sherlock.y].HexCharacter=8;
                                sherlock.y = (sherlock.y)-1;
                                board[sherlock.x][sherlock.y].HexCharacter=0;
                            }else{
                            //#####
                            }
                        }
                    }
                }
            }else if(choice2==2){
                for(int i=0;i<move_num;i++){
                    printf("Which direction do you want to move for the %dth move?\n", i+1);
                    printf("1.Up   ");
                    printf("2.Down   ");
                    printf("3.UpRight   ");
                    printf("4.DownRight   ");
                    printf("5.UpLeft   ");
                    printf("6.DownLeft   ");
                    int direction;
                    scanf("%d", &direction);
                    if(direction==1){
                        if(board[(watson.x)-1][watson.y].HexType==0 || board[(watson.x)-1][watson.y].HexType==4 || board[(watson.x)-1][watson.y].HexType==5){
                            board[watson.x][watson.y].HexCharacter=8;
                            watson.x = (watson.x)-1;
                            board[watson.x][watson.y].HexCharacter=1;
                        }else{
                            //###### try again
                        }
                    }else if(direction==2){
                        if(board[(watson.x)+1][watson.y].HexType==0 || board[(watson.x)+1][watson.y].HexType==4 || board[(watson.x)+1][watson.y].HexType==5){
                            board[watson.x][watson.y].HexCharacter=8;
                            watson.x = (watson.x)+1;
                            board[watson.x][watson.y].HexCharacter=1;
                        }else{
                            //#####
                        }
                    }else if(direction==3){
                        if(watson.y%2==0){
                            if(board[watson.x][(watson.y)+1].HexType==0 || board[watson.x][(watson.y)+1].HexType==4 || board[watson.x][(watson.y)+1].HexType==5){
                                board[watson.x][watson.y].HexCharacter=8;
                                watson.y = (watson.y)+1;
                                board[watson.x][watson.y].HexCharacter=1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[(watson.x)-1][(watson.y)+1].HexType==0 || board[(watson.x)-1][(watson.y)+1].HexType==4 || board[(watson.x)-1][(watson.y)+1].HexType==5){
                                board[watson.x][watson.y].HexCharacter=8;
                                watson.y = (watson.y)+1;
                                watson.x = (watson.x)-1;
                                board[watson.x][watson.y].HexCharacter=1;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==4){
                        if(watson.y%2==0){
                            if(board[(watson.x)+1][(watson.y)+1].HexType==0 || board[(watson.x)+1][(watson.y)+1].HexType==4 || board[(watson.x)+1][(watson.y)+1].HexType==5){
                                board[watson.x][watson.y].HexCharacter=8;
                                watson.y = (watson.y)+1;
                                watson.x = (watson.x)+1;
                                board[watson.x][watson.y].HexCharacter=1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[watson.x][(watson.y)+1].HexType==0 || board[watson.x][(watson.y)+1].HexType==4 || board[watson.x][(watson.y)+1].HexType==5){
                                board[watson.x][watson.y].HexCharacter=8;
                                watson.y = (watson.y)+1;
                                board[watson.x][watson.y].HexCharacter=1;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==5){
                        if(watson.y%2==0){
                            if(board[watson.x][(watson.y)-1].HexType==0 || board[watson.x][(watson.y)-1].HexType==4 || board[watson.x][(watson.y)-1].HexType==5){
                                board[watson.x][watson.y].HexCharacter=8;
                                watson.y = (watson.y)-1;
                                board[watson.x][watson.y].HexCharacter=1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[(watson.x)-1][(watson.y)-1].HexType==0 || board[(watson.x)-1][(watson.y)-1].HexType==4 || board[(watson.x)-1][(watson.y)-1].HexType==5){
                                board[watson.x][watson.y].HexCharacter=8;
                                watson.y = (watson.y)-1;
                                watson.x = (watson.x)-1;
                                board[watson.x][watson.y].HexCharacter=1;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==6){
                        if(watson.y%2==0){
                            if(board[(watson.x)+1][(watson.y)-1].HexType==0 || board[(watson.x)+1][(watson.y)-1].HexType==4 || board[(watson.x)+1][(watson.y)-1].HexType==5){
                                board[watson.x][watson.y].HexCharacter=8;
                                watson.y = (watson.y)-1;
                                watson.x = (watson.x)+1;
                                board[watson.x][watson.y].HexCharacter=1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[watson.x][(watson.y)-1].HexType==0 || board[watson.x][(watson.y)-1].HexType==4 || board[watson.x][(watson.y)-1].HexType==5){
                                board[watson.x][watson.y].HexCharacter=8;
                                watson.y = (watson.y)-1;
                                board[watson.x][watson.y].HexCharacter=1;
                            }else{
                                //#####
                            }
                        }
                    }

                }

            }else if(choice2==3){
                for(int i=0;i<move_num;i++){
                    printf("Which direction do you want to move for the %d move?\n", i+1);
                    printf("1.Up   ");
                    printf("2.Down   ");
                    printf("3.UpRight   ");
                    printf("4.DownRight   ");
                    printf("5.UpLeft   ");
                    printf("6.DownLeft   \n");
                    int direction;
                    scanf("%d", &direction);
                    if(direction==1){
                        if(board[(smith.x)-1][smith.y].HexType==0 || board[(smith.x)-1][smith.y].HexType==4 || board[(smith.x)-1][smith.y].HexType==5){
                            board[smith.x][smith.y].HexCharacter = 8;
                            board[(smith.x)-1][smith.y].HexCharacter = 2;
                            smith.x = (smith.x)-1;
                        }else{
                            //###### try again
                        }
                    }else if(direction==2){
                        if(board[(smith.x)+1][smith.y].HexType==0 || board[(smith.x)+1][smith.y].HexType==4 || board[(smith.x)+1][smith.y].HexType==5){
                            board[smith.x][smith.y].HexCharacter = 8;
                            board[(smith.x)+1][smith.y].HexCharacter = 2;
                            smith.x = (smith.x)+1;
                        }else{
                            //#####
                        }
                    }else if(direction==3){
                        if(smith.y%2==0){
                            if(board[smith.x][(smith.y)+1].HexType==0 || board[smith.x][(smith.y)+1].HexType==4 || board[smith.x][(smith.y)+1].HexType==5){
                                board[smith.x][smith.y].HexCharacter = 8;
                                board[smith.x][(smith.y)+1].HexCharacter = 2;
                                smith.y = (smith.y)+1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[(smith.x)-1][(smith.y)+1].HexType==0 || board[(smith.x)-1][(smith.y)+1].HexType==4 || board[(smith.x)-1][(smith.y)+1].HexType==5){
                                board[smith.x][smith.y].HexCharacter = 8;
                                board[(smith.x)-1][(smith.y)+1].HexCharacter = 2;
                                smith.y = (smith.y)+1;
                                smith.x = (smith.x)-1;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==4){
                        if(smith.y%2==0){
                            if(board[(smith.x)+1][(smith.y)+1].HexType==0 || board[(smith.x)+1][(smith.y)+1].HexType==4 || board[(smith.x)+1][(smith.y)+1].HexType==5){
                                board[smith.x][smith.y].HexCharacter = 8;
                                board[(smith.x)+1][(smith.y)+1].HexCharacter = 2;
                                smith.y = (smith.y)+1;
                                smith.x = (smith.x)+1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[smith.x][(smith.y)+1].HexType==0 || board[smith.x][(smith.y)+1].HexType==4 || board[smith.x][(smith.y)+1].HexType==5){
                                board[smith.x][smith.y].HexCharacter = 8;
                                board[smith.x][(smith.y)+1].HexCharacter = 2;
                                smith.y = (smith.y)+1;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==5){
                        if(smith.y%2==0){
                            if(board[smith.x][(smith.y)-1].HexType==0 || board[smith.x][(smith.y)-1].HexType==4 || board[smith.x][(smith.y)-1].HexType==5){
                                board[smith.x][smith.y].HexCharacter = 8;
                                board[smith.x][(smith.y)-1].HexCharacter = 2;
                                smith.y = (smith.y)-1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[(smith.x)-1][(smith.y)-1].HexType==0 || board[(smith.x)-1][(smith.y)-1].HexType==4 || board[(smith.x)-1][(smith.y)-1].HexType==5){
                                board[smith.x][smith.y].HexCharacter = 8;
                                board[(smith.x)-1][(smith.y)-1].HexCharacter = 2;
                                smith.y = (smith.y)-1;
                                smith.x = (smith.x)-1;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==6){
                        if(smith.y%2==0){
                            if(board[(smith.x)+1][(smith.y)-1].HexType==0 || board[(smith.x)+1][(smith.y)-1].HexType==4 || board[(smith.x)+1][(smith.y)-1].HexType==5){
                                board[smith.x][smith.y].HexCharacter = 8;
                                board[(smith.x)+1][(smith.y)-1].HexCharacter = 2;
                                smith.y = (smith.y)-1;
                                smith.x = (smith.x)+1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[smith.x][(smith.y)-1].HexType==0 || board[smith.x][(smith.y)-1].HexType==4 || board[smith.x][(smith.y)-1].HexType==5){
                                board[smith.x][smith.y].HexCharacter = 8;
                                board[smith.x][(smith.y)-1].HexCharacter = 2;
                                smith.y = (smith.y)-1;
                            }else{
                                //#####
                            }
                        }
                    }
                }

            }else if(choice2==4){
                for(int i=0;i<move_num;i++){
                    printf("Which direction do you want to move for the %d move?\n", i+1);
                    printf("1.Up   ");
                    printf("2.Down   ");
                    printf("3.UpRight   ");
                    printf("4.DownRight   ");
                    printf("5.UpLeft   ");
                    printf("6.DownLeft   \n");
                    int direction;
                    scanf("%d", &direction);
                    if(direction==1){
                        if(board[(lestrade.x)-1][lestrade.y].HexType==0 || board[(lestrade.x)-1][lestrade.y].HexType==4 || board[(lestrade.x)-1][lestrade.y].HexType==5){
                            board[lestrade.x][lestrade.y].HexCharacter = 8;
                            board[(lestrade.x)-1][lestrade.y].HexCharacter = 3;
                            lestrade.x = (lestrade.x)-1;
                        }else{
                            //###### try again
                        }
                    }else if(direction==2){
                        if(board[(lestrade.x)+1][lestrade.y].HexType==0 || board[(lestrade.x)+1][lestrade.y].HexType==4 || board[(lestrade.x)+1][lestrade.y].HexType==5){
                            board[lestrade.x][lestrade.y].HexCharacter = 8;
                            board[(lestrade.x)+1][lestrade.y].HexCharacter = 3;
                            lestrade.x = (lestrade.x)+1;
                        }else{
                            //#####
                        }
                    }else if(direction==3){
                        if(lestrade.y%2==0){
                            if(board[lestrade.x][(lestrade.y)+1].HexType==0 || board[lestrade.x][(lestrade.y)+1].HexType==4 || board[lestrade.x][(lestrade.y)+1].HexType==5){
                                board[lestrade.x][lestrade.y].HexCharacter = 8;
                                board[lestrade.x][(lestrade.y)+1].HexCharacter = 3;
                                lestrade.y = (lestrade.y)+1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[(lestrade.x)-1][(lestrade.y)+1].HexType==0 || board[(lestrade.x)-1][(lestrade.y)+1].HexType==4 || board[(lestrade.x)-1][(lestrade.y)+1].HexType==5){
                                board[lestrade.x][lestrade.y].HexCharacter = 8;
                                board[(lestrade.x)-1][(lestrade.y)+1].HexCharacter = 3;
                                lestrade.y = (lestrade.y)+1;
                                lestrade.x = (lestrade.x)-1;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==4){
                        if(lestrade.y%2==0){
                            if(board[(lestrade.x)+1][(lestrade.y)+1].HexType==0 || board[(lestrade.x)+1][(lestrade.y)+1].HexType==4 || board[(lestrade.x)+1][(lestrade.y)+1].HexType==5){
                                board[lestrade.x][lestrade.y].HexCharacter = 8;
                                board[(lestrade.x)+1][(lestrade.y)+1].HexCharacter = 3;
                                lestrade.y = (lestrade.y)+1;
                                lestrade.x = (lestrade.x)+1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[lestrade.x][(lestrade.y)+1].HexType==0 || board[lestrade.x][(lestrade.y)+1].HexType==4 || board[lestrade.x][(lestrade.y)+1].HexType==5){
                                board[lestrade.x][lestrade.y].HexCharacter = 8;
                                board[lestrade.x][(lestrade.y)+1].HexCharacter = 3;
                                lestrade.y = (lestrade.y)+1;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==5){
                        if(lestrade.y%2==0){
                            if(board[lestrade.x][(lestrade.y)-1].HexType==0 || board[lestrade.x][(lestrade.y)-1].HexType==4 || board[lestrade.x][(lestrade.y)-1].HexType==5){
                                board[lestrade.x][lestrade.y].HexCharacter = 8;
                                board[lestrade.x][(lestrade.y)-1].HexCharacter = 3;
                                lestrade.y = (lestrade.y)-1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[(lestrade.x)-1][(lestrade.y)-1].HexType==0 || board[(lestrade.x)-1][(lestrade.y)-1].HexType==4 || board[(lestrade.x)-1][(lestrade.y)-1].HexType==5){
                                board[lestrade.x][lestrade.y].HexCharacter = 8;
                                board[(lestrade.x)-1][(lestrade.y)-1].HexCharacter = 3;
                                lestrade.y = (lestrade.y)-1;
                                lestrade.x = (lestrade.x)-1;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==6){
                        if(lestrade.y%2==0){
                            if(board[(lestrade.x)+1][(lestrade.y)-1].HexType==0 || board[(lestrade.x)+1][(lestrade.y)-1].HexType==4 || board[(lestrade.x)+1][(lestrade.y)-1].HexType==5){
                                board[lestrade.x][lestrade.y].HexCharacter = 8;
                                board[(lestrade.x)+1][(lestrade.y)-1].HexCharacter = 3;
                                lestrade.y = (lestrade.y)-1;
                                lestrade.x = (lestrade.x)+1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[lestrade.x][(lestrade.y)-1].HexType==0 || board[lestrade.x][(lestrade.y)-1].HexType==4 || board[lestrade.x][(lestrade.y)-1].HexType==5){
                                board[lestrade.x][lestrade.y].HexCharacter = 8;
                                board[lestrade.x][(lestrade.y)-1].HexCharacter = 3;
                                lestrade.y = (lestrade.y)-1;
                            }else{
                                //#####
                            }
                        }
                    }
                }
            }else if(choice2==5){
                for(int i=0;i<move_num;i++){
                    printf("Which direction do you want to move for the %d move?\n", i+1);
                    printf("1.Up   ");
                    printf("2.Down   ");
                    printf("3.UpRight   ");
                    printf("4.DownRight   ");
                    printf("5.UpLeft   ");
                    printf("6.DownLeft   \n");
                    int direction;
                    scanf("%d", &direction);
                    if(direction==1){
                        if(board[(stealthy.x)-1][stealthy.y].HexType==0 || board[(stealthy.x)-1][stealthy.y].HexType==4 || board[(stealthy.x)-1][stealthy.y].HexType==5){
                            board[stealthy.x][stealthy.y].HexCharacter=8;
                            stealthy.x = (stealthy.x)-1;
                            board[stealthy.x][stealthy.y].HexCharacter=4;
                        }else{
                            //###### try again
                        }
                    }else if(direction==2){
                        if(board[(stealthy.x)+1][stealthy.y].HexType==0 || board[(stealthy.x)+1][stealthy.y].HexType==4 || board[(stealthy.x)+1][stealthy.y].HexType==5){
                            board[stealthy.x][stealthy.y].HexCharacter=8;
                            stealthy.x = (stealthy.x)+1;
                            board[stealthy.x][stealthy.y].HexCharacter=4;
                        }else{
                            //#####
                        }
                    }else if(direction==3){
                        if(stealthy.y%2==0){
                            if(board[stealthy.x][(stealthy.y)+1].HexType==0 || board[stealthy.x][(stealthy.y)+1].HexType==4 || board[stealthy.x][(stealthy.y)+1].HexType==5){
                                board[stealthy.x][stealthy.y].HexCharacter=8;
                                stealthy.y = (stealthy.y)+1;
                                board[stealthy.x][stealthy.y].HexCharacter=4;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[stealthy.x-1][stealthy.y+1].HexType==0 || board[stealthy.x-1][stealthy.y+1].HexType==4 || board[stealthy.x-1][stealthy.y+1].HexType==5){
                                board[stealthy.x][stealthy.y].HexCharacter=8;
                                stealthy.x = stealthy.x-1;
                                stealthy.y = stealthy.y+1;
                                board[stealthy.x][stealthy.y].HexCharacter=4;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==4){
                        if(stealthy.y%2==0){
                            if(board[(stealthy.x)+1][(stealthy.y)+1].HexType==0 || board[(stealthy.x)+1][(stealthy.y)+1].HexType==4 || board[(stealthy.x)+1][(stealthy.y)+1].HexType==5){
                                board[stealthy.x][stealthy.y].HexCharacter=8;
                                stealthy.y = (stealthy.y)+1;
                                stealthy.x = (stealthy.x)+1;
                                board[stealthy.x][stealthy.y].HexCharacter=4;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[stealthy.x][(stealthy.y)+1].HexType==0 || board[stealthy.x][(stealthy.y)+1].HexType==4 || board[stealthy.x][(stealthy.y)+1].HexType==5){
                                board[stealthy.x][stealthy.y].HexCharacter=8;
                                stealthy.y = (stealthy.y)+1;
                                board[stealthy.x][stealthy.y].HexCharacter=4;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==5){
                        if(stealthy.y%2==0){
                            if(board[stealthy.x][(stealthy.y)-1].HexType==0 || board[stealthy.x][(stealthy.y)-1].HexType==4 || board[stealthy.x][(stealthy.y)-1].HexType==5){
                                board[stealthy.x][stealthy.y].HexCharacter=8;
                                stealthy.y = (stealthy.y)-1;
                                board[stealthy.x][stealthy.y].HexCharacter=4;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[(stealthy.x)-1][(stealthy.y)-1].HexType==0 || board[(stealthy.x)-1][(stealthy.y)-1].HexType==4 || board[(stealthy.x)-1][(stealthy.y)-1].HexType==5){
                                board[stealthy.x][stealthy.y].HexCharacter=8;
                                stealthy.y = (stealthy.y)-1;
                                stealthy.x = (stealthy.x)-1;
                                board[stealthy.x][stealthy.y].HexCharacter=4;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==6){
                        if(stealthy.y%2==0){
                            if(board[(stealthy.x)+1][(stealthy.y)-1].HexType==0 || board[(stealthy.x)+1][(stealthy.y)-1].HexType==4 || board[(stealthy.x)+1][(stealthy.y)-1].HexType==5){
                                board[stealthy.x][stealthy.y].HexCharacter=8;
                                stealthy.y = (stealthy.y)-1;
                                stealthy.x = (stealthy.x)+1;
                                board[stealthy.x][stealthy.y].HexCharacter=4;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[stealthy.x][(stealthy.y)-1].HexType==0 || board[stealthy.x][(stealthy.y)-1].HexType==4 || board[stealthy.x][(stealthy.y)-1].HexType==5){
                                board[stealthy.x][stealthy.y].HexCharacter=8;
                                stealthy.y = (stealthy.y)-1;
                                board[stealthy.x][stealthy.y].HexCharacter=4;
                            }else{
                                //#####
                            }
                        }
                    }
                }

            }else if(choice2==6){
                for(int i=0;i<move_num;i++){
                    printf("Which direction do you want to move for the %d move?\n", i+1);
                    printf("1.Up   ");
                    printf("2.Down   ");
                    printf("3.UpRight   ");
                    printf("4.DownRight   ");
                    printf("5.UpLeft   ");
                    printf("6.DownLeft   \n");
                    int direction;
                    scanf("%d", &direction);
                    if(direction==1){
                        if(board[(william.x)-1][william.y].HexType==0 || board[(william.x)-1][william.y].HexType==4 || board[(william.x)-1][william.y].HexType==5){
                            board[william.x][william.y].HexCharacter = 8;
                            board[(william.x)-1][william.y].HexCharacter = 6;
                            william.x = (william.x)-1;
                        }else{
                            //###### try again
                        }
                    }else if(direction==2){
                        if(board[(william.x)+1][william.y].HexType==0 || board[(william.x)+1][william.y].HexType==4 || board[(william.x)+1][william.y].HexType==5){
                            board[william.x][william.y].HexCharacter = 8;
                            board[(william.x)+1][william.y].HexCharacter = 6;
                            william.x = (william.x)+1;
                        }else{
                            //#####
                        }
                    }else if(direction==3){
                        if(william.y%2==0){
                            if(board[william.x][(william.y)+1].HexType==0 || board[william.x][(william.y)+1].HexType==4 || board[william.x][(william.y)+1].HexType==5){
                                board[william.x][william.y].HexCharacter = 8;
                                board[william.x][(william.y)+1].HexCharacter = 6;
                                william.y = (william.y)+1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[(william.x)-1][(william.y)+1].HexType==0 || board[(william.x)-1][(william.y)+1].HexType==4 || board[(william.x)-1][(william.y)+1].HexType==5){
                                board[william.x][william.y].HexCharacter = 8;
                                board[(william.x)-1][(william.y)+1].HexCharacter = 6;
                                william.y = (william.y)+1;
                                william.x = (william.x)-1;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==4){
                        if(william.y%2==0){
                            if(board[(william.x)+1][(william.y)+1].HexType==0 || board[(william.x)+1][(william.y)+1].HexType==4 || board[(william.x)+1][(william.y)+1].HexType==5){
                                board[william.x][william.y].HexCharacter = 8;
                                board[(william.x)+1][(william.y)+1].HexCharacter = 6;
                                william.y = (william.y)+1;
                                william.x = (william.x)+1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[william.x][(william.y)+1].HexType==0 || board[william.x][(william.y)+1].HexType==4 || board[william.x][(william.y)+1].HexType==5){
                                board[william.x][william.y].HexCharacter = 8;
                                board[william.x][(william.y)+1].HexCharacter = 6;
                                william.y = (william.y)+1;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==5){
                        if(william.y%2==0){
                            if(board[william.x][(william.y)-1].HexType==0 || board[william.x][(william.y)-1].HexType==4 || board[william.x][(william.y)-1].HexType==5){
                                board[william.x][william.y].HexCharacter = 8;
                                board[william.x][(william.y)-1].HexCharacter = 6;
                                william.y = (william.y)-1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[(william.x)-1][(william.y)-1].HexType==0 || board[(william.x)-1][(william.y)-1].HexType==4 || board[(william.x)-1][(william.y)-1].HexType==5){
                                board[william.x][william.y].HexCharacter = 8;
                                board[(william.x)-1][(william.y)-1].HexCharacter = 6;
                                william.y = (william.y)-1;
                                william.x = (william.x)-1;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==6){
                        if(william.y%2==0){
                            if(board[(william.x)+1][(william.y)-1].HexType==0 || board[(william.x)+1][(william.y)-1].HexType==4 || board[(william.x)+1][(william.y)-1].HexType==5){
                                board[william.x][william.y].HexCharacter = 8;
                                board[(william.x)+1][(william.y)-1].HexCharacter = 6;
                                william.y = (william.y)-1;
                                william.x = (william.x)+1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[william.x][(william.y)-1].HexType==0 || board[william.x][(william.y)-1].HexType==4 || board[william.x][(william.y)-1].HexType==5){
                                board[william.x][william.y].HexCharacter = 8;
                                board[william.x][(william.y)-1].HexCharacter = 6;
                                william.y = (william.y)-1;
                            }else{
                                //#####
                            }
                        }
                    }
                }
            }else if(choice2==7){
                for(int i=0;i<move_num;i++){
                    printf("Which direction do you want to move for the %d move?\n", i+1);
                    printf("1.Up   ");
                    printf("2.Down   ");
                    printf("3.UpRight   ");
                    printf("4.DownRight   ");
                    printf("5.UpLeft   ");
                    printf("6.DownLeft   \n");
                    int direction;
                    scanf("%d", &direction);
                    if(direction==1){
                        if(board[(jeremy.x)-1][jeremy.y].HexType==0 || board[(jeremy.x)-1][jeremy.y].HexType==4 || board[(jeremy.x)-1][jeremy.y].HexType==5){
                            board[jeremy.x][jeremy.y].HexCharacter = 8;
                            board[(jeremy.x)-1][jeremy.y].HexCharacter = 7;
                            jeremy.x = (jeremy.x)-1;
                        }else{
                            //###### try again
                        }
                    }else if(direction==2){
                        if(board[(jeremy.x)+1][jeremy.y].HexType==0 || board[(jeremy.x)+1][jeremy.y].HexType==4 || board[(jeremy.x)+1][jeremy.y].HexType==5){
                            board[jeremy.x][jeremy.y].HexCharacter = 8;
                            board[(jeremy.x)+1][jeremy.y].HexCharacter = 7;
                            jeremy.x = (jeremy.x)+1;
                        }else{
                            //#####
                        }
                    }else if(direction==3){
                        if(jeremy.y%2==0){
                            if(board[jeremy.x][(jeremy.y)+1].HexType==0 || board[jeremy.x][(jeremy.y)+1].HexType==4 || board[jeremy.x][(jeremy.y)+1].HexType==5){
                                board[jeremy.x][jeremy.y].HexCharacter = 8;
                                board[jeremy.x][(jeremy.y)+1].HexCharacter = 7;
                                jeremy.y = (jeremy.y)+1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[(jeremy.x)-1][(jeremy.y)+1].HexType==0 || board[(jeremy.x)-1][(jeremy.y)+1].HexType==4 || board[(jeremy.x)-1][(jeremy.y)+1].HexType==5){
                                board[jeremy.x][jeremy.y].HexCharacter = 8;
                                board[(jeremy.x)-1][(jeremy.y)+1].HexCharacter = 7;
                                jeremy.y = (jeremy.y)+1;
                                jeremy.x = (jeremy.x)-1;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==4){
                        if(jeremy.y%2==0){
                            if(board[(jeremy.x)+1][(jeremy.y)+1].HexType==0 || board[(jeremy.x)+1][(jeremy.y)+1].HexType==4 || board[(jeremy.x)+1][(jeremy.y)+1].HexType==5){
                                board[jeremy.x][jeremy.y].HexCharacter = 8;
                                board[(jeremy.x)+1][(jeremy.y)+1].HexCharacter = 7;
                                jeremy.y = (jeremy.y)+1;
                                jeremy.x = (jeremy.x)+1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[jeremy.x][(jeremy.y)+1].HexType==0 || board[jeremy.x][(jeremy.y)+1].HexType==4 || board[jeremy.x][(jeremy.y)+1].HexType==5){
                                board[jeremy.x][jeremy.y].HexCharacter = 8;
                                board[jeremy.x][(jeremy.y)+1].HexCharacter = 7;
                                jeremy.y = (jeremy.y)+1;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==5){
                        if(jeremy.y%2==0){
                            if(board[jeremy.x][(jeremy.y)-1].HexType==0 || board[jeremy.x][(jeremy.y)-1].HexType==4 || board[jeremy.x][(jeremy.y)-1].HexType==5){
                                board[jeremy.x][jeremy.y].HexCharacter = 8;
                                board[jeremy.x][(jeremy.y)-1].HexCharacter = 7;
                                jeremy.y = (jeremy.y)-1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[(jeremy.x)-1][(jeremy.y)-1].HexType==0 || board[(jeremy.x)-1][(jeremy.y)-1].HexType==4 || board[(jeremy.x)-1][(jeremy.y)-1].HexType==5){
                                board[jeremy.x][jeremy.y].HexCharacter = 8;
                                board[(jeremy.x)-1][(jeremy.y)-1].HexCharacter = 7;
                                jeremy.y = (jeremy.y)-1;
                                jeremy.x = (jeremy.x)-1;
                            }else{
                                //#####
                            }
                        }
                    }else if(direction==6){
                        if(jeremy.y%2==0){
                            if(board[(jeremy.x)+1][(jeremy.y)-1].HexType==0 || board[(jeremy.x)+1][(jeremy.y)-1].HexType==4 || board[(jeremy.x)+1][(jeremy.y)-1].HexType==5){
                                board[jeremy.x][jeremy.y].HexCharacter = 8;
                                board[(jeremy.x)+1][(jeremy.y)-1].HexCharacter = 7;
                                jeremy.y = (jeremy.y)-1;
                                jeremy.x = (jeremy.x)+1;
                            }else{
                                //#####
                            }
                        }else{
                            if(board[jeremy.x][(jeremy.y)-1].HexType==0 || board[jeremy.x][(jeremy.y)-1].HexType==4 || board[jeremy.x][(jeremy.y)-1].HexType==5){
                                board[jeremy.x][jeremy.y].HexCharacter = 8;
                                board[jeremy.x][(jeremy.y)-1].HexCharacter = 7;
                                jeremy.y = (jeremy.y)-1;
                            }else{
                                //#####
                            }
                        }
                    }
                }
            }else{
                //####
            }
        }
        //system("cls");
        printf("\nNow you have to move 1 to 3 hexes\n");
        printf("How many moves do you want to do?\n");
        int number_of_moves;
        scanf("%d", &number_of_moves);
        for(int i=0;i<number_of_moves;i++){
            //system("cls");
        printf("Which direction do you want to move for the %dth move?\n", i+1);
        printf("1.Up   ");
        printf("2.Down   ");
        printf("3.UpRight   ");
        printf("4.DownRight   ");
        printf("5.UpLeft   ");
        printf("6.DownLeft   \n");
        if(board[goodley.x][goodley.y].HexType==4){
            printf("7. Pass Through The Tunnel\n");
        }
        int choice2;
        scanf("%d", &choice2);
        if(choice2==1){
            if(board[(goodley.x)-1][goodley.y].HexType==0 || board[(goodley.x)-1][goodley.y].HexType==4 || board[(goodley.x)-1][goodley.y].HexType==5){
                board[goodley.x][goodley.y].HexCharacter = 8;
                board[(goodley.x)-1][goodley.y].HexCharacter = 5;
                goodley.x = (goodley.x)-1;
            }else{
                //###### try again
            }
        }else if(choice2==2){
            if(board[(goodley.x)+1][goodley.y].HexType==0 || board[(goodley.x)+1][goodley.y].HexType==4 || board[(goodley.x)+1][goodley.y].HexType==5){
                board[goodley.x][goodley.y].HexCharacter = 8;
                board[(goodley.x)+1][goodley.y].HexCharacter = 5;
                goodley.x = (goodley.x)+1;
            }else{
                //#####
            }
        }else if(choice2==3){
            if(goodley.y%2==0){
                if(board[goodley.x][(goodley.y)+1].HexType==0 || board[goodley.x][(goodley.y)+1].HexType==4 || board[goodley.x][(goodley.y)+1].HexType==5){
                    board[goodley.x][goodley.y].HexCharacter = 8;
                    board[goodley.x][(goodley.y)+1].HexCharacter = 5;
                    goodley.y = (goodley.y)+1;
                }else{
                    //#####
                }
            }else{
                if(board[(goodley.x)-1][(goodley.y)+1].HexType==0 || board[(goodley.x)-1][(goodley.y)+1].HexType==4 || board[(goodley.x)-1][(goodley.y)+1].HexType==5){
                    board[goodley.x][goodley.y].HexCharacter = 8;
                    board[(goodley.x)-1][(goodley.y)+1].HexCharacter = 5;
                    goodley.y = (goodley.y)+1;
                    goodley.x = (goodley.x)-1;
                }else{
                    //#####
                }
            }
        }else if(choice2==4){
            if(goodley.y%2==0){
                if(board[(goodley.x)+1][(goodley.y)+1].HexType==0 || board[(goodley.x)+1][(goodley.y)+1].HexType==4 || board[(goodley.x)+1][(goodley.y)+1].HexType==5){
                    board[goodley.x][goodley.y].HexCharacter = 8;
                    board[(goodley.x)+1][(goodley.y)+1].HexCharacter = 5;
                    goodley.y = (goodley.y)+1;
                    goodley.x = (goodley.x)+1;
                }else{
                    //#####
                }
            }else{
                if(board[goodley.x][(goodley.y)+1].HexType==0 || board[goodley.x][(goodley.y)+1].HexType==4 || board[goodley.x][(goodley.y)+1].HexType==5){
                    board[goodley.x][goodley.y].HexCharacter = 8;
                    board[goodley.x][(goodley.y)+1].HexCharacter = 5;
                    goodley.y = (goodley.y)+1;
                }else{
                    //#####
                }
            }
        }else if(choice2==5){
            if(goodley.y%2==0){
                if(board[goodley.x][(goodley.y)-1].HexType==0 || board[goodley.x][(goodley.y)-1].HexType==4 || board[goodley.x][(goodley.y)-1].HexType==5){
                    board[goodley.x][goodley.y].HexCharacter = 8;
                    board[goodley.x][(goodley.y)-1].HexCharacter = 5;
                    goodley.y = (goodley.y)-1;
                }else{
                    //#####
                }
            }else{
                if(board[(goodley.x)-1][(goodley.y)-1].HexType==0 || board[(goodley.x)-1][(goodley.y)-1].HexType==4 || board[(goodley.x)-1][(goodley.y)-1].HexType==5){
                    board[goodley.x][goodley.y].HexCharacter = 8;
                    board[(goodley.x)-1][(goodley.y)-1].HexCharacter = 5;
                    goodley.y = (goodley.y)-1;
                    goodley.x = (goodley.x)-1;
                }else{
                    //#####
                }
            }
        }else if(choice2==6){
            if(goodley.y%2==0){
                if(board[(goodley.x)+1][(goodley.y)-1].HexType==0 || board[(goodley.x)+1][(goodley.y)-1].HexType==4 || board[(goodley.x)+1][(goodley.y)-1].HexType==5){
                    board[goodley.x][goodley.y].HexCharacter = 8;
                    board[(lestrade.x)+1][(lestrade.y)-1].HexCharacter = 5;
                    goodley.y = (goodley.y)-1;
                    goodley.x = (goodley.x)+1;
                }else{
                    //#####
                }
            }else{
                if(board[goodley.x][(goodley.y)-1].HexType==0 || board[goodley.x][(goodley.y)-1].HexType==4 || board[goodley.x][(goodley.y)-1].HexType==5){
                    board[goodley.x][goodley.y].HexCharacter = 8;
                    board[goodley.x][(goodley.y)-1].HexCharacter = 5;
                    goodley.y = (goodley.y)-1;
                }else{
                    //#####
                }
            }
        }else if(choice2==7 && board[goodley.x][goodley.y].HexType==4){
            printf("Which manhole do you want to get out of?\n");
            if(board[0][5].HexType==4){
                printf("1.The manhole in the first row & 6th columns\n");
            }
            if(board[2][0].HexType==4){
                printf("2.The manhole in the 3th row & first column\n");
            }
            if(board[1][11].HexType==4){
                printf("3.The manhole in the 2th row & 12th column\n");
            }
            if(board[3][5].HexType==4){
                printf("4.The manhole in the 4th row & 6th column\n");
            }
            if(board[5][7].HexType==4){
                printf("5.The manhole in the 6th row & 8th column\n");
            }
            if(board[6][2].HexType==4){
                printf("6.The manhole in the 7th row & 3th column\n");
            }
            if(board[8][7].HexType==4){
                printf("7.The manhole in the 9th row & 8th column\n");
            }
            if(board[4][12].HexType==4){
                printf("8.The manhole in the 5th row & 13th column\n");
            }
            int tunnel_choice1;
            scanf("%d", &tunnel_choice1);
            if(tunnel_choice1==1){
                board[goodley.x][goodley.y].HexCharacter = 8;
                goodley.x = 0;
                goodley.y = 5;
                board[goodley.x][goodley.y].HexCharacter = 5;
            }else if(tunnel_choice1==2){
                board[goodley.x][goodley.y].HexCharacter = 8;
                goodley.x = 2;
                goodley.y = 0;
                board[goodley.x][goodley.y].HexCharacter = 5;
            }else if(tunnel_choice1==3){
                board[goodley.x][goodley.y].HexCharacter = 8;
                goodley.x = 1;
                goodley.y = 11;
                board[goodley.x][goodley.y].HexCharacter = 5;
            }else if(tunnel_choice1==4){
                board[goodley.x][goodley.y].HexCharacter = 8;
                goodley.x = 3;
                goodley.y = 5;
                board[goodley.x][goodley.y].HexCharacter = 5;
            }else if(tunnel_choice1==5){
                board[goodley.x][goodley.y].HexCharacter = 8;
                lestrade.x = 5;
                lestrade.y = 7;
                board[goodley.x][goodley.y].HexCharacter = 5;
            }else if(tunnel_choice1==6){
                board[goodley.x][goodley.y].HexCharacter = 8;
                goodley.x = 5;
                goodley.y = 2;
                board[goodley.x][goodley.y].HexCharacter = 5;
            }else if(tunnel_choice1==7){
                board[goodley.x][goodley.y].HexCharacter = 8;
                goodley.x = 8;
                goodley.y = 7;
                board[goodley.x][goodley.y].HexCharacter = 5;
            }else if(tunnel_choice1==8){
                board[goodley.x][goodley.y].HexCharacter = 8;
                goodley.x = 4;
                goodley.y = 12;
                board[goodley.x][goodley.y].HexCharacter = 5;
            }else{
                //to control user foolishness
            }
            

        }else{
            //to control user foolishness
        }
        }
    }
    return board;
}