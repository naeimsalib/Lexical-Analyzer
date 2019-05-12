// Naeim Salib 
// lexical analyzer Program (also known as scanner).

#include<iostream>
#include <string>
#include <vector>
#include <string.h>

using namespace std;


struct atom{
    char atomCheck[1];
    string atomItself ;
    string type;
};

struct atomTree{
	atom atom_A;
	atom rightAtom;
	atom leftAtom;
};

atom getNextTocken(char &char_array,atom &result,vector<string> &atomVector,int &spaceTotal,vector<int> &numAtomVector);
void  printFunction(int &numOfOpenParantheses,int &numOfClosedParantheses,vector<string> &atomVector,vector<int> &numAtomVector);
bool checkAtom(string atom_String);
void printTree(list <atomTree>& s_Sequence);


int main(){
    
    string line;
    list <atomTree> s_Sequence;

    int numOfOpenParantheses = 0 , numOfClosedParantheses = 0;
    vector<string> atomVector;
    vector<int> numAtomVector;
    while(getline(cin,line)){
    bool last_p_Is_Closed;
    int x = line.size();
    char char_array[x];
    strcpy(char_array,line.c_str());
    int spaceTotal = 0;
    atom result;
    int temp;
        
    for (int count = 0; count < x ;count++){
        if(isspace(char_array[count])){
            spaceTotal++;
        }
    }
     temp = spaceTotal;
        
        
    for (int i=0;i<x;i++){
       
        	
            result = getNextTocken(char_array[i],result,atomVector,spaceTotal,numAtomVector);
        
            if (result.type == "Open Parantheses"){
                numOfOpenParantheses++;
                last_p_Is_Closed = false;
            }else if((result.type == "Closed Parantheses")){
                    numOfClosedParantheses++;
                    

                        if(spaceTotal == 0){
                            spaceTotal = temp;
                        }
                        if(last_p_Is_Closed){
                        	printTree(s_Sequence);
                        }else{
                        last_p_Is_Closed = true;
                    }
            }
            result.type = "\0";
    }
    
    }

    printFunction(numOfOpenParantheses,numOfClosedParantheses,atomVector,numAtomVector);
    
    
    
}
//getNextToken function to reseave an input and returns if open or closed Paranthese
//and if it is a character or a digit , it consumes it untill it has enough to form and atom
//it also calls the function checkAtom that checks if the atom is a valid atom 
atom getNextTocken(char &char_array,atom &result,vector<string> &atomVector,int &spaceTotal,vector<int> &numAtomVector){
    
    result.atomCheck[0] = char_array;
    if (result.atomCheck[0] == '0'){
        result.type = "EOF";
    }else if (result.atomCheck[0] == ')'){
        if (spaceTotal == 0){
            if (isalpha(result.atomItself[0])){
                atomVector.push_back(result.atomItself);
                
                result.atomItself = "\0";
            }else if (isdigit(result.atomItself[0])){
                int x = stoi(result.atomItself);
                numAtomVector.push_back(x);
                result.atomItself = "\0";
                x = 0;
            }
            result.type = "Closed Parantheses";
           
        }else{
            result.type = "Closed Parantheses";
           
        }
    }else if (result.atomCheck[0] == '('){
        
        result.type = "Open Parantheses";
        result.atomItself = "\0";
    }else if (isalpha(result.atomCheck[0])){
        result.atomItself += result.atomCheck[0];
        
    }else if (isdigit(result.atomCheck[0])){
        result.atomItself += result.atomCheck[0];
        
    }else if (isspace(result.atomCheck[0])){
        
        if (isalpha(result.atomItself[0])){
            atomVector.push_back(result.atomItself);
            
            result.atomItself = "\0";
        }else if (isdigit(result.atomItself[0])){
            bool result_digit = checkAtom(result.atomItself);
            if (result_digit){
                int x = stoi(result.atomItself);
                numAtomVector.push_back(x);
                result.atomItself = "\0";
                x = 0;
            }else{
                result.type = "ERROR";
                 cerr << "ERROR: Invalid token " << result.atomItself<<endl;
                 exit(0);
            }
        }
        spaceTotal--;
    }
    return result ;
}

// function to check if the atom is valid 
//and return True it is is valid 
// or false if the atom is in-valid
bool checkAtom(string atom_String){
    
    char char_array_2[atom_String.size()];
    strcpy(char_array_2,atom_String.c_str());
    unsigned int j=0;
            if (isalpha(char_array_2[0])){
                    for (j=0;j < atom_String.size();j++){
                        if (isalpha(char_array_2[j]) || isdigit(char_array_2[j])){
                            continue;
                        }else {
                            return false;
                        }
                    }
            }else if (isdigit(char_array_2[0])){
                    for (j=0;j < atom_String.size();j++){
                        if (isdigit(char_array_2[j])){
                            continue;
                        }else {
                            return false;
                        }
                    }
            }
    return true;
}

// a function to Print at the end if not in-valid atoms were found 
	void  printFunction(int &numOfOpenParantheses,int &numOfClosedParantheses,vector<string> &atomVector,vector<int> &numAtomVector){
			    int sumOfNumAtoms = 0;
			    	//cout << numOfOpenParantheses << " " << sizeof(numOfClosedParantheses) << " " << sizeof(atomVector) << endl;
			    	if(numOfOpenParantheses != 0 && numOfClosedParantheses != 0 && atomVector.size() != 0 && numAtomVector.size() != 0){
			        for (unsigned int k = 0; k<numAtomVector.size();k++){
			            sumOfNumAtoms += numAtomVector[k];
			        }

			    cout << "LITERAL ATOMS: " << atomVector.size();
			        for (unsigned int w=0; w<atomVector.size();w++){
			            cout << ", " << atomVector[w];
			        }

			        cout << endl;
			    cout << "NUMERIC ATOMS: "<< numAtomVector.size() << ", "<< sumOfNumAtoms<<endl;
			    cout << "OPEN PARENTHESES: "<< numOfOpenParantheses << endl;
			    cout << "CLOSING PARENTHESES: "<< numOfClosedParantheses << endl;
			}else{

			}
	}


	void printTree(list <atomTree>& s_Sequence){
		LITERAL it;
		for(it=s_Sequence.begin(); it != s_Sequence.end();it++){
			cout << it->atom_A <<endl;
		}
	}


