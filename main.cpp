#include <iostream>
#include <iomanip>
#include "expression.h"
#include "grid.h"
#include <ctime>
#include <cstdlib>
#include <time.h>
using namespace std;

void greyScale(int windWidth, int windHeight, Expression * expr);
void colorScale(int windWidth, int windHeight, Expression * expr1, Expression * expr2,Expression * expr3);
string randomer(int depth);
int RandomInt(int min, int max);

int main()
{
    char userChoice = ' ';
    int min = 1, max = 1;
    string userExpress = "";
      do {
        cout << "Welcome the Random Art Creator" << endl
             << "========================================" << endl
             << "1. Enter an Expression" << endl
             << "2. Set min and max recursion depth" << endl
             << "3. Generate a random greyscale image" << endl
             << "4. Generate for a random color image" << endl
             << "5. Quit" << endl
             << "Please enter a menu option: ";
        cin.clear();
        cin.get(userChoice);
        cin.clear();
        switch (userChoice) {

            case('1'): {
                    cout << "Enter an expression: ";
                    cin >> userExpress;
                    cin.clear();
                    cin.ignore(256,'\n');
                    Expression * expr = new Expression(userExpress);
                    cout<< endl << "Expression: "<<endl;
                    cout<<userExpress<<endl<<endl;
                    greyScale(800, 800, expr);
            break;
            } //end case 1

            case('2'): {
                while (true)
                {
                    cout << "Enter a min and max Recursion depth (default min = 1 and max = 1\n";
                    cout << "Min: ";
                    cin >> min;
                    cin.clear();
                    cin.ignore(256,'\n');
                    cout << "Max: ";
                    cin >> max;
                    cin.clear();
                    cin.ignore(256,'\n');
                    if (min<0||max>12)
                        cout << "invalid range for min or max. Must be 0 - 12 inclusive.\n";
                    else
                        break;
                }
            break;
            } //end case 2

            case ('3'): {
                string express = randomer(RandomInt(min, max));
                Expression * expr = new Expression(express);
                cout<<"Expression: "<<endl;
                cout<<express<<endl<<endl;
                greyScale(800, 800, expr);
                cin.clear();
                cin.ignore(256,'\n');
            break;
            } //end case 3

            case ('4'): {
                string express1 = randomer(RandomInt(min, max));
                string express2 = randomer(RandomInt(min, max));
                string express3 = randomer(RandomInt(min, max));
                Expression * expr1 = new Expression(express1);
                Expression * expr2 = new Expression(express2);
                Expression * expr3 = new Expression(express3);
                cout<<"Expressions: "<<endl;
                cout<<"1. "<<express1<<endl<<"2. "<<express2<<endl<<"3. "<<express3<<endl;
                colorScale(800,800,expr1,expr2,expr3);
                cin.clear();
                cin.ignore(256,'\n');
            break;
            } //end case 4

            case ('5'): {

            break;
            }

            default: {
            cout << "Invalid entry. Please choose from options 1 - 5\n" << endl;
            break;
            }
        } //end switch
        } while (userChoice != '5'); //end do-while

    cout << "program ending have a nice day!\n";

}

void greyScale(int windWidth, int windHeight, Expression * expr)
{
    GraphicsWindow win(windWidth, windHeight, "window");
    for(double y=1; y<win.GetHeight()-1;y++)
    {
        double ycalc = (y/win.GetHeight()*2-1);
        for(double x=1;x<win.GetWidth()-1;x++)
        {
            double xcalc= (x/win.GetWidth()*2-1);
            double val = expr->Evaluate (xcalc, ycalc);
            int Bright = (val + 1)/ 2 *255;
            Color grey(Bright,Bright,Bright);
            win.DrawRectangle(x, y, 1, 1, grey);
        }
    }
    win.Refresh();
}

void colorScale(int windWidth, int windHeight, Expression * expr1, Expression * expr2,Expression * expr3)
{
    GraphicsWindow win(windWidth, windHeight, "window");
    for(double y=1; y<win.GetHeight()-1;y++)
    {
        double ycalc = (y/win.GetHeight()*2-1);
        for(double x=1;x<win.GetWidth()-1;x++)
        {
            double xcalc= (x/win.GetWidth()*2-1);
            double val1 = expr1->Evaluate (xcalc, ycalc);
            double val2 = expr2->Evaluate (xcalc, ycalc);
            double val3 = expr3->Evaluate (xcalc, ycalc);
            int Bright1 = (val1 + 1)/ 2 *150;
            int Bright2 = (val2 + 1)/ 2 *200;
            int Bright3 = (val3 + 1)/ 2 *100;
            Color rainbow(Bright1,Bright2,Bright3);
            win.DrawRectangle(x, y, 1, 1, rainbow);
        }
    }
    win.Refresh();
}

string randomer(int depth)
{
    if(depth==0)
    {
        string vars[2]={"x","y"};
        return vars[rand()%2];
    }
    else
    {
        int r=rand()%4;
        switch(r)
        {
            case 0:
                return randomer(depth-1)+"*"+randomer(depth-1);
            case 1:
                return "avg("+randomer(depth-1)+","+randomer(depth-1)+")";
            case 2:
                return "sin(pi*"+randomer(depth-1)+")";
            case 3:
                return "cos(pi*"+randomer(depth-1)+")";
        }
    }
}

int RandomInt(int min, int max)
{
    return rand()%(max-min+1) + min;
}
