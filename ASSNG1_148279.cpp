//**************************************************************************************//
// This program calculate Body Mass Index(BMI), Basal Metabolic Rate(BMR) and
// Resting Metabolic Rate(RMR) for every USM's staff. This program allows USM's staff 
// to search their BMI, BMR and RMR based on their IC Number and they also can know
// their BMI level and get an advice from their BMI Level .
//**************************************************************************************//
#include<windows.h>
#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

class personalInfo{		// base class of personalInfo
	
	private :
		string staffName, // to hold name
			gender;	// to hold gender
		long long int staffID;	// to hold staffID / IC Number
	
	public :
		void setData1(long long int, string, string);	
		string getName(){return staffName;}	// to return name
		long long int getStaffID(){return staffID;}	// to return staffID
		string getGen(){return gender;}	// to return gender
		void displayData1();	// display data in personalInfo
		personalInfo(){staffID=0; staffName=" "; gender=" ";}	// constructor
		personalInfo(long long int, string, string);	// constructor
		~personalInfo(){}	// destructor
		
};

void personalInfo :: setData1(long long int S, string N, string G)
{
	staffID = S;
	staffName = N;
	gender = G;
}

void personalInfo :: displayData1()
{
	cout << "Name : " << staffName << endl;
	cout << "IC number : " << staffID << endl;
	cout << "Gender : " << gender << endl;
}

personalInfo :: personalInfo(long long int S, string N, string G)
{
	staffID = S;
	staffName = N;
	gender = G;
}


class fitInfo{		// base class of fitInfo
	
	private :
		long long int StaffId;	// to hold StaffId
		float weight,	// to hold weight
			height;	// to hold height
		
	public :
		void setData2(long long int, float, float);
		long long int getStaffId(){return StaffId;}	// to return StaffId
		float getWeight(){return weight;}	// to return weight
		float getHeight(){return height;}	// to return height
		void displayData2();	// display data of fitInfo
		fitInfo(){StaffId = 0; weight=0.0; height=0.0;}	// constructor
		fitInfo(long long int, float, float);	// constructor
		~fitInfo(){}	// destructor
};

void fitInfo :: setData2(long long int ID, float W, float H)
{
	StaffId = ID;
	weight = W;
	height = H;
}

void fitInfo :: displayData2()
{
	cout << "Weight(kg) : " << weight << endl;
	cout << "Height(cm) : " << height << endl;	
}

fitInfo :: fitInfo(long long int ID, float W, float H)
{
	StaffId = ID;
	weight = W;
	height = H;
}


class letGetFit : public personalInfo{		// derived class 
	
	private :
		long long int temp;	// to hold temp
		int age;	// to hold age
		float BMI, bmiVal;	// to hold BMI value
		float BMR, bmrVal;	// to hold BMR value
		float RMR, rmrVal;	// to hold RMR value
		fitInfo staff;	// composition
	
	public :
		void setInfo1(long long int, string, string);
		void setInfo2(long long int, float, float);
		//long long int STAFFID(){return staff.getStaffId();}
		//string GENDER(){return getGen();}
		int calAge();
		int setAge(int);
		int getAge(){return age;}
		float calBMI();	
		float calBMR();
		float calRMR();
		float getBMIVal(){return BMI;}
		float getBMRVal(){return BMR;}
		float getRMRVal(){return RMR;}
		float setBMI(float);
		float setBMR(float);
		float setRMR(float);
		void display();	// display data from personalInfo and fitInfo
		friend void menu(letGetFit);	// display menu
		friend void search(letGetFit ob[], int&);		// allow user to search about their BMI, BMR, RMR value
		friend void statistic(letGetFit ob[], int&);	// display statistic of the BMI 
		friend void addStaff(letGetFit);		// allow user to add more staffs
		friend void rangeBMIUnder(letGetFit ob[], int&);	// display underweight BMI 
		friend void rangeBMINormal(letGetFit ob[], int&);	// display normal BMI 
		friend void rangeBMIOver(letGetFit ob[], int&);		// display overweight BMI
		friend void rangeBMIObese(letGetFit ob[], int&);	// display obese BMI
		friend void outputFile(letGetFit ob[], int&);	// contain new staff information
};

void letGetFit :: setInfo1(long long int S, string N, string G)
{
	setData1(S, N, G);	// inherit
}

void letGetFit :: setInfo2(long long int ID, float W, float H)
{
	staff.setData2(ID, W, H);	// composition
}

