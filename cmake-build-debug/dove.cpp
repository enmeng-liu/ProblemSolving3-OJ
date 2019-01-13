// find_replace_str.cpp : 定义控制台应用程序的入口点。
//

//#include <cstdafx>
#include <iostream>
#include <cstring>
using namespace std;
void fandr ( char *str , char *fin , char *rep);
int main ()
{
    char a[] = { "Your life only lasts for a few decades,so be sure that you don't leave any regrets. Laugh or cry as you like,and it's meaningless to oppress yourself." };
    char *p = new char [strlen ( a ) + 1 ] ;
    strcpy ( p , a );
    cout << p << endl;
    fandr ( p , "you" , "I");
    fandr ( p , "your" , "my");
//    fandr ( p , "yours" , "mine" );
    cout << p << endl;
    fandr ( p , "yourself" , "myself" );
    cout << p << endl;
    //fandr ( p , "You" , "I");
    //fandr ( p , "Your" , "My");
    // fandr ( p , "Yours" , "Mine" );
    //  fandr ( p , "Yourself" , "Myself" );
    //  cout << p << endl;
    //system ( "pause" );
}
void fandr ( char *str , char *fin , char *rep){
    int s = strlen (str);
    int f = strlen (fin);
    int r = strlen (rep);
    int deta = r - f;
    for (int i = 0 ; i < s ; i ++){
        int j = 0, k = 0;
        //for ( int k = 0 ; k < f ; k ++ )
            //if ( str [i + k] == fin [k] ) j ++;
        while(str[i + k] == fin[k]) j ++, k++;
        if (j == f){
            bool first = !(isalpha(str[i - 1]));
            bool last = !(isalpha(str[i + f]));
            if ( ( i == 1 && last ) || ( i + f + 1 == s && last) || ( first && last ) ){
                s += deta;
                char *p = new char [s];
                for (int k = 0; k < i;k ++)
                    p [ k ] = str [ k ] ;
                for (int k = 0; k < r; k ++ )
                    p [i + k  = rep [k];
                for ( int k = 0 ; k + i + r < s; k ++)
                    p [ i + r + k ] = str [ i + f + k ];

                delete []str;
                str = p;

            }

        }
    }
    cout << str << endl;
    return ;
}
