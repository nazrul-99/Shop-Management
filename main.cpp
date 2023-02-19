#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<fstream>
#include<conio.h>


using namespace std;


ifstream fin;
ofstream fout;
fstream fio;


const int session=50;
int i,n,frog=0;
char user[10];
char pass[10];




class product
{
    char name[20];
    float price;
    int quant;
public:
    void get();
    void show();
    int token(char nm[30]);
    void refil(int qty);
    bool withd(int qty);
    void withdraw(int qty);
    void get_c(int a);
    void see();
    int bill();
    bool bought();
    void deleted_c();
    int restock();
} st,s[session];


void product::get()
{
    cout << "Name : \t" ;
    cin >> name ;
    cout << "Price : ";
    cin >> price;
    cout << "Quantity : ";
    cin >> quant;
}

void product::show()
{
    cout<<"\n"<<name<<"\t\t\t"<<quant<<"\t\t\t"<<price;
}

int product::token(char nm[30])
{
    if(strcmp(nm,name)==0)
        return 0;
    else
        return 1;
}

void product::refil(int qty)
{
    quant+=qty;
}

bool product::withd(int qty)
{
    if(quant>=qty)
    {
        return true;
    }
    else
    {
        return false;
    }

}

void product::withdraw(int qty)
{
    if(quant>=qty)
    {
        quant-=qty;
    }
    else
    {
        cout<<"\n\nInsufficient stock";
    }
    getch();
}

void product::get_c(int a)
{
    quant=a;
}

void product::see()
{
    system("cls");
    cout << "\n\n\n\t\tYou have just purchased :" << endl << "\nName : " << name << endl << "\nPrice : " << price << endl << "\nQuantity : " << quant <<endl;
}

int product::bill()
{
    return (price*quant);
}

bool product::bought()
{
    if (price!=0)
    {
        return true;
    }
    else
        return false;
}

void product::deleted_c()
{
    quant = 0;
}

int product::restock()
{
    return quant;
}




class employee : public product
{
public:
    void disp();
    void login();
    void refill(char temp[100],int qty);
};

void employee::disp()
{
    int i=1;
    cout<<"\n==================================================================";
    cout<<"\n\n=================\tTHE STOCK ITEMS ARE\t==================";
    cout<<"\n\n==================================================================\n";
    cout<<"\n\nITEMS\t\tSTOCK AVAILABLE\t\t\tPRICE";
    cout<<"\n\n============================================================\n";
    fin.open("shop.csv");
    while(!fin.eof())
    {
        fin.read((char*)&st,sizeof(st));
        if(!fin.eof())
        {
            if(fin.tellg()<0)
            {
                i=0;
                break;
            }
            st.show();
        }
    }
    if(i==0)
    {
        cout<<"\n\n\t\t\t!!Empty record room!!";
    }
    fin.close();
}

void employee::login()
{
    int a=0,i=0;
    char username[10],c=' ';
    char password[10];
    do
    {
        cout << "\n\n\n\n\n\n\n\t\t\t|============ Enter Your Username and Password ============|\n";
        cout << "\t\t\t\t\tENTER USERNAME :";
        cin >> username;
        cout << "\t\t\t\t\tENTER PASSWORD :";

        while(i<10)
        {
            password[i]=getch();
            c=password[i];
            if(c==13)
                break;
            else
                cout <<"*";
            i++;
        }
        password[i]='\0';

        i=0;

        if(strcmp(username,user)==0 && strcmp(password,pass)==0)
        {
            cout << endl ;
            cout << "\t\t\t\t Accessed as ADMINISTRATOR !!!" << endl ;
            getch();
            break;
        }
        else
        {
            cout << "\n\t\t\t\tSORRY !!!!  LOGIN IS UNSUCESSFUL\n\n\t\t\t\tAuthorised Personnel Only\n\n";
            a++;
            getch();
            system("cls");

        }
    }
    while(a<=2);
    if (a>2)
    {
        cout << endl;
        cout << "\n\t\t\tSorry you have entered the wrong username and password for three times!!!";
        getch();
        //cout << "\n\n\t\t\t\t\t\t\t\t\t-------------------Created by NAZRUL,1707086";
        //getch();
        exit(0);
    }

}

