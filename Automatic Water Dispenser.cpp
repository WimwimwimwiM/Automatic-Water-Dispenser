#include<stdio.h>
#include<stdlib.h>
#include <string.h>
//switch case in main
char choice;
//data menu user
int menu[100];
int item[100];
//check_order and sum order
int check_order = 0;
int total_order = 0;
//money value
int result = 0;
int money = 0;
int total_money = 0;
int discount = 0;
//all member value
char number[11];
char member_num[11];
int allmember_check = 0;

int reset_value(int *rm,int *ri) { //reset value
 for(total_order;total_order>=0;total_order--) {
 	rm[total_order]  = 0;
    ri[total_order] = 0;
 }	
 choice = 0;

 check_order = 0;
 total_order = 0;

 result = 0;
 money = 0 ;
 total_money = 0;
 discount = 0;

 number[11] = '0';
 member_num[11] = '0';
 allmember_check = 0;

}

int Menu(int *m,int *p){ //menu in this program
    printf("Choose your Item\n\n");
    int break_loop_menu = 0;
    do{
    	if (total_order >= 90) {
    		system("cls");
    		printf("Limit order!\n");
    		break;
    	}
    	char count;
    	printf("1.Water : 10 baht\n2.Milk  : 15 baht \n3.Coke  : 20 baht\n\nItem : ");
    	scanf("%d",& m[total_order]);
    	system("cls");
    	printf("How many pieces\n\npieces : ");
    	scanf("%d",& p[total_order]);
    	system("cls");
    	while(1) {
    	printf("If you want to buy again please press 1.\nIf you don't buy press 0.\n\npress : ");
    	scanf("%s",&count);
    	total_order++;
	    if (count == '1' ) {
    	    system("cls");
    	    break;
		}else if (count == '0') {
			system("cls");
			break_loop_menu = 1;
			break;
		}else {
			system("cls");
			printf("please press the correct button!\n\n");
		}
	}
	if(break_loop_menu == 1) {
		break;
	}
	}while (total_order<100) ;
}		

int cal_price(int *M, int *I) { //calculate price
	int sum1 = 0;
	int sum2 = 0;
	int sum3 = 0;
	for (total_order;total_order >= 0;total_order--) {
		if (M[total_order] == 1) {
			sum1 = sum1 + I[total_order]*10;
			M[total_order] = 0;
			I[total_order] = 0;
		}else if (M[total_order] == 2) {
			sum2 +=  I[total_order]*15;
			M[total_order] = 0;
			I[total_order] = 0;
		}else if (M[total_order] == 3) {
			sum3 +=  I[total_order]*20;
			M[total_order] = 0;
			I[total_order] = 0;
		}
	}
	return sum1+sum2+sum3;
}
int change_money(void) { //change money
	while (1) {
	int discount_member = result;
	if (discount == 1) {
		discount_member *= 0.1;
	}else {
		discount_member = 0;
	}
	printf("All price %d Baht Account balance %d Baht : ",result-discount_member,result - discount_member - total_money);
	scanf("%d",&money);
	total_money += money;
	system("cls");
	if (result - discount_member - total_money <= 0 ) {
        	int balance = total_money - (result - discount_member);
        	return balance;
        	break;
		}else{
			printf("Insufficient balance!\n\n");
		}
	 }    
}

int check_allmember() { //check allmember in file
	FILE*member;
	member = fopen("All_Member.txt", "r");
	int found = 0;
	while (fscanf(member, "%s",member_num) != EOF) {
		if (strcmp(member_num, number) == 0) {	
		    found = 1;
		    break;	
		}
	}
	return found;
	fclose(member);
}
void add_allmember(void) { //add allmember in file
	FILE*member;
	member = fopen("All_Member.txt","a+");
	fprintf(member, "%s\n",number);
	fclose(member);
}
int all_member () { //allmember function
	int break_loop = 0;
	while(1) {
	    char all_count;
	    printf("Do you have an all member? \n\nIf you have please press 1.\nIf you don't have press 0.\n\n");
        printf("press : ");
        scanf("%s",&all_count);
        system("cls");
        if (all_count == '1') {
        	while (1) {
			    printf("press your number : ");	
        	    scanf("%s",&number);
        	    system("cls");
        	    int check = 0;
        	    check = check_allmember();
        	    if (check==1) {
        	    	printf("You price receive a 10 percent discount.\n\n");
        	    	discount = 1;
        	    	break_loop = 1;
        	    	allmember_check = 1;
        	    	break;
				}else {
					printf("You don't have an allmember\n\n");
					break;	
					}
				}	          	    
			}else if (all_count == '0') {
				int count;
			    printf("Would you like to sign up for All Member?\n\nIf you want please press 1.\nIf you don't want press 0.\n\n");
			    printf("press : ");
			    scanf("%d",&count);
			    system("cls");
			    if (count==1) {
        	    	printf("press your number : ");
        	    	scanf("%s",&number);
        	    	int check = 0;
        	        check = check_allmember();
        	        if (check==1) {
        	        	system("cls");
        	        	printf("Your ID is in the system!\n\n");
        	        	discount = 1;
        	        	break_loop = 1;
        	        	allmember_check = 1;
        	        	break;
					}else{
						add_allmember();
        	    	    break_loop = 1;
        	    	    system("cls");
        	    	    printf("Thank for sign up!\n\n");
			            printf("You price receive a 10 percent discount later.\n\n");
			            allmember_check = 1;
			            discount = 1;
        	    	    break;
					}        	    	
				}else if (count == 0) {
					system("cls");
					break_loop = 1;
					allmember_check = 1;
					break;	
					}
		}else {
		    printf("please press the correct button!\n\n");	
		}
		if(break_loop!=0) {
			break;
		}
	}
}

