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

//�ʷ�������

int id=0;
int k=0;
int num=0;
//�ļ�ָ��
FILE *source;
FILE *target;
FILE *target2;
//�ؼ���
string arrlist[6]={"MAXVALUE","while","if","else","switch","case"};
//���ű�
string symbol[MAXVALUE]={""};
//������
string digite[MAXVALUE]={""};

	//�ַ�����
char  token[10]="";
//���ܺ�����ȥ���ո�
	char getbe(char s)
	{
		while(s==' ')
        s=fgetc(source);
		return s;
	}

//�ж�character���Ƿ�Ϊ��ĸ
	bool letter(char s)
	{
		//s����ĸ
		//if(s>'a'&& s<'z'|| s>'A'&&s<'Z')
		//Сд��ĸ
		if(s>='a'&& s<='z')
			return true;
		else
			return false;
	}
//�ж�characgter���Ƿ�������token
	bool digit(char s)
	{
		//s������
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

//ɨ��ָ�����һ���ַ���ͬʱ��character��Ϊ�հ�
	char retract(char character)
	{
		character='\0';
		return character;
	}

//��token�е��ַ������ǰ����,���ر����#define tfName "target.c"0
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
//������
    void error()
    {
        cout<<"����Ƿ��ַ�";
    }
//��¼�����ű���
void buildlist()
{
	//����ǰtoken�����д�����ַ����������������
	symbol[id]=token;
	id++;
}

//��¼����������
void buildlistnum()
{
	digite[num]=token;
	num++;
}

//���ַ���ͳ�����д���ļ���
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
//ɨ�躯��
void scanner()
{
    //�ַ�����������ַ���
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
			  //ɨ��ָ�����һ���ַ�
                fseek(source,-1,SEEK_CUR);

			c=reserve(token);

			if(c==0)
            {
                buildlist();
                cout<<symbol[id-1]<<"  "<<id-1<<endl;
            }
            else
            {
               cout<<"��������"<<",null";
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
            //ɨ��ָ�����һ���ַ�
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
                    character=retract(character);//��0
                    //ɨ��ָ�����һ���ַ�
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
                    character=retract(character);//��0
                    //ɨ��ָ�����һ���ַ�
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
    //�ж��ļ��Ƿ����
      if((source=fopen(sfName,"r"))==NULL)
    {
        printf("�ļ���ʧ�ܣ�\n");
        exit(0);
    }
    if((target=fopen(tfName,"w"))==NULL)
    {
        fprintf(stderr,"�ļ�д��ʧ�ܣ�\n");
        exit(0);
    }
    if((target2=fopen(tfName2,"w"))==NULL)
    {
        fprintf(stderr,"�ļ�д��ʧ�ܣ�\n");
        exit(0);
    }
    while(!feof(source))
    {
        scanner();
        memset(token, 0x00, sizeof (char) * 10);
        k=0;
    }
    //�����ű�ͳ�����д��target�ļ���
    outputfile();
    outputfile2();
    //�ر��ļ�
    fclose(source);
    fclose(target);
    fclose(target2);
    system("pause");
	return 0;
}
