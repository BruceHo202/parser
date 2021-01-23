#include<iostream>
using namespace std;
#define MAX 100

string table[MAX][MAX];
char func[20] = {'(', ')', '+', '-', '*', '/', 'n' ,'$', 'E', 'T', 'F'};

int find_index(char ch){
    for(int i=0;i<11;i++){
        if(func[i] == ch)
            return i;
    }
    return -1;
}

string lge[100];
void init_lge(){
    cout<<"输入文法数量："<<endl;
    int lge_num;
    cin>>lge_num;
    cout<<"输入文法："<<endl;
    for(int i=1;i<=lge_num;i++){
        cin>>lge[i];
    }
}

void init_table(){
    table[0][0] = "S4";
    table[0][6] = "S5";
    table[0][8] = "1";
    table[0][9] = "2";
    table[0][10] = "3";
    table[1][2] = "S6";
    table[1][3] = "S7";
    table[1][7] = "acc";
    table[2][2] = "R3";
    table[2][3] = "R3";
    table[2][4] = "S8";
    table[2][5] = "S9";
    table[2][7] = "R3";
    // $+-*/
    for(int i=2;i<=5;i++){
        table[3][i] = "R6";
        table[5][i] = "R8";
        table[17][i] = "R4";
        table[18][i] = "R5";
        table[19][i] = "R7";
    }
    for(int i=7;i<=7;i++){
        table[3][i] = "R6";
        table[5][i] = "R8";
        table[17][i] = "R4";
        table[18][i] = "R5";
        table[19][i] = "R7";
    }
    
    table[4][0] = "S13";
    table[4][6] = "S14";
    table[4][8] = "10";
    table[4][9] = "11";
    table[4][10] = "12";
    table[6][0] = "S4";
    table[6][2] = "R1";
    table[6][3] = "R1";
    table[6][6] = "S5";
    table[6][7] = "R1";
    table[6][9] = "15";
    table[6][10] = "3";
    table[7][0] = "S4";
    table[7][2] = "R2";
    table[7][3] = "R2";
    table[7][6] = "S5";
    table[7][7] = "R2";
    table[7][9] = "16";
    table[7][10] = "3";
    table[8][0] = "S4";
    table[8][6] = "S5";
    table[8][10] = "17";
    table[9][0] = "S4";
    table[9][6] = "S5";
    table[9][10] = "18";
    table[10][1] = "S19";
    table[10][2] = "S20";
    table[10][3] = "S21";
    table[11][1] = "R3";
    table[11][2] = "R3";
    table[11][3] = "R3";
    table[11][4] = "S22";
    table[11][5] = "S23";
    for(int i=1;i<=5;i++){
        table[12][i] = "R6";
        table[14][i] = "R8";
        table[27][i] = "R4";
        table[28][i] = "R5";
        table[29][i] = "R7";
    }
    table[13][0] = "S13";
    table[13][6] = "S14";
    table[13][8] = "24";
    table[13][9] = "11";
    table[13][10] = "12";
    table[15][2] = "R1";
    table[15][3] = "R1";
    table[15][4] = "S8";
    table[15][5] = "S9";
    table[15][7] = "R1";
    table[16][2] = "R2";
    table[16][3] = "R2";
    table[16][4] = "S8";
    table[16][5] = "S9";
    table[16][7] = "R2";
    for(int i=2;i<=5;i++){
        table[17][i] = "R4";
        table[18][i] = "R5";
        table[19][i] = "R7";
    }
    for(int i=7;i<=7;i++){
        table[17][i] = "R4";
        table[18][i] = "R5";
        table[19][i] = "R7";
    }
    for(int i=20;i<=23;i++){
        table[i][0] = "S13";
        table[i][6] = "S14";
    }
    table[20][9] = "25";
    table[20][10] = "12";
    table[21][9] = "26";
    table[21][10] = "12";
    table[22][10] = "27";
    table[23][10] = "28";
    table[24][1] = "S29";
    table[24][2] = "S20";
    table[24][3] = "S21";
    for(int i=1;i<=3;i++){
        table[25][i] = "R1";
        table[26][i] = "R2";
    }
    table[25][4] = "S22";
    table[25][5] = "S23";
    table[26][4] = "S22";
    table[25][5] = "S23";
}
int stack1[100];
int top1 = 0;
char stack2[100];
int top2 = 0;
void proc(string s){
    while(1){
        cout<<"***********"<<endl;
        cout<<"状态栈：";
        for(int i=0;i<top1;i++){
            cout<<stack1[i]<<" ";
        }
        cout<<"\t输入："<<s;
        cout<<endl<<"符号栈：";
        for(int i=0;i<top2;i++){
            cout<<stack2[i]<<" ";
        }
        cout<<endl;
        
        int S = stack1[top1-1];
        if(s[0] >= '0' && s[0] <= '9'){
            int j = 1;
            while(s[j] >= '0' && s[j] <= '9')
                j++;
            string t = "n";
            for(int i=j;i<s.length();i++){
                t.append(1, s[i]);
            }
            s = "";
            s = t;
        }
        int a = find_index(s[0]);
        if(table[S][a][0] == 'S'){//移进操作
            int s1;
            if(table[S][a][2] == '\0')
                s1 = table[S][a][1] - '0';
            else{
                s1 = 10 * (table[S][a][1] - '0') + table[S][a][2] - '0';
            }
            stack1[top1++] = s1;
            stack2[top2++] = s[0];
            cout<<"shift "<<s1<<endl;
            string t = "";
            for(int i=1;i<s.length();i++){
                t.append(1, s[i]);
            }
            s = t;
        }
        else if(table[S][a][0] == 'R'){//归约操作
            int lge_num;
            if(table[S][a][2] == '\0')
                lge_num = table[S][a][1] - '0';
            else
                lge_num = 10 * (table[S][a][1] - '0') + table[S][a][2] - '0';
            int cnt = (int)lge[lge_num].length() - 3;
            top1 -= cnt;
            top2 -= cnt;
            int s1 = stack1[top1-1];
            int A = find_index(lge[lge_num][0]);
            int _goto;
            if(table[s1][A][1] == '\0')
                _goto = table[s1][A][0] - '0';
            else
                _goto = 10 * (table[s1][A][0] - '0') + table[s1][A][1] - '0';
            stack1[top1++] = _goto;
            stack2[top2++] = lge[lge_num][0];
            cout<<"reduce by "<<lge[lge_num]<<endl;
        }
        else if(table[S][a][0] == 'a'){//接受
            cout<<"acc"<<endl;
            return ;
        }
        else{
            cout<<"error"<<endl;
            return ;
        }
    }
}
int main(){
    init_lge();
    init_table();
    stack1[top1++] = 0;
    stack2[top2++] = '-';
    string s;
    cout<<"输入待分析的字符串，输$结束程序"<<endl;
    cin>>s;
    while(s!="$"){
        s.append(1, '$');
        proc(s);
        s="";
        top1 = 0;
        top2 = 0;
        stack1[top1++] = 0;
        stack2[top2++] = '-';
        cout<<"输入待分析的字符串，输$结束程序"<<endl;
        cin>>s;
    }
}
/*
文法：
8
E->E+T
E->E-T
E->T
T->T*F
T->T/F
T->F
F->(E)
F->n
如果需要其他文法，需要在程序中改变符号表（init_table函数）
测试用例：
(134+15)*(84/12)
(2+3*5
 */