// calculate age
int letGetFit :: calAge()
{
	float a;
	int birthYear, index=12;
	int ic[index] = {0};
	temp = staff.getStaffId();
	
	for(int x=0; x<index; x++){
		ic[x] = temp % 10;
		temp = temp/10;
	}
	
	if(ic[11]==0){
		birthYear = 2000 + (ic[11]*10) + ic[10];
		age = 2020 - birthYear;
	}
	
	else{
		birthYear = 1900 + (ic[11]*10) + ic[10];
		age = 2020 - birthYear;
	}
	
	a = age;
	return a;
}

int letGetFit :: setAge(int a)
{
	age = a;
}

// calculate BMI
float letGetFit :: calBMI()
{
	bmiVal = staff.getWeight()/((staff.getHeight()/100)*(staff.getHeight()/100));
	BMI = bmiVal;
	return BMI;
}

// calculate BMR
float letGetFit :: calBMR()
{
	if(getGen() == "Male"){
		bmrVal = (10 * staff.getWeight() + 6.25 * staff.getHeight() - 5 * getAge() + 5);
	}
	
	else{
		bmrVal = (10 * staff.getWeight() + 6.25 * staff.getHeight() - 5 * getAge() - 161);
	}	
		
	BMR = bmrVal;
	return BMR;
}

// calculate RMR
float letGetFit :: calRMR()
{	
	if(getGen() == "Male"){
		rmrVal = (88.362 + (13.397 * staff.getWeight()) + (4.799 * staff.getHeight()) - (5.677 * getAge()));
	}
	
	else{
		rmrVal = (447.593 + (9.247 * staff.getWeight()) + (3.098 * staff.getHeight()) - (4.330 * getAge()));		
	}	
	
	RMR = rmrVal;
	return RMR;
}

float letGetFit :: setBMI(float bmi)
{
	BMI = bmi;
}

float letGetFit :: setBMR(float bmr)
{
	BMR = bmr;
}

float letGetFit :: setRMR(float rmr)
{
	RMR = rmr;
}

void letGetFit :: display()
{
	displayData1();	// display data from personalInfo
	staff.displayData2();	// display data from fitInfo
	cout << "Age : " << age << endl;
	cout << "BMI : " << BMI << endl;
	cout << "BMR : " << BMR << endl;
	cout << "RMR : " << RMR << endl;	
}

//*****************************************************************************
// Definition of function showMenu which displays the menu that 
// users can choose.
//*****************************************************************************
void menu(letGetFit ob2)
{
	// Display welcome screen
	cout << "\n\t\t____________________________________________________________\t\t\n";
	cout << "\t\t************************************************************\n";
	cout << "\t\t************************************************************";
	cout << endl;
	cout << "\t\t\tWELCOME TO LET'S GET FIT (LGF) CALCULATOR\t\t\t";
	cout << endl;	
	cout << "\t\t____________________________________________________________\t\t\n";
	cout << "\t\t************************************************************\n";
	cout << "\t\t************************************************************";
	cout << endl << endl;
			
	// Display the menu and get the user's choice	
	cout << "\n\tLET'S GET FIT (LGF) MENU\n";
	cout << endl;
	cout << "\tWhat you want to know ?\n";
	cout << "\tChoose one !\n";
	cout << endl;
	cout << " [1] |\tSearch Your Data Here !\n";
	cout << " [2] |\tStatistic of USM's Staff\n";
	cout << " [3] |\tCombination data of USM's Staff\n";
	cout << " [4] |\tAdd New Staff\n";
	cout << " [5] |\tDisplay All Information of USM's Staff\n";
	cout << " [6] |\tQuit\n";
	cout << " Please enter your choice: ";
	
	cout << endl << endl;
}

