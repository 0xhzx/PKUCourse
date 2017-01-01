// ����ϵر�֤��
    
// ���Լ��������������������ӷ�������Ƶ���������й�����
// ��������������У���������ʲô���Ѷ�������ˣ���ô���ҽ��ڳ���ʵϰ������
// ��ϸ���о��������������⣬�Լ����˸��ҵ���ʾ��

// �ҵĳ������з������õ�����������ĵ�֮����
// ����̲ġ����ñʼǡ����ϵ�Դ�����Լ������ο����ϵĴ����,
// �Ҷ��Ѿ��ڳ����ע����������ע�������õĳ�����

// �Ҵ�δ��Ϯ�����˵ĳ���Ҳû�е��ñ��˵ĳ���
// �������޸�ʽ�ĳ�Ϯ����ԭ�ⲻ���ĳ�Ϯ��

// �ұ�д������򣬴���û�����Ҫȥ�ƻ���������������ϵͳ��������ת��

// ���ݽṹ���㷨ʵϰ֮����ģ����
// �ļ�����lift_simulator.cpp
// ���ߣ����Ӻ� 
// ���ڣ�2012��10��16��
// �汾��1.5.0
// ���뻷����Microsoft Visual C++ 6.0
// ����ϵͳ��Microsoft Windows XP
// ���뷽ʽ�����̶�������
// �����ʽ��win32����̨�������

// �������ܣ�
// 1.��������˿͵��ܵȺ�ʱ�䡢�ܳ���ʱ�䣬ÿ���˿͵��˾��Ⱥ�ʱ�䡢�˾�����ʱ�䣬���е��ݵ��ؿ�����ÿ�����ݵ�λʱ���ڵ��ؿ���
// 2.ʹ��win32����̨������������˶�״̬��λ�á������ڳ˿������Լ�ÿ��¥�ȴ��ĳ˿���
// ��չ���ܣ�
// 1.ʹ�������ֵ��ݵ����㷨���ܼ�������㷨���˾��Ⱥ�ʱ�䡢�ؿ����������ݣ��������ؿ��������㷨���ӽ�������
// 2.���ÿ�������ڵĳ˿Ͱ��İ�ť���ȴ��ĳ˿Ͱ��İ�ť��ÿ����ÿ��¥�³��ֵĳ˿��������ϵ��ݵĳ˿��������뿪���ݵĳ˿�����
// 3.�ڸ��������������ϵͳ�����£��ó��˵�������������ָ���Ӱ�죨��ʵϰ���棩
// 4.�ڸ��������������ϵͳ�����£��ó��˸߲��ݡ��Ͳ��ݶ�ϵͳ����ָ���Ӱ�죨��ʵϰ���棩

#include<iostream>
#include<iomanip>
#include<cmath>
#include<ctime>
#include<vector>
#include<list>
#include<windows.h>
#pragma comment(lib,"winmm.lib")

#define MIN_MAXLOAD 5
#define MAX_MAXLOAD 20 // ÿ�����ݵ�����صķ�Χ��5��20
#define MIN_FLOOR_NUM 2
#define MAX_FLOOR_NUM 40 // ¥�������ķ�Χ��2��40
#define MIN_LIFT_NUM 1
#define MAX_LIFT_NUM 13 // ���������ķ�Χ��1��13
#define MIN_LAMBDA 0.1
#define MAX_LAMBDA 20 // ���ɲ����ķ�Χ��0.1��20
#define MAX_NEW_PASSENGER 100 // ÿ���³��ֵĳ˿����Ϊ100��
#define MAX_PASSTIME 400 // ����ģ�����ʾ���ʱ��Ϊ400�루�������ָ����ģ����������ʱ�������ʵʱ�䣩
#define NORMAL 0 // ����ɫ����ͬ
#define INFO 1
#define BLANK 2
#define DOWN 3
#define UP 4
#define OPEN 5
#define BUTTON 6
#define TABLE 7
#define SCREEN_WIDTH 168 // ��Ļ���
#define SCREEN_HEIGHT 57 // ��Ļ�߶�
#define WINDOW_WIDTH 167 // ���ڿ��
#define WINDOW_HEIGHT 43 // ���ڸ߶�
#define SECONDS_PER_HOUR 3600.0

using namespace std;

double maximum(double,double); 
// ���������������ֵ����������Ϊx��y������x��y�����ֵ
double minimum(double,double); 
// ��������������Сֵ����������Ϊx��y������x��y����Сֵ
double average(double,double); 
// ������������ƽ��ֵ����������Ϊx��y������x��y��ƽ��ֵ
double poisson(double,int); 
// ���㲴�ɷֲ��ĸ���ֵ����һ������Ϊ�ˣ��ڶ�������Ϊk������exp(-��)*(��^k)/(k!)
void play(int); 
// �������֣�����Ϊ0��17������������Ϊ0ʱ�����ţ�������0ʱ����ĳһƵ�ʵ���
void calcpk(double,double[]); 
// ����ÿһ���������ĳ˿͵������ĸ���ֵ����һ������Ϊ�ˣ��������Ľ�������ڵڶ���������������
int createpassenger(int,int,double[]); 
// ���ݸ���ֵ�����³˿ͣ���һ������Ϊ¥���������ڶ�������Ϊ��ǰ�ĳ˿�������������������Ϊ֮ǰ����ĸ���ֵ������ֵΪ֮��ĳ˿�������
int recreatepassenger(int,int[]); 
// �ڲ�ͬ�㷨�Ŀ���ģ��͸����㷨����ʾ�����²���֮ǰ�����ĳ˿�������һ������Ϊ��ǰ�ĳ˿����������ڶ�������Ϊÿ��¥�����ĳ˿�����������ֵΪ֮��ĳ˿�������
void calc(int);
// �����ܵȴ�ʱ�䡢�������ȸ������ݣ�����Ϊ��ǰ�ĳ˿�������
void print(int,int,int,int,int,int[],int[],int[]);
// �����������������Ϊ���״̬�����õ��㷨��¥��������������������ǰ�˿���������ÿ��¥�����ĳ˿�������ÿ��¥�뿪�ĳ˿�������ÿ��¥�ϵ��ݵĳ˿�����
void goonlift(int,int,int,int[],list<int>::iterator);
// ��˿��ϵ��ݣ���������Ϊ������š�����¥�㡢�˿���š�ÿ��¥�ϵ��ݵĳ˿�������ÿ��¥�ȴ��ĳ˿����еĵ�����
void operate(int,int,int,int,int[],int[]);
// ���ȵ��ݣ���������Ϊ���õ��㷨��¥��������������������������ء�ÿ��¥�ϵ��ݵĳ˿�������ÿ��¥�뿪�ĳ˿�����
void setcolor(int);
// �ı䱳����ɫ��������ɫ������Ϊ��ɫ����
void clearscreen(int,int,int,double);
// ��ÿ����ʾǰ��������������Ϊ¥��������������������������ء����ɲ�����

class PASSENGER
{
public:
	int from,to,createtime,onlifttime,leavetime;
	// from��ʾ�˿����Ĳ�¥���֣�to��ʾ�˿͵�Ŀ��¥�㣬createtime��ʾ�˿ͳ��ֵ�ʱ�䣬onlifttime��ʾ�˿ͽ����ݵ�ʱ�䣬leavetime��ʾ�˿��뿪���ݵ�ʱ��
	PASSENGER(const int f,const int t,const int c)
	{
		from=f;
		to=t;
		createtime=c;
		onlifttime=leavetime=0;
	}
	void init()
	{
		onlifttime=leavetime=0;
	}
};

class FLOOR
{
public:
	list<int> lstp;
	// lstp��¼�ڸò�¥�ȴ��ĳ˿͵����
	void init()
	{
		lstp.clear();
	}
};

class LIFT
{
public:
	bool stop[MAX_FLOOR_NUM+1];
	// stop��ʾ�����Ƿ�Ӧ����ĳ��¥ͣ��Ҳ�����Ϊ�����ڵĳ˿��Ƿ���ĳ��¥�İ�ť��
	int flor,target,formerfloor;
	// flor��ʾ���ݵ�ǰ����¥�㣬targetΪ���ݵ�Ŀ��¥�㣬formerfloor��ʾ��������һ�����ڵ�¥��
	list<int> lstp;
	// lstp��¼�ڸõ����ڵĳ˿͵����
	LIFT()
	{
		target=formerfloor=0;
		int i;
		for(i=1;i<=MAX_FLOOR_NUM;i++)
			stop[i]=0;
	}
	void init()
	{
		lstp.clear();
		target=formerfloor=0;
		int i;
		for(i=1;i<=MAX_FLOOR_NUM;i++)
			stop[i]=0;
	}
};

HANDLE hOut; // ������
COORD pos={0,0}; // ���λ��
HMIDIOUT handle; // ��Ƶ������
unsigned long result=midiOutOpen(&handle,0,0,0,CALLBACK_NULL); // ��ȡ��Ƶ������
vector<PASSENGER> passenger; // �˿�����
FLOOR flor[MAX_FLOOR_NUM+1]; // ¥��
LIFT lift[MAX_LIFT_NUM+1]; // ����
int passtime=0,passengerwaiting=0,passengerin=0,passengerout=0,totalwaitingtime=0,totalduration=0;
// passtime:��ǰʱ�� passengerwaiting:���ڵȺ�ĳ˿����� passengerin:���ڳ��ݵĳ˿����� passengerout:���뿪���ݵĳ˿�����
double averagewaitingtime,averageduration;
// totalwaitingtime:���г˿͵ȴ�������ʱ�� averagewaitingtime:�˾��ȴ�����ʱ�� totalduration:���г˿ͳ�����ʱ�� averageduration:�˾�����ʱ��

double maximum(const double x,const double y)
{
	if(x>=y)return x;
	return y;
}

double minimum(const double x,const double y)
{
	if(x<=y)return x;
	return y;
}

double average(const double x,const double y)
{
	return (x+y)/2.0;
}

double poisson(const double x,const int y)
{
	double r=exp(-x);
	int i;
	for(i=1;i<=y;i++)
	{
		r*=x;
		r/=i;
	}
	return r;
}

void calcpk(const double lambda,double pk[])
{
	double sum=0;
	int i;
	for(i=0;i<=MAX_NEW_PASSENGER;i++)
	{
		pk[i]=poisson(lambda,i);
		sum+=pk[i];
	}
	for(i=0;i<=MAX_NEW_PASSENGER;i++)
	{
		pk[i]/=sum; // ���������ֵ���Ϊ1
		if(i>0)pk[i]+=pk[i-1]; // Ϊ�����������������ֵ�ۼ�����
	}
}

int createpassenger(const int floornum,int passengernum,double pk[])
{
	int i,j;
	double pr=rand()%30000/30000.0;
	for(i=0;i<=MAX_NEW_PASSENGER;i++)
	{
		if(pk[i]>pr) // �����������ĳһ����ʱ�������Ӹ������Ӧ������
		{
			for(j=1;j<=i;j++)
			{
				int f=rand()%floornum+1,t=rand()%floornum+1;
				while(f==t) // ����Ŀ�ĵغ͡�������¥��һ��
					t=rand()%floornum+1;
				passenger.push_back(PASSENGER(f,t,passtime));
				passengernum++;
			}
			return passengernum;
		}
	}
	return passengernum;
}

int recreatepassenger(int passengernum,int add[])
{
	int i;
	for(i=passengernum; ;i++)
	{
		if(i>=passenger.size())return passengernum;
		if(passenger[i].createtime==passtime)
		{
			passenger[i].init();
			flor[passenger[i].from].lstp.push_back(passengernum);
			add[passenger[i].from]++;
			passengernum++;
		}
		else return passengernum;
	}
	return passengernum;
}

