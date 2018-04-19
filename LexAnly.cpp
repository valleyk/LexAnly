#include<iostream>
#include<stdio.h>
#include<string>
#include<string.h>
#include<stdlib.h>
#define sfName "source.c"
#define tfName "target.c"
#define tfName2 "target2.c"
#define MAXVALUE 50
using namespace std;

//词法分析器

int id=0;
int k=0;
int num=0;
//文件指针
FILE *source;
FILE *target;
FILE *target2;
//关键字
string arrlist[6]={"MAXVALUE","while","if","else","switch","case"};
//符号表
string symbol[MAXVALUE]={""};
//常数表
string digite[MAXVALUE]={""};

	//字符数组
char  token[10]="";
//功能函数：去除空格
	char getbe(char s)
	{
		while(s==' ')
        s=fgetc(source);
		return s;
	}

//判断character中是否为字母
	bool letter(char s)
	{
		//s是字母
		//if(s>'a'&& s<'z'|| s>'A'&&s<'Z')
		//小写字母
		if(s>='a'&& s<='z')
			return true;
		else
			return false;
	}
//判断characgter中是否是数字token
	bool digit(char s)
	{
		//s是数字
		if(s>='0'&& s<='9')
			return true;
		else
			return false;
	}
	void  concatenation(char s)
	{
            while(token[k]=='\0')
            {
                token[k]=s;
            }
            k++;
	}

//扫描指针回退一个字符，同时将character置为空白
	char retract(char character)
	{
		character='\0';
		return character;
	}

//将token中的字符串查表前五项,返回编码和#define tfName "target.c"0
	int reserve(char *token)
	{
	    string str=token;
	    for(int i=0;i<6;i++)
	    {
	        if(str==arrlist[i])
                return i;
	    }
		return 0;
	}
//错误函数
    void error()
    {
        cout<<"输入非法字符";
    }
//记录到符号表中
void buildlist()
{
	//将当前token数组中储存的字符串放入符号数组中
	symbol[id]=token;
	id++;
}

//记录到常数表中
void buildlistnum()
{
	digite[num]=token;
	num++;
}

//将字符表和常数表写入文件中
void outputfile()
{
        for(int i=0;i<MAXVALUE;i++)
    {
       fprintf(target,"%s\n",symbol[i].c_str());
    }
}

void outputfile2()
{
        for(int j=0;j<MAXVALUE;j++)
    {
       fprintf(target2,"%s\n",digite[j].c_str());
    }
}
//扫描函数
void scanner()
{
    //字符变量，存放字符串
	char  character=fgetc(source);

	character=getbe(character);
	int c;

	switch(character)
	{
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':
			while(letter(character)||digit(character))
			{
				concatenation(character);
				character=fgetc(source);
			}
			character=retract(character);
			  //扫描指针回退一个字符
                fseek(source,-1,SEEK_CUR);

			c=reserve(token);

			if(c==0)
            {
                buildlist();
                cout<<symbol[id-1]<<"  "<<id-1<<endl;
            }
            else
            {
               cout<<"保留字码"<<",null";
            }
            break;

        case'0':
        case'1':
        case'2':
        case'3':
        case'4':
        case'5':
        case'6':
        case'7':
        case'8':
        case'9':
            while(digit(character))
            {
                concatenation(character);
                character=fgetc(source);
            }
            reserve(token);
            buildlistnum();
            cout<<digite[num-1]<<"  "<<num-1<<endl;
            //扫描指针回退一个字符
                fseek(source,-1,SEEK_CUR);
            break;
        case'+':
            cout<<"+"<<",null";
            break;
        case'-':
            cout<<"-"<<",null";
        case'*':
            cout<<"*"<<",null";
        case'<':
            character=getchar();
            if(character=='=')
                cout<<"relop"<<",LE";
            else
                {
                    character=retract(character);//置0
                    //扫描指针回退一个字符
                    fseek(source,-1,SEEK_CUR);

                    cout<<"relop"<<",LT";
                }
                break;
        case'=':
            character=fgetc(source);
            if(character=='=')
                cout<<"relop"<<",EQ"<<endl;
            else
                {
                    character=retract(character);//置0
                    //扫描指针回退一个字符
                    fseek(source,-1,SEEK_CUR);
                    cout<<"="<<",null"<<endl;
                }
            break;
        case';':
            cout<<";"<<",null"<<endl;
            break;
        case '\377':
            break;
        default:
            error();
	}
}
int main()
{
	int n=0;
	int rec=0;
    //判断文件是否存在
      if((source=fopen(sfName,"r"))==NULL)
    {
        printf("文件打开失败！\n");
        exit(0);
    }
    if((target=fopen(tfName,"w"))==NULL)
    {
        fprintf(stderr,"文件写入失败！\n");
        exit(0);
    }
    if((target2=fopen(tfName2,"w"))==NULL)
    {
        fprintf(stderr,"文件写入失败！\n");
        exit(0);
    }
    while(!feof(source))
    {
        scanner();
        memset(token, 0x00, sizeof (char) * 10);
        k=0;
    }
    //将符号表和常数表写入target文件中
    outputfile();
    outputfile2();
    //关闭文件
    fclose(source);
    fclose(target);
    fclose(target2);
    system("pause");
	return 0;
}
