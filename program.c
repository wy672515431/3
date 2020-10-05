#include<stdio.h>
#include<ctype.h>
#include<math.h>
#include<string.h>
#define maxn 10000
//当前读入的字符
char ch;
//存放单词的字符串
char token[maxn];
//存放保留字的字符串数组
char* Reserve[maxn];
//存放要输出的保留字
char* out_Reserve[maxn];
//存放读入文件的字符串
char str[];
//存放读入到文件的位置
int index=0;
// 表示文件出错
int err_num = 0;
//初始化保留字数组
void init_reserve(){
    Reserve[0]="BEGIN";
    out_Reserve[0]="Begin";
    Reserve[1]="END";
    out_Reserve[1]="End";
    Reserve[2]="FOR";
    out_Reserve[2]="For";
    Reserve[3]="IF";
    out_Reserve[3]="If";
    Reserve[4]="THEN";
    out_Reserve[4]="Then";
    Reserve[5]="ELSE";
    out_Reserve[5]="Else";
}
void getChar(){
    ch = str[index++];
}
void filter_blank_ch(){
    while(ch == ' '|| ch == '\n' || ch =='\t'){
        getChar();
    }
}
void catToken(){
    int len = strlen(token);
    token[len]=ch;
    token[len+1]='\0';
}
int reserver(){
    for(int i=0;i<=5;i++){
        if(strcmp(token,Reserve[i])==0)
            return i;
    }
    return -1;
}
void retract(){
    ch=' ';
    index--;
}
int transNum(){
    return atoi(token);
}
//清空token数组
void clearToken(){
    token[0]='\0';
}
//出错
void error(){
    err_num=1;
    printf("Unknown\n");
}
//进行词法分析
void lexical_analysis(){
    clearToken();
    getChar();
    filter_blank_ch();
    //保留字和标识符
    if(isalpha(ch)){
        while(isalnum(ch)){
            catToken();
            getChar();
        }
        retract();
        //是保留字
        if(reserver()!=-1){
            printf("%s\n",out_Reserve[reserver()]);
        }
        else 
            printf("Ident(%s)\n",token);
    }
    else if(isdigit(ch)){
        int flag=0;
        while(isdigit(ch)){
            if(ch != '0'){
                flag=1;
                catToken();
                getChar();
            }
            else if(ch =='0'&&flag==1){
                catToken();
                getChar();
            }
            else{
                getChar();
            }
        }
        retract();
        printf("Int(%d)\n",transNum());
    }
    else if(ch == ':'){
        getChar();
        if(ch == '='){
            printf("Assign\n");
        }
        else{
            retract();
            printf("Colon\n");
        }
    }
    else if(ch == '+') printf("Plus\n");
    else if(ch == '*') printf("Star\n");
    else if(ch == ',') printf("Comma\n");
    else if(ch == '(') printf("LParenthesis\n");
    else if(ch == ')') printf("RParenthesis\n");
    else error();
}
int main(int argc,char * argv[]){
    FILE *fp;
    fp=fopen(argv[1],"r");
    char tem[maxn];
    while(fgets(tem,maxn,fp)!=NULL){
        strcat(str,tem);
    }
    init_reserve();
    while(index<strlen(str)&&err_num==0){
        lexical_analysis();
    }
    return 0;
}