void calc(const int passengernum)
{
	passengerwaiting=passengerin=passengerout=totalwaitingtime=totalduration=0;
	int i;
	for(i=0;i<passengernum;i++)
	{
		if(!passenger[i].onlifttime)passengerwaiting++;
		else if(!passenger[i].leavetime)
		{
			passengerin++;
			totalwaitingtime+=passenger[i].onlifttime-passenger[i].createtime;
		}
		else
		{
			passengerout++;
			totalduration+=passenger[i].leavetime-passenger[i].onlifttime;
			totalwaitingtime+=passenger[i].onlifttime-passenger[i].createtime;
		}
	}
	averagewaitingtime=double(totalwaitingtime)/(passengerin+passengerout);
	if(passengerin+passengerout==0)averagewaitingtime=0;
	averageduration=double(totalduration)/passengerout;
	if(passengerout==0)averageduration=0;
}

void play(int c)
{
	if(c==0)return;
	else if(c==1)midiOutShortMsg(handle,0x007a3590);
	else if(c==2)midiOutShortMsg(handle,0x007a3790);
	else if(c==3)midiOutShortMsg(handle,0x007a3990);
	else if(c==4)midiOutShortMsg(handle,0x007a3b90);
	else if(c==5)midiOutShortMsg(handle,0x007a3C90);
	else if(c==6)midiOutShortMsg(handle,0x007a3E90);
	else if(c==7)midiOutShortMsg(handle,0x007a4090);
	else if(c==8)midiOutShortMsg(handle,0x007a4190);
	else if(c==9)midiOutShortMsg(handle,0x007a4390);
	else if(c==10)midiOutShortMsg(handle,0x007a4590);
	else if(c==11)midiOutShortMsg(handle,0x007a4790);
	else if(c==12)midiOutShortMsg(handle,0x007a4890);
	else if(c==13)midiOutShortMsg(handle,0x007a4a90);
	else if(c==14)midiOutShortMsg(handle,0x007a4c90);
	else if(c==15)midiOutShortMsg(handle,0x007a4d90);
	else if(c==16)midiOutShortMsg(handle,0x007a4f90);
}

void print(const int t,const int opt,const int floornum,const int liftnum,const int passengernum,int add[],int leave[],int onlift[])
{
	int i,j,sleeptime;
	list<int>::iterator iter;
	time_t tmptime=clock();
	if(t==1) // ���ÿ��¥�³��ֵĳ˿�������������ϵ��ݵ��������뿪������
	{
		for(i=2;i<=floornum+1;i++)
		{
			pos.X=29+10*liftnum;
			pos.Y=i;
			setcolor(NORMAL);
			SetConsoleCursorPosition(hOut,pos);
			cout<<"    ";
			pos.X=23;
			SetConsoleCursorPosition(hOut,pos);
			cout<<"    ";
			pos.X=5;
			SetConsoleCursorPosition(hOut,pos);
			if(add[floornum+2-i])
			{
				if(add[floornum+2-i]<100)cout<<setw(3)<<add[floornum+2-i];
				else cout<<setw(4)<<add[floornum+2-i];
			}
			else cout<<"    ";
		}
	}
	else // ���ÿ��¥�ϵ��ݵĳ˿��������뿪�ĳ˿�������������³��ֵĳ˿�����
	{
		for(i=2;i<=floornum+1;i++)
		{
			pos.X=5;
			pos.Y=i;
			setcolor(NORMAL);
			SetConsoleCursorPosition(hOut,pos);
			cout<<"    ";
			pos.X=29+10*liftnum;
			SetConsoleCursorPosition(hOut,pos);
			if(leave[floornum+2-i])
			{
				if(leave[floornum+2-i]<100)cout<<setw(3)<<leave[floornum+2-i];
				else cout<<setw(4)<<leave[floornum+2-i];
			}
			else cout<<"    ";
			pos.X=23;
			SetConsoleCursorPosition(hOut,pos);
			if(onlift[floornum+2-i])
			{
				if(onlift[floornum+2-i]<100)cout<<setw(3)<<onlift[floornum+2-i];
				else cout<<setw(4)<<onlift[floornum+2-i];
			}
			else cout<<"    ";
			pos.X=17;
			SetConsoleCursorPosition(hOut,pos);
			bool tup=0,tdown=0;
			for(iter=flor[floornum+2-i].lstp.begin();iter!=flor[floornum+2-i].lstp.end();iter++)
			{
				if(passenger[*iter].to>floornum+2-i)tup=1;
				else if(passenger[*iter].to<floornum+2-i)tdown=1;
				if(tup&&tdown||(tup&&i==floornum+1)||(tdown&&i==2))break;
			}
			if(tup)cout<<"��";
			else cout<<"  ";
			if(tdown)cout<<"��";
			else cout<<"  ";
		}
	}
	for(i=2;i<=floornum+1;i++) // ���ÿ��¥���ڵȺ�ĳ˿�����
	{
		pos.X=11;
		pos.Y=i;
		SetConsoleCursorPosition(hOut,pos);
		if(flor[floornum+2-i].lstp.size()<100)cout<<setw(3)<<flor[floornum+2-i].lstp.size();
		else cout<<setw(4)<<flor[floornum+2-i].lstp.size();
	}
	for(i=1;i<=liftnum;i++) // ���ÿ�����ݵ��˶�״̬�����صĳ˿�������
	{
		if(t==1&&!lift[i].formerfloor)
		{
			setcolor(NORMAL);
			pos.X=19+10*i;
			pos.Y=floornum+2-lift[i].flor;
			SetConsoleCursorPosition(hOut,pos);
			cout<<"��"<<setw(2)<<lift[i].lstp.size()<<"��  ";
		}
		else if(t==2)
		{
			setcolor(NORMAL);
			pos.X=19+10*i;
			pos.Y=floornum+2-lift[i].formerfloor;
			SetConsoleCursorPosition(hOut,pos);
			cout<<"        ";
			pos.Y=floornum+2-lift[i].flor;
			SetConsoleCursorPosition(hOut,pos);
			if(lift[i].flor==lift[i].formerfloor)
			{
				setcolor(OPEN);
				cout<<"��"<<setw(2)<<lift[i].lstp.size()<<"���_";
				setcolor(BUTTON);
				for(j=1;j<=floornum;j++)
				{
					if(lift[i].flor==j)continue;
					if(lift[i].stop[j])
					{
						pos.Y=floornum+2-j;
						SetConsoleCursorPosition(hOut,pos);
						cout<<setw(5)<<j;
					}
				}
			}
			else if(lift[i].flor<lift[i].formerfloor)
			{
				setcolor(DOWN);
				cout<<"��"<<setw(2)<<lift[i].lstp.size()<<"����";
			}
			else
			{
				setcolor(UP);
				cout<<"��"<<setw(2)<<lift[i].lstp.size()<<"����";
			}
			setcolor(NORMAL);
		}
	}
	pos.X=0;
	pos.Y=floornum+3;
	SetConsoleCursorPosition(hOut,pos); // �����ǰʱ�������
	setcolor(INFO);
	cout<<"   ��ǰ�㷨��"<<setw(7)<<opt<<"   ";
	cout<<"     ��ǰʱ�䣺"<<setw(9)<<passtime<<" s  ";
	cout<<"�˿���������"<<setw(9)<<passengernum<<"  ";
	cout<<"    �Ⱥ���������"<<setw(9)<<passengerwaiting<<"  ";
	cout<<"  ������������"<<setw(6)<<passengerin<<"��    ";
	cout<<"  �뿪��������"<<setw(6)<<passengerout<<"  "<<endl;
	cout<<" �ܵȺ�ʱ�䣺"<<setw(7)<<totalwaitingtime<<" s  ";
	cout<<"�˾��Ⱥ�ʱ�䣺"<<setw(9)<<averagewaitingtime<<" s  ";
	cout<<"�ܳ���ʱ�䣺"<<setw(9)<<totalduration<<" s  ";
	cout<<"�˾�����ʱ�䣺"<<setw(9)<<averageduration<<" s  ";
	cout<<"ÿ�������ؿ�������"<<setw(9)<<SECONDS_PER_HOUR*passengerout/liftnum/passtime<<" ��/Сʱ                  ";
	setcolor(NORMAL);
	//play(rand()%17);
	sleeptime=100*t-clock()+tmptime;
	if(sleeptime>0)Sleep(sleeptime); // ��ͣ��һ��
}

void goonlift(const int liftid,const int floorid,const int passengerid,int onlift[],list<int>::iterator iter)
{
	passenger[passengerid].onlifttime=passtime;
	lift[liftid].lstp.push_back(passengerid); // ���ó˿ͼ�����ݵĳ˿�������
	lift[liftid].stop[passenger[passengerid].to]=1;
	onlift[floorid]++;
	flor[floorid].lstp.erase(iter); // ���ó˿ʹӸ�¥��ĵȴ�������ɾ��
}

void operate(const int t,const int floornum,const int liftnum,const int maxload,int onlift[],int leave[])
{
	// ���������㷨����Ϊ��1���ڣ�����Ҫô���ϣ�Ҫô���£�Ҫô����
	// ���������㷨�����������ڵ�¥���г˿�Ҫ�뿪�����뿪�ŷ���
	// �㷨1�����Ⱥ�ĳ˿͵�Ŀ�ĵ�������ڵĳ˿͵�Ŀ�ĵ����ظ�ʱ�����ߵȺ��ߵ�Ŀ�ĵظ�Զʱ��������ͣ�����˵ĵ��ݲ������ó˿ͽ���
	// �㷨2��ֻҪ�˿͵�Ŀ�ĵط�����/�£�����ݵ��˶�����һ�£��������ó˿ͽ���
	// �㷨3��ֻҪ�г˿��ڵȺ������˶����򣬶������ó˿ͽ���
	// �㷨4���ڿ��ŵ�ѡ���Ϻ��㷨2һ�£���֮ͬ���������۵����Ƿ����˶��ϵ������µ���ײ�ŷ���
	int i,j,k,target[MAX_FLOOR_NUM+1]={0},fartarget;
	bool opendoor[MAX_LIFT_NUM+1]={0},move[MAX_LIFT_NUM+1]={0}; // opendoor��ǵ����Ƿ��ţ�move��ǵ����Ƿ��ƶ�
	list<int>::iterator iter,iter2;
	for(i=1;i<=floornum;i++)
		onlift[i]=leave[i]=0;
	for(i=1;i<=liftnum;i++)
		lift[i].formerfloor=lift[i].flor;
	if(t==4&&passtime==1) // �㷨4��ֱ��ֱ��
	{
		for(i=1;i<=liftnum;i++)
			if(i%2)lift[i].target=floornum;
			else lift[i].target=1;
	}
	for(i=1;i<=liftnum;i++) // ���������г˿��ڸò�¥��Ҫ�뿪ʱ��������
	{
		j=lift[i].flor;
		if(lift[i].stop[j])
		{
			opendoor[i]=1;
			lift[i].stop[j]=0;
			for(iter=lift[i].lstp.begin();iter!=lift[i].lstp.end(); )
			{
				k=*iter;
				iter2=iter;
				iter++;
				if(passenger[k].to==j)
				{
					passenger[k].leavetime=passtime;
					lift[i].lstp.erase(iter2);
					leave[j]++;
				}
			}
			if(t!=4) // ���㷨4��������ʱû��Ŀ��¥��
			{
				if(lift[i].lstp.empty())lift[i].target=0;
				else if(lift[i].target==j)
				{
					lift[i].target=0;
					for(iter=lift[i].lstp.begin();iter!=lift[i].lstp.end();iter++)
					{
						k=*iter;
						if(!lift[i].target)lift[i].target=passenger[k].to;
						else if(abs(passenger[k].to-j)>abs(lift[i].target-j))lift[i].target=passenger[k].to;
					}
				}
			}
		}
	}
	for(i=1;i<=liftnum;i++) // ������Ϊ���������ڵ�������¥��Ⱥ�ʱ�������ó˿ͽ���
	{
		if(t==4&&lift[i].lstp.empty()&&!flor[lift[i].flor].lstp.empty()) // �㷨4����ͬ��ĳ˿ͽ���
		{
			j=lift[i].flor;
			for(iter=flor[j].lstp.begin();iter!=flor[j].lstp.end(); )
			{
				k=*iter;
				iter2=iter;
				iter++;
				if((passenger[k].to-j)*(lift[i].target-j)>0)
				{
					goonlift(i,j,k,onlift,iter2);
				}
				if(lift[i].lstp.size()>=maxload)break;
			}
		}
		else if(lift[i].lstp.empty()&&!flor[lift[i].flor].lstp.empty()) // ���㷨4����ͬһ�������ĳ˿ͽ���
		{
			int upnum=0,up2=0,downnum=0,down2=0;
			j=lift[i].flor;
			for(iter=flor[j].lstp.begin();iter!=flor[j].lstp.end();iter++)
			{
				k=*iter;
				if(passenger[k].to>j)
				{
					upnum++;
					up2+=passenger[k].to-j;
				}
				else
				{
					downnum++;
					down2+=j-passenger[k].to;
				}
			}
			if(upnum>downnum||(upnum==downnum&&up2>down2))
			{
				fartarget=0;
				for(iter=flor[j].lstp.begin();iter!=flor[j].lstp.end(); )
				{
					k=*iter;
					iter2=iter;
					iter++;
					if(passenger[k].to>j&&lift[i].lstp.size()<maxload)
					{
						goonlift(i,j,k,onlift,iter2);
						if(passenger[k].to>fartarget)fartarget=passenger[k].to;
					}
					if(lift[i].lstp.size()==maxload)break;
				}
				if(fartarget>lift[i].target||!lift[i].target)lift[i].target=fartarget;
			}
			else
			{
				fartarget=MAX_FLOOR_NUM;
				for(iter=flor[j].lstp.begin();iter!=flor[j].lstp.end(); )
				{
					k=*iter;
					iter2=iter;
					iter++;
					if(passenger[k].to<j&&lift[i].lstp.size()<maxload)
					{
						goonlift(i,j,k,onlift,iter2);
						if(passenger[k].to<fartarget)fartarget=passenger[k].to;
					}
					if(lift[i].lstp.size()>=maxload)break;
				}
				if(fartarget<lift[i].target||!lift[i].target)lift[i].target=fartarget;
			}
			if(t==3&&lift[i].lstp.size()<maxload&&!flor[j].lstp.empty()) // �㷨3��������ĳ˿�Ҳ����
			{
				for(iter=flor[j].lstp.begin();iter!=flor[j].lstp.end(); )
				{
					k=*iter;
					iter2=iter;
					iter++;
					goonlift(i,j,k,onlift,iter2);
					if(lift[i].lstp.size()>=maxload)break;
				}
			}
			opendoor[i]=1;
		}
	}
	for(i=1;i<=liftnum;i++) // ���յ���֮ǰû�п���ʱ���˶�ȥ����¥��
	{
		if(t==4&&!opendoor[i]&&lift[i].lstp.empty()) // �㷨4��ֱ��ֱ��
		{
			if(lift[i].target>lift[i].flor)
			{
				lift[i].flor++;
				move[i]=1;
				if(lift[i].flor==floornum)lift[i].target=1;
			}
			else
			{
				lift[i].flor--;
				move[i]=1;
				if(lift[i].flor==1)lift[i].target=floornum;
			}
		}
		else if(!opendoor[i]&&lift[i].lstp.empty()) // ���㷨4����������¥��Ⱥ�ĳ˿����ѡ�����ϻ�����
		{
			k=0;
			for(j=1;j<=floornum;j++)
			{
				if(!flor[j].lstp.empty()&&target[j]<2)
				{
					if(!k)k=j;
					else if(abs(lift[i].flor-j)<abs(lift[i].flor-k))k=j;
				}
			}
			lift[i].target=k;
			target[k]++;
			if(lift[i].target>lift[i].flor||(!lift[i].target&&floornum/2+1>lift[i].flor))
			{
				lift[i].flor++;
				move[i]=1;
			}
			else if((lift[i].target&&lift[i].target<lift[i].flor)||(!lift[i].target&&floornum/2+1<lift[i].flor))
			{
				lift[i].flor--;
				move[i]=1;
			}
			else
			{
				move[i]=0;
			}
		}
	}
	for(i=1;i<=liftnum;i++) // �ǿյ���ѡ���Ż����ƶ�
	{
		j=lift[i].flor;
		if(!move[i]&&!lift[i].lstp.empty())
		{
			if(!flor[j].lstp.empty()&&lift[i].lstp.size()<maxload)
			{
				for(iter=flor[j].lstp.begin();iter!=flor[j].lstp.end(); )
				{
					k=*iter;
					iter2=iter;
					iter++;
					if(t==1)
					{
						if(lift[i].stop[passenger[k].to]&&lift[i].lstp.size()<maxload)
						{
							goonlift(i,j,k,onlift,iter2);
							opendoor[i]=1;
						}
					}
					else
					{
						if((passenger[k].to-j)*(lift[i].target-j)>0&&lift[i].lstp.size()<maxload)
						{
							goonlift(i,j,k,onlift,iter2);
							opendoor[i]=1;
							if((passenger[k].to-lift[i].target)*(lift[i].target-j)>0)lift[i].target=passenger[k].to;
						}
					}
					if(lift[i].lstp.size()>=maxload)break;
				}
				if(t==1&&lift[i].lstp.size()<maxload&&opendoor[i])
				{
					for(iter=flor[j].lstp.begin();iter!=flor[j].lstp.end(); )
					{
						k=*iter;
						iter2=iter;
						iter++;
						if(((passenger[k].to-lift[i].target)*(lift[i].target-j)>0)&&lift[i].lstp.size()<maxload)
						{
							goonlift(i,j,k,onlift,iter2);
							opendoor[i]=1;
							lift[i].target=passenger[k].to;
						}
						if(lift[i].lstp.size()>=maxload)break;
					}
				}
				else if(t==3&&lift[i].lstp.size()<maxload&&opendoor[i]&&!flor[j].lstp.empty())
				{
					for(iter=flor[j].lstp.begin();iter!=flor[j].lstp.end(); )
					{
						k=*iter;
						iter2=iter;
						iter++;
						goonlift(i,j,k,onlift,iter2);
						opendoor[i]=1;
						if((passenger[k].to-lift[i].target)*(lift[i].target-j)>0)lift[i].target=passenger[k].to;
						if(lift[i].lstp.size()>=maxload)break;
					}
				}
			}
		}
		if(!move[i]&&!opendoor[i]&&!lift[i].lstp.empty())
		{
			if(lift[i].target==j)
			{
				if(t==4)
				{
					if(lift[i].target==1)lift[i].target=floornum;
					else lift[i].target=1;
				}
				else
				{
					for(iter=lift[i].lstp.begin();iter!=lift[i].lstp.end();iter++)
					{
						k=*iter;
						if(abs(passenger[k].to-j)>abs(lift[i].target-j))lift[i].target=passenger[k].to;
					}
				}
			}
			if(lift[i].target>j)
			{
				lift[i].flor++;
				move[i]=1;
				if(lift[i].flor==floornum)lift[i].target=1;
			}
			else if(lift[i].target<j)
			{
				lift[i].flor--;
				move[i]=1;
				if(lift[i].flor==1)lift[i].target=floornum;
			}
			else
			{
				move[i]=0;
			}
		}
	}
}

