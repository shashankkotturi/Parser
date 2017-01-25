#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

struct Label{
	char name[30];
	int value;
};

void copyStr(char* str1, char* str2)
{
	int i;
	for (i = 0; str2[i] != 0; i++)
	{
		str1[i] = str2[i];
	}
	str1[i] = 0;
}

void removeWhitespaces(char line[]){
	// Find the length of the str parameter to the first null terminator
	int length = 0;
	for (int i = 0; line[i] != 0; i++)
		length++;
	
	char result[length + 1];
	
	int count = 0;
	
	// Checks to see if it's the whitespace after the opcode
	bool first = true;
	
	int counter = 0;
	// Trims any initial whitespaces or tabs
	while (line[0] == ' ' || line[0] == '\t')
	{
		for (int j = 0; line[j] != 0; j++)
		{
			line[j] = line[j + 1];
		}
	}
	
	
	// Copies the str parameter with only the first whitespace
	// into another str array
	for (int i = 0; line[i] != 0; i++)
	{
		if ((line[i] == ' ' || line[i] == '\t') && first)
		{
			result[count] = ' ';
			count++;
			first = false;
		}
		
		if (line[i] != ' ' && line[i] != '\t')
		{
			result[count] = line[i];
			count++;
		}
	}
	
	
	// Copies the str from result to line
	int index = 0;
	while (result[index] != 0 && index < count)
	{
		line[index] = result[index];
		index++;
	}
	line[index] = 0;
}

int comparestr(char str1[], char str2[]){
	
	// Finding the length of the two strs
	int length1 = 0;
	int length2 = 0;
	
	for (int i = 0; str1[i] != 0; i++)
		length1++;
	
	for (int i = 0; str2[i] != 0; i++)
		length2++;
	
	// Comparing strs that are of different lengths but are otherwise same
	// If the first str is less than the second str
	if ((length1 < length2) || (length1 > length2))
	{
		return -1;
	}
	
	// If both strs have the same length
	for (int j = 0; j < length2; j++){
		
		// If a character in the first str is ahead of the corresponding
		// character in the second str		
		if (str1[j] < str2[j])
			return 1;
		
		// If a character in the first str is behind the corresponding
		// character in the second str
		else if (str1[j] > str2[j])
			return -1;
	}
	
	// If strs are exactly equal
	return 0;
}

