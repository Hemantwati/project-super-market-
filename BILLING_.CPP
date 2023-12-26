#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<stdio.h>
#include<process.h>

class product
{
	int pno;
	char name[25];
	float price,qty,tax,dis;
public:
	void create_product()
	{
	     cout<<"\n Please enter the Product no. of the product: ";
	     cin>>pno;
	     cout<<"\n Please enter product name";
	     gets(name);
	     cout<<"\n Please enter the price of the product:";
	     cin>>price;
	     cout<<"\n Please enetr the discount:";
	     cin>>dis;
	}

	void show_product()
	{
	     cout<<"\n The product no.of the product :"<<pno;
	     cout<<"\n The name of the product:";
	     puts(name);
	     cout<<"\n The price of the product:"<<price;
	     cout<<"\n Discount:"<<dis;
	}

	int retpno()
	{
	     return pno;
	}

	float retprice()
	{
	      return price;
	}

	char *retname()
	{
	      return name;
	}

	int retdis()
	{
	      return dis;
	}
};

fstream fp;
product pr;

void write_product()
{
	 fp.open("shop.dat",ios::app);
	 pr.create_product();
	 fp.write((char*)&pr,sizeof(product));
	 fp.close();
	 cout<<"/n/n The product has been created.";
	 getch();
}

void display_all()
{
	clrscr();
	cout<<"\n\n\t\t DISPLAY ALL THE RECORD !!!\n\n";
	fp.open("shop.dat",ios::in);
	while(fp.read((char*)&pr,sizeof(product)))
	{
	      pr.show_product();
	      getch();
	}
	fp.close();
	getch();
}

void display_sp(int n)
{
       int flag=0;
       fp.open("shop.dat",ios::in);
       while(fp.read((char*)&pr,sizeof(product)))
       {
	      if(pr.retpno()==n)
	      {
		     clrscr();
		     pr.show_product();
		     flag=1;
	      }
       }
       fp.close();
       if(flag==0)
       cout<<"\n\n Record not exist";
       getch();
}

void modify_product()
{
       int no,found=0;
       clrscr();
       cout<<"\n\n to nodify:";
       cout<<"\n\n\t Please enter the product no. of the product:";
       cin>>no;
       fp.open("shop.dat",ios::in|ios::out);
       while(fp.read((char*)&pr,sizeof(product))&&found==0)
       {
	      if(pr.retpno()==no)
	      {
		    pr.show_product();
		    cout<<"\n Please enter the new details of the product:"<<endl;
		    pr.create_product();
		    int pos=-1 * sizeof(pr);
		    fp.seekp(pos,ios::cur);
		    fp.write((char*)&pr,sizeof(product));
		    cout<<"\n\n\t Record updated";
		    found = 1;
	      }
       }
       fp.close();
       if(found==0)
       cout<<"\n\n Record not found";
       getch();
}

