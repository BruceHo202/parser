#include<iostream>
#include<map>
using namespace std;

string lge[100];
int lge_cnt = 0;
char none_ch[100];
int n_cnt = 0;
char end_ch[100];
int e_cnt = 0;


map<char, string>_first;
map<char, string>_follow;

string table[100][100];
int top=0;
char stack[1000];



string first(char ch){
    string ans="";
    if(!(ch >= 'A' && ch <= 'Z')){
        ans.append(1, ch);
        return ans;
    }
    for(int i=0;i<lge_cnt;i++){
        if(lge[i][0] == ch && lge[i][3]>='A' && lge[i][3]<='Z'){
            if(lge[i][3] != ch)
               ans = ans + first(lge[i][3]);
        }
        else if(lge[i][0] == ch){
            int flag = 0;
            for(int j=0;j<ans.length();j++){
                if(ans[i] == lge[i][3]){
                    flag=1;
                    break;
                }
            }
            if(flag == 0){
                ans.append(1, lge[i][3]);
                
            }
        }
    }
    _first.insert(pair<char, string>(ch, ans));
    return ans;
}

string follow(char ch){
    string ans;
    if(ch == 'E'){
        ans="$";
    }
    for(int i=0;i<lge_cnt;i++){
        for(int j=3;j<lge[i].length();j++){
            if(lge[i][j] != ch)
                continue;
            string s;
            if(j != lge[i].length()-1){//不是最后
                
                s = first(lge[i][j+1]);
                for(int k=0;k<s.length();k++){
                    if(s[k]!='e'){//加入非e元素
                        int flag=0;
                        for(int t=0;t<ans.length();t++){
                            if(ans[t] == s[k])
                                flag=1;
                        }
                        if(flag == 0)
                            ans.append(1, s[k]);
                    }
                    else{//如果有e元素则把左边的follow加入
                        if(lge[i][0] != ch){
                            string s2="";
                            s2 = follow(lge[i][0]);
                            
                            for(int k=0;k<s2.length();k++){
                                int flag=0;
                                for(int t=0;t<ans.length();t++){
                                    if(ans[t] == s2[k])
                                        flag=1;
                                }
                                if(flag == 0)
                                    ans.append(1, s2[k]);
                            }
                        }
                    }
                }
                
            }
//            int flag=0;
            else{
                if(lge[i][0] != ch){
                    s="";
                    s = follow(lge[i][0]);
                    
                    for(int k=0;k<s.length();k++){
                        int flag=0;
                        for(int t=0;t<ans.length();t++){
                            if(ans[t] == s[k])
                                flag=1;
                        }
                        if(flag == 0)
                            ans.append(1, s[k]);
                    }
                }
            }
            
        }
    }
    _follow.insert(pair<char, string>(ch, ans));
    return ans;
}

int find_index(char ch){
    if(ch >= 'A' && ch <= 'Z'){
        for(int i=0;i<n_cnt;i++){
            if(none_ch[i] == ch)
                return i;
        }
    }
    for(int i=0;i<e_cnt;i++){
        if(end_ch[i] == ch)
            return i;
    }
    return -1;
}

void make_table(){
    for(int i=0;i<lge_cnt;i++){
        string s = first(lge[i][3]);
        int index0 = find_index(lge[i][0]);
        int e_flag = 0;
        for(int j=0;j<s.length();j++){
            if(s[j] == 'e')
                e_flag = 1;
            int index1 = find_index(s[j]);
            table[index0][index1] = lge[i];
        }
        if(e_flag == 1){
            string s1 = follow(lge[i][0]);
            for(int j=0;j<s1.length();j++){
                int index2 = find_index(s1[j]);
                table[index0][index2] = lge[i];
            }
        }
    }
}

