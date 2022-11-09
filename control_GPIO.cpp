/** GPIO control program that sets the state of an LED connect to a GPIO pin and reads the state
*    of a push button attached to another GPIO pin - written in C++ by Joshua Ryan
*
*    Usage is: control_GPIO output_gpio state input_gpio
*
**/

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include"GPIO.h"
using namespace std;

int writeGPIO(string gpio, string value);
string readGPIO(string gpio);

int writeGPIO(string gpio, string value){
   ofstream fs;
   ostringstream s;
   string path;
   s << "/sys/class/gpio/" << gpio << "/value";
   path = string(s.str());
   fs.open((path).c_str());
   if (!fs.is_open()){
           perror("GPIO: write failed to open file ");
           return -1;
   }
   fs << value;
   fs.close();
   return 0;
}

string readGPIO(string gpio){
   ifstream fs;
   ostringstream s;
   string path;
   s << "/sys/class/gpio/" << gpio<< "/value";
   path = string(s.str());
   fs.open((path).c_str());
   if (!fs.is_open()){
           perror("GPIO: read failed to open file ");
    }
   string input;
   getline(fs,input);
   fs.close();

   if(input=="0"){
      return "low";
   }
   else{
      return "high";
   }
}


int main(int argc, char* argv[]){
   if(argc!=4){
	cout << "Usage is: control_GPIO gpio_number1 state gpio_number2" << endl;
        cout << "gpio_number1: LED output GPIO" << endl;
	cout << "state: Output GPIO hi or low" << endl;
        cout << "gpio_number2: Button input GPIO" << endl;
        return 2;
   }
   string state;
   state = argv[2];
   ostringstream gpio1;
   ostringstream gpio2;
   gpio1<<"gpio"<<argv[1];
   gpio2<<"gpio"<<argv[3];
   cout << "Starting the control_GPIO program" << endl;

   if(state=="low"){
        cout << "Setting the LED " << argv[2] << endl;
        writeGPIO(string(gpio1.str()), "0");
   }
   else if(state=="hi"){
        cout << "Setting the LED " << argv[2] << endl;
        writeGPIO(string(gpio1.str()), "1");
   }
   else{
	cout << "Invalid state!" << endl;
        cout << "State options are hi or low" << endl;
   }

   cout << "GPIO " << argv[3] << " state is " << readGPIO(string(gpio2.str())) << endl;
   cout << "Ending the control_GPIO Program" << endl;
   return 0;
}