void delete_product()
{
	int no;
	clrscr();
	cout<<"\n\n\nDelete Record";
	cout<<"\n\n Please enter the product no.of the product you want to delete";
	cin>>no;
	fp.open("shop.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&pr,sizeof(product)))
	{
		if(pr.retpno()!=no)
		{
			fp2.write((char*)&pr,sizeof(product));
		}
	}
	fp2.close();
	fp.close();
	remove("shop.dat");
	rename("temp.dat","shop.dat");
	cout<<"\n\n\t Record Deleted....";
	getch();
}



void menu()
{
	clrscr();
	fp.open("shop.dat",ios::in);
	if(!fp)
	{
		cout<<"\n\n ERROR!!! file could not be open\n\n\n GO TO Admin menu to create file";
		cout<<"\n\n Program is closing.....";
		getch();
		exit(0);
	}
	cout<<"\n\t Product Menu \n\n";
	cout<<"=================================================\n";
	cout<<"P.NO\t\t\t NAME \t\t\t\t price\n";
	cout<<"=================================================\n";
	while(fp.read((char*)&pr,sizeof(product)))
	{
		cout<<pr.retpno()<<"\t\t\t"<<pr.retname()<<"\t\t\t\t"<<pr.retprice()<<endl;
	}
	fp.close();
}

void place_order()
{
	int order_arr[50],quan[50],c=0;
	float amt,damt,total=0;
	char ch='y';
	menu();
	cout<<"\n\n-----------------------------------------------";
	cout<<"\n--------->PLACE YOUR ORDER<----------";
	cout<<"\n\n----------------------------------------------";
	do
	{
	cout<<"\n\nEnter the product no. of the product:";
	cin>>order_arr[c];
	cout<<"\nQuantity in number:";
	cin>>quan[c];
	c++;
	cout<<"\n Do you want to order another product? (y/n) ";
	cin>>ch;
	}while(ch=='y'||ch=='Y');
	cout<<"\n\t Thank you for placing the order";
	getch();
	clrscr();
	cout<<"\n\n Pr no.\t Pr Name\t\t Qty\tPrice\t\tAmt\t after dis\n";
	for(int x=0;x<=c;x++)
	{
	fp.open("shop.dat",ios::in);
	fp.read((char*)&pr,sizeof(product));
	while(!fp.eof())
	{
	if(pr.retpno()==order_arr[x])
	{
	      amt=pr.retprice()*quan[x];
	      damt=amt-(amt*pr.retdis()/100);
	      cout<<"\n"<<order_arr[x]<<"\t"<<pr.retname()<<"\t\t\t"<<quan[x]<<"\t\t"<<pr.retprice()<<"\t"<<amt<<"\t\t"<<damt;
	      total+=damt;
	}
	fp.read((char*)&pr,sizeof(product));
}
fp.close();
}
cout<<"\n\n\t\t\t\tTOTAL="<<total;
getch();
}
void intro()
{
      clrscr();
      gotoxy(25,3);
      cout<<"------->SUPER MARKET<--------";
      gotoxy(25,7);
      cout<<"---------->BILLING<--------";
      gotoxy(25,11);
      cout<<"---------->PRODUCT<----------";
      cout<<"\n\n\n\n\t\t\t   MADE BY : HEMANTWATI";
      getch();
}

void admin_menu()
{
      clrscr();
      char ch2;
      cout<<"\n\n\n\tADMIN MENU";
      cout<<"\n\n\t1. CREATE PRODUCT";
      cout<<"\n\n\t2. DISPLAY ALL PRODUCTS";
      cout<<"\n\n\t3. QUERY";
      cout<<"\n\n\t4. MODIFY PRODUCT";
      cout<<"\n\n\t5. DELETE PRODUCT";
      cout<<"\n\n\t6. VIEW PRODUCTTMENU";
      cout<<"\n\n\t7. BACK TO MAIN MENU";
      cout<<"\n\n\t Please Enter Your Choice(1-7)";
      ch2=getche();
      switch(ch2)
      {
	   case'1': clrscr();
		    write_product();
		    break;
	   case'2': display_all();
		    break;
	   case'3': int num;
		    clrscr();
		    cout<<"\n\n\t Please Enter The Product No.";
		    cin>>num;
		    display_sp(num);
		    break;
	   case'4': modify_product();
		    break;
	   case'5': delete_product();
		    break;
	   case'6': menu();
		    getch();
	   case'7': break;
	   default: cout<<"\a";
		    admin_menu();
      }
}

void main()
{
      char ch;
      intro();
      do
      {
	    clrscr();
	    cout<<"\n\n\t MAIN MENU";
	    cout<<"\n\n\t01. CUSTOMER";
	    cout<<"\n\n\t02. ADMINISTRATOR";
	    cout<<"\n\n\t03. EXIT";
	    cout<<"\n\n\t Please Select Your Option(1-3)";
	    ch=getche();
	    switch(ch)
	    {
		 case'1': clrscr();
			  place_order();
			  getch();
			  break;
		 case'2': admin_menu();
			  break;
		 case'3': exit(0);
		 default: cout<<"\a";
	    }
      }while(ch!='3');
}