void employee::refill(char temp[100],int qty)
{
    int i=0;
    long pos=0;
    fio.open("shop.csv",ios::out|ios::in);
    while(!fio.eof())
    {
        pos=fio.tellp();
        fio.read((char*)&st,sizeof(st));
        if(st.token(temp)==0)
        {

            st.refil(qty);
            fio.seekp(pos);
            fio.write((char*)&st,sizeof(st));
            i++;
            break;
        }
    }
    if(i!=1)
    {
        cout<<"\n\n!!Record not found!!";
    }
    fio.close();
}




class owner : public employee
{
public:
    void addnew();
    void removed();
    void modify();
    virtual void display(){ };
};

void owner::addnew()
{
    system("cls");
    disp();
    getch();
    system("cls");
    cout<<"\nEnter the No. of Products that you wish to add: ";
    cin>>n;

    if (n!=0)
    {
        fout.open("shop.csv",ios::app);
        for(i=0; i<n; i++)
        {
            cout<<"\nInput the name, price and the quantity of item respectively\n";
            st.get();
            fout.write((char*)&st,sizeof(st));
            cout<<"\n\nitem Added!!";
        }
        fout.close();
    }
    else
    {
        fout.close();
        system("cls");
        cout<<"\n\nNo items to be added" << endl;
        getch();
        //cout << "\n\n\t\t\t\t\t\t\t\t\t-------------------Created by NAZRUL,1707086";
        //getch();
        exit(0);
    }
}

void owner::removed()
{
    system("cls");
    int i=0;
    char temp[30];
    disp();
    cout << "\n\n|============ Delete Record ============|\n";
    cout<<"\n\nEnter the name of the product :\n";
    cin>>temp;
    fout.open("temp.csv");
    fin.open("shop.csv");
    while(!fin.eof())
    {
        fin.read((char*)&st,sizeof(st));
        if(!fin.eof()){
            if(st.token(temp)==0)
            {
                st.show();
                cout<<"\n\n\t\tRecord Deleted !!!";
                i++;
            }
            else{
                fout.write((char*)&st,sizeof(st));
            }
        }
    }
    if(i==0)
    {
        cout<<"\n\n!!Record not found!!";
    }
    fin.close();
    fout.close();
    remove("shop.csv");
    rename("temp.csv","shop.csv");
}

void owner::modify()
{
    system("cls");
    char temp[100];
    int i=0;
    long pos=0;
    disp();
    cout<<"\n\nEnter the product's name :\n";
    cin>>temp;
    fio.open("shop.csv",ios::out|ios::in);
    while(!fio.eof())
    {
        pos=fio.tellp();
        fio.read((char*)&st,sizeof(st));
        if(st.token(temp)==0)
        {
            cout<<"\nInput the name, price and the quantity of item respectively\n";
            st.get();
            fio.seekp(pos);
            fio.write((char*)&st,sizeof(st));
            cout<<"\n\nitem updated";
            getch();
            i++;
            break;
        }
    }
    if(i!=1)
    {
        cout<<"\n\n!!Record not found!!";
    }
    fio.close();
}




class customer : public owner
{
public:
    void purchase();
    void display();

};

void customer::purchase()
{
    system("cls");
    char temp[100];
    int qty;
    int i=0;
    long pos=0;
    disp();
    cout<<"\n\nEnter the product's name :"<<endl;
    cin>>temp;
    cout<<"Enter quantity :"<<endl;
    cin>>qty;
    fio.open("shop.csv",ios::out|ios::in);
    while(!fio.eof())
    {
        pos=fio.tellp();
        fio.read((char*)&st,sizeof(st));
        if(st.token(temp)==0)
        {
            if(st.withd(qty))
            {
                st.withdraw(qty);
                s[frog]=st;
                s[frog].get_c(qty);
                s[frog].see();
                getch();
                ++frog;
                fio.seekp(pos);
                fio.write((char*)&st,sizeof(st));
                i++;
                break;
            }
            else
            {
                st.withdraw(qty);
                i++;
                break;
            }
        }
    }
    if(i!=1)
    {
        cout<<"\n\n!!Record not found!!";
        getch();
    }
    fio.close();
    system("cls");
}