//*****************************************************************************
// Definition of function search which display the BMI, BMR and RMR of user
// after they enter their IC Number
//*****************************************************************************
void search(letGetFit ob[], int& size)
{
	long long int staffID;
	bool flag = false;		// flag to indicate if the staffID was found
	cout << "\t\t---------------------------------------------------------------\t\t\n";
	cout << "\t\t\tThis space need you to enter your IC Number\t\t\t\n";
	cout << "\t\t---------------------------------------------------------------\t\t\n\n";
	cout << " Please enter your IC number. (Example : 980213060278)\n";
	cout << " IC Number : ";
	cin >> staffID ;
	
	for (int j = 0; j < size; j++){		
		if( ob[j].getStaffID() == staffID )		// if user's staff ID entered same as in the array
		{
			cout << " Name : " << ob[j].getName() << endl;	// display staff's name
			cout << " BMI : " << ob[j].getBMIVal();	// display BMI Value
			if (ob[j].getBMIVal() < 20){
				cout  << " You are Underweight !" << endl;
			}
			else if ((ob[j].getBMIVal() >= 20) && (ob[j].getBMIVal() < 25)){
				cout << "  You are Normal ! " << endl;
			}
			else if ((ob[j].getBMIVal() >= 25) && (ob[j].getBMIVal() < 30)){
				cout << "  You are Overweight ! " << endl ;
			}
			else if (ob[j].getBMIVal() >= 30){
				cout << "  You are Obese ! " << endl;
			}					
			else{
				cout << "Not Valid!" << endl;
			}
			
			cout << " BMR : " << ob[j].getBMRVal() << endl;	// display BMR Value
			cout << " RMR : " << ob[j].getRMRVal();	// display RMR Value
			flag = true;	// set the flag
		}
	}
	if ( flag == false){	// set the flag
		cout << "Error ! Your data are missing.\n";
	}
}

//*****************************************************************************
// Definition of function statistic which display the statistic of 
// USM's staff based on their BMI Condition and age
//*****************************************************************************
void statistic(letGetFit ob[], int& size)
{
	int j, k;
	int under20=0, under30=0, under40=0, normal20=0, normal30=0, normal40=0,
		over20=0, over30=0, over40=0, obese20=0, obese30=0, obese40=0;
	
	for(j = 0; j < size; j++){		
	
		if(ob[j].getBMIVal() <= 20 && ob[j].getAge() <= 30){
			under20++;	// increment
		}
		else if(ob[j].getBMIVal() <= 20 && ob[j].getAge() > 30 && ob[j].getAge() <= 40){
			under30++;	// increment
		}
		else if(ob[j].getBMIVal() <= 20 && ob[j].getAge() > 40){
			under40++;	// increment
		}
		else if(ob[j].getBMIVal() >= 20 && ob[j].getBMIVal() < 25 && ob[j].getAge() <= 30){
			normal20++;	// increment
		}
		else if(ob[j].getBMIVal() >= 20 && ob[j].getBMIVal() < 25 && ob[j].getAge() > 30 && ob[j].getAge() <= 40){
			normal30++;	// increment
		}
		else if(ob[j].getBMIVal() >= 20 && ob[j].getBMIVal() < 25 && ob[j].getAge() > 40){
			normal40++;	// increment
		}
		else if(ob[j].getBMIVal() >= 25 && ob[j].getBMIVal() < 30 && ob[j].getAge() <= 30){
			over20++;	// increment
		}
		else if(ob[j].getBMIVal() >= 25 && ob[j].getBMIVal() < 30 && ob[j].getAge() > 30 && ob[j].getAge() <= 40){
			over30++;	// increment
		}
		else if(ob[j].getBMIVal() >= 25 && ob[j].getBMIVal() < 30 && ob[j].getAge() > 40){
			over40++;	// increment
		}
		else if(ob[j].getBMIVal() >= 30 && ob[j].getAge() <= 30){
			obese20++;	// increment
		}
		else if(ob[j].getBMIVal() >= 30 && ob[j].getAge() > 30 && ob[j].getAge() <= 40){
			obese30++;	// increment
		}
		else if(ob[j].getBMIVal() >= 30 && ob[j].getAge() > 40){
			obese40++;	// increment
		}	
	}
	
	
	cout << "\t\t\t\tStaff Statisic\t\t\t\t\n\n";
	cout << "................................................................................\n";
	cout << " Category	  | 				Age				" << endl;
	cout << " \t\t  ..............................................................\n";
	cout << " \t\t  |	30 & less	|	31 - 40	|	41 - 50	" << endl;
	cout << ".................................................................................\n";
	cout << " Underweight" << "\t\t" << under20 << "\t\t\t" << under30 << "\t\t" << under40 << "\t\t" << endl;
	cout << " Normal" << "\t\t\t" << normal20 << "\t\t\t" << normal30 << "\t\t" << normal40 << "\t\t" << endl;
	cout << " Overweight" << "\t\t" << over20 << "\t\t\t" << over30 << "\t\t" << over40 << "\t\t" << endl;
	cout << " Obese" << "\t\t\t" << obese20 << "\t\t\t" << obese30 << "\t\t" << obese40 <<  endl;
	cout << ".................................................................................\n";

}

