/***************************************************************************
�ļ�����������۴���ҵ-���淭ת.cpp
���ߣ�������ѧ��Ϣ��ѧ����ѧԺ2011��3�� ���Ӻ�
���ڣ�2011��12��4��
���뻷����Microsoft Visual C++ 6.0 (��dev-cpp��Ҳ�ܱ���ͨ��)
�汾��2.4.0

�������ܣ�
1.�������к졢��������ɫ������Ϸ��ʼʱ��ĳЩ����Ϊ��ɫ��ĳЩ����Ϊ��ɫ
2.�û�ͨ����������鼴�ɷ�ת���飬����Ҫʹ�ü���
3.���û�ͨ�����Ϸ�ת���ѷ�����ķ��鶼�����ɫʱ����Ϸ����ʾ�û�ʤ��
4.���û�Ҫ��ϵͳ������ʾʱ����Ϸ�����ṩ���û�һ����ȷ�ķ�ת��ʽ
���书�ܣ�
1.�������������������Χ����2��20��������ȣ�Ҳ���Բ����
2.��Ϸ�ṩ��������Ϸ�Ѷȹ��û�ѡ���û����Ը�����Ҫѡ��ͬ���Ѷȣ�Ҳ��ѡ������Ѷ�
3.��Ϸ�ṩ��������ʾ��ʽ�������ṩ��ת��ʽ���⣬��������ʾ�û����ٻ��跭ת���ٴη���
4.����Ϸ�����п���ʱ���¿��ֻ��˳���Ϸ
5.ʵʱ��ʾ��Ϸʱ��
6.���Զ���ʾģʽ���Զ���תģʽ������������Ϸ�������������ĳЩ�ض�λ�ò�������
7.��ÿ��������Ϸʱ�����Զ���󻯴��ڣ�����ȫ����
8.��ÿ�η�תʱ�м���ʱ���ͣ�Ͷ���ʾ����ת��Ч��

��ʷ�汾���޸Ĺ��ܼ�����
1.0 �ü��̶������ꣻ��������ʾ��ʽ��������Ϸ�����������Ϸʱ�䣻��������������Ϊ18
1.1 ��ÿ�η�תʱ���м���ʱ���ͣ�Ͷ���ʾ����ת��Ч����ÿ��������Ϸʱ���Զ���󻯴���
1.2 �ṩ�����Ѷȼ�����Ѷ�
1.3 �Ѵ�ǰ�汾��������ָ����������������
2.0 �����������
2.1 �Ż���ʼ��������㷨�����������������޸�Ϊ20���ṩ�����Ѷȼ�����Ѷȣ�ʵʱ��ʾ��Ϸʱ�䣻�ڷ�תʱ������
2.2 �����Զ���ʾģʽ���Ż���ͬ�Ѷ��³�ʼ��������㷨
2.3 �Ż���ת����ʱ���㷨�������Զ���תģʽ���޸�2.1��2.2����ʾ��������ʱ����ʧ��bug���޸��������δ��ʼ����bug
2.4 �����Ż���ͬ�Ѷ��³�ʼ��������㷨

����������Ϸ����������Դ�������κδ�©�򲻵�֮������ӭָ��
***************************************************************************/

#include<windows.h>
#include<iostream>
#include<ctime>
#include<string>
#include<iomanip>
using namespace std;
HANDLE hIn,hOut;//���ڻ�ȡ���������롢������ľ��
INPUT_RECORD mouseRec;//���ڴ�������λ�á��Ƿ�������Ϣ
DWORD res;//���ڴ������괦������Ϣ�ĸ���
COORD pos={0,0};//���ڼ�¼���ָ���λ��

/*����ȫ�ֱ������壺
n��width�ֱ��ʾ�����������������
���Ѻ�ɫ�ķ�����1����ɫ�ķ�����0����ʾ����ÿ�еķ����״̬�������������������һ������������
line1[25]���ڼ�¼ÿһ�е��������������ʮ���Ʊ�ʾ��ʽ��ȡֵΪ0��2^width-1����֮Ϊ����״̬
block[25][25]���ڼ�¼ÿ�������״̬��ȡֵΪ0��1
ver[626]����ÿ�γ�ʼ��ʱ��¼Ҫ��ת��Щ���飬ȡֵΪ0��1
steptotal,hint1total,hint2total,timetotal�ֱ��¼�Ѿ���ת�˶��ٴΡ����˶��ٴ���ʾһ�����˶��ٴ���ʾ������Ϸʱ��
leaststep��ʾ���ٻ��跭ת���ٴ��ܰ�ȫ����������ɫ
step[25][25]���ڼ�¼��Ҫ��ת��Щ���飬ȡֵΪ0��1
laststepx��laststepy�ֱ��ʾ��һ�η�ת�ķ������ڵ��к���
hintx��hinty�ֱ��ʾ��ʾ�ķ������ڵ��к���
cheat1��cheat2�ֱ��ʾ�Ƿ������Զ���ʾģʽ���Զ���תģʽ
difficulty��¼�û�ѡ����Ѷ�
coediffmem[25][25]���ڴ��治ͬ�����������ķ������Ӧ�ġ��Ѷ�ϵ����   */
int line1[25]={0},block[25][25]={0},step[25][25]={0},ver[626]={0};
int steptotal=0,hint1total=0,hint2total=0,laststepx=0,laststepy=0,n=0,width=0,leaststep=0,cheat1=0,cheat2=0,hintx=0,hinty=0;
int difficulty=0,coediffmem[25][25]={0};
time_t timetotal;

/*�������ܣ������������ڽ�������Ļ�ı�����ɫ��ɰ�ɫ���������ַ�������������������ڻ��������Ϸ�
��welcome,gamestart,win,gameend,main�����б�����*/
void clearscreen();

/*�������ܣ�������ɫ���������趨ÿ�����ʱ�ı�����ɫ��������ɫ
i����һ�ֱ�����ɫ��������ɫ�ķ���
��clearscreen,welcome,gamestart,output,outputword,press,hint,win�����б�����*/
void setcolor(int i);

/*�������ܣ���Ϸ�Ļ�ӭ����
��main�����б�����*/
void welcome();

/*�������ܣ���ʼ��Ϸ����ѡ�񷽿����������������ѡ����Ϸ�Ѷȣ�����ʼ������
����ֵ�̶�Ϊ1
��main�����б�����*/
bool gamestart();

/*�������ܣ���������a,b�����ֵ
��calcdifficultyinf,calcdifficultysup,output�����б�����*/
inline int maxnum(int a,int b);

/*�������ܣ�������ĳ���ѶȺ��Ѷ�ϵ���³�ʼ״̬��leaststepֵ������
coediff�����Ѷ�ϵ��
��main�����б�����*/
inline int calcdifficultyinf(int coediff);

/*�������ܣ�������ĳ���ѶȺ��Ѷ�ϵ���³�ʼ״̬��leaststepֵ������
coediff�����Ѷ�ϵ��
��main�����б�����*/
inline int calcdifficultysup(int coediff);