void customer::display()
{
    system("cls");
    cout << "\n\n\t\t  Your Purchased Items are" << endl ;
    cout<<"\n\n==================================================================\n";
    cout<<"\n\nITEMS\t\tPURCHASED ITEM\t\t\t PRICE";
    cout<<"\n\n============================================================\n";
    for (int show=0; s[show].bought(); show++)
    {
        s[show].show();
    }
    getch();
}




int main()
{
    char i,j;

    cout<<"\n\n\n\n\n\n\n\t\t\t\t|============ WELCOME TO STORE MANAGEMENT ============|";
    cout << "\n\n\t\t\t\t\t     Press any key to continue...";

    getch();

menu:
    system("cls");

    cout<<"\n\t\t   STORE MANAGEMENT SYSTEM\n";
    cout<<"=============================================================";
    cout<<"\n\n\t\t   1. Owner Menu\n\n\t\t   2. Customer Menu\n\n\t\t   3. Employee Menu";
    cout<<"\n\n=============================================================\n";
    cout<<"\n\nEnter Your Choice :\t";
    cin>>j;


    if(j=='1')
    {
        system("cls");

        owner a;

        char user_o[]="user";
        char pass_o[]="pass";
        strcpy(user,user_o);
        strcpy(pass,pass_o);

        a.login();

        cout << "\n\n\t\t\t\t\t OWNER !!!" << endl ;
        getch();

owner_menu:
        system("cls");

        cout << "\n\n\t\t\tOWNER !!!" << endl ;
        cout<<"=================================================================";
        cout<<"\n\n\t\t\t    OWNER MENU\n1. Add new product\n2. Display stock\n3. Refill\n4. Remove an item\n5. Modify an item\n6. Exit:";
        cout<<"\n\n\n==========================END OF MENU=============================";
        cout<<"\n\n Enter your Choice :\t";
        cin>>i;

        if(i=='1')
        {
            a.addnew();
            getch();
            goto owner_menu;
        }

        else if(i=='2')
        {
            system("cls");
            a.disp();
            getch();
            goto owner_menu;
        }

        else if(i=='3')
        {
            system("cls");
            a.disp();
            char temp[100];
            int qty;
            cout<<"\n\nEnter the products name :"<<endl;
            cin>>temp;
            cout<<"\nEnter quantity :"<<endl;
            cin>>qty;
            a.refill(temp,qty);
            cout<<"\n\nStock updated.";
            getch();
            goto owner_menu;
        }

        else if(i=='4')
        {
            system("cls");
            a.removed();
            getch();
            goto owner_menu;
        }

        else if(i=='5')
        {
            a.modify();
            goto owner_menu;
        }

        else if(i=='6')
        {
            system("cls");
            cout<<"\n\n\n\t\t\tThank You!!";
            getch();
            //cout << "\n\n\t\t\t\t\t\t\t\t\t-------------------Created by NAZRUL,1707086";
            //getch();
            exit(0);
        }

        else
        {
            system("cls");
            cout<<"\n\n\n\t\t\tInvalid Option!!";
            getch();
            goto owner_menu;
        }
    }


    else if(j=='2')
    {
        system("cls");

        customer b;

        cout << "\n\n\n\n\n\n\n\t\t\t\tAccessed as CUSTOMER !!!";
        getch();

customer_menu:
        system("cls");

        cout<<"=================================================================";
        cout<<"\n\n\t\t\t    CUSTOMER MENU\n1. Purchase\n2. Display stock\n3. Purchased Item\n4. Remove an Purchased Item\n5. Generate Bill\n6. Exit";
        cout<<"\n\n\n==========================END OF MENU=============================";
        cout<<"\n\n Enter your Choice :\t";
        cin>>i;

        if (i=='1')
        {
            b.purchase();
            goto customer_menu;
        }

        else if(i=='2')
        {
            system("cls");
            b.disp();
            getch();
            goto customer_menu;
        }

        else if (i=='3')
        {
            owner *o;
            customer c;
            o=&c;

            o->display();
            goto customer_menu;
        }

        else if (i=='4')
        {
            char dl[30];
            b.display();
            cout << "\n\n\n\n|============ Enter Your Choice of Item to Remove ============|\n\n";
            cout << "Item Name :\n";
            cin >> dl;
            for ( int del=0; del<50; del++)
            {
                if(s[del].token(dl)==0)
                {
                    b.refill(dl,s[del].restock());
                    s[del].deleted_c();
                }
            }
            goto customer_menu;
        }

        else if (i=='5')
        {
            cout << "\n\n\t\t\t||| Generating Your Bill |||" << endl << endl ;
            cout << "\n\n\t\t\tPress any key to see BILL...";
            getch();
            int bill = 0;
            for ( int bug=0; bug<50; bug++)
            {
                bill += s[bug].bill();
            }
            cout << "\n\n\n\t\t\tYour Bill is : \t" <<  bill;
            getch();
            cout<<"\n\n\n\t\t\tThank You for Shopping with Us !!";
            getch();
            //cout << "\n\n\t\t\t\t\t\t\t\t\t-------------------Created by NAZRUL,1707086";
            //getch();
            exit (0);
        }

        else if (i=='6')
        {
            system("cls");
            cout<<"\n\n\n\t\t\tThank You!!";
            getch();
            //cout << "\n\n\t\t\t\t\t\t\t\t\t-------------------Created by NAZRUL,1707086";
            //getch();
            exit(0);
        }

        else
        {
            system("cls");
            cout<<"\n\n\n\t\t\tInvalid Option!!";
            getch();
            goto customer_menu;
        }
    }


    else if(j=='3')

    {
        system("cls");

        employee e;

        char user_e[]="emp";
        char pass_e[]="passe";
        cout << endl << user[1] << endl << pass[1];
        strcpy(user,user_e);
        strcpy(pass,pass_e);

        e.login();

        cout << "\n\n\t\t\t\t\tEMPLOYER !!!" << endl ;
        getch();

employee_menu:
        system("cls");

        cout << "\n\n\t\t\tEmployee !!!" << endl ;
        cout<<"=================================================================";
        cout<<"\n\n\t\t\tEMPLOYEE MENU\n1. Display stock\n2. Refill\n3. Exit";
        cout<<"\n\n\n==========================END OF MENU=============================";
        cout<<"\n\n Enter your Choice :\t";
        cin>>i;

        system("cls");

        if(i=='1')
        {
            system("cls");
            e.disp();
            getch();
            goto employee_menu;
        }
        else if(i=='2')
        {
            e.disp();
            char temp[100];
            int qty;
            cout<<"\n\nEnter the products name :"<<endl;
            cin>>temp;
            cout<<"\nEnter quantity :"<<endl;
            cin>>qty;
            e.refill(temp,qty);
            cout<<"\n\nStock updated.";
            getch();
            goto employee_menu;
        }
        else if(i=='3')
        {
            system("cls");
            cout<<"\n\n\n\t\t\tThank You!!";
            //getch();
            //cout << "\n\n\t\t\t\t\t\t\t\t\t-------------------Created by NAZRUL,1707086";
    getch();
            exit(0);
        }
        else
        {
            system("cls");
            cout<<"\n\n\n\t\t\tInvalid Option!!";
            getch();
            goto employee_menu;
        }
    }

    else
    {
        system("cls");
        cout<<"\n\n\n\t\t\tInvalid Option!!";
        getch();
        goto menu;
    }
    //cout << "\n\n\t\t\t\t\t\t\t\t\t-------------------Created by NAZRUL,1707086";
    //getch();
    return 0;
}



