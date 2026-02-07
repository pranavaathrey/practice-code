#include <stdio.h>

int main(){
    int choice, balance = 0, credeb;
    
    while(choice != 4){
        scanf("%d", &choice);
        
        switch(choice){
            case 1:
                scanf("%d", &credeb);
                balance += credeb;
                printf("Deposit successful.\n");
                break;
            case 2:
                scanf("%d", &credeb);
                if(credeb <= balance){
                    balance -= credeb;
                    printf("Withdrawal successful.\n");
                }else
                    printf("Insufficient balance.\n");
                break;
            case 3:
                printf("Current Balance: %d\n", balance);
                break;
            case 4:
                printf("Exiting program.");
                return 0;
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    }
    return 0;
}