void setcolor(const int i)
{
	if(i==NORMAL)SetConsoleTextAttribute(hOut,FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);// �ڵװ���
	else if(i==INFO)SetConsoleTextAttribute(hOut,BACKGROUND_INTENSITY|BACKGROUND_GREEN|BACKGROUND_RED|BACKGROUND_BLUE);// �׵׺���
	else if(i==BLANK)SetConsoleTextAttribute(hOut,BACKGROUND_GREEN|BACKGROUND_RED);// �ص׺���
	else if(i==DOWN)SetConsoleTextAttribute(hOut,BACKGROUND_INTENSITY|BACKGROUND_BLUE|FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);// ���װ���
	else if(i==UP)SetConsoleTextAttribute(hOut,BACKGROUND_INTENSITY|BACKGROUND_RED|FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);// ��װ���
	else if(i==OPEN)SetConsoleTextAttribute(hOut,BACKGROUND_GREEN|FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);// �̵װ���
	else if(i==BUTTON)SetConsoleTextAttribute(hOut,FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED);// �ڵ׻���
	else if(i==TABLE)SetConsoleTextAttribute(hOut,BACKGROUND_BLUE|BACKGROUND_RED|FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);// �ϵװ���
}

void clearscreen(const int floornum,const int liftnum,const int maxload,const double lambda)
{
	system("cls");
	pos.X=pos.Y=0;
	SetConsoleCursorPosition(hOut,pos);
	setcolor(NORMAL);
	cout<<" ��";
	setcolor(BLANK);
	cout<<"��";
	setcolor(NORMAL);
	cout<<"����";
	setcolor(BLANK);
	cout<<"��";
	setcolor(NORMAL);
	cout<<"�Ⱥ�";
	setcolor(BLANK);
	cout<<"��";
	setcolor(NORMAL);
	cout<<"��ť";
	setcolor(BLANK);
	cout<<"��";
	setcolor(NORMAL);
	cout<<"����";
	setcolor(BLANK);
	cout<<"��";
	int i,j;
	for(i=1;i<=liftnum;i++)
	{
		setcolor(NORMAL);
		cout<<" ����"<<setw(2)<<i<<" ";
		setcolor(BLANK);
		cout<<"��";
	}
	setcolor(NORMAL);
	cout<<"�뿪"<<endl;
	setcolor(BLANK);
	for(i=1;i<=33+10*liftnum;i++)
		cout<<"-";
	setcolor(NORMAL);
	cout<<endl;
	for(i=floornum;i>=1;i--)
	{
		cout<<" "<<setw(2)<<i;
		setcolor(BLANK);
		cout<<"��";
		setcolor(NORMAL);
		cout<<"    ";
		setcolor(BLANK);
		cout<<"��";
		setcolor(NORMAL);
		cout<<"    ";
		setcolor(BLANK);
		cout<<"��";
		setcolor(NORMAL);
		cout<<"    ";
		setcolor(BLANK);
		cout<<"��";
		setcolor(NORMAL);
		cout<<"    ";
		setcolor(BLANK);
		cout<<"��";
		for(j=1;j<=liftnum;j++)
		{
			setcolor(NORMAL);
			cout<<"        ";
			setcolor(BLANK);
			cout<<"��";
		}
		setcolor(NORMAL);
		cout<<endl;
	}
	setcolor(BLANK);
	for(i=1;i<=33+10*liftnum;i++)
		cout<<"-";
	setcolor(NORMAL);
	cout<<endl;
	setcolor(INFO);
	for(i=1;i<=SCREEN_WIDTH*2;i++)
		cout<<" ";
	cout<<"     �ܲ�����"<<setw(7)<<floornum<<"  ";
	cout<<"      ����������"<<setw(9)<<liftnum<<"  ";
	cout<<"    ����أ�"<<setw(9)<<maxload<<"  ";
	cout<<"    ���ɲ����ˣ�"<<setw(9)<<lambda<<"  ";
	cout<<"  ���ճ˿�������"<<setw(6)<<passenger.size()<<"  ";
	cout<<"    ��ģ��ʱ�䣺"<<setw(6)<<MAX_PASSTIME<<" s                   ";
	setcolor(NORMAL);
}