//*****************************************************************************
// Definition of function addStaff where new information about another staff
// will be add into the file.
//*****************************************************************************
void addStaff(letGetFit ob2)
{
	string NAME, GENDER;
	long long int STAFFID;
	float WEIGHT, HEIGHT;

	cout << " Please enter your information.\n";
	cout << " Enter IC Number : ";
	cin >> STAFFID;
	cin.ignore(1500, '\n');
	cout << " Enter name : ";
	getline(cin, NAME);
	cout << " Enter gender : ";
	getline(cin, GENDER);
	cout << " Enter weight (kg): ";
	cin >> WEIGHT;
	cout << " Enter height (cm): ";
	cin >> HEIGHT;

	cout << " DONE !\n";
	cout << " Your information will be saved.\n";
	
	fstream personalFile, fitnessFile;
	
	personalFile.open("output1 file.txt", ios::app);	// Open file in append mode

		personalFile << endl;
		personalFile << STAFFID << "\t";	
		personalFile << NAME << "\t";
		personalFile << GENDER << "\t";
	
	personalFile.close();	// close the file
	
	fitnessFile.open("output2 file.txt", ios::app);	// open file in append mode
		personalFile << endl;	
		personalFile << WEIGHT << "\t";
		personalFile << HEIGHT << "\t";
		
	fitnessFile.close();	// close the file	
}

//*****************************************************************************
// Definition of function rangeBMI20 where it display the total number of 
// USM's staff that has BMI value less than 20 (Underweight) .
//*****************************************************************************
void rangeBMIUnder(letGetFit ob[], int& size)
{
	double BMIval;
	double sum = 0;
	int j;
		
	for (j = 0; j<size; j++)
	{		
		if(ob[j].getBMIVal() <= 20)		// BMIVAL less than BMIval which is 20
		{
			sum++;	
		}
	}
	cout << endl;
	cout << "There are " << sum << " staffs that has BMI";
	cout << " less than 20 (Underweight).\n";
	
}

//*****************************************************************************
// Definition of function rangeBMINormal where it display the number of 
// USM's staff that has normal BMI value.
//*****************************************************************************
void rangeBMINormal(letGetFit ob[], int& size)
{
	double sum = 0;
	int j;
	
	for (j = 0; j < size; j++)
	{		
		if(ob[j].getBMIVal() >= 20 && ob[j].getBMIVal() < 25)	// BMIVAL more than or equal to 20, less than 25
		{
			sum ++;	
		}
	}
	cout << endl;
	cout << "There are " << sum << " staffs that has";
	cout << " normal BMI value.\n";
}

//*****************************************************************************
// Definition of function rangeBMI25 where it display the total number of 
// USM's staff that has BMI value more than 25 (Overweight).
//*****************************************************************************
void rangeBMIOver(letGetFit ob[], int& size)
{
	double sum = 0;
	int j;
		
	for (j = 0; j < size; j++)
	{		
		if(ob[j].getBMIVal() >= 25 && ob[j].getBMIVal() < 30)	// BMIVAL more than or equal to 25, less than 30
		{
			sum ++;
		}
	}
	cout << endl;
	cout << "There are " << sum << " staffs that has BMI";
	cout << " more than 25 but less than 30 (Overweight).\n";
}

//*****************************************************************************
// Definition of function rangeBMIObese where it display the total number of 
// USM's staff that has BMI value more than 30 (Obese) .
//*****************************************************************************
void rangeBMIObese(letGetFit ob[], int& size)
{
	double sum = 0;
	int j;
	
	for (j = 0; j < size; j++)
	{		
		if(ob[j].getBMIVal() >= 30)		// BMIVAL more than or equal to 30
		{
			sum ++;
		}
	}
	cout << endl;
	cout << "There are " << sum << " staffs that has BMI";
	cout << " more than 30 (Obese).\n";
	
}

//*****************************************************************************
// Definition of function outputFile where this file will show the information
// off the staff and new staff that have been added
//*****************************************************************************
void outputFile(letGetFit ob[], int& size)
{
	int i, k;
	string name, gender;
	long long int staffID;
	float weight, height;
	
	fstream personalFile, fitnessFile;
	
	personalFile.open("output1 file.txt", ios::app	| ios::out);	// Open file in append and output mode
	
		personalFile << endl;
		personalFile << staffID << "\t";
		personalFile << name << "\t";
		personalFile << gender << "\t";
		ob[i].setInfo1(staffID, name, gender);
		i++;
	
	personalFile.close();	// close the file
	
	fitnessFile.open("output2 file.txt", ios::app	| ios::out);	// Open file in append and output mode

		fitnessFile << endl;
		fitnessFile << staffID << "\t";
		fitnessFile << weight << "\t";
		fitnessFile << height << "\t";
		ob[i].setInfo2(staffID, weight, height);
		k++;
	
	fitnessFile.close();	// close the file
}