/*�������ܣ������ʼ���������ɫ���ɷ��������ɫ״̬�õ�ÿ�з���״̬��ֵ
����ֵ�����ʼ�������з�ת�ķ�������
inf,sup�ֱ����leaststepֵ�����޺�����
w=2^width������line1[ ]����ÿ��Ԫ�ص�����ֵ��һ
��main�����б�����*/
int randomblock(int inf,int sup,int w);

/*�������ܣ����㽫ĳ��״̬�µķ�����ȫ�������ɫ����Ҫ��ת�����ٴ�����������һ�ַ�ת����������step[ ][ ]������
k=2^width������line1[ ]����ÿ��Ԫ�ص�����ֵ��һ
��main�����б�����*/
void calculate(int k);

/*�������ܣ��ڵ���randomblock������leaststep�����Ѷ�Ҫ��󣬽�ÿ�еķ���״̬ת����block[ ][ ]��ֵ
��main�����б�����*/
void turn();

/*�������ܣ������������������ͬ��ָ��(��t��ֵȷ��)��������󣬲�������Ҫ����outputword��press����
w=2^width������line1[ ]����ÿ��Ԫ�ص�����ֵ��һ
����ֵ�����Ǽ�����Ϸ�����¿��֣������˳���Ϸ
��invert,win,main�����б�����*/
int output(int t,int w);

/*�������ܣ�����Ϸ����������������Ϸ�������
��output�����б�����*/
void outputword();

/*�������ܣ����������������Ϸ�����������λ�ò�������Ӧ����
��output�����б����ã�����ֵ����Ϊoutput�����ķ���ֵ*/
int press(int w);

/*�������ܣ���ʾһ��������step[ ][ ]��leaststep�����ṩһ�ַ�ת��ʽ��������output�����ڷ������н��÷����ʾ����
k��������ɵ���ֵ���������ѡ��һ����Ҫ��ת�ķ���
��press�����б�����*/
void hint(int k);

/*�������ܣ���ת���顪������i�е�j���Լ����������ҵ����ڷ������ɫ�ı�
w=2^width������line1[ ]����ÿ��Ԫ�ص�����ֵ��һ
��press�����б�����*/
void invert(int i,int j,int w);

/*�������ܣ��ж��Ƿ�ʤ�������ʤ���������ʾ����
����ֵ������δʤ����ʤ��������һ�̣�����ʤ�����˳���Ϸ
��main�����б�����*/
int win();

/*�������ܣ���Ϸ�Ľ�������
��main�����б�����*/
void gameend();

//------------------------------------------------------------------------------------------------------------

void clearscreen()
{
    setcolor(2);//����ı�����ɫ�趨Ϊ��ɫ��������ɫ�趨Ϊ��ɫ
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
    GetConsoleScreenBufferInfo(hOut,&bInfo);
	COORD home={0,0};
	WORD att=bInfo.wAttributes;
	unsigned long size = bInfo.dwSize.X * bInfo.dwSize.Y;
	FillConsoleOutputAttribute(hOut, att, size, home, NULL);
	FillConsoleOutputCharacter(hOut, ' ', size, home, NULL);//��������Ļ���' '�ַ�
	SetConsoleCursorPosition(hOut,home);//������ƶ������Ͻ�
}//����clearscreen����

//------------------------------------------------------------------------------------------------------------