int operandCheck(char operand[], char opcode[], int line) 
{
		if(!comparestr(opcode, (char*)"LD"))//
		{
			bool AlreadyChecked=false;
			if (operand[0]=='0' || operand[0]=='1'||operand[0]=='2'||operand[0]=='3'||operand[0]=='4'||operand[0]=='5'||operand[0]=='6'||operand[0]=='7'||operand[0]=='8'||operand[0]=='9')
			{
				int i=1;
				for (i=1 ; operand[i]!=',' && operand[i]!=0; i++)
				{
					if (operand[i]!='0' && operand[i]!='1'&&operand[i]!='2'&&operand[i]!='3'&&operand[i]!='4'&&operand[i]!='5'&&operand[i]!='6'&&operand[i]!='7'&&operand[i]!='8'&&operand[i]!='9')
					{
						cerr << "Error on line " << line << ": invalid missing value for number" << endl;
						return -1;
					}
				}
				if (operand[i]!= ',')
				{
					cerr << "Error on line " << line << ": invalid missing comma after Register" << endl;
					return -1;
				}
				if ((operand[i]==',' && operand[i+1]==',') ||(operand[i]==',' && operand[i+1]==0) )
				{
					cerr << "Error on line "<<line<<" missing operand" << endl;
					return -1;
				}
				if (operand[i+1]!= 'R')
				{
				cerr << "Error on line " << line << ": invalid missing Register after comma; saw "<< operand[i+1] << endl;
					/*
					cerr << "Error on line " << line << " : invalid Register after comma; saw \"";
					for (int j = i+1; operand[j] != 0; j++)
						cerr << operand[j];
					cerr << "\"" << endl;
					
					return -1;
					*/
					return -1;
				}
				int p=i+2;
				if (operand[i+2]==0)
				{
					cerr << "Error on line " << line << ": invalid missing integer or extra value" << endl;
					return -1;
				}
					
				for (p = i+2 ; operand[p]!=0; p++)
				{
					if (operand[p]!='0' && operand[p]!='1'&&operand[p]!='2'&&operand[p]!='3'&&operand[p]!='4'&&operand[p]!='5'&&operand[p]!='6'&&operand[p]!='7'&&operand[p]!='8'&&operand[p]!='9')
					{
						cerr << "Error on line " << line << ": invalid missing value for register or extra value" << endl;
						return -1;
					}
				}
				AlreadyChecked = true;
			}
			if (operand[0] == 'R')  //might have to add an error for this case
			{
				int i=1;
				if (operand[i]==',')
				{
					cerr << "Error on line " << line << ": invalid missing integer or extra value" << endl;
					return -1;
				}
					
				for (i = 1 ; operand[i]!=',' && operand[i]!=0; i++)
				{
					if (operand[i]!='0' && operand[i]!='1'&&operand[i]!='2'&&operand[i]!='3'&&operand[i]!='4'&&operand[i]!='5'&&operand[i]!='6'&&operand[i]!='7'&&operand[i]!='8'&&operand[i]!='9')
					{
						cerr << "Error on line " << line << ": invalid missing value for register or extra value" << endl;
						return -1;
					}
				}
				
				if (operand[i]!=',')
				{
					cerr << "Error on line " << line << ": invalid missing comma after Register" << endl;
					return -1;
				}
				if ((operand[i]==',' && operand[i+1]==',') ||(operand[i]==',' && operand[i+1]==0) )
				{
					cerr << "Error on line "<<line<<" missing operand" << endl;
					return -1;
				}
				if (operand[i+1]!='R')
				{
				cerr << "Error on line " << line << ": invalid missing Register after comma; saw " << operand[i+1] << "" << endl;
				return -1;
				}
				int p=i+2;
				if (operand[i+2]==0)
				{
					cerr << "Error on line " << line << ": invalid missing integer or extra value" << endl;
					return -1;
				}
					
				for (p = i+2 ; operand[p]!=0; p++)
				{
					if (operand[p]!='0' && operand[p]!='1'&&operand[p]!='2'&&operand[p]!='3'&&operand[p]!='4'&&operand[p]!='5'&&operand[p]!='6'&&operand[p]!='7'&&operand[p]!='8'&&operand[p]!='9')
					{
						cerr << "Error on line " << line << ": invalid missing value for register or extra value" << endl;
						return -1;
					}
				}
				AlreadyChecked= true;
			}
			else if(AlreadyChecked==false){
				cerr << "Error on line " << line << ":invalid missing Register; " << "saw " << operand[0] << endl; //MIGHT BE invalid , missing, SAME WITH OTHERS WHICH ARE AFTER THE WHOLE CODE.
				return -1;
			}
			return 0;
			
		}
		
		if(!comparestr(opcode, (char*)"LDi")) //working fine
		{
			
			if (operand[0]=='0' || operand[0]=='1'||operand[0]=='2'||operand[0]=='3'||operand[0]=='4'||operand[0]=='5'||operand[0]=='6'||operand[0]=='7'||operand[0]=='8'||operand[0]=='9')
			{
				int i=1;
				for (i=1 ; operand[i]!=',' && operand[i]!=0; i++)
				{
					if (operand[i]!='0' && operand[i]!='1'&&operand[i]!='2'&&operand[i]!='3'&&operand[i]!='4'&&operand[i]!='5'&&operand[i]!='6'&&operand[i]!='7'&&operand[i]!='8'&&operand[i]!='9')
					{
						cerr << "Error on line " << line << ": invalid missing value for number or extra value" << endl;
						return -1;
					}
				}
				if (operand[i]!= ',')
				{
					cerr << "Error on line " << line << ": invalid missing comma after Register" << endl;
					return -1;
				}
				if ((operand[i]==',' && operand[i+1]==',') ||(operand[i]==',' && operand[i+1]==0) )
				{
					cerr << "Error on line "<<line<<" missing operand" << endl;
					return -1;
				}
				if (operand[i+1]!='R')
				{
					cerr << "Error on line " << line << ": invalid missing Register after comma; saw " << operand[i+1] << "" << endl;
					return -1;
				}
				
				int p=i+2;
				if (operand[i+2]==0)
				{
					cerr << "Error on line " << line << ": invalid missing integer or extra value" << endl;
					return -1;
				}
					
				for (p = i+2 ; operand[p]!=0; p++)
				{
					if (operand[p]!='0' && operand[p]!='1'&&operand[p]!='2'&&operand[p]!='3'&&operand[p]!='4'&&operand[p]!='5'&&operand[p]!='6'&&operand[p]!='7'&&operand[p]!='8'&&operand[p]!='9')
					{
						cerr << "Error on line " << line << ": invalid missing value for register or extra value" << endl;
						return -1;
					}
				}
			}
			else{
				cerr << "Error on line " << line << ": invalid missing Register; " << "saw " << operand[0] << endl; 
				return -1;
			}
			return 0;
		}
		
		if(!comparestr(opcode, (char*)"SD")) //working fine so far
		{			
			if (operand[0] == 'R') 
			{
				int p=1;
				
				int i=1;
				if (operand[i]==',')
				{
					cerr << "Error on line " << line << ": invalid missing integer or extra value" << endl;
					return -1;
				}
					
				for (i=1 ; operand[i]!=',' && operand[i]!=0; i++)
				{
					if (operand[i]!='0' && operand[i]!='1'&&operand[i]!='2'&&operand[i]!='3'&&operand[i]!='4'&&operand[i]!='5'&&operand[i]!='6'&&operand[i]!='7'&&operand[i]!='8'&&operand[i]!='9')
					{
						cerr << "Error on line " << line << ": invalid missing value for register or extra value" << endl;
						return -1;
					}
				}
				
				
				if (operand[i]!=',')
				{
					cerr << "Error on line " << line << ": invalid missing comma after Register" << endl;
					return -1;
				}
				if ((operand[i]==',' && operand[i+1]==',') ||(operand[i]==',' && operand[i+1]==0) )
				{
					cerr << "Error on line "<<line<<" missing operand" << endl;
					return -1;
				}
				if (operand[i+1]!='R' && operand[i+1]!='0' && operand[i+1]!='1'&&operand[i+1]!='2'&&operand[i+1]!='3'&&operand[i+1]!='4'&&operand[i+1]!='5'&&operand[i+1]!='6'&&operand[i+1]!='7'&&operand[i+1]!='8'&&operand[i+1]!='9') // need to re-check this condition
				{
					cerr << "Error on line " << line << ": invalid missing Register after comma; saw " << operand[p] << "" << endl;
					return -1;
				}
				if (operand[i+2]==0)
				{
					cerr << "Error on line " << line << ": invalid missing integer or extra value" << endl;
					return -1;
				}
					
				for (p=i+2; operand[p]!=0; p++)
				{
					if (operand[p]!='0' && operand[p]!='1'&&operand[p]!='2'&&operand[p]!='3'&&operand[p]!='4'&&operand[p]!='5'&&operand[p]!='6'&&operand[p]!='7'&&operand[p]!='8'&&operand[p]!='9')
					{
						cerr << "Error on line " << line << ": invalid missing value for number or extra value" << endl;
						return -1;
					}
				}
				
			}
			else{
				cerr << "Error on line " << line << ": invalid missing Register; " << "saw " << operand[0] << endl;
				return -1;
			}
			return 0;
		}
		if(!comparestr(opcode, (char*)"SDi")) //might be working
		{			
			bool check = true;
			int p=1;
			if (operand[0]=='0' || operand[0]=='1'||operand[0]=='2'||operand[0]=='3'||operand[0]=='4'||operand[0]=='5'||operand[0]=='6'||operand[0]=='7'||operand[0]=='8'||operand[0]=='9')
			{
				int i=1;
				for (i=1 ; operand[i]!=',' && operand[i]!=0; i++)
				{
					if (operand[i]!='0' && operand[i]!='1'&&operand[i]!='2'&&operand[i]!='3'&&operand[i]!='4'&&operand[i]!='5'&&operand[i]!='6'&&operand[i]!='7'&&operand[i]!='8'&&operand[i]!='9')
					{
						cerr << "Error on line " << line << ": invalid missing value for number or extra value" << endl;
						return -1;
					}
				}
				if (operand[i]!= ',')
				{
					cerr << "Error on line " << line << ": invalid missing comma after number" << endl;
					return -1;
				}
				if ((operand[i]==',' && operand[i+1]==',') ||(operand[i]==',' && operand[i+1]==0) )
				{
					cerr << "Error on line "<<line<<" missing operand" << endl;
					return -1;
				}
				if (operand[i+1]!='R' && operand[i+1]!='0' && operand[i+1]!='1'&&operand[i+1]!='2'&&operand[i+1]!='3'&&operand[i+1]!='4'&&operand[i+1]!='5'&&operand[i+1]!='6'&&operand[i+1]!='7'&&operand[i+1]!='8'&&operand[i+1]!='9') // need to re-check this condition
				{
					cerr << "Error on line " << line << ": invalid missing Register after comma; saw " << operand[p] << "" << endl;
					return -1;
				}
				if (operand[i+2]==0)
				{
					cerr << "Error on line " << line << ": invalid missing integer or extra value" << endl;
					return -1;
				}
					
				for (p=i+2; operand[p]!=0; p++)
				{
					if (operand[p]!='0' && operand[p]!='1'&&operand[p]!='2'&&operand[p]!='3'&&operand[p]!='4'&&operand[p]!='5'&&operand[p]!='6'&&operand[p]!='7'&&operand[p]!='8'&&operand[p]!='9')
					{
						cerr << "Error on line " << line << ": invalid missing value for number or extra value" << endl;
						return -1;
					}
				}
			
			}
			else{
				cerr << "Error on line " << line << ": invalid missing number; " << "saw " << operand[0] << endl;
				return -1;
			}
			return 0;
		}
		
		if(!comparestr(opcode, (char*)"ADD") || !comparestr(opcode, (char*)"SUB") || !comparestr(opcode, (char*)"MUL") || !comparestr(opcode, (char*)"DIV")) //working fine
		{	
			if (operand[0] == 'R')
			{
				int i=1;
				if (operand[i]==',')
				{
					cerr << "Error on line " << line << ": invalid missing integer or extra value" << endl;
					return -1;
				}
					
				for (i=1 ; operand[i]!=',' && operand[i]!=0; i++)
				{
					if (operand[i]!='0' && operand[i]!='1'&&operand[i]!='2'&&operand[i]!='3'&&operand[i]!='4'&&operand[i]!='5'&&operand[i]!='6'&&operand[i]!='7'&&operand[i]!='8'&&operand[i]!='9')
					{
						cerr << "Error on line " << line << " : invalid missing value for register or extra value" << endl;
						return -1;
					}
				}
				if (operand[i]!=',')
				{
					cerr << "Error on line " << line << " : invalid missing comma after Register" << endl;
					return -1;
				}
				if ((operand[i]==',' && operand[i+1]==',') ||(operand[i]==',' && operand[i+1]==0))
				{
					cerr << "Error on line "<<line<<" missing operand" << endl;
					return -1;
				}
				if (operand[i+1]!='R')
				{
					cerr << "Error on line " << line << " : invalid missing Register after comma; saw " << operand[i+1] << "" << endl;
					return -1;
				}
				if (operand[i+2]==',')
				{
					cerr << "Error on line " << line << ": invalid missing integer or extra value" << endl;
					return -1;
				}
					
				for (i=i+2 ; operand[i]!=',' && operand[i]!=0; i++)
				{
					if (operand[i]!='0' && operand[i]!='1'&&operand[i]!='2'&&operand[i]!='3'&&operand[i]!='4'&&operand[i]!='5'&&operand[i]!='6'&&operand[i]!='7'&&operand[i]!='8'&&operand[i]!='9')
					{
						cerr << "Error on line " << line << " : invalid missing value for register or extra value" << endl;
						return -1;
					}
				}
				
				if (operand[i]!=',')
				{
					cerr << "Error on line " << line << " : invalid missing comma after Register" << endl;
					return -1;
				}
				if ((operand[i]==',' && operand[i+1]==',') ||(operand[i]==',' && operand[i+1]==0))
				{
					cerr << "Error on line "<<line<<" missing operand" << endl;
					return -1;
				}
				if (operand[i+1]!='R')
				{
					cerr << "Error on line " << line << " : invalid missing Register after comma; saw " << operand[i+1] << "" << endl;
					return -1;
				}
				if (operand[i+2]==0)
				{
					cerr << "Error on line " << line << ": invalid missing integer or extra value" << endl;
					return -1;
				}
					
				for (i=i+2 ;operand[i]!=0; i++)
				{
					if (operand[i]!='0' && operand[i]!='1'&&operand[i]!='2'&&operand[i]!='3'&&operand[i]!='4'&&operand[i]!='5'&&operand[i]!='6'&&operand[i]!='7'&&operand[i]!='8'&&operand[i]!='9')
					{
						cerr << "Error on line " << line << " : invalid missing value for register or extra value" << endl;
						return -1;
					}
				}
				
			}
			else{
				cerr << "Error on line " << line << "invalid missing Register; " << "saw " << operand[0] << endl;
				return -1;
			}
			return 0;
		}
		if( !comparestr(opcode, (char*)"SUBi") ||!comparestr(opcode, (char*)"ADDi") || !comparestr(opcode, (char*)"MULi") || !comparestr(opcode, (char*)"DIVi")) //working fine
		{
			if (operand[0] == 'R')
			{
				int i=1;
				int p=0;
				if (operand[i]==',')
				{
					cerr << "Error on line " << line << ": invalid misssing integer or extra value" << endl;
					return -1;
				}
					
				for (i=1 ; operand[i]!=',' && operand[i]!=0; i++)
				{
					if (operand[i]!='0' && operand[i]!='1'&&operand[i]!='2'&&operand[i]!='3'&&operand[i]!='4'&&operand[i]!='5'&&operand[i]!='6'&&operand[i]!='7'&&operand[i]!='8'&&operand[i]!='9')
					{
						cerr << "Error on line " << line << " : invalid missing value for register or extra value" << endl;
						return -1;
					}
				}
				if (operand[i]!=',')
				{
					cerr << "Error on line " << line << " : invalid missing comma after Register" << endl;
					return -1;
				}
				if ((operand[i]==',' && operand[i+1]==',') ||(operand[i]==',' && operand[i+1]==0))
				{
					cerr << "Error on line "<<line<<" missing operand" << endl;
					return -1;
				}
				for ( p=i+1; operand[p]!=',' && operand[i]!=0; p++)
				{
					if (operand[p]!='0' && operand[p]!='1'&&operand[p]!='2'&&operand[p]!='3'&&operand[p]!='4'&&operand[p]!='5'&&operand[p]!='6'&&operand[p]!='7'&&operand[p]!='8'&&operand[p]!='9')
					{
						cerr << "Error on line " << line << " : invalid missing number to be added to register or extra value added" << endl;
						return -1;
					}
				}
				if (operand[p] != ',')
				{
					cerr << "Error on line " << line << " : invalid missing comma after Register" << endl;
					return -1;
				}
				if ((operand[p]==',' && operand[p+1]==',') ||(operand[p]==',' && operand[p+1]==0))
				{
					cerr << "Error on line "<<line<<" missing operand" << endl;
					return -1;
				}
				if (operand[p+1] != 'R')
				{
					cerr << "Error on line " << line << " : invalid missing Register after comma; saw " << operand[i+1] << "" << endl;
					return -1;
				}
				if (operand[p+2]==0)
				{
					cerr << "Error on line " << line << ": invalid missing integer or extra value" << endl;
					return -1;
				}
					
				for (p=p+2 ; operand[p]!=0; p++)
				{
					if (operand[p]!='0' && operand[p]!='1'&&operand[p]!='2'&&operand[p]!='3'&&operand[p]!='4'&&operand[p]!='5'&&operand[p]!='6'&&operand[p]!='7'&&operand[p]!='8'&&operand[p]!='9')
					{
						cerr << "Error on line " << line << " : invalid missing value for register or extra value" << endl;
						return -1;
					}
				}
				
			}
			else {
				cerr << "Error on line " << line << "invalid missing Register; " << "saw " << operand[0] << endl;
				return -1;
			}
			return 0;
		}
		
		if(!comparestr(opcode, (char*)"JZ") || !comparestr(opcode, (char*)"JNZ") || !comparestr(opcode, (char*)"JGZ") || !comparestr(opcode, (char*)"JGEZ") || !comparestr(opcode, (char*)"JLZ") || !comparestr(opcode, (char*)"JLEZ")) //working fine
		{
			
			if (operand[0] == 'R')
			{
				int l=0;
				int i=1;
				int p=0;
				if (operand[i]==',')
				{
					cerr << "Error on line " << line << ": invalid missing integer or extra value" << endl;
					return -1;
				}
									
				for (i=1 ; operand[i]!=',' && operand[i]!=0; i++)
				{
					
					if (operand[i]!='0'&& operand[i]!='1'&&operand[i]!='2' && operand[i]!='3'&&operand[i]!='4'&&operand[i]!='5'&&operand[i]!='6'&&operand[i]!='7'&&operand[i]!='8'&&operand[i]!='9')
					{
						
						cerr << "Error on line " << line << ": invalid missing number for register, need integer" << endl;
						return -1;
					}
				}
			
				if (operand[i]!=',')
				{
					cerr << "Error on line " << line << " : invalid missing comma after Register" << endl;
					return -1;
				}
				if ((operand[i]==',' && operand[i+1]==',') ||(operand[i]==',' && operand[i+1]==0))
				{
					cerr << "Error on line "<<line<<" missing operand" << endl;
					return -1;
				}
				
				for (i=i+1; operand[i]!=0 ; i++)
				{
					if (operand[i]!='0' && operand[i]!='1'&&operand[i]!='2'&&operand[i]!='3'&&operand[i]!='4'&&operand[i]!='5'&&operand[i]!='6'&&operand[i]!='7'&&operand[i]!='8'&&operand[i]!='9')
					{
						cerr << "Error on line " << line << ": invalid missing integer or extra value" << endl;
						return -1;
					}
				}
			}
			else {
				cerr << "Error on line " << line << "invalid missing Register; " << "saw " << operand[0] << endl;
				return -1;
			}
			return 0;
		}
		if (!comparestr(opcode, (char*)"JMP")) //working fine
		{ 
			if (operand[0]==0)
			{
				cerr << "Error on line "<<line<<" missing operand" << endl;
				return -1;
				
			}
			else 
			{
				for (int h=0 ; operand[h]!=0 ; h++)
				{
					if (operand[h]!='0' && operand[h]!='1'&& operand[h]!='2' && operand[h]!='3'&&operand[h]!='4'&&operand[h]!='5'&&operand[h]!='6'&&operand[h]!='7'&&operand[h]!='8'&&operand[h]!='9')
					{
						cerr << "Error on line " << line << ": invalid missing integer or extra value" << endl;
						return -1;
					}
				}
			}	
			return 0;
		}
		
}


