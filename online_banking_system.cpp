#include<bits/stdc++.h>
using namespace std;

class user{
    public:
        char phone[50];
		char ac[50];
		char password[50];
		float balance;
};

int main(){
	user user,u;
	char filename[50],phone[50],password[50],phone2[50];
	FILE *fp,*fptr;
	int opt,choice;
	int amount;
	char cont = 'y';
	system("cls");
	cout<<"\n\nWhat do you want to do?"<<endl;
	cout<<"\n1.Register your account"<<endl;
	cout<<"2.Login to your account"<<endl;
	cout<<"\nPlease enter your choice:  ";
	cin>>opt;
	if(opt == 1){
		system("cls");
		cout<<"\nEnter your account number:\t";
		cin>>user.ac;
		cout<<"Enter your phone number:\t";
		cin>>user.phone;
		cout<<"Enter your new password:\t";
		cin>>user.password;
		user.balance=0;
		strcpy(filename,user.phone);
		fp=fopen(strcat(filename,".dat"),"w");
		fwrite(&user,sizeof(user),1,fp);
		if(fwrite != 0){
			cout<<"Succesfully registered";
		}
	}
	else if(opt == 2){
		system("cls");
		cout<<"\nPhone No.:\t";
		cin>>phone;
		cout<<"Password:\t";
		cin>>password;
		fp = fopen(strcat(phone,".dat"),"r");
		if(fp == NULL) 
			cout<<"Account number not registered";
		else {
			fread(&user,sizeof(struct user),1,fp);
			fclose(fp);
			if(!strcmp(password,user.password)){
				while(cont == 'y'){
				system("cls");
				cout<<"\n\tWelcome "<<user.phone<<endl;
				cout<<"Press 1 for balance inquiry"<<endl;
				cout<<"Press 2 for adding fund"<<endl;
				cout<<"Press 3 for cash withdraw"<<endl;
				cout<<"Press 4 for online transfer"<<endl;
				cout<<"Press 5 for changing password\n\n";
				cin>>choice;
				switch(choice){
					case 1:
						cout<<"Your current balance is Rs. %.2f",user.balance;
						break;

					case 2:
						system("cls");
						cout<<"Enter amount to be added:\t";
						cin>>amount;
						user.balance += amount;
						fp = fopen(phone,"w");
						fwrite(&user,sizeof(struct user),1,fp);
						if(fwrite !=0) 
							cout<<"\n\nYou have depostied Rs."<<amount;
						fclose(fp);
						break;

					case 3:
						system("cls");
						cout<<"Enter withdrawl amount:\t";
						cin>>amount;
						if(amount % 500 != 0) 
							cout<<"\nSorry amount should be multiple of 500";
						else if(amount>user.balance) 
							cout<<"\nSorry insufficeint balance";
						else {
							user.balance -= amount;
						fp = fopen(phone,"w");
						fwrite(&user,sizeof(struct user),1,fp);
						if(fwrite !=0) 
							cout<<"\n\nYou have withdrawn Rs."<<amount;
						fclose(fp);
						}
						break;
					
					case 4:
						cout<<"Please enter the phone number to trasnfer balance:\t";
						cin>>phone;
						cout<<"Enter the amount to transfer:\t";
						cin>>amount;
						if(amount > user.balance) 
							cout<<"\nSorry insufficent balance";
						else {
							fptr = fopen(strcat(phone,".dat"),"r");
							if(fptr==NULL) 
								cout<<"Sorry number is not registered";
							else {
								fread(&u,sizeof(struct user),1,fptr);
								fclose(fptr);
							
								u.balance += amount;
								
								fptr = fopen(phone,"w");
								fwrite(&u,sizeof(struct user),1,fptr);
								if(fwrite != 0){
									cout<<"Your trasfer is completed. You have trasnfered Rs."<<amount<<" to %s"<<u.phone;
									fclose(fptr);
									user.balance -= amount;
									strcpy(filename,user.phone);
									fp = fopen(strcat(filename,".dat"),"w");
									fwrite(&user,sizeof(struct user),1,fp);
									fclose(fp);
								}
							}
						}
						break;
					case 5:
						cout<<"\n\nPlease enter your old password:\t";
						cin>>password;
						if(!strcmp(password,user.password)){
							cout<<"\n\nPlease enter your new password:\t";
							cin>>password;
							strcpy(user.password,password);
							strcpy(filename,user.phone);
							fp = fopen(strcat(filename,".dat"),"w");
							fwrite(&user,sizeof(struct user),1,fp);
							fclose(fp);	
							cout<<"\nPassword succesfullly changed";
						}
						else 
							cout<<"\nSorry your password is wrong";
					
					default:
						break;
				}
				cout<<"\n\nDo you want to continue?[y/n]:\t";
				cin>>cont;
				}
			}
			else {
				cout<<"Invalid password";
			}	
		}
		cout<<"\n\n***Thank you for banking with ADV. bank***\n\n";
	}
	return 0;
}