void setcolor(int i)
{
	if(i==0) 
	{
		//����״̬����ɫ���������趨��������ɫΪ��ɫ��������ɫΪ��ɫ
		SetConsoleTextAttribute(hOut,BACKGROUND_INTENSITY|BACKGROUND_BLUE|FOREGROUND_INTENSITY);
	}
	else if(i==1) 
	{
		//����״̬����ɫ���������趨��������ɫΪ��ɫ��������ɫΪ��ɫ
		SetConsoleTextAttribute(hOut,BACKGROUND_INTENSITY|BACKGROUND_RED|FOREGROUND_INTENSITY);
	}
	else if(i==2) 
	{
		//�������������ʱ������趨��������ɫΪ��ɫ��������ɫΪ��ɫ
		SetConsoleTextAttribute(hOut,BACKGROUND_INTENSITY|BACKGROUND_GREEN|BACKGROUND_RED|BACKGROUND_BLUE);
	}
	else if(i==3) 
	{
		//�������·����ҷ���ɺ�ɫ����ʱ������趨��������ɫΪ��ɫ��������ɫΪ��ɫ
		SetConsoleTextAttribute(hOut,FOREGROUND_INTENSITY|FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
	}
	else if(i==4) 
	{
		//��ʾ��ת��ɫ����ʱ����ɫ���������趨��������ɫΪ��ɫ��������ɫΪ��ɫ
		SetConsoleTextAttribute(hOut,BACKGROUND_INTENSITY|BACKGROUND_BLUE|FOREGROUND_INTENSITY|FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
	}
	else if(i==5) 
	{
		//��ʾ��ת��ɫ����ʱ����ɫ���������趨��������ɫΪ��ɫ��������ɫΪ��ɫ
		SetConsoleTextAttribute(hOut,BACKGROUND_INTENSITY|BACKGROUND_RED|FOREGROUND_INTENSITY|FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
	}
	else if(i==6) 
	{
		//�ڷ�ת��ɫ����ʱ������趨����״̬ÿ��ֻ����ּ���ʱ�䣬������ɫΪ��죬������ɫΪ��ɫ
		SetConsoleTextAttribute(hOut,BACKGROUND_RED|FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);//��ת״̬��ɫ
	}
	else if(i==7) 
	{
		//�ڷ�ת��ɫ����ʱ������趨����״̬ÿ��ֻ����ּ���ʱ�䣬������ɫΪ������������ɫΪ��ɫ
		SetConsoleTextAttribute(hOut,BACKGROUND_BLUE|FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);//��ת״̬��ɫ
	}
	else if(i==8) 
	{
		//��ɫ���������趨��������ɫΪ��ɫ��������ɫΪ��ɫ
		SetConsoleTextAttribute(hOut,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_BLUE|FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
	}
}//����setcolor����

//------------------------------------------------------------------------------------------------------------

void welcome()
{
	//��ȡ���롢��������
	hIn=GetStdHandle(STD_INPUT_HANDLE);
	hOut=GetStdHandle(STD_OUTPUT_HANDLE);
	
	//�ı䴰�ڱ���
	SetConsoleTitle("���淭ת");
	
	//���ô��ڳߴ�
	COORD size={123,43};
	SetConsoleScreenBufferSize(hOut,size);
	SMALL_RECT rc={0,0,122,42};
    SetConsoleWindowInfo(hOut,true,&rc);
	
	//���ò���ʾ��˸���
	CONSOLE_CURSOR_INFO ConsoleCursorInfo;
    GetConsoleCursorInfo(hOut,&ConsoleCursorInfo);
    ConsoleCursorInfo.bVisible=false;
    SetConsoleCursorInfo(hOut,&ConsoleCursorInfo);
	
	//������Ϸʱ�Զ����������
	HWND hwnd=GetForegroundWindow();
	ShowWindow(hwnd,SW_MAXIMIZE);
	clearscreen();
	cout<<"                                              ��ӭ�������淭ת��Ϸ\n";
	cout<<"                                                                            �����ߣ������ſ�2011�� ���Ӻ�\n";
	cout<<"\n\n\n";
	cout<<"��Ϸ����\n\n";
	cout<<"1.����ѡ�񷽿��������������\n\n";
	cout<<"2.�������У�ÿ�鷽�����ɫΪ��ɫ����ɫ��ÿ��תһ�鷽�飬���ı���鷽���Լ����ϡ��¡����Ҳ����ڷ��鹲��鷽�����ɫ\n\n";
	cout<<"3.������ȫ���������ɫ�����ɫʱ����Ϸ�����������ʤ��\n\n";
	cout<<"4.��Ϸ����������ʾ��ʽ����ʾһ�����ṩһ����ȷ�ķ�ת��ʽ����ʾ�����������ٻ��跭ת���ٷ��飬��ÿ����Ϸ��ÿ�η�ת������ʹ����ʾ������ÿ�η�ת��ֻ��ʹ��һ��\n\n";
	cout<<"5.��Ϸʹ�������в�������ʹ��������������ɫ�ķ���\n\n";
	cout<<"6.Ϊȷ����Ϸ˳�����У�������Ϸ������һֱʹ������󻯣�����Ҫȫ������ѡ��8��16�������С��������򿪿��ٱ༭ģʽ\n\n";
	cout<<"\n\n\n\n";
	
	//���·��в��������ʼ��Ϸ���Ĺ����������ɫ����
	COORD po={50,26};
	setcolor(8);
	SetConsoleCursorPosition(hOut,po);
	cout<<"            ";
	po.Y++;
	SetConsoleCursorPosition(hOut,po);
	cout<<"  ��ʼ��Ϸ  ";
	po.Y++;
	SetConsoleCursorPosition(hOut,po);
	cout<<"            ";
	setcolor(2);
	cout<<"\n\n";
	
	//�ȴ����������ʼ��Ϸ��
    while(1)
	{
		ReadConsoleInput(hIn,&mouseRec,1,&res);
		if(mouseRec.EventType==MOUSE_EVENT)
		{
			pos=mouseRec.Event.MouseEvent.dwMousePosition;
			if(mouseRec.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED)
				if(pos.Y<=28&&pos.Y>=26&&pos.X>=50&&pos.X<=61)break;//�������÷���ʱ�����ȴ���ѭ��
		}
	} 
}//����welcome����

//------------------------------------------------------------------------------------------------------------

bool gamestart()
{
	clearscreen();
	cout<<"��ѡ��������\n\n";
	int i,j;

	//�������2,3,4,...,20����ɫ����
	for(i=1;i<=3;i++)
	{
		for(j=2;j<=20;j++)
		{
			setcolor(2);
			cout<<' ';
			setcolor(8);
			if(i%2==1&&j<10)cout<<"   ";
			else if(i%2==1)cout<<"    ";
			else cout<<' '<<j<<' ';
		}
		setcolor(2);
		cout<<endl;
	}

	//�ȴ�ѡ������
	while(1)
	{
		ReadConsoleInput(hIn,&mouseRec,1,&res);
		if(mouseRec.EventType==MOUSE_EVENT)
		{
			pos=mouseRec.Event.MouseEvent.dwMousePosition;
			if(mouseRec.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED&&pos.Y>=2&&pos.Y<=4)
			{
				if(pos.X<32&&pos.X%4!=0)
				{
					n=pos.X/4+2;
					break;
				}
				if(pos.X>32&&pos.X<87&&pos.X%5!=2)
				{
					n=(pos.X+2)/5+3;
					break;
				}
			}
		}
	}

	//�������2,3,4,...,20����ɫ����
	cout<<"\n��ѡ������\n\n";
	for(i=1;i<=3;i++)
	{
		for(j=2;j<=20;j++)
		{
			setcolor(2);
			cout<<' ';
			setcolor(8);
			if(i%2==1&&j<10)cout<<"   ";
			else if(i%2==1)cout<<"    ";
			else cout<<' '<<j<<' ';
		}
		setcolor(2);
		cout<<endl;
	}

	//�ȴ�ѡ������
	while(1)
	{
		ReadConsoleInput(hIn,&mouseRec,1,&res);
		if(mouseRec.EventType==MOUSE_EVENT)
		{
			pos=mouseRec.Event.MouseEvent.dwMousePosition;
			if(mouseRec.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED&&pos.Y>=8&&pos.Y<=10)
			{
				if(pos.X<32&&pos.X%4!=0)
				{
					width=pos.X/4+2;
					break;
				}
				if(pos.X>32&&pos.X<87&&pos.X%5!=2)
				{
					width=(pos.X+2)/5+3;
					break;
				}
			}
		}
	}
	cout<<"\n��ѡ����"<<n<<"��"<<width<<"�еķ�����\n";
	cout<<"\n��ѡ����Ϸ�Ѷȣ�\n\n";
	string diff[5]={"����","ҵ��","ר��","��ʦ","���"};

	//������������֡�����ҵ�ࡱ����ר�ҡ�������ʦ���������������ɫ����
	for(i=1;i<=3;i++)
	{
		for(j=0;j<=4;j++)
		{
			setcolor(2);
			cout<<"  ";
			setcolor(8);
			i%2==0?cout<<"  "<<diff[j]<<"  ":cout<<"        ";
		}
		cout<<endl;
	}

	//�ȴ�ѡ���Ѷ�
	while(1)
	{
		ReadConsoleInput(hIn,&mouseRec,1,&res);
		if(mouseRec.EventType==MOUSE_EVENT)
		{
			pos=mouseRec.Event.MouseEvent.dwMousePosition;
			if(mouseRec.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED&&pos.Y>=16&&pos.Y<=18)
			{
				if(pos.X<50&&pos.X/2%5!=0)
				{
					//��������֡�����ҵ�ࡱ����ר�ҡ�������ʦ������������Ľ�����ֱ��Ӧdifficultyȡֵ0,1,2,3,4
					difficulty=pos.X/10;
					//��laststepx,laststepy��ֵ��ʼ��Ϊѡ���Ѷ�ʱ�ĵ��λ��
					laststepx=(pos.Y+1)/2;
					laststepy=(pos.X+1)/4;
					break;
				}
			}
		}
	}
	setcolor(2);
	cout<<"\n\n��ѡ����"<<diff[difficulty]<<"�Ѷ�\n\n";

	//ȫ�ֱ�����ʼ��
	for(i=0;i<=n+1;i++)
		line1[i]=0;
	steptotal=hint1total=hint2total=cheat1=cheat2=hintx=hinty=0;
	cout<<"\n\n���������У����Ժ�..";
	return 1;
}//����startgame����

//------------------------------------------------------------------------------------------------------------

inline int maxnum(int a,int b)
{
	//����a,b�����ֵ
	if(a>b)return a;
	return b;
}

//------------------------------------------------------------------------------------------------------------

inline int calcdifficultyinf(int coediff)
{
	if(difficulty==3)
	{
		if(coediff==7)return int(n*width*0.6);
		if(coediff==6)return int(n*width*0.55);
		if(coediff==5)return int(n*width*0.5);
		if(coediff==4)return int(n*width*0.45);
		if(coediff==3)return int(n*width*0.4);
		if(coediff==2)return int(n*width*0.375);
		if(coediff==1)return int(n*width*0.35);
	}
	if(difficulty==2)
	{
		if(coediff>4)return int(n*width*0.35);
		else return int(n*width*0.25);
	}
	if(difficulty==1)
	{
		//�˴�����maxnum(1, )�������Ǳ����ʼ���ķ�����ȫ��������ɫ����clacdifficultysup������ͬ��
		if(coediff>4)return maxnum(int(n*width*0.175),1);
		else return maxnum(int(n*width*0.125),1);
	}
	return maxnum(int(n*width*0.025),1);
}//����calcdifficultyinf����

//------------------------------------------------------------------------------------------------------------

inline int calcdifficultysup(int coediff)
{
	if(difficulty==4)return n*width;
	if(difficulty==3)return int(n*width*0.85);
	if(difficulty==2)
	{
		if(coediff>4)return int(n*width*0.8);
		else return int(n*width*0.7);
	}
	if(difficulty==1)
	{
		if(coediff>4)return int(n*width*0.55);
		else return int(n*width*0.45);
	}
	if(difficulty==0)
	{
		if(coediff>4)return int(n*width*0.25);
		else return maxnum(int(n*width*0.2),1);
	}
	return n*width;
}//����calcdifficultysup����

//------------------------------------------------------------------------------------------------------------

int randomblock(int inf,int sup,int w)
{
	int i,j,k,m,d,a[25]={0};//k��d�����������������a[ ]��line1[ ]�������ƣ��ǰ�ÿһ�е�ĳ��0��1״̬����������ʮ��������ʾ����֮Ϊ��ת״̬
	//������inf��sup֮���һ�������k
	srand((unsigned)time(0));
	k=rand()%(sup-inf+1)+inf;

	//ver[ ]��ʼ��
	m=n*width;
	for(i=1;i<=m;i++)
		ver[i]=0;

	//����k����ͬ��1��n*width֮��������������ver�������±�Ϊ��Щ�������Ԫ�ر��Ϊ1��
	for(i=1;i<=k;i++)
	{
		d=rand()%m+1;
		while(ver[d]!=0)
			d!=m?d++:d=1;//�������������ظ��Ļ����������ң����ҵ�m������1�����ң�ֱ�����ظ�
		ver[d]=1;
	}

	/*�Ȱ�ver[ ]��ÿ��Ԫ�طֳ�n��width�У�����ver[ ]ÿ��Ԫ�ؼ���Ӧһ������
	�ٰ�ver[ ]����ֵΪ1�ķ��鼰�������������ڷ������ɫ�ı䣨һ��ʼ������ɫ��
	�ٰ�ÿ�еķ�ת״̬����������a��
	��������a���еķ�ת״̬��ͨ�����ơ����ƺ��������õ�ÿ�з���״̬��ֵ*/
	for(i=1;i<=n;i++)
	{
		d=1;
		for(j=1;j<=width;j++)
		{
			//��0��1��״̬��������ת��Ϊʮ������
			a[i]+=ver[(i-1)*width+j]*d;
			d*=2;
		}
	}
	for(i=1;i<=n;i++)
		line1[i]=(a[i-1]^a[i]^(a[i]<<1)^(a[i]>>1)^a[i+1])%w;//line1[ ]��ֵ���ܳ���w
	return k;
}//����randomblock����

//------------------------------------------------------------------------------------------------------------

void calculate(int k)
{
	int c[25]={0},i,j,sum,d;//c[ ]����randomblock�е�a[ ]���Ǽ�¼ÿ�еķ�ת״̬��ʮ��������sum����ÿ�ַ�����ת�˶��ٴη��飻dΪ��ʱ����
	leaststep=10000000;
	/*�����ȡ��ö�ٷ����㷨���Ӷ�ΪO(n*k)=O(n*(2^width))
	����һ�еķ�ת״̬��ѭ����ö�٣�����ÿһ�еķ�ת״̬����ǰ�����еķ�ת״̬�Լ�����״̬ȷ��
	����n�з�ת״̬ȷ�������������ȫ�������ɫ������һ����ȷ�ķ�ת����*/
	for(c[1]=0;c[1]<k;c[1]++)
	{
		for(i=2;i<=n;i++)
			c[i]=(line1[i-1]^c[i-1]^c[i-2]^(c[i-1]>>1)^(c[i-1]<<1))%k;//����ÿһ�еķ�ת״̬
		if((c[n-1]^c[n]^(c[n]>>1)^(c[n]<<1)^line1[n])%k==0)//�����ת�����һ��ȫΪ��ɫ
		{
			//���������ȷ�ķ�����ת�˶��ٴη���
			sum=0;
			for(i=1;i<=n;i++)
				for(j=1;j<=width;j++)
					sum+=(1^(c[i]>>(j-1))+1)%2;

			if(sum<leaststep)
			{
				leaststep=sum;
				for(i=1;i<=n;i++)
				{
					d=c[i];
					//���ÿ��з����ķ�ת״̬��¼��step[ ][ ]��
					for(j=1;j<=width;j++)
					{
						step[i][j]=0;
						step[i][j]=d%2;
						d/=2;
					}
				}
			}
		}//����if(���һ��ȫΪ��ɫ)
	}//����ö��ѭ��
}//����calculate����

//------------------------------------------------------------------------------------------------------------

void turn()
{
	int i,j,d;//dΪ��ʱ����
	for(i=1;i<=n;i++)
	{
		d=line1[i];
		for(j=1;j<=width;j++)
		{
			//������״̬��¼��block[ ][ ]��
			block[i][j]=0;
			block[i][j]=d%2;
			d/=2;
		}
	}
	cout<<"\n\n�����������";
	Sleep(150);
}//����turn����

//------------------------------------------------------------------------------------------------------------

int output(int t,int w)
{
	string titl[25]={"��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��"};
	COORD po;
	int i,j;
	//x[ ],y[ ]��ʾ����Ϸ�е��ĳ�鷽��ʱ����Ҫ��������ķ�����С�������
	int x[6]={0,laststepx,laststepx-1,laststepx+1,laststepx,laststepx},y[6]={0,laststepy,laststepy,laststepy,laststepy-1,laststepy+1};

	po.X=0;
	po.Y=2*n+2;
	SetConsoleCursorPosition(hOut,po);
	setcolor(2);
	cout<<"            ";
	po.Y=0;
	SetConsoleCursorPosition(hOut,po);
	if(t>=0)//����ʼ��Ϸ(t=0)��ʤ��(t=2)ʱ�����˷�֧�����ȫ�������������
	{
	    po.X=0;
	    po.Y=2*n+2;
	    SetConsoleCursorPosition(hOut,po);
	    setcolor(2);
	    cout<<"                             ";
	    
		//�ڻ�������һ�������,��,��,...
		po.Y=0;
	    SetConsoleCursorPosition(hOut,po);
		cout<<"   ";
	    for(i=0;i<width;i++)
		    cout<<' '<<titl[i]<<' ';
	    cout<<endl;

		//���ÿ�з�����ÿ�з�����ռ�����������У���ÿ�з�����ĵ�һ�е���ߺ��ұ��������
	    for(i=1;i<=n;i++)
		{
		    cout<<setw(2)<<i<<' ';
		    for(j=1;j<=width;j++)
			{
			    setcolor(block[i][j]);
			    cout<<setw(2)<<i<<char(j+64)<<' ';
			}
		    setcolor(2);
		    cout<<' '<<setw(2)<<i<<endl<<"___";
		    for(j=1;j<=width;j++)
			{
			    setcolor(block[i][j]);
			    cout<<"   .";
			}
		    setcolor(2);
		    cout<<"____"<<endl;
		}

		//�ڷ������¶��ٴ������,��,��,...
	    cout<<"   ";
	    for(i=0;i<width;i++)
		    cout<<' '<<titl[i]<<' ';
	    cout<<endl;

		//�������ҷ����·��Ķ��������ɺ�ɫ����
		setcolor(3);
		CONSOLE_SCREEN_BUFFER_INFO bInfo;
        GetConsoleScreenBufferInfo(hOut,&bInfo);
		WORD att=bInfo.wAttributes;
		po.X=0;
		po.Y=maxnum(15,2*n+3);
		FillConsoleOutputAttribute(hOut,att,123*(42-maxnum(15,2*n+3)+1),po,NULL);
		po.X=width*4+43;
		for(po.Y=0;po.Y<=42;po.Y++)
		{
			FillConsoleOutputAttribute(hOut,att,80-width*4,po,NULL);
		}

	}//����if(t>=0)��֧

	else//����Ϸ���������������ʱ���Ⱥ����˷�֧����(t=-1,t=-2)��ֻ���x[ ],y[ ]�еķ����������
	{
		for(i=1;i<=5;i++)
		{
			if(x[i]>0&&x[i]<=n&&y[i]>0&&y[i]<=width)//��x[ ],y[ ]�еķ����ڷ�����Χ����ʱ
			{
				po.X=4*y[i]-1;
	            po.Y=2*x[i]-1;
	            SetConsoleCursorPosition(hOut,po);
	            if(t==-1)//��ת˲���Ч����ԭ����ɫ�ķ�������죬ԭ����ɫ�ķ���������
				{
					setcolor(block[x[i]][y[i]]+6);
					cout<<"    ";
					po.Y++;
					SetConsoleCursorPosition(hOut,po);
					cout<<"    ";
				}
				else if(t==-2)//��ת֮��
				{
					setcolor(block[x[i]][y[i]]);
					cout<<setw(2)<<x[i]<<char(y[i]+64)<<' ';
					po.Y++;
					SetConsoleCursorPosition(hOut,po);
					cout<<"   .";
				}
			}
		}
		if(t==-2&&hintx>0&&hinty>0)//���ʹ������ʾһ����ô��ĳ�鷽�鴦���С���ת��顱����������Ҫ��ȥ������
		{
			po.X=4*hinty-1;
			po.Y=2*hintx-1;
			SetConsoleCursorPosition(hOut,po);
			setcolor(block[hintx][hinty]);
			cout<<setw(2)<<hintx<<char(hinty+64)<<' ';
			po.Y++;
			SetConsoleCursorPosition(hOut,po);
			cout<<"   .";
			hintx=hinty=0;
		}
	}//����else�ķ�֧

	po.X=0;
	po.Y=2*n+2;
	setcolor(2);
	SetConsoleCursorPosition(hOut,po);
	if(t!=0&&t!=-2)return 0;//��t=2ʱ�����Ϸ������������win����ȷ������t=-1ʱ��Ϊ��ת˲���Ч��������Ҫ������Ϸ�������
	outputword();//������Ϸ�������
	return press(w);//����press����������press�ķ���ֵ��Ϊoutput�ķ���ֵ
}//����output����

//------------------------------------------------------------------------------------------------------------

void outputword()
{
	COORD po;
	//���������Ϸ������һ����ת�ķ���λ�á���ת������ʹ����ʾһ������ʹ����ʾ��������ʱ��
	po.X=width*4+8;
	po.Y=0;
	SetConsoleCursorPosition(hOut,po);
	if(steptotal>0)cout<<"|��һ����ת�˵�"<<laststepx<<"�С���"<<char(laststepy+64)<<"�еķ���";
	po.Y=1;
	SetConsoleCursorPosition(hOut,po);
	cout<<"|Ŀǰ�ѷ�ת��"<<steptotal<<"�η���";
	po.Y=2;
	SetConsoleCursorPosition(hOut,po);
	cout<<"|Ŀǰ��ʹ����"<<hint1total<<"����ʾһ";
	po.Y=3;
	SetConsoleCursorPosition(hOut,po);
	cout<<"|Ŀǰ��ʹ����"<<hint2total<<"����ʾ��";
	po.Y=4;
	SetConsoleCursorPosition(hOut,po);
	cout<<"|";
	if(cheat1==0&&cheat2==0)cout<<'*';//û�������Զ���ʾ/�Զ���תģʽ�����*���������!
	else cout<<'!';
	cout<<"ʱ��:";
	po.Y=5;
	SetConsoleCursorPosition(hOut,po);
	cout<<"|---------------------------";
	
	//�������ʾһ��������ʾ�����������¿��֡������˳���Ϸ������ɫ����
	po.Y=6;
	SetConsoleCursorPosition(hOut,po);
	cout<<'|';
	if(cheat1+cheat2==0)//���������Զ���ʾ/�Զ���תģʽʱ�����������ʾһ��������ʾ��������ͬ
	{
		setcolor(8);
	    cout<<"            ";
	    setcolor(2);
	    cout<<"  ";
	    setcolor(8);
	    cout<<"            ";
	}
	po.Y=7;
	SetConsoleCursorPosition(hOut,po);
	setcolor(2);
	cout<<'|';
	if(cheat1+cheat2==0)
	{
	    setcolor(8);
	    cout<<"  �� ʾ һ  ";
	    setcolor(2);
	    cout<<"  ";
	    setcolor(8);
	    cout<<"  �� ʾ ��  ";
	    setcolor(2);
	}
	po.Y=8;
	SetConsoleCursorPosition(hOut,po);
	cout<<'|';
	if(cheat1+cheat2==0)
	{
	    setcolor(8);
	    cout<<"            ";
	    setcolor(2);
	    cout<<"  ";
	    setcolor(8);
	    cout<<"            ";
	    setcolor(2);
	}
	po.Y=9;
	SetConsoleCursorPosition(hOut,po);
	cout<<"|---------------------------";
	po.Y=10;
	SetConsoleCursorPosition(hOut,po);
	cout<<'|';
	setcolor(8);
	cout<<"            ";
	setcolor(2);
	cout<<"  ";
	setcolor(8);
	cout<<"            ";
	po.Y=11;
	SetConsoleCursorPosition(hOut,po);
	setcolor(2);
	cout<<'|';
	setcolor(8);
	cout<<"  ���¿���  ";
	setcolor(2);
	cout<<"  ";
	setcolor(8);
	cout<<"  �˳���Ϸ  ";
	setcolor(2);
	po.Y=12;
	SetConsoleCursorPosition(hOut,po);
	cout<<'|';
	setcolor(8);
	cout<<"            ";
	setcolor(2);
	cout<<"  ";
	setcolor(8);
	cout<<"            ";
	setcolor(2);
	po.Y=13;
	SetConsoleCursorPosition(hOut,po);
	cout<<"|---------------------------";
	po.X=0;
	po.Y=2*n+2;
	SetConsoleCursorPosition(hOut,po);
}//����outputword����

//------------------------------------------------------------------------------------------------------------

int press(int w)
{
    COORD po;
	time_t starttime,endtime,temp;//starttime��ʾÿ�η�ת����ʱ�䣬endtime��ʾ���ʱ��ʱ��
	//h��ʾ�Ƿ��ʹ����ʾ(0/1)��cheat��ʾ���*�Ĵ�����changecheat��ʾ�Ƿ���������Զ���ʾ/�Զ���תģʽ��repeat��ʾ�ظ����ͬһ����Ĵ���
	int i,j,h=1,cheat=0,changecheat=1,repeat=0;
	starttime=clock();
	if(cheat1==1||cheat2==1)//���������Զ���ʾ/�Զ���תģʽʱ�����ҵ���ʾ��ת�ķ���λ��
	{
		h=changecheat=0;
		srand((unsigned)time(0));
		i=rand()%leaststep+1;
		hint(i);
		if(cheat1==1)hint1total++;
		if(cheat2==1)hint2total++;
	}
	while(1)//�������������������¿��֡������˳���Ϸ�����Զ���תģʽ��ʼ��תʱ���˳�ѭ��
	{
		//ģ��һֱ�ڰ��ż��̵�A����������ʹ���ƶ���꣬ReadConsoleInputҲ��һֱִ��
		keybd_event('A',0,0,0);
		ReadConsoleInput(hIn,&mouseRec,1,&res);

		//����ʱ�䲢ʵʱ��ʾʱ��
		endtime=clock();
		temp=timetotal+endtime-starttime;
		i=int(temp)/1000/60;
		j=int(temp)/1000%60;
		po.X=width*4+15;
		po.Y=4;
		SetConsoleCursorPosition(hOut,po);
		setcolor(2);
		cout<<' '<<i<<"����"<<j<<"��";

		//���������Զ���תģʽʱ������ѭ����һС��ʱ�伴��ת
		if(cheat2==1&&temp-timetotal>60)
		{
			endtime=clock();
			timetotal+=endtime-starttime;
			invert(hintx,hinty,w);
			return 0;
		}

		if(mouseRec.EventType==MOUSE_EVENT)//��������ƶ����е��ʱ
		{
			keybd_event('A',0,KEYEVENTF_KEYUP,0);//ģ���ɿ����̵�A��
			pos=mouseRec.Event.MouseEvent.dwMousePosition;
			if(mouseRec.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED)//�����������ʱ
			{
				if(pos.X==width*4+9&&pos.Y==4&&changecheat==1)//�����������Զ���ʾ/�Զ���תģʽ���ҵ���ˡ�ʱ�䡱�󷽵�*ʱ
				{
					cheat++;
					if(cheat==6)//�����λ��ǡ�ô�6��ʱ��*���?
					{
						po.X=width*4+9;
		                po.Y=4;
		                SetConsoleCursorPosition(hOut,po);
						cout<<'?';
					}
				}
				else if(cheat!=6)//��cheat������6�����������λ��ʱ
				{
					changecheat=0;
				}

				//û�������Զ���תģʽ�ҵ���˷���ʱ
				if(pos.X>=3&&pos.X<=4*width+2&&pos.Y>=1&&pos.Y<=2*n&&mouseRec.Event.MouseEvent.dwEventFlags!=DOUBLE_CLICK&&cheat2==0)
				{
					i=(pos.Y+1)/2;
					j=(pos.X+1)/4;
					//���ϣ���������η�תͬһ���飬�������÷������β��ܷ�ת������Ϊ�˱��������
					if(i==laststepx&&j==laststepy)repeat++;
					if(i!=laststepx||j!=laststepy||(i==laststepx&&j==laststepy&&repeat>2))
					{
						endtime=clock();
						timetotal+=endtime-starttime;
						invert(i,j,w);
					    return 0;
					}
				}

				//����ʹ����ʾ������ˡ���ʾһ��ʱ��������ʾһ
				if(pos.X>=4*width+9&&pos.X<=4*width+20&&pos.Y>=6&&pos.Y<=8&&h==1)
				{
					srand((unsigned)time(0));
					i=rand()%leaststep+1;
					hint1total++;
					if(cheat==6&&changecheat==1)//��*�ձ��?ʱ���������ʾһ�������Զ���ʾģʽ������?��Ϊ!
					{
						cheat1=1;
						changecheat=0;
						po.X=width*4+9;
		                po.Y=4;
		                SetConsoleCursorPosition(hOut,po);
						cout<<'!';
					}
					hint(i);
					h=0;
				}

				//����ʹ����ʾ������ˡ���ʾ����ʱ��������ʾ��
				if(pos.X>=4*width+23&&pos.X<=4*width+34&&pos.Y>=6&&pos.Y<=8&&h==1)
				{
					hint2total++;
					if(cheat==6&&changecheat==1)//��*�ձ��?ʱ���������ʾ���������Զ���תģʽ������?��Ϊ!
					{
						cheat2=1;
						changecheat=0;
						po.X=width*4+9;
		                po.Y=4;
		                SetConsoleCursorPosition(hOut,po);
						cout<<'!';
					}

					//�����Ϸ��������ʾ������Ӧ������
					setcolor(2);
					po.X=4*width+9;
					po.Y=6;
					SetConsoleCursorPosition(hOut,po);
					cout<<"��ʾ����                      ";
					po.Y=7;
					SetConsoleCursorPosition(hOut,po);
					cout<<"���ٻ��跭ת"<<leaststep<<"�η���        ";
					po.Y=8;
					SetConsoleCursorPosition(hOut,po);
					cout<<"������ת����������ʹ����ʾ  ";
					po.X=0;
	                po.Y=2*n+2;
	                SetConsoleCursorPosition(hOut,po);
					h=0;

					//������������Զ���תģʽ�������ϼ���Ҫ��ʾ�ķ��鲢��ʼ�Զ���ת
					if(cheat2==1)
					{
		                srand((unsigned)time(0));
		                i=rand()%leaststep+1;
		                hint(i);
					}
				}

				if(pos.X>=4*width+9&&pos.X<=4*width+20&&pos.Y>=10&&pos.Y<=12)//��������¿��֡�ʱ
				{
					return 1;
				}
				
				if(pos.X>=4*width+23&&pos.X<=4*width+34&&pos.Y>=10&&pos.Y<=12)//������˳���Ϸ��ʱ
				{
					return 2;
				}
			}//�����жϵ��������
		}//�����ж�����ƶ�����
	}//�����ȴ���������ȴ��Զ���ת
}//����press����

//------------------------------------------------------------------------------------------------------------

void hint(int k)
{
    int i,j;
	//�������£���������Ѱ����Ҫ��ת�ķ��飬���ҵ���k��ʱ�˳�ѭ�������ѵ�k�������������Ϊ��ʾ�ķ��������
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=width;j++)
		{
			if(step[i][j]==1)k--;
			if(k==0)break;
		}
		if(k==0)break;
	}
	hintx=i;
	hinty=j;

	//�������ʾһ�������Ϸ���Ӧ������
	setcolor(2);
	COORD po;
	po.X=4*width+9;
	po.Y=6;
	SetConsoleCursorPosition(hOut,po);
	if(cheat1==1)cout<<"���������Զ���ʾģʽ��       ";
	else if(cheat2==1)cout<<"���������Զ���תģʽ��       ";
	else cout<<"��ʾһ��                      ";
	po.Y=7;
	SetConsoleCursorPosition(hOut,po);
	if(cheat2==1)cout<<"���ٻ��跭ת"<<leaststep<<"�η���        ";
	else cout<<"��ת��"<<i<<"�С���"<<char(j+64)<<"�еķ���     ";
	po.Y=8;
	SetConsoleCursorPosition(hOut,po);
	if(cheat2==0)cout<<"������ת����������ʹ����ʾ  ";
	else cout<<"���������ֶ���ת����      ";

	//��û�������Զ���תģʽʱ���ڷ��������ҵ���ʾ�ķ��飬���ڷ������������ת��顱
	if(cheat2==0)
	{
	    po.X=4*j-1;
	    po.Y=2*i-1;
	    SetConsoleCursorPosition(hOut,po);
	    setcolor(block[i][j]+4);
	    cout<<"��ת";
	    po.Y=2*i;
    	SetConsoleCursorPosition(hOut,po);
	    cout<<"���";
	}
	setcolor(2);
	po.X=0;
	po.Y=2*n+2;
	SetConsoleCursorPosition(hOut,po);
}//����hint����

//------------------------------------------------------------------------------------------------------------

void invert(int i,int j,int w)
{
	int k=0;//kΪ��ʱ����
	steptotal++;
	laststepx=i;
	laststepy=j;
	//��Ҫ��ת�ķ��鼰�������������ڷ���ķ�תʱ��˲��״̬���
	output(-1,w);
	cout<<"���ڷ�ת��..";

	//�ı�Ҫ��ת�ķ��鼰�������������ڷ������ɫ
	block[i][j]=(block[i][j]+1)%2;
	block[i-1][j]=(block[i-1][j]+1)%2;
	block[i+1][j]=(block[i+1][j]+1)%2;
	block[i][j-1]=(block[i][j-1]+1)%2;
	block[i][j+1]=(block[i][j+1]+1)%2;

	//��block[ ][ ]��ֵת��Ϊÿ�еķ���״̬��ֻ��ı䷭ת�ķ��������м�����һ�С���һ�й����еķ���״̬����
	for(i=laststepx-1;i<=laststepx+1;i++)
	{
		k=1;
		line1[i]=0;
		for(j=1;j<=width;j++)
		{
			line1[i]+=block[i][j]*k;
			k*=2;
		}
	}
}//����invert����

//------------------------------------------------------------------------------------------------------------

int win()
{
	int i,s=0,second,minute;//sΪÿ�з���״̬�ĺ�
	for(i=1;i<=n;i++)
		s+=line1[i];
	if(s!=0)return 0;//����ĳЩ�з���״̬��Ϊ0�������ں�ɫ����
	
	//���s=0��ִ����������

	second=int(timetotal)/1000%60;
	minute=int(timetotal)/1000/60;
	clearscreen();
	output(2,NULL);//����output��������ȫ����������������Ϸ���������win���������Ҫoutputword�����
	
	//������Ϸ�������
	COORD po={width*4+8,0};
	SetConsoleCursorPosition(hOut,po);
	cout<<"|Congratulations!!!!��ʤ���ˣ�����";
	po.Y=1;
	SetConsoleCursorPosition(hOut,po);
	cout<<"|������Ϸ�У�������ת��"<<steptotal<<"�η���";
	po.Y=2;
	SetConsoleCursorPosition(hOut,po);
	cout<<"|��ʹ����"<<hint1total<<"����ʾһ     ";
	po.Y=3;
	SetConsoleCursorPosition(hOut,po);
	cout<<"|��ʹ����"<<hint2total<<"����ʾ��     ";
	po.Y=4;
	SetConsoleCursorPosition(hOut,po);
	cout<<"|����ʱ"<<minute<<"����"<<second<<"��   ";
		setcolor(2);
	po.Y=5;
	SetConsoleCursorPosition(hOut,po);
	cout<<"|---------------------------";

	//���������һ�֡������˳���Ϸ������ɫ����
	po.Y=6;
	SetConsoleCursorPosition(hOut,po);
	cout<<'|';
	setcolor(8);
	cout<<"            ";
	setcolor(2);
	cout<<"  ";
	setcolor(8);
	cout<<"            ";
	po.Y=7;
	SetConsoleCursorPosition(hOut,po);
	setcolor(2);
	cout<<'|';
	setcolor(8);
	cout<<"  ����һ��  ";
	setcolor(2);
	cout<<"  ";
	setcolor(8);
	cout<<"  �˳���Ϸ  ";
	setcolor(2);
	po.Y=8;
	SetConsoleCursorPosition(hOut,po);
	cout<<'|';
	setcolor(8);
	cout<<"            ";
	setcolor(2);
	cout<<"  ";
	setcolor(8);
	cout<<"            ";
	setcolor(2);
	po.Y=9;
	SetConsoleCursorPosition(hOut,po);
	cout<<"|---------------------------";

	//�ȴ������������һ�֡����˳���Ϸ��
	while(1)
	{
		ReadConsoleInput(hIn,&mouseRec,1,&res);
		if(mouseRec.EventType==MOUSE_EVENT)
		{
			pos=mouseRec.Event.MouseEvent.dwMousePosition;
			if(mouseRec.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				if(pos.X>=4*width+9&&pos.X<=4*width+20&&pos.Y>=6&&pos.Y<=8)return 1;
				if(pos.X>=4*width+23&&pos.X<=4*width+34&&pos.Y>=6&&pos.Y<=8)return 2;
			}
		}
	}
}//����win����

//------------------------------------------------------------------------------------------------------------

void gameend()
{
	clearscreen();
	cout<<"\n\n\n";
	cout<<"                    +-----------------------------------------------------------+\n";
	cout<<"                    |                                                           |\n";
	cout<<"                    |                 �� �� �� л �� �� �� �� �� Ϸ             |\n";
	cout<<"                    |                                                           |\n";
	cout<<"                    |  ��л������ѧ��Ϣ��ѧ����ѧԺ��                           |\n";
	cout<<"                    |  ��лÿλ������������Ϸ�Ĺ����������ṩ��������ʦ��ͬѧ�� |\n";
	cout<<"                    |  �ر��л�����ʦ����Ԫ����̣�                           |\n";
	cout<<"                    |                                                           |\n";
	cout<<"                    |                                                           |\n";
	cout<<"                    |  ����������Ϸ�������κδ�©�򲻵�֮����ӭָ����           |\n";
	cout<<"                    |                                                           |\n";
	cout<<"                    +-----------------------------------------------------------+\n\n\n\n\n��˫������˳���Ϸ. . .\n\n\n\n";
	while(1)//�ȴ����˫������
	{
		ReadConsoleInput(hIn,&mouseRec,1,&res);
		if(mouseRec.EventType == MOUSE_EVENT&&mouseRec.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)return;
	}
}//����gameend����

//============================================================================================================

int main()
{
	welcome();//�򿪻�ӭ����
	/*time1�������Ϸʱ�ĵȴ�ʱ���йأ���ֵ��widthȷ��
	calctime=2^width
	restartorexitΪoutput������win�����ķ���ֵ�����������Ϸ�����¿��ֻ��˳���Ϸ
	inf,sup�ֱ��ʾ�����Ѷ�Ҫ���leaststep���½���Ͻ�
	coediff��ʾ�Ѷ�ϵ������n��widthȷ������ʼֵ��Ϊ7�����������leaststep��ȡ�������ֵԽ��ʱ��coediffԽ��
	difftempΪ��ʱ�������ڼ���coediffʱҪ��
	rantime��ʾ������Ϸʱ�ĵȴ�ʱ�䣬�Լ�ÿ�η�ת�еļ���ʱ��*/
	int i,j,time1,calctime,restartorexit,inf,sup,coediff,difftemp;
	time_t rantime,startrantime,temprantime;

	while(gamestart())
	{
		//��ʼ��ʱ�䣬������calctime
		timetotal=rantime=0;
		calctime=1;
		for(i=1;i<=width;i++)
			calctime*=2;

		//�Ѷ����difficulty�����ȴ�����difftemp�У���difficulty��Ϊ3������coediff
		difftemp=difficulty;
		difficulty=3;

		//��coediffmem[n][width]������0���������֮ǰ�����coediff���ݣ�
		//��coediff��ʼֵΪcoediffmem[n][width]+1��+1��Ϊ�˱������������ʼֵΪ7
		coediff=coediffmem[n][width]!=0&&coediffmem[n][width]!=7?coediffmem[n][width]+1:7;
		time1=(width<16)?(width<10?100:200):(width<19?300:400);
		i=j=0;
		startrantime=clock();
		
		/*�Ȱ�difficuly=3��coediff��ֵ����inf��sup��
		����õ���leaststep��С��inf��
		��ô�͸�ԭԭ��ѡ����difficulty��ֵ����difftemp��ֵ��difficulty��
		��ͨ��coediff����inf��sup��Ȼ���ҳ�һ�ֿ��еķ���״̬
		����õ���leaststepһֱС��inf��
		��ô�ڼ���һ��ʱ��󣬾���coediff��һ����������*/
		do
		{
			inf=calcdifficultyinf(coediff);
		    sup=calcdifficultysup(coediff);
		    do
			{
			    randomblock(inf,sup,calctime);
			    temprantime=clock();
			    rantime=temprantime-startrantime;
			    if(int(rantime)/time1>i)//������һ��ʱ����Ȼû�п��н�
				{
				    if((++i)%3==2)cout<<'.';//�ڡ����������У����Ժ�..���������һ��'.'
				    if(coediff>1)coediff--;
				    inf=calcdifficultyinf(coediff);
				    sup=calcdifficultysup(coediff);
				}
			    calculate(calctime);//�ó�leaststep��ֵ
			}while(leaststep<inf||leaststep>sup);
			difficulty=difftemp;//��ԭdifficulty��ֵ
			j++;
		}while(j==1&&difftemp!=3);//��ѭ��ֻ��֮��1�λ�2��

		coediffmem[n][width]=coediff;//��coediff�Ľ��������coediffmem[ ][ ]�У��Ա��´ε���
		turn();//������״̬������block[ ][ ]��
		clearscreen();

		//����Ϸ������û��ѡ�����¿��֡����˳���Ϸ������û�л��ʤ��ǰ����ѭ������ֹ
		do
		{
			//��һ�η�תʱҪ���ȫ�����飬����ķ�תֻ��������ַ���
			if(steptotal==0)restartorexit=output(0,calctime);
			else restartorexit=output(-2,calctime);

			//�������ˡ����¿��֡����˳���Ϸ������ô�˳�ѭ��
			if(restartorexit>0)
			{
				break;
			}

			startrantime=clock();

			//����������Ҫ��ת�ķ��飬����Ҫͨ��calculate��������leaststep��step[ ][ ]�ļ��㣬ֱ�ӽ���leatstep--����
			if(step[laststepx][laststepy]==1||cheat2==1)
			{
				leaststep--;
				step[laststepx][laststepy]=0;
			}

			/*���û�е����Ҫ��ת�ķ��飬
			����Ҫͨ��calculate�������м��㣬
			����Ϊn=20,18,16��width=20ʱ��
			��ÿ�ַ���״̬������ֻ��һ�ַ�ת;����
			���������������������Ҫ����calculate���̣�
			����calctime̫�󣬽���calculate���˷�ʱ��*/
			else if((n==20||n==18||n==16)&&width==20)
			{
				leaststep++;
				step[laststepx][laststepy]=1;
			}

			//����û�е����Ҫ��ת�ķ����ҷ����������������������calculate��������
			else calculate(calctime);

			/*����ÿ�η�ת���ڼ����л��˶���ʱ�䣬
			���ʱ�����80ms������Ļ����ͣ�ͣ�ʹ���ַ�תʱ��Ч��*/
			temprantime=clock();
			rantime=temprantime-startrantime;
			if(int(rantime)<80)Sleep(80-int(rantime));

			//�ж��Ƿ�ʤ�������ʤ�������ж�������һ�仹���˳���Ϸ
			restartorexit=win();
		}while(restartorexit==0);//restartorexit=0��ʾ������Ϸ��restartorexit=1��ʾ���¿��֣�restartorexit=2��ʾ�˳���Ϸ

		if(restartorexit==2)break;//�˳���Ϸ
	}//����while(gamestart())ѭ��
	gameend();//�򿪽�������
	return 0;
}
