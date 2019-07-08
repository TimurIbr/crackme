#include <iostream>
#include <string>
#include <bitset> 
#include <algorithm> 

const int XORPassMask = 0x99;
const int MaxValubaleNumber = 0xff;

std::string alphabeta[] = {"hIYYY", "kIYYY", "u19I", "19Y", 
                            "IYYY", "9YY", "YYY", "YY"};
std::string zeros[] = {"YYYY", "99Y"};
int ProcessPass(std::string Pass){
    int result = 0;
	for (int i = 0; i < Pass.length(); ++i){
		result = result + (Pass[i] ^ 0x99);
	}
	return result & 0xff;
}
int ProcessLogin(std::string login)
{
	int result = 0xffffffff;
	int temp = 0;
	for (int j = 0; j < login.length(); ++j){
		result = result ^ login[j];
		for (int i = 7; i >= 0; i--){
			temp = result;
			temp = temp & 1;
			temp = ~ temp;
			temp = temp >> 1; ///////////////////result
			temp = temp & 0xedb88320;
			result = result ^ temp;
		}
	}
	return result;
}

int createReuquare(std::string login){
    int loginResult = ProcessLogin(login);
    loginResult = ~loginResult;
    loginResult = loginResult & 0xff;
    return loginResult;
}

std::string createTempPass (int request){
    request = request & MaxValubaleNumber;
    std::string pass = "";
    for(int i = 0; (1 << i) <= MaxValubaleNumber; ++i){
        if((1 << i) & request){
            pass += alphabeta[i];
        }
    }
    return pass;
}
const bool beauti = true;
std::string createPass(int request){
    std::string pass = createTempPass (request);
    if(!beauti){
        return pass;
    }
    while(1){
        int i; 
        int entry[zeros[0].length()];
        for(i = 0; i < zeros[0].length(); ++i){
            entry[i] = pass.find( std::string(1, zeros[0][i]), (i > 0 ? entry[i - 1] + 1 : 0) );
           if(entry[i] == std::string::npos){
              entry[i] = - 1;
              break;
            }
        }
        if(entry[i] == -1)
            break;
        for(i = zeros[0].length() - 1; i >= 0; --i){
            pass.erase(entry[i], 1);
        }
    }
    return pass;
}
const bool DEBUG = false;
bool ProcessCred(std::string login, std::string password){
    int loginResult = ProcessLogin(login);
    if(DEBUG)
        std::cout<< "loginResult = " <<  std::bitset<sizeof(int) * 8>(loginResult) << "\t";
	int passResult = ProcessPass(password);
	if(DEBUG)
	    std::cout<< "passResult = " <<  std::bitset<sizeof(int) * 8>(passResult) << std::endl;
    loginResult = ~loginResult;
	loginResult = loginResult & 0xff;
	passResult = passResult & 0xff;
	if(DEBUG){
	    std::cout<< "after loginResult = " <<  std::bitset<sizeof(int) * 8>(loginResult) << "\t";
	    std::cout<< "after passResult = " <<  std::bitset<sizeof(int) * 8>(passResult) << std::endl;
	    std::cout<< "requare = " <<  std::bitset<sizeof(int) * 8>(createReuquare(login)) << std::endl;
	}
	if (loginResult == passResult){
		return true;
	}
	return false; 
}
//char CrackSimbols = 
/*bool CharValidate(char ch){
    if( (ch >= '0') && (ch <= '9') )
        return true;
    if( (ch >= 'A') && (ch <= 'Z') )
        return true;
    if( (ch >= 'a') && (ch <= 'z') )
        return true;
    return false;
}
char testChar(int i){
    return char( (XORPassMask ^ i) & 0x7f);
}
std::string createPass (int request){
    request = request & MaxValubaleNumber;
    std::string pass = "";
    char test = 0; 
    for(int i = 1; i <= MaxValubaleNumber; i = i << 1){
        if(i & request){
            
            std::cout << "i = " << i << std::endl;
            
            int DisPos = 0;
            for( DisPos = 0; !CharValidate(testChar(i >> DisPos)); ++DisPos ){
                std::cout << "test_char = " << std::bitset<sizeof(char) * 8>(testChar(i >> DisPos)); 
                std::cout <<  " that is " << char(testChar(i >> DisPos)) << std::endl;
                if(! (i >> DisPos) ){
                    std::cout << "error: no such passwords" << std::endl;
                    return nullptr;
                }
            }
            for(int j = 0; j < 1 << DisPos; ++j)
                pass += testChar(i >> DisPos);
        }
    }
    return pass;
}*/
int main()
{
    //std::cout << CharValidate('`') << CharValidate('2') << CharValidate('K') << CharValidate ('k') << std::endl;
/*    std::cout << "OUR MASK is " << std::bitset<sizeof(int) * 8>(XORPassMask) << std::endl;
    std::cout << "OUR max valuable number is " << std::bitset<sizeof(int) * 8>(MaxValubaleNumber) << std::endl;*/
/*    int temp = 2123;
    std::cout << createPass(temp) << (ProcessPass(createPass(temp)) == (temp & 0xff) ? " _VALUABLE": " _NotValuable") << std::endl;*/
    std::string login;
    std::cin >> login;
    if(ProcessCred(login, createPass(createReuquare(login)) ))
        std::cout << createPass(createReuquare(login)) << std::endl;
    else{
        std::cout << "error: login and pass dismatch" << std::endl;
        std::cout << createPass(createReuquare(login)) << std::endl;
        std::cout << "ProcessLogin " << ProcessLogin(login) << std::endl;
        std::cout << "ProcessReuquare " << createReuquare(login) << std::endl;
        std::cout << "ProcessPass " << ProcessPass(createPass(createReuquare(login))) << std::endl;
    }

/*   for(int i = 0; i < 8; ++i ){
        std::cout << std::bitset<8>( ProcessPass(alphabeta[i]) )<< std::endl;
   }*/
    return 0;
}