void proc(string s){
    cout << "*******************"<<endl;
    cout << "分析过程"<<endl;
    
    stack[top++] = 'E';
    while(top != 1){
        if(!(stack[top-1] >= 'A' && stack[top-1] <= 'Z')){//栈顶是终结符
            if(stack[top-1] == s[0]){
                top--;
                string s2;
                for(int i=1;i<s.length();i++)
                    s2.append(1, s[i]);
                s=s2;
                cout<<"栈：";
                for(int i=0;i<top;i++){
                    cout<<stack[i]<<" ";
                }
                cout<<"输入"<<s;
                
                cout<<"输出"<<endl;
                continue;
            }
            else if(stack[top-1] == 'n' && s[0] >= '0' && s[0] <= '9'){
                top--;
                
                int k = 1;
                while(s[k] >= '0' && s[k] <= '9')
                    k++;
                string s2 = "";
                for(int i=k;i<s.length();i++){
                    s2.append(1, s[i]);
                }
                s = s2;
                cout<<"栈：";
                for(int i=0;i<top;i++){
                    cout<<stack[i]<<" ";
                }
                cout<<"输入"<<s;
                
                cout<<"输出"<<endl;
                continue;
            }
            else{
                
                cout<<"err"<<endl;
                return ;
            }
        }
        else if(s[0]>='0' && s[0] <= '9'){//栈顶是终结符 输入串首字符是数字 和下面一个分支的区别是这里找table[index][find_index('n')]
            int num = s[0] - '0';
            int k = 1;
            while(s[k] >='0' && s[k]<='9'){
                num = num * 10 + s[k++] - '0';
            }
            
            int index = find_index(stack[top-1]);
            cout<<"栈：";
            for(int i=0;i<top;i++){
                cout<<stack[i]<<" ";
            }
            cout<<"输入"<<s;
            
            cout<<"输出"<<table[index][find_index('n')]<<endl;
            string s1 = table[index][find_index('n')];
            
            if(s1.length()!=0){
                top--;
                int len = (int)s1.length();
                if(s1[len-1] == '\0')
                   len--;
                for(int t=len-1;t>=3;t--){
                    stack[top++] = s1[t];
                }
            }
            else{
                cout<<"error"<<endl;
                return ;
            }
        }
        else{
            
            int index = find_index(stack[top-1]);
            cout<<"栈：";
            for(int i=0;i<top;i++){
                cout<<stack[i]<<" ";
            }
            cout<<"输入"<<s;
            
            cout<<"输出"<<table[index][find_index(s[0])]<<endl;
            string s1 = table[index][find_index(s[0])];
            
            if(s1.length()!=0){
                top--;
                if(s1[3] != 'e'){
                    
                    for(int t=(int)s1.length()-1;t>=3;t--){
                        stack[top++] = s1[t];
                    }
                }
            }
            else{
                cout<<"error"<<endl;
                return ;
            }
        }
    }
    if(stack[top-1] == '$' && s[0] == '$' && s.length() == 1){
        cout<<"acc"<<endl;
    }
    else{
        cout<<"err"<<endl;
        return ;
    }
}

int main(){
    stack[top++] = '$';
    cout<<"输入文法数量和文法（需要以E为起始符，ε用e代替，大写字母为非终结符，需要消除左公因子和左递归）"<<endl;
    cin>>lge_cnt;
    for(int i=0;i<lge_cnt;i++){
        cin>>lge[i];
    }
    for(int i=0;i<lge_cnt;i++){//产生式中num改成n
        for(int j=0;j<lge[i].length();j++){
            if(lge[i][j]=='n'&&lge[i][j+1]=='u'&&lge[i][j+2]=='m'){
                string s1;
                for(int k=0;k<=lge[i].length();k++){
                    if(k!=j+1 && k!=j+2)
                        s1.append(1, lge[i][k]);
                }
                lge[i]="";
                lge[i] = s1;
            }
        }
    }
    for(int i=0;i<lge_cnt;i++){//找出非终结符和终结符
        for(int j=0;j<lge[i].length();j++){
            if(j == 1 || j == 2)
                continue;
            if(lge[i][j] >= 'A' && lge[i][j] <= 'Z'){
                int flag = 0;
                for(int k=0;k<n_cnt;k++){
                    if(none_ch[k] == lge[i][j])
                        flag = 1;
                }
                if(flag == 0)
                    none_ch[n_cnt++] = lge[i][j];
            }
            else{
                int flag = 0;
                for(int k=0;i<e_cnt;k++){
                    if(end_ch[k] == lge[i][j])
                        flag = 1;
                }
                if(flag == 0)
                    end_ch[e_cnt++] = lge[i][j];
            }
        }
    }
    
    end_ch[e_cnt++] = '$';
    make_table();
    cout<<"*******************"<<endl;
    cout<<"分析表："<<endl;
    for(int i=0;i<n_cnt;i++){
        for(int j=0;j<e_cnt;j++){
            if(table[i][j].length()==0)
                continue;
            if(end_ch[j] != 'n')
                cout<<none_ch[i]<<" "<<end_ch[j]<<" "<<table[i][j]<<endl;
            else
                cout<<none_ch[i]<<" "<<"num"<<" "<<table[i][j]<<endl;
        }
    }
    string s;
    cout << "输入待分析的符号串，如果要结束程序则输入$"<<endl;
    cin >> s;
    while(s!="$"){
        s.append(1, '$');
        proc(s);
        s="";
        top = 1;
        cout << "输入待分析的符号串，如果要结束程序则输入$"<<endl;
        cin >> s;
    }
}
/*
题目中的文法消除左递归后如下（第一行是文法数量）：
12
E->TA
A->PA
A->e
T->FB
B->QB
B->e
P->+T
P->-T
Q->*F
Q->/F
F->(E)
F->num
测试用例：
(21+1)*(2456432+13)/134542-16
1*(1+1
1+(
 */
