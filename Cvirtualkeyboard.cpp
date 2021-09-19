#include<iostream>
#include<unistd.h>
#include<thread>
#include <signal.h>
#include <cstring>


using namespace std;


bool quit =false;
void gotSignal(int)
{
    quit=true;
}

class KeyBoard
{

    string curr_line;
    long num_lines = 0;

    public:
    KeyBoard()
    {
        cout << "Virtual Keyboard started.\n";
        cout << "Please type in. Output will be displayed on the screen.\n";
        cout << "In order to close the keyboard, press the 'ctrl' + 'C' key and press the 'Enter' key: \n";
        cout << "Please note that the empty lines are not considered for printing on console. \n\n";
    }

    ~KeyBoard()
    {
        cout << "\nVirtual Keyboard closed.\n";
        cout << "Number of lines printed on the console: " + to_string(num_lines) + "\n\n";
    }

    void startListening()
    {
        while(true){
            curr_line = "";
            if( quit) break;
            else{
                getline(cin, curr_line);
                if (curr_line != ""){
                    cout << "Keyboard output: " + curr_line + "\n";
                    num_lines++;
                }
            }
        }

    }
};


int main(){


    // declare an object of the keyboard class
    KeyBoard keyboard;

    // set up the exit signal listener
    struct sigaction sa;

    memset(&sa,0,sizeof(sa) );
    sa.sa_handler = gotSignal;
    sigfillset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);

    // start a thread that runs the keyboard listener.
    thread th([&]()
    {
        keyboard.startListening();
    });


    th.join();

    return 0;
}