int main()
{
	int passengernum=0,liftnum,floornum,maxload,i,j,k,opt,maxtwt,mintwt,maxtd,mintd,maxpass,minpass,order[5]={0,1,2,3,4};
	int totalwt[5],totald[5],passout[5],add[MAX_FLOOR_NUM+1]={0},leave[MAX_FLOOR_NUM+1],onlift[MAX_FLOOR_NUM+1];
	// passengernum:��ǰ���ֹ��ĳ˿������� liftnum:�������� floornum:¥������ maxload:����� opt:ѡ����㷨
	// maxtwt:��ܵȴ�ʱ�� mintwt:����ܵȴ�ʱ�� maxtd:��ܳ���ʱ�� mintd:����ܳ���ʱ�� maxpass:����ܿ����� minpass:��С�ܿ�����
	// order:�����㷨�������� totalwt:�����㷨���ܵȴ�ʱ�� totald:�����㷨���ܳ���ʱ�� passout:�����㷨���ܿ�����
	// add:ĳһ�����¥�³��ֵĳ˿����� leave:ĳһ�����¥�뿪���ݵĳ˿����� onlift:ĳһ�����¥�ϵ��ݵĳ˿�����
	double lambda,avgwt[5],avgd[5],passperhour[5],avgtwt,avgtd,avgpass,avgawt,avgad,avgpph,maxawt,minawt,maxad,minad,maxpph,minpph;
	double pk[MAX_NEW_PASSENGER+1];
	// lambda:���ɲ����� avgwt:�����㷨���˾��ȴ�ʱ�� avgd:�����㷨���˾�����ʱ�� passperhour:�����㷨��ÿ�����ݵ�λʱ���ؿ����� pk:�³��ֵĳ˿����ĸ�����ֵ
	// avgtwt:ƽ���ܵȴ�ʱ�� avgtd:ƽ���ܳ���ʱ�� avgpass:ƽ���ܿ����� avgawt:ƽ���˾��ȴ�ʱ�� avgad:ƽ���˾�����ʱ�� avgpph:ƽ���ؿ�����
	// max_/min_:��һ�и����ݵ����/��Сֵ
	time_t starttime;
	srand(unsigned(time(0))); // ��ʼ���������
	hOut=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitle("����ģ����"); // �趨���ڱ���
	COORD size={SCREEN_WIDTH,SCREEN_HEIGHT};
	SetConsoleScreenBufferSize(hOut,size);
	SMALL_RECT rc={0,0,WINDOW_WIDTH,WINDOW_HEIGHT};
	SetConsoleWindowInfo(hOut,true,&rc); // �趨���ڴ�С
	HWND hwnd=GetForegroundWindow();
	ShowWindow(hwnd,SW_MAXIMIZE); // ������
	cout<<setprecision(7);
	cout<<"���������������(5-20)���ܵ�����(1-13)����¥����(2-40)�����ɹ��̲�����(0.1-20)\n";
	cin>>maxload>>liftnum>>floornum>>lambda; // ������������ء�����������¥�����������ɹ��̲�����
	CONSOLE_CURSOR_INFO ConsoleCursorInfo;
    GetConsoleCursorInfo(hOut,&ConsoleCursorInfo);
    ConsoleCursorInfo.bVisible=false;
    SetConsoleCursorInfo(hOut,&ConsoleCursorInfo); // �趨����ʾ���
	if(maxload<MIN_MAXLOAD||maxload>MAX_MAXLOAD||liftnum<MIN_LIFT_NUM||liftnum>MAX_LIFT_NUM||floornum<MIN_FLOOR_NUM||floornum>MAX_FLOOR_NUM||lambda<MIN_LAMBDA||lambda>MAX_LAMBDA)
	{
		cout<<"���ݲ����ʣ���������һ����Զ��˳�����"; // ���ݳ�����Χ�����벻�淶
		Sleep(1000);
		return 0;
	}
	cout<<endl<<"�����������ݣ����Ժ�......"<<endl;
	calcpk(lambda,pk); // ���������ֵ
	while(passtime<MAX_PASSTIME)
	{
		passtime++;
		passengernum=createpassenger(floornum,passengernum,pk); // ���ɳ˿���
	}
	cout<<endl<<"���ڿ���ģ�⣬���Ժ�......"<<endl;
	starttime=clock();
	for(i=1;i<=8;i++) // i<=4ʱΪ�����㷨�Ŀ���ģ�⣬i>=5ʱΪ�����㷨���ŵ��ӵ���ʾ
	{
		for(j=1;j<=liftnum;j++)
		{
			lift[j].init();
			lift[j].flor=floornum/2+1;
		}
		for(j=1;j<=floornum;j++)
			flor[j].init();
		passtime=passengernum=passengerwaiting=passengerin=passengerout=totalwaitingtime=totalduration=0;
		if(i<=4)opt=i;
		else opt=order[i-4];
		while(passtime<MAX_PASSTIME)
		{
			if(i<=4&&clock()-starttime>8000) // ��ǰ����ʱ���������ڲ����ڴ˴���
			{
				cout<<endl<<"���ݲ����ʣ���������һ����Զ��˳�����"<<endl;
				Sleep(1000);
				return 0;
			}
			passtime++;
			for(j=1;j<=floornum;j++)
				add[j]=0;
			passengernum=recreatepassenger(passengernum,add); // �������ɳ˿���
			if(i>=5)
			{
				calc(passengernum);
				print(1,opt,floornum,liftnum,passengernum,add,leave,onlift); // ��ʾʱ�������
			}
			operate(opt,floornum,liftnum,maxload,onlift,leave); // ���ȵ���
			if(i>=5)
			{
				calc(passengernum);
				print(2,opt,floornum,liftnum,passengernum,add,leave,onlift); // ��ʾʱ�������
			}
		}
		calc(passengernum);
		if(i<=4)
		{
			passout[i]=passengerout;
			passperhour[i]=SECONDS_PER_HOUR*passengerout/liftnum/passtime;
			totalwt[i]=totalwaitingtime;
			totald[i]=totalduration;
			avgwt[i]=averagewaitingtime;
			avgd[i]=averageduration;
		}
		if(i==4) // ���������������ֵ������ֵ��ƽ��ֵ�������ݸ����㷨���ؿ����Ը����㷨������������
		{
			for(j=1;j<=4;j++)
				for(k=j+1;k<=4;k++) // ���㷨���ӽ��������������ݹ�ģ��С���Բ���ð�ݷ���
				{
					if(passout[order[j]]<passout[order[k]]||(passout[order[j]]==passout[order[k]]&&avgwt[order[j]]+avgd[order[j]]>avgwt[order[k]]+avgd[order[k]]))
					{
						order[j]^=order[k];
						order[k]^=order[j];
						order[j]^=order[k];
					}
				}
			// ��������ݵ�ƽ��ֵ�����ֵ����Сֵ
			avgpass=average(average(passout[1],passout[2]),average(passout[3],passout[4]));
			avgtwt=average(average(totalwt[1],totalwt[2]),average(totalwt[3],totalwt[4]));
			avgtd=average(average(totald[1],totald[2]),average(totald[3],totald[4]));
			avgawt=average(average(avgwt[1],avgwt[2]),average(avgwt[3],avgwt[4]));
			avgad=average(average(avgd[1],avgd[2]),average(avgd[3],avgd[4]));
			avgpph=average(average(passperhour[1],passperhour[2]),average(passperhour[3],passperhour[4]));
			maxtwt=maximum(maximum(totalwt[1],totalwt[2]),maximum(totalwt[3],totalwt[4]));
			maxtd=maximum(maximum(totald[1],totald[2]),maximum(totald[3],totald[4]));
			maxawt=maximum(maximum(avgwt[1],avgwt[2]),maximum(avgwt[3],avgwt[4]));
			maxad=maximum(maximum(avgd[1],avgd[2]),maximum(avgd[3],avgd[4]));
			maxpph=maximum(maximum(passperhour[1],passperhour[2]),maximum(passperhour[3],passperhour[4]));
			mintwt=minimum(minimum(totalwt[1],totalwt[2]),minimum(totalwt[3],totalwt[4]));
			mintd=minimum(minimum(totald[1],totald[2]),minimum(totald[3],totald[4]));
			minawt=minimum(minimum(avgwt[1],avgwt[2]),minimum(avgwt[3],avgwt[4]));
			minad=minimum(minimum(avgd[1],avgd[2]),minimum(avgd[3],avgd[4]));
			minpph=minimum(minimum(passperhour[1],passperhour[2]),minimum(passperhour[3],passperhour[4]));
		}
		if(i==1)
		{
			maxpass=minpass=passengerout;
		}
		else if(i==2||i==3||i==4)
		{
			if(passengerout>maxpass)
			{
				maxpass=passengerout;
			}
			else if(passengerout<minpass)
			{
				minpass=passengerout;
			}
		}
		if(i>=4)
		{
			if(i!=4)
			{
				setcolor(INFO);
				pos.X=43;
				pos.Y=17;
				SetConsoleCursorPosition(hOut,pos);
				for(j=1;j<=72;j++)
					cout<<" ";
				pos.Y+=2;
				SetConsoleCursorPosition(hOut,pos);
				for(j=1;j<=72;j++)
					cout<<" ";
				pos.Y--;
				if(i==8)
				{
					for(j=3;j>=1;j--)
					{
						SetConsoleCursorPosition(hOut,pos);
						cout<<"         "<<j<<"     ��    ��    ��    ��    ��    ��    ��    ��             ";
						Sleep(1000);
					}
					return 0;
				}
				else
				{
					for(j=3;j>=1;j--)
					{
						SetConsoleCursorPosition(hOut,pos);
						cout<<"         "<<j<<"     ��    ��    ģ    ��    ��    һ    ��    ��    ��       ";
						Sleep(1000);
					}
				}
			}
			setcolor(NORMAL);
			clearscreen(floornum,liftnum,maxload,lambda);
			setcolor(TABLE);
			for(j=1;j<=SCREEN_WIDTH;j++)
				cout<<" ";
			cout<<"             �ܿ�����       ÿ�������ؿ�����(��/Сʱ)           �ܵȺ�ʱ��(s)        �˾��Ⱥ�ʱ��(s)          �ܳ���ʱ��(s)        �˾�����ʱ��(s)                      ";
			for(j=1;j<=4;j++)
				cout<<"  �㷨"<<j<<"  "<<setw(12)<<passout[j]<<"                "<<setw(12)<<passperhour[j]<<"              "<<setw(12)<<totalwt[j]<<"           "<<setw(12)<<avgwt[j]<<"           "<<setw(12)<<totald[j]<<"           "<<setw(12)<<avgd[j]<<"                        ";
			cout<<"  ƽ��ֵ "<<setw(12)<<avgpass<<"                "<<setw(12)<<avgpph<<"              "<<setw(12)<<avgtwt<<"           "<<setw(12)<<avgawt<<"           "<<setw(12)<<avgtd<<"           "<<setw(12)<<avgad<<"                        ";
			cout<<"  ����ֵ "<<setw(12)<<maxpass<<"                "<<setw(12)<<maxpph<<"              "<<setw(12)<<mintwt<<"           "<<setw(12)<<minawt<<"           "<<setw(12)<<mintd<<"           "<<setw(12)<<minad<<"                        ";
			cout<<"  ����ֵ "<<setw(12)<<minpass<<"                "<<setw(12)<<minpph<<"              "<<setw(12)<<maxtwt<<"           "<<setw(12)<<maxawt<<"           "<<setw(12)<<maxtd<<"           "<<setw(12)<<maxad<<"                        ";
			for(j=1;j<=SCREEN_WIDTH;j++)
				cout<<" ";
			setcolor(NORMAL);
		}
	}
	return 0;
}