void Review_order(int *m,int *i) { //review order for cancle or changemoney
	int round_review = total_order;
	while(1) {
		int round_change = 0;
		printf("| Order Review |\n");
	    printf("----------------------------\n\n");
	    for (round_review;round_review >= 0;round_review--) {
		    if (m[round_review] == 1) {
			    printf("Order %d : Water : %d pieces\n",round_review+1,i[round_review]);
			    round_change++;
		    }else if (m[round_review] == 2) {
			    printf("Order %d : Milk : %d pieces\n",round_review+1,i[round_review]);
			    round_change++;
		    }else if (m[round_review] == 3) {
			    printf("Order %d : Coke : %d pieces\n",round_review+1,i[round_review]);
			    round_change++;
		    }		
	    }
	    if(round_change==0) {
	    	check_order = 1;
	    	system("cls");
	    	break;
		}
		printf("\n----------------------------\n\n");
	    int count;
	    printf("Cancle Order press 0\nCharge money press 1\n\npress : ");
	    scanf("%d",&count);
		    if(count==0) {
	            system("cls");
	            int c;
	            printf("Which order will you cancle : ");
	            scanf("%d",&c);
	            if (c <= round_change&& m[c-1]!=0) {
	            	system("cls");
	            	round_change-1;
	            	m[c-1] = 0;
	            	i[c-1] = 0;
	        	    printf("Cancle succeed!\n\n");
			    }else {
				    system("cls");
				    printf("Your order is not available!\n\n");
			    }
	        }else if (count==1) {
	    	    system("cls");
	    	    break;
		    }else {
		    	system("cls");
		    	printf("please press the correct button!\n\n");
			}
		round_review = round_change;
	}
	
}

int main() { //main program
	//fr code I hope you get 5 point for us nakub eiei
	while (1) {
		printf("-------------------------------------\n");
		printf("Welcome to Automatic Water Dispenser.\n");
		printf("-------------------------------------\n\n");
		printf("Please choose botton!\n\n");
	    printf("1.Menu\n2.Review Order\n3.All member\n4.Reset\n\npress : ");
	    scanf("%s",&choice);
	    switch (choice) {
	        case '1' :  system("cls");
			         Menu(menu,item);
	                 break;
	        case '2' : system("cls");
	                 Review_order(menu,item);
	                 system("cls");
	                 if (check_order == 1){
	                 	reset_value(menu,item);
	                 	break;
					 }else if(allmember_check == 0) {
	                 	all_member();
					 }
			         result = cal_price(menu,item);
                     printf("Cash change : %d Baht\n\n",change_money());
                     printf("Thank you I hope you get 5 point for us nakub eiei!\n\n");
                     printf("--------------------------------------------------\n\n");
                     reset_value(menu,item);
			         break;
			case '3' : system("cls");
			         all_member();
			         printf("--------------------------------------------------\n\n");
			         break;
			case '4' : system("cls");
			         reset_value(menu,item);
			         break;	
		    default :printf("please press the correct button!\n\n");
			         break;  		         
		 }
	}   //demo code 
		/*int menu[100]  = {0};
        int item[100] = {0};
        int all_count = 0;
		printf("Welcome to Automatic Water Dispenser.\n\n");
        Menu(menu,item);
        all_member();
        result = cal_price(menu,item);
        printf("Cash change : %d\n\n",change_money());
        printf("Thank you I hope  you get 5 point for us eiei!\n\n");
        printf("--------------------------------------------------\n\n");
        reset();*/
}