int main(int argc, char* argv[])
{
	
	// Checks if the file exists
	ifstream infile;
	infile.open(argv[1]);
	
	if (argc != 2)
	{
		cerr << "Error: INVALID ARGUMENTS." << endl; 
		cerr << "Error: File can't be opened." << endl;
		return -1;
	}
	
	if (infile.is_open())
	{
		// cout << "File exists." << endl;
	}
	
	else
	{
		cerr << "Error: File can't be opened." << endl;
		return -1;
	}
	
	const int maxLineLength = 100;
	char line[maxLineLength];
	
	// char nextChar;
	int numAssembly = 0;
	int codeValue = 0;
	int dataValue = 0;
	int numLines = 1;
	int numOfALU = 0;
	int numOfLoads = 0;
	int numJump = 0;
	int errors = 0;
	int labelsIndex = 0;
	int codeOccur=0;
	bool AlreadyPrintedOut;
	
	enum LineStyle {COMMENT, LABEL, ASSEMBLY};
	LineStyle style;
	
	
	Label labelArray[10];
	
	// Set maximum line length, so we don't overflow the buffer
	infile >> setw(maxLineLength);
  
   // Read from file
	while(infile.getline(line, maxLineLength)) 
	{
		removeWhitespaces(line);
		style = ASSEMBLY;
		
		if (line[0] == '#')
			style = COMMENT;
		
		if (style != COMMENT)
		{
			for (int i = 0; line[i] != 0 && i < 100; i++)
			{
				if (line[i] == ':'){
					style = LABEL;
					break;
				}
			}
		}
		
		switch(style){
			
			case COMMENT:{
				
				//cout << "COMMENT";
				break;
			}
			
			case LABEL:{
				
				//cout << "LABEL";
				
				char label[30];
				
				int j=0;
				
				if (line[j] == ':')
				{
					cerr << "Error on line " << numLines << ": Invalid label detected" << endl;
					errors++;
					break;
				}
				
				while(line[j]!=':')
				{
					label[j] = line[j];
					
					j++;
				}
				label[j] = ':';
				label[j+1] = 0;
				// cout << label << endl;
				
				// When it's a code directive
				
				if (!comparestr(label, (char*)"Code:") && numAssembly == 0)
				{
					int numElemData = 1;
					codeOccur=1;										
					int val;
					for (val=6; line[val]!=0 && line[val]!='#' && line[val]!='\n'  && line[val] != ' '; val++)
					{
						numElemData++;
					}
					
					char codeValueArray[numElemData];
					int c=0;
					
					for (int y=6; line[y]!=0 && line[y]!='#' && line[y]!='\n'  && line[y] != ' '; y++) 
					{
						codeValueArray[c] = line[y];
						c++;
					}
					
					codeValueArray[c] = 0;
					codeValue = atoi(codeValueArray);
					
					break;
				}
				//cout << "Codeoccur " << codeOccur << endl;
				if (!comparestr(label, (char*)"Code:") && numAssembly != 0 && codeOccur!=1)
				{
					cerr << "Error on Line: 1" << " missing directive (code) before the first assembly instruction" << endl;
					errors++;
					AlreadyPrintedOut = true;
					break;
				}
				// When the Code directive is repeated again in the assembly file
				if (!comparestr(label, (char*)"Code:") && codeOccur==1)
				{
					cerr << "Error on line " << numLines << ": duplicate directive found" << endl;
					errors++;
					break;
				}
				
				// When it's a data directive
				if (!comparestr(label, (char*)"Data:"))
				{	
					int numElemData = 1;
															
					int val;
					for (val=6; line[val]!=0 && line[val]!='#' && line[val]!='\n'  && line[val] != ' '; val++)
					{
						numElemData++;
					}
					
					char dataValueArray[numElemData];
					int c=0;
					
					for (int y=6; line[y]!=0 && line[y]!='#' && line[y]!='\n'  && line[y] != ' '; y++) 
					{
						dataValueArray[c] = line[y];
						c++;
					}
					
					dataValueArray[c] = 0;
					dataValue = atoi(dataValueArray);
					// cout << dataValue << endl;
					break;
				}
				
				// When it is not a Code or Data directive
				// Aka when it's a label
				
				int ind = j + 1;
				while (line[ind] != 0 && line[ind] != '#')
				{
					if (line[ind] != ' ' && line[ind] != '\t')
					{
						cerr << "Error on line " << numLines << ": Invalid input detected" << endl;
						errors++;
						break;
					}
					ind++;
				}
					
				// Removing colon from the label to insert into data array
				label[j] = 0;
				
				copyStr(labelArray[labelsIndex].name, label);
				labelArray[labelsIndex].value = codeValue + numAssembly;
					
				// Checks if there is a duplicate label
				for(int l = 0; l < labelsIndex - 1; l++)
				{
					if (!comparestr(label, labelArray[l].name)) // shouldnt this be l instead of labelsIndex
					{
						cerr << "Error on line " << numLines << ": duplicate label detected" << endl;
						errors++;
						break;
					}
				}	
					
				// cout << labelArray[labelsIndex].name << endl;
				labelsIndex++;
			
				break;
			}
			
			case ASSEMBLY:
			{
				//cout << "Hitting assembly" << endl;
				enum opcodestyles {LDSD, ALU, JMP};
				opcodestyles OPCODE = LDSD;
				char opcodeStr[5] = "";
				char operand[100] = "";
				int ind = 0;
				int indl;
				
				/*
				if (line[0]=='\n'){
					numLines++;
					break;
				}*/
				
				// Failing for new line character
				/*if (line[0]!='A'&&line[0]!='S'&&line[0]!='L'&&line[0]!='J'&&line[0]!='D'&&line[0]!='M' && line[0] != 0)
				{
					cerr << "Error on Line " << numLines<< " opcode not found" << endl;
					errors++;
				}*/
				
				
				//cout<< "After trim spaces: "<<line<< endl;
				for (ind=0; line[ind]!= ' ' && line[ind]!=0; ind++) 
				{
					opcodeStr[ind] = line[ind];
				}
				if ((!(!comparestr(opcodeStr, (char*)"LD") || !comparestr(opcodeStr, (char*)"SD") || !comparestr(opcodeStr, (char*)"LDi") || !comparestr(opcodeStr, (char*)"SDi") || !comparestr(opcodeStr, (char*)"ADD") || !comparestr(opcodeStr, (char*)"SUB") ||!comparestr(opcodeStr, (char*)"MUL") || !comparestr(opcodeStr, (char*)"DIV")|| !comparestr(opcodeStr, (char*)"ADDi") || !comparestr(opcodeStr, (char*)"SUBi") ||!comparestr(opcodeStr, (char*)"MULi") || !comparestr(opcodeStr, (char*)"DIVi") || !comparestr(opcodeStr, (char*)"JLZ")||!comparestr(opcodeStr, (char*)"JZ")||!comparestr(opcodeStr, (char*)"JNZ")||!comparestr(opcodeStr, (char*)"JGZ")||!comparestr(opcodeStr, (char*)"JGEZ")||!comparestr(opcodeStr, (char*)"JLEZ")|| !comparestr(opcodeStr, (char*)"JMP")))&&line[0]!=0)
				{
					cerr << "Error on Line " << numLines<< " invalid or opcode not found" << endl;
					errors;
				}
				
				//cout <<comparestr(opcodeStr, "LD")<<"$$$"<<endl;
				if (!comparestr(opcodeStr, (char*)"LD") || !comparestr(opcodeStr, (char*)"SD"))
				{
					
					//cout << "Hitting LD/SD" << endl;
					
					int dummy =0; 
					
					for (indl=ind+1; (line[indl]!= 0) && (line[indl]!= '\n') && (line[indl]!= '#'); indl++)
					{				
						operand[dummy] = line[indl];
						dummy++;
					}
					
					//cout << operandCheck(operand, opcodeStr, numLines) << endl << endl << endl;
					if (operandCheck(operand, opcodeStr, numLines) < 0)
						errors++;
					
					numOfLoads++;
					numAssembly++;
				}
				
				if (!comparestr(opcodeStr, (char*)"LDi") || !comparestr(opcodeStr, (char*)"SDi"))
				{
					//cout << "Hitting LDi/SDi" << endl;
					
					int dummy =0; 
					for (indl=ind+1; line[indl]!= 0 && line[indl]!= ' ' && line[indl]!= '\n' && line[indl]!= '#'; indl++)
					{
						operand[dummy] = line[indl];
						dummy++;
					}
					
					if (operandCheck(operand, opcodeStr, numLines) < 0)
						errors++;
					
					numOfLoads++;
					numAssembly++;
				}
				
				if (!comparestr(opcodeStr, (char*)"ADD") || !comparestr(opcodeStr, (char*)"MUL") || !comparestr(opcodeStr, (char*)"SUB") || !comparestr(opcodeStr, (char*)"DIV"))
				{	
					//cout << "Hitting ADD/SUB/MUL/SUB/DIV" << endl;
					
					int dummy =0; 
					for (indl=ind+1; line[indl]!= 0 && line[indl]!= ' ' && line[indl]!= '\n' && line[indl]!= '#'; indl++)
					{
						operand[dummy] = line[indl];
						dummy++;
					}
					
					if (operandCheck(operand, opcodeStr, numLines) < 0)
						errors++;
					
					numOfALU++;
					numAssembly++;
				}
								
				if (!comparestr(opcodeStr, (char*)"ADDi") || !comparestr(opcodeStr, (char*)"MULi") || !comparestr(opcodeStr, (char*)"SUBi") || !comparestr(opcodeStr, (char*)"DIVi"))
				{				
					//cout << "Hitting ADDi/SUBi/MULi/SUBi/DIVi" << endl;
					
					int dummy =0; 
					for (indl=ind+1; line[indl]!= 0 && line[indl]!= ' ' && line[indl]!= '\n' && line[indl]!= '#'; indl++)
					{
						operand[dummy] = line[indl];
						dummy++;
					}
					//cout << "~~~~~" << opcodeStr << "&&" << operand << endl <<endl;
					//cout << operandCheck(operand, opcodeStr, numLines) << endl << endl << endl;
					if (operandCheck(operand, opcodeStr, numLines) < 0)
						errors++;
					
					numOfALU++;
					numAssembly++;
				}
				
				if (!comparestr(opcodeStr, (char*)"JZ") || !comparestr(opcodeStr, (char*)"JNZ") || !comparestr(opcodeStr, (char*)"JGZ") || !comparestr(opcodeStr, (char*)"JGEZ")|| !comparestr(opcodeStr, (char*)"JLZ")|| !comparestr(opcodeStr, (char*)"JLEZ"))
				{
					//cout << "Hitting JZ/JNZ/JGZ/JGEZ/JLZ/JLEZ" << endl;
					
					int dummy =0; 
					for (indl=ind+1; line[indl]!= 0 && line[indl]!= ' ' && line[indl]!= '\n' && line[indl]!= '#'; indl++)
					{
						operand[dummy] = line[indl];
						dummy++;
					}
					//cout << "~~~~~" << opcodeStr << "&&" << operand << endl <<endl;
					//cout << operandCheck(operand, opcodeStr, numLines) << endl << endl << endl;
					if (operandCheck(operand, opcodeStr, numLines) < 0)
						errors++;
					
					numJump++;
					numAssembly++;
				}
				
				if (!comparestr(opcodeStr, (char*)"JMP"))
				{
					//cout << "Hitting JMP" << endl;
					
					int dummy =0; 
					for (indl=ind+1; line[indl]!= 0 && line[indl]!= ' ' && line[indl]!= '\n' && line[indl]!= '#'; indl++)
					{
						operand[dummy] = line[indl];
						dummy++;
					}
					
					if (operandCheck(operand, opcodeStr, numLines) < 0)
						errors++;
					
					numJump++;
					numAssembly++;
				}
				
				
			} // case: Assembly
			
		} // switch
		
		numLines++;
		
	} // while
	if (codeOccur == 0 && !AlreadyPrintedOut)
	{
		cerr << "Error on Line 1, no code directive found" << endl;
		errors++;
	}
	//if (errors == 0)
	//{
		// cout << codeValue << endl;
		// cout << numAssembly << endl;	
		cout << "Total number of assembly instructions: " << numAssembly << endl;
		cout << "Number of Load/Store: " << numOfLoads << endl;
		cout << "Number of ALU: " << numOfALU << endl;
		cout << "Number of Compare/Jump: " << numJump << endl;
		for (int p = 0; p < labelsIndex; p++)
		{
			cout << labelArray[p].name << ": " << labelArray[p].value << endl;
		}	
	//}

	return 0;

}