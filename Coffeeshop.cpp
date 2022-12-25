//Resturant Billing System Project.
#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<ctime>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
using namespace std;
ifstream in("Coffeemenu.txt");
fstream textfile("Guestbill.txt",ios::out);
fstream admin("CompanyBill.txt",ios::in|ios::out|ios::app);
fstream statement("Sales.txt",ios::in|ios::out|ios::app);
float sum=0.0,asum=0.0,gTotal=0.0,add=0.0,discount = 0.0,servicecharge,tax;
int randomSerial,quantity,count=0,status,quan[265],flag = 0;// count=no of items in bill
string stablenum,a,food;
time_t t=time(0);
struct tm *now=localtime(&t);
char again;
class Resturant{
	string item;
	double serial,price;
	public:
		int returnprice()
		{
			return price;
		}
		int serialNo()
		{
			return serial;
		}
		string itemreturn()
		{
			return item;
		}
		Resturant()
		{
			in>>serial>>item>>price;
		}
	};
string time()
	{
		time_t now=time(0);
		char *d=ctime(&now);
		return d;	
	}
string utime()
{
	time_t now=time(0);
	char *dt=ctime(&now);
	tm*gmtm=gmtime(&now);
	dt=asctime(gmtm);
	return dt;
}
int invoicenumber()
{
	int a;
    int b;
	ifstream outs("number.txt");
    outs>>a;
    b=a+1;
    ofstream ins("number.txt");
    ins<<b;
	return b;
}
int invoicenumbers()
{
	int c;
    int d;
	ifstream text("numbers.txt");
    text>>c;
    d=c+1;
    ofstream texts("numbers.txt");
    texts<<d;
	return d;
}
int invoicecompany()
{
	int e;
    int f;
	ifstream com("num.txt");
    com>>e;
    f=e+1;
    ofstream coms("num.txt");
    coms<<f;
	return f;
}
int invoiceout()
{
	int g;
    int h;
	ifstream show("numb.txt");
    show>>g;
    h=g+1;
    ofstream shows("numb.txt");
    shows<<h;
	return h;
}
void topic()
{
		cout<<endl<<"*******************************************************************"<<endl;
		cout<<endl<<"       !!!  YOU ARE NOW LOGGED IN TO THE SYSTEM  !!!                    ";
		cout<<endl<<"       !!!  WELCOME TO RESTAURANT BILLING SYSTEM !!!                    ";
		cout<<endl<<"********************************************************************"<<endl;
		cout<<"                       ROYAL SAINO RESTAURANT AND BAR             "<<endl;
		cout<<"                            Durbarmarg,Kathmandu                  "<<endl;
		cout<<"********************************************************************"<<endl;
		cout<<"             ENTER SECTION WITH TABLE NUMBER  :      ";cin>>stablenum;
		cout<<"********************************************************************"<<endl;
		cout<<"\n              ENTER FOOD ID FROM 1 TO 320 :       "<<endl;
}
Resturant R[80];
void controlunit()
{
	ofstream items("bill.txt");
	if(!items)
	{
		cout<<"File Opening Error!";
	}
	while(1)
	{
		cout<<"         Enter Coffee ID and quantity : ";
		cin>>randomSerial>>quantity;
		if(randomSerial>=1)
		{
		for(int i=0;i<80;i++)
		{
			 if(R[i].serialNo()==randomSerial)
			{			
				quan[count]=quantity;
				items.write((char*)&R[i],sizeof(R[i]));
				count++;			
				sum +=R[i].returnprice()*quantity;
				flag = 50;
			}
		}
	}
		if(flag != 50)
		{
			cout<<"\n         NO ITEMS FOUND FOR THIS ID NUMBER      "<<endl;;
			
		}
		fflush(stdin);
		cout<<"     IF ITEM IS FINISHED ENTER 0 : ";
		cin>>status;
		if(status == 0)
		{
			items.close();
			break;
		}
	}
}
void calculation()
{
	ifstream itemsIn("bill.txt");
	if(!itemsIn)
	{
		cout<<"File Opening Error!"; 
	}
	itemsIn.read((char*)R,sizeof(R[0])*count);
	cout<<"\n  What Discount % Available For This Bill? : ";
	cin>>discount;
	asum = sum * (1-discount/100.0); //sum after discount
	discount = (sum - asum);//Discount
	servicecharge=(asum*10)/100;//service charge
	gTotal=asum+servicecharge;//afterservice charge Total
	tax=((gTotal)*13)/100;//For tax
	add=asum+tax+servicecharge; 
}
void guestbill()
{
	textfile<<"\n**********************************************************************"<<endl;
	textfile<<"              Royal Saino Resturant and Bar                "<<endl;
	textfile<<"                  DurbarMarg,Kathmandu                     "<<endl;
	textfile<<"\n**********************************************************************"<<endl;
	textfile<<"                     ==========                                        "<<endl;
	textfile<<"                      INVOICE                                          "<<endl;
	textfile<<"                     ==========                                        "<<endl;
	textfile<<"Invoice No. : "<<invoicenumbers()<<"        "<<"                            Date(d/m/y):"<<now->tm_mday<<'/'<<(now->tm_mon+1)<<'/'<<(now->tm_year+1900)<<endl;
	textfile<<"------------------------------------------------------------------------"<<endl;
	textfile<<"Section & Table Number: "<<stablenum<<"        "<<"      Payment mode :"<<"Cash/Visa/credit"<<endl;
	textfile<<"------------------------------------------------------------------------"<<endl;
	textfile<<endl;
	textfile<<"Guest's Name :_______________________________________________"<<endl;
	textfile<<"Phone Number :_______________________________________________"<<endl;
	textfile<<"TPIN Number  :_______________________________________________"<<endl;
	textfile<<endl;
	textfile<<"________________________________________________________________________"<<endl;
	textfile<<setw(4)<<"SN"<<setw(27)<<"Particulars"<<setw(9)<<"Price";
	textfile<<setw(10)<<"Quantity"<<setw(8)<<"Coffee"<<endl;
	textfile<<"________________________________________________________________________"<<endl;
	for(int i=0;i<count;i++)
	textfile<<setw(4)<<i+1<<setw(4)<<setw(30)<<R[i].itemreturn()<<setw(5)<<R[i].returnprice()<<setw(6)
	<<quan[i]<<setw(12)<<R[i].returnprice()*quan[i]<<endl<<endl;
	textfile<<"________________________________________________________________________"<<endl;
	textfile<<"       "<<"                           Total of Coffee : "<<sum<<endl;
	textfile<<"________________________________________________________________________"<<endl;
	textfile<<"       "<<"                           Discount        : "<<discount<<endl;
	textfile<<"                                      __________________________________"<<endl;
	textfile<<"       "<<"                           Grand Total     : "<<asum<<endl;
	textfile<<"                                      __________________________________"<<endl;
	textfile<<"       "<<"                           Service Charge  : "<<servicecharge<<endl;
	textfile<<"                                      __________________________________"<<endl;
	textfile<<"       "<<"                           Grand Total     : "<<gTotal<<endl;
	textfile<<"                                      __________________________________"<<endl;
	textfile<<"       "<<"                           Tax             : "<<tax<<endl;
	textfile<<"                                      __________________________________"<<endl;
	textfile<<"       "<<"                           Net Total       : "<<add<<endl;
	textfile<<"                                      __________________________________"<<endl;
	textfile<<endl;
	textfile<<"________________________________________________________________________"<<endl;
	textfile<<" \n\nThe local date and time is : "<<time()<<endl;
	textfile<<"     The UTC date and time is   : "<<utime()<<endl;
	textfile<<"     Thank You For Visiting Us!              "<<endl;
	textfile<<"       Hope To See You Again!!              "<<endl;
	textfile<<"\n                                      Cashier : "<<"Babulal \n"<<endl;
	textfile<<endl;
	textfile<<"----------------------------------------------------------------------------------------------"<<endl;
	textfile.close();
}
void resturantcopy()
{
	admin<<"\n**************************************************************************"<<endl;
	admin<<"              Royal Saino Resturant and Bar                            "<<endl;
	admin<<"                  DurbarMarg,Kathmandu                                 "<<endl;
	admin<<"\n**************************************************************************"<<endl;
	admin<<"                     ==========              "<<endl;
	admin<<"                       INVOICE                            				"<<endl;
	admin<<"                     ==========             						    "<<endl;
    admin<<"Invoice No. : "<<invoicecompany()<<"          "<<"                            Date(d/m/y):"<<now->tm_mday<<'/'<<(now->tm_mon+1)<<'/'<<(now->tm_year+1900)<<endl;
	admin<<"----------------------------------------------------------------------------"<<endl;
	admin<<"Section & Table Number: "<<stablenum<<"          "<<"               Payment mode :"<<"Cash/Visa/credit"<<endl;
	admin<<"----------------------------------------------------------------------------"<<endl;
	admin<<endl;
	admin<<"Guest's Name :______________________________________________________________"<<endl;
	admin<<"Phone Number :______________________________________________________________"<<endl;
	admin<<"TPIN Number  :______________________________________________________________"<<endl;
	admin<<endl;
	admin<<"____________________________________________________________________________"<<endl;
	admin<<setw(4)<<"SN"<<setw(27)<<"Particulars"<<setw(9)<<"Price";
	admin<<setw(10)<<"Quantity"<<setw(8)<<"Coffee"<<endl;
	admin<<"____________________________________________________________________________"<<endl;
	for(int i=0;i<count;i++)
	admin<<setw(4)<<i+1<<setw(30)<<R[i].itemreturn()<<setw(5)<<R[i].returnprice()
	<<setw(6)<<quan[i]<<setw(12)<<R[i].returnprice()*quan[i]<<endl<<endl;
	admin<<"____________________________________________________________________________"<<endl;
	admin<<"       "<<"                           Total of Coffee : "<<sum<<endl;
	admin<<"____________________________________________________________________________"<<endl;
	admin<<"       "<<"                           Discount        : "<<discount<<endl;
	admin<<"                                      ______________________________________"<<endl;
	admin<<"       "<<"                           Grand Total     : "<<asum<<endl;
	admin<<"                                      ______________________________________"<<endl;
	admin<<"       "<<"                           Service Charge  : "<<servicecharge<<endl;
	admin<<"                                      ______________________________________"<<endl;
	admin<<"       "<<"                           Grand Total     : "<<gTotal<<endl;
	admin<<"                                      ______________________________________"<<endl;
	admin<<"       "<<"                           Tax             : "<<tax<<endl;
	admin<<"                                      ______________________________________"<<endl;
	admin<<"       "<<"                           Net Total       : "<<add<<endl;
	admin<<"                                      ______________________________________"<<endl;
	admin<<endl;
	admin<<"____________________________________________________________________________"<<endl;
	admin<<endl;
	admin<<"The local date and time is  : "<<time();
	admin<<"The UTC date and time is    : "<<utime();
	admin<<"     Thank You For Visiting Us!              "<<endl;
	admin<<"       Hope To See You Again!!              "<<endl;
	admin<<"\n                                       Cashier : "<<"Babulal                \n"<<endl;
	admin<<"-----------------------------------------------------------------------------------------------------"<<endl;
	admin<<endl;
}
void execucation()
{
	cout<<"\n**************************************************************************"<<endl;
	cout<<"              Royal Saino Resturant and Bar                "<<endl;
	cout<<"                  DurbarMarg,Kathmandu                     "<<endl;
	cout<<"\n**************************************************************************"<<endl;
	cout<<"                     ==========                                       "<<endl;
	cout<<"                       INVOICE                                        "<<endl;
	cout<<"                     ==========                                       "<<endl;
	cout<<"Invoice No. : "<<invoiceout()<<"  "<<"                          Date(d/m/y):"<<now->tm_mday<<'/'<<(now->tm_mon+1)<<'/'<<(now->tm_year+1900)<<endl;
	cout<<"----------------------------------------------------------------------------"<<endl;
	cout<<"Section & Table Number: "<<stablenum<<"                   Payment mode :"<<"Cash/Visa/credit"<<endl;
	cout<<"----------------------------------------------------------------------------"<<endl;
	cout<<endl;
	cout<<"Guest's Name :______________________________________________________________"<<endl;
	cout<<"Phone Number :______________________________________________________________"<<endl;
	cout<<"TPIN Number  :______________________________________________________________"<<endl;
	cout<<endl;
	cout<<"____________________________________________________________________________"<<endl;
	cout<<setw(4)<<"SN"<<setw(5)<<"ID"<<setw(26)<<"Particulars"<<setw(9)<<"Price";cout<<setw(10)
	<<"Quantity"<<setw(8)<<"Coffee"<<endl;
	cout<<"____________________________________________________________________________"<<endl;
	for(int i=0;i<count;i++)
	cout<<setw(4)<<i+1<<setw(4)<<R[i].serialNo()<<setw(30)<<R[i].itemreturn()<<setw(5)<<R[i].returnprice()
	<<setw(6)<<quan[i]<<setw(12)<<R[i].returnprice()*quan[i]<<endl<<endl;
	cout<<"____________________________________________________________________________"<<endl;
	cout<<"       "<<"                           Total of Coffee : "<<sum<<endl;
	cout<<"                                     _______________________________________"<<endl;
	cout<<"       "<<"                           Discount        : "<<discount<<endl;
	cout<<"                                      ______________________________________"<<endl;
	cout<<"       "<<"                           Grand Total     : "<<asum<<endl;
	cout<<"                                      ______________________________________"<<endl;
	cout<<"       "<<"                           Service Charge  : "<<servicecharge<<endl;
	cout<<"                                      ______________________________________"<<endl;
	cout<<"       "<<"                           Grand Total     : "<<gTotal<<endl;
	cout<<"                                      ______________________________________"<<endl;
	cout<<"       "<<"                           Tax             : "<<tax<<endl;
	cout<<"                                      ______________________________________"<<endl;
	cout<<"       "<<"                           Net Total       : "<<add<<endl;
	cout<<"                                      ______________________________________"<<endl;
	cout<<endl;
	cout<<"_________________________________________________________________________________"<<endl;
	cout<<endl;
	cout<<"The local date and time is  : "<<time();
	cout<<"The UTC date and time is    : "<<utime();
	cout<<"     Thank You For Visiting Us!              "<<endl;
	cout<<"       Hope To See You Again!!              "<<endl;
	cout<<"\n                                       Cashier : "<<"Babulal                           \n"<<endl;
	cout<<"----------------------------------------------------------------------------------------------------"<<endl;
}
void password()
{
	START:
	system("cls");
	cout<<"***********************************************";
	cout<<"\n User Name		 :  Royal Saino Resturant"<<endl;
	cout<<"***********************************************";
	cout<<"\n Enter password : ";
	char pass[10];
	int i=0;
	char a;
	while(1)
	{
		a=getch();
		if((a>='a'&&a<='z')||(a>='A'&&a<='Z')||(a>='0'&&a<='9'))//check a is a num or alpha.
		{
			pass[i]=a;
			++i;
			cout<<"*";
		}
		else if(a=='\b'&&i>=1)//if user typed backspace 
		{
			cout<<"\b\b";
			--i;
		}
		else if (a==13 && i>=6)
		{
			pass[i]='\0';
			break;
		}
	
	}
	if(strcmp(pass,"Coffees")==0)
	{
	topic();
	controlunit();
	calculation();
	guestbill();
	execucation();
	resturantcopy();
	}
	else{
		cout<<"\n Credentials does not match! Try Again to Login : ";
		getch();
		goto START;
	}	
}
int main()
{
	password();
    statement<<invoicenumber()<<setw(10)<<setw(16)<<sum<<setw(18)<<discount<<setw(20)<<servicecharge<<setw(22)<<tax<<setw(18)<<add<<endl;
	statement.close();
	system("pause");
return 0;
}