int main()
{
	long long int staffId;
	string name, gender, space;
	float weight, height; 
	int i = 0, k = 0; // Index of array
	int max = 100;	// Size index of array
	int size = 20; // maximum number of array
	int choice;	// To hold a menu choice
	char pick;	// To hold choices
	
	letGetFit ob2;
	letGetFit ob[size];
	
	ifstream personalFile, fitnessFile;
	//file 1st
	personalFile.open("PersonalInfo.txt");
	
	if(personalFile){
			
		personalFile >> staffId;
		getline(personalFile, space, '\t');
		getline(personalFile, name, '\t');
		getline(personalFile, gender);
		
		while(personalFile){
			ob[i].setInfo1(staffId, name, gender);
			i++;
			
			
			personalFile >> staffId;
			getline(personalFile, space, '\t');
			getline(personalFile, name, '\t');
			getline(personalFile, gender);	
		}
	
		personalFile.close();
	}
	
	else
		cout << "Sorry. Cannot find file." << endl;
		
	//file 2nd
	fitnessFile.open("FitnessInfo.txt");
	
	if(fitnessFile){
			
		fitnessFile >> staffId >> weight >> height;
		
		while(fitnessFile){
			ob[k].setInfo2(staffId, weight, height);
			k++;
			
			// read the next data
			fitnessFile >> staffId >> weight >> height;
		}
		fitnessFile.close();
	}
	
	else
		cout << "Cannot find file." << endl;
		
	size=i=k;
	
	// Constants for the menu choices
	const int SEARCH_CHOICE = 1 ,
		 	  STATISTIC_CHOICE = 2,
		 	  COMBINATION_CHOICE = 3,
		  	  ADDSTAFF_CHOICE= 4,
		  	  STAFFINFO_CHOICE = 5,
		      QUIT_CHOICE = 6;
		      
	cout << fixed << showpoint << setprecision(1); 		// set to 1 decimal place
	
	for(int j=0; j<size; j++){
		ob[j].calAge();					
		ob[j].calBMI();
		ob[j].calBMR();
		ob[j].calRMR();
	}
	
	do{
		menu(ob2);
		cin >> choice;  		// user enter their choice
		cout << endl << endl;
		
		// validate the menu selection
		while (choice < SEARCH_CHOICE || choice > QUIT_CHOICE)
		{
			cout << " Please enter a valid menu choice: ";
			cin >> choice;
		}
			
		// if the user does not want to quit, proceed
		if (choice != QUIT_CHOICE)
		{
			// if user choose 1
			if (choice == 1){
				search(ob, size);	// calling friend function search
			}
			// if user choose 2
			else if (choice == 2){
				statistic(ob, size);	// calling friend function statistic
			}
			// if user choose 3
			else if (choice == 3){
				cout << " What do you want to know ?\n\n";
				cout << " A) All staff with BMI less than 20 (Underweight) ?\n";
				cout << " B) All staff with normal BMI\n";
				cout << " C) All staff with BMI more than 25 ";
				cout << "less than 30 (Overweight) ?\n";
				cout << " D) All staff with BMI more than 30 (Obese) ?\n";
				cout << endl;
				cout << " Enter your choice. (Example : A)" << " ";
				cin >> pick;	// user enter the choice they want
				
				switch(pick)
				{
					case 'A' : rangeBMIUnder(ob, size);	// Display number of staff that have BMI less than 20
						break;
					case 'B' : rangeBMINormal(ob, size);	// Display number of staff that have BMI more than 25
						break;
					case 'C' : rangeBMIOver(ob, size);	// Display number of staff that have normal BMI
						break;
					case 'D' : rangeBMIObese(ob, size);	// Display number of staff that have BMI more than 30
						break;
					default : cout << " Invalid choice !\n";	// If user enter invalid choice
				}
				
			}
			// if user choose 4
			else if (choice == 4){
				addStaff(ob2);	// calling friend function addStaff
			}
			// if user choose 5
			else if (choice == 5){
				for(int j=0; j<size; j++){
					ob[j].display();	// calling function display in derived class
					cout << endl << endl;
				}
			}
			else{
				cout << "Invalid choice !\n";
			}
			
		}
	}
	
	while (choice != QUIT_CHOICE);
	
	outputFile(ob, size);	// calling friend function outputFile
	
	cout << "\n\n";
	system("pause");
	system("cls");
	
}
