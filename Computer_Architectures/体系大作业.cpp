/*
Main.cpp
���ߣ����Ӻ� ��� ������

�������̣�
1.��instruction.txt�ж�ȡUnicore32ָ��
2.����asm2bin.h�еĺ����������ָ��ת�ɶ�����ָ���������ָ��洢����
3.��ȡָ->����->ִ��->�ô�->д�ص�˳������ˮ�߽ṹ������ָ��
 (1)ÿ��ʱ�����ڣ��ֱ𴴽�һ��ȡָ�̡߳�һ�������̡߳�һ��ִ���̡߳�һ���ô��̺߳�һ����д�̣߳�Ȼ��ȴ�������̶߳������󣬲Ž�����һ��ʱ������ 
 (2)ȡָ�̶߳�ָ��洢����PC�Ĵ����ĵ�ַ����ȡָ
 	�ٰ�PC�Ĵ����ĵ�ַ����ȡָ
	�����ȡ����ָ����0xFFFFFFFF������һ���ڲ���ȡָ�����ٽ�����һ��
	�������ǰִ�е�ָ�����תָ���δ�ж��Ƿ���תָ������PC+4����
 (3)�����̶߳���һʱ������ȡ��ָ�����еĻ�����������
	��ָ��ĸ�8λΪ������
	�ڸ��ݲ�����ȷ��state��ֵ���������ڵ�ִ�з�ʽ���Ƿ�ô桢�Ƿ�ȡָ
 (4)ִ���̸߳�����һ���ڶ�ָ������Ľ���������R�͡�I�͡���ȡ����֧����ת�ȣ�ִ��ָ��
	���ȶ�ȡ�Ĵ�����ֵ
    ��ִ��R��ָ������Ҫ��λ��ִ����λ������Ǽ�����Բ�����2ȡ����1��֮����ݲ�����ȷ��ALU��opֵ��Ȼ����ALU���м���
	��ִ��I��ָ��ȶ�������������չ��Ȼ����λ���ٸ��ݲ�����ȷ��ALU��opֵ��setflagλ��Ȼ����ALU���м���
	��ִ�д�ȡָ������rs2���������λ�������imm14���������չ��������ALU�����ַ
	��ִ��BEQָ����ZλΪ1����PC��ֵ���PC+4+offset��������ָ���Ϊ��תָ����ZλΪ0���޲���
	��ִ��Bָ���PC��ֵ���PC+4+offset��������ָ���Ϊ��תָ��
	��ִ��JUMPָ���PC��ֵ���rs2�Ĵ�����ֵ��������ָ���Ϊ��תָ��
 (5)�ô��̶߳���һ���ڵĴ�ȡָ����зô��д����
    ���ж��Ƕ��洢������д�洢��
	�ڷ���Cache��ͨ��Cache���ʴ洢��
 (6)д���̶߳���������ִ�е�ָ����Ҫ��д���������Ҫ�Ļ���
 (7)�����ʱ������ִ�е�ָ�������ת������һ���ڲ����������ִ�У��൱��ֹͣ��˳��ִ�е�ָ���ִ�У�
 (8)��ӡ��Ϣ
*/
 
#include "types.h" // �����˼Ĵ����ѡ��洢����Cache��ALU����չ������λ������
#include "asm2bin.h" // ���ת�����Ƶĺ���

#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <windows.h>

#define INSTRUCTION_FILE_NAME "instruction.txt"
#define STRING_MAXLENGTH 1024

using namespace std;

vector<string> vasm; // ��������Ļ��ָ��
vector<unsigned> vins; // ������ָ���Ӧ�Ķ�����ָ��
vector<LABEL> vlabel,vbi; // ������ת��ŵĵ�ַ
int clock=0; // ʱ������

REGISTER_FILE regf; // �Ĵ�����
PC pc; // PC�Ĵ���
ALU alu; // ALU
ADDER adder; // �ӷ���
MEMORY insmemory(IMEM_SIZE),datamemory(DMEM_SIZE); // ָ��洢�������ݴ洢��
EXTENDER extender; // ��չ��
SHIFTER shifter; // ��λ��
CACHE cache(&datamemory); // ���ݴ洢����Cache

HANDLE mutex_pc=CreateSemaphore(NULL,1,1,NULL); // ���̱߳����PC�Ĵ������ź���
HANDLE mutex_cpi=CreateSemaphore(NULL,1,1,NULL);

void InputInstructions();
void ParseInstruction(string instruction);
void ParseBInstruction();
void LoadInstructions();

int state[5][5]={{0,-1,-1,-1,-1},{0,0,-1,-1,-1},{0,0,0,-1,-1},{0,0,0,0,-1},{0,0,0,0,0}}; // ��һ���ڸ��̵߳�״̬���Ƿ���Ҫ��ĳһ����/��Ҫ��β�����
unsigned instructions[5]={0}; // ĳһ����ȡ��ָ��
unsigned pctemp[5]={0}; // ĳһ����ȡָʱ��PC�Ĵ���ֵ
unsigned cachetemp[5][2]={0}; // ĳһ���ڷô�ĵ�ַ������
unsigned regwritetemp[5][3]={0}; // ĳһ����ִ�л�ô���޸ĵļĴ����Ľ��
bool isjumpins=false; // ִ�е�ָ���Ƿ���ת
bool wbtemp[5]={0}; // д�صĽ��

unsigned cpiwithcache=0; // ʹ��Cache��CPI
unsigned cpiwithoutcache=0; // ��ʹ��Cache��CPI
unsigned execins=0;

DWORD WINAPI FetchInstructions(LPVOID lpParam);
DWORD WINAPI Decode(LPVOID lpParam);
DWORD WINAPI Execute(LPVOID lpParam);
DWORD WINAPI VisitCache(LPVOID lpParam);
DWORD WINAPI WriteBack(LPVOID lpParam);

void ExecRIns(unsigned instruction);
void ExecIIns(unsigned instruction);
void ExecSL(unsigned instruction);
void ExecBeq(unsigned instruction);
void ExecB(unsigned instruction);
void ExecJump(unsigned instruction);

// ��instruction.txt������ָ��
void InputInstructions()
{
	ifstream fin;
	fin.open(INSTRUCTION_FILE_NAME);
	char instruction[STRING_MAXLENGTH];
	while(fin.getline(instruction,STRING_MAXLENGTH))
	{
		ParseInstruction(instruction);
	}
	fin.close();
}

inline bool isSplit(char c)
{
	return c==' '||c==','||c=='<'||c=='>'||c=='+'||c=='['||c==']'||c=='#';
}

// ���������ָ��Ĳ�������asm2bin.h�ĺ���ת���ɶ�����
void ParseInstruction(string instruction)
{
	int length=instruction.length();
	int i;
	bool islabel=false;
	string params[8];
	string inscopy=instruction;
	if(length==0)
	{
		return;
	}
	for(i=0;i<length;i++)
	{
		if(isSplit(instruction[i]))
		{
			instruction[i]=' ';
		}
		else if(instruction[i]==':')
		{
			islabel=true;
			break;
		}
	}
	if(!islabel)
	{
		stringstream ss;
		unsigned ins;
		i=0;
		ss<<instruction;
		while(ss>>params[i])
		{
			i++;
		}
		string operation=params[0];
		if(params[0]=="ADD")
		{
			ins=ADD2BinCode(i,params);
		}
		else if(params[0]=="SUB")
		{
			ins=SUB2BinCode(i,params);
		}
		else if(params[0]=="MUL")
		{
			ins=MUL2BinCode(i,params);
		}
		else if(params[0]=="AND")
		{
			ins=AND2BinCode(i,params);
		}
		else if(params[0]=="OR")
		{
			ins=OR2BinCode(i,params);
		}
		else if(params[0]=="MOV")
		{
			ins=MOV2BinCode(i,params);
		}
		else if(params[0]=="LDB")
		{
			ins=LDB2BinCode(i,params);
		}
		else if(params[0]=="LDW")
		{
			ins=LDW2BinCode(i,params);
		}
		else if(params[0]=="STB")
		{
			ins=STB2BinCode(i,params);
		}
		else if(params[0]=="STW")
		{
			ins=STW2BinCode(i,params);
		}
		else if(params[0]=="CMPSUB.A")
		{
			ins=CMPSUBA2BinCode(i,params);
		}
		else if(params[0]=="BEQ")
		{
			string label=params[1];
			vbi.push_back(LABEL(vins.size(),label));
			ins=BEQ2BinCode(i,params);
		}
		else if(params[0]=="B")
		{
			string label=params[1];
			vbi.push_back(LABEL(vins.size(),label));
			ins=B2BinCode(i,params);
		}
		else if(params[0]=="JUMP")
		{
			ins=JUMP2BinCode(i,params);
		}
		else return;
		vins.push_back(ins);
		vasm.push_back(inscopy);		
	}
	else
	{
		int j=-1,k;
		for(k=0;k<length;k++)
		{
			if(j==-1&&((instruction[k]>='a'&&instruction[k]<='z')||(instruction[k]>='A'&&instruction[k]<='Z')||(instruction[k]>='0'&&instruction[k]<='9')||instruction[k]=='_'))
			{
				j=k;
			}
			else if(instruction[k]==':')
			{
				break;
			}
		}
		vlabel.push_back(LABEL(vins.size(),instruction.substr(j,k-j)));
		ParseInstruction(instruction.substr(i+1,instruction.length()-i-1));
	}
}

// �����֧����תָ��ĵ�ַ
void ParseBInstructions()
{
	int i,j;
	for(i=0;i<vbi.size();i++)
	{
		for(j=0;j<vlabel.size();j++)
		{
			if(vbi[i].name==vlabel[j].name)
			{
				break;
			}
		}
		int index=vbi[i].pos;
		int imm24=(vlabel[j].pos-index)*4-4;
		vins[index]|=SignedInt(imm24,24);
	}
}

// ��������ָ�����ָ��洢��
void LoadInstructions()
{
	int i;
	cout<<"ָ��:"<<endl;
	for(i=0;i<vins.size();i++)
	{
		insmemory.addr=i*4;
		insmemory.data=vins[i];
		insmemory.Write(4);
		printf("0x%08X : ",i*4);
		BinOut(vins[i]);
		cout<<vasm[i]<<endl;
	}
	insmemory.addr=i*4;
	insmemory.data=0xFFFFFFFF; // ���һ��ָ��֮���4���ֽ���0xFFFFFFFF��ʾ����Ϊָ��Ľ���
	insmemory.Write(4);
}

// ȡָ�߳�
DWORD WINAPI FetchInstructions(LPVOID lpParam)
{ 
	if(state[clock%5][0]==-1)
	{
		state[(clock+1)%5][0]=state[(clock+1)%5][1]=-1;
		return 0;
	}
	WaitForSingleObject(mutex_output,INFINITE);
	cout<<"ȡָ - "<<vasm[pc.pc/4]<<endl;
	ReleaseSemaphore(mutex_output,1,NULL);
	insmemory.addr=pc.pc;
	insmemory.Read(4);
	instructions[clock%5]=insmemory.data;
	if(instructions[clock%5]==0xFFFFFFFF)
	{
		state[(clock+1)%5][0]=state[(clock+1)%5][1]=-1;
		return 0;
	}
	else
	{
		state[(clock+1)%5][0]=state[(clock+1)%5][1]=0;
	}
	pctemp[(clock+2)%5]=pc.pc;
	
	//��������ڵ�ִ�й����ж���ִ�е�ָ������תָ����Ѿ��޸���PC�Ĵ�����ֵ���Ͳ�����PC+4������������������PC+4
	WaitForSingleObject(mutex_pc,INFINITE);
	if(isjumpins)
	{
		ReleaseSemaphore(mutex_pc,1,NULL);
		return 0;
	}
	else
	{
		adder.inA=pc.pc;
		adder.inB=4;
		adder.add();
		pc.pcsrc[0]=pc.pcsrc[1]=0;
		pc.next(regf,adder,alu);
	}
	ReleaseSemaphore(mutex_pc,1,NULL);
	
	return 0;
}

// �����߳�
DWORD WINAPI Decode(LPVOID lpParam)
{
	if(state[clock%5][1]==-1)
	{
		state[(clock+1)%5][2]=-1;
		return 0;
	}
	WaitForSingleObject(mutex_output,INFINITE);
	cout<<"���� - "<<vasm[pctemp[(clock+1)%5]/4]<<endl;
	ReleaseSemaphore(mutex_output,1,NULL);
	unsigned instruction=instructions[(clock+4)%5];
	unsigned opcode=(instruction>>24)&0xFF;
	if(opcode==0xA0) // ��֧��BEQ��ָ��
	{
		state[(clock+1)%5][2]=3;
		state[(clock+2)%5][3]=state[(clock+3)%5][4]=-1;
	}
	else if(opcode==0xBC) // B��תָ��
	{
		state[(clock+1)%5][2]=4;
		state[(clock+2)%5][3]=state[(clock+3)%5][4]=-1;
	}
	else if(opcode==0x10) // JUMP��תָ��
	{
		state[(clock+1)%5][2]=5;
		state[(clock+2)%5][3]=state[(clock+3)%5][4]=-1;		
	}
	else if((opcode&0x60)==0) // R��ָ��
	{
		state[(clock+1)%5][2]=0;
		
		// CMPSUB.Aָ������д�أ�����Ҫд�أ���ͬ
		if(opcode!=0x15)
		{
			state[(clock+2)%5][3]=-1;
			state[(clock+3)%5][4]=0;
		}
		else
		{
			state[(clock+2)%5][3]=state[(clock+3)%5][4]=-1;
		}
	}
	else if((opcode&0x60)==0x20) // I��ָ��
	{
		state[(clock+1)%5][2]=1;
		if(opcode!=0x35)
		{
			state[(clock+2)%5][3]=-1;
			state[(clock+3)%5][4]=0;
		}
		else
		{
			state[(clock+2)%5][3]=state[(clock+3)%5][4]=-1;
		}
	}
	else if((opcode&0x40)==0x40) // ��ȡ��ST/LD��ָ��
	{
		state[(clock+1)%5][2]=2;
		state[(clock+2)%5][3]=state[(clock+3)%5][4]=0;
	}
	return 0;
}

// ִ���߳�
DWORD WINAPI Execute(LPVOID lpParam)
{
	if(state[clock%5][2]==-1)
	{
		state[(clock+1)%5][3]=state[(clock+2)%5][4]=-1;
		return 0;
	}
	WaitForSingleObject(mutex_output,INFINITE);
	cout<<"ִ�� - "<<vasm[pctemp[clock%5]/4]<<endl;
	ReleaseSemaphore(mutex_output,1,NULL);
	WaitForSingleObject(mutex_cpi,INFINITE);
	cpiwithcache++;
	cpiwithoutcache++;
	ReleaseSemaphore(mutex_cpi,1,NULL);
	execins++;
	unsigned instruction=instructions[(clock+3)%5];
	unsigned opcode=(instruction>>24)&0xFF;
	regf.readreg1=(instruction>>19)&0x1F;
	regf.readreg2=instruction&0x1F;
	regf.writereg=(instruction>>14)&0x1F;
	
	// �Դ�ȡָ��������ݴ洢���ĵ�ַ
	if(state[clock%5][2]==3||state[clock%5][2]==4)
	{
		alu.srcA=1;
		alu.srcB[0]=0;
		alu.srcB[1]=1;
		alu.op[0]=alu.op[1]=0;
		alu.setflag=0;
		extender.sign=1;
		extender.in=instruction&0xFFFFFF;
		extender.extend(24);
		WaitForSingleObject(mutex_pc,INFINITE);
		unsigned tmppc=pc.pc;
		pc.pc=pctemp[clock%5]+4;
		alu.calculate(regf,pc,shifter,extender);
		pc.pc=tmppc;
		ReleaseSemaphore(mutex_pc,1,NULL);
	}
	
	/*
	  �ȶ�ȡ�Ĵ�����
	  ���������ð��ǰ�ݴ���
	    �����������Ҫ�ļĴ�����ֵ������һ���ڻ���������д�Ĵ�����ֵ��
		����ܻ�δд�ؼĴ����ѣ���ʱ��Ҫ��regwritetemp��ʱ�����ж�ȡ����
		�������������£���һָ����LDָ�����ͬһ���ڵķô����������
		���ܻ�ȡ��ֵ����ʱ��Ҫ�ȴ��ô��������
	  ���⣬regwritetemp����ؽ���˽ṹð�յ����⣺
	    ��ͬһ���ڵ�д���߳���дĳһ�Ĵ�����ֵʱ��ͬʱִ���߳�Ҳ��Ҫ��
		�üĴ�����ֵ����ôִ���߳����ն�ȡ������������regwritetemp��������
		regf��������Ϊ���������ڣ��üĴ�����ֵ���޸ģ���˻ᱻ������regwritetemp�� 
	*/
	regf.run();
	if(regwritetemp[(clock+3)%5][0]!=0&&regwritetemp[(clock+3)%5][1]==regf.readreg1)
	{
		regf.regA=regwritetemp[(clock+3)%5][2];
	}
	if(regwritetemp[(clock+3)%5][0]!=0&&regwritetemp[(clock+3)%5][1]==regf.readreg2)
	{
		regf.regB=regwritetemp[(clock+3)%5][2];
	}
	if(regwritetemp[(clock+3)%5][0]!=0&&regwritetemp[(clock+3)%5][1]==regf.writereg)
	{
		regf.regC=regwritetemp[(clock+3)%5][2];
	}	
	if(regwritetemp[(clock+4)%5][0]!=0&&regwritetemp[(clock+4)%5][1]==regf.readreg1)
	{
		while(regwritetemp[(clock+4)%5][0]!=1)
		{
			Sleep(10);
		}
		regf.regA=regwritetemp[(clock+4)%5][2];
	}
	if(regwritetemp[(clock+4)%5][0]!=0&&regwritetemp[(clock+4)%5][1]==regf.readreg2)
	{
		while(regwritetemp[(clock+4)%5][0]!=1)
		{
			Sleep(10);
		}
		regf.regB=regwritetemp[(clock+4)%5][2];
	}
	if(regwritetemp[(clock+4)%5][0]!=0&&regwritetemp[(clock+4)%5][1]==regf.writereg)
	{
		while(regwritetemp[(clock+4)%5][0]!=1)
		{
			Sleep(10);
		}
		regf.regC=regwritetemp[(clock+4)%5][2];
	}
	
	if(opcode==0x1A||opcode==0x3A)
	{
		regf.regA=0;
	}
	if(state[clock%5][2]==0)
	{
		ExecRIns(instruction);
	}
	else if(state[clock%5][2]==1)
	{
		ExecIIns(instruction);
	}
	else if(state[clock%5][2]==2)
	{
		ExecSL(instruction);
	}
	else if(state[clock%5][2]==3)
	{
		ExecBeq(instruction);
	}
	else if(state[clock%5][2]==4)
	{
		ExecB(instruction);
	}
	else
	{
		ExecJump(instruction);
	}
	wbtemp[clock%5]=regf.write;
	return 0;
}

// ִ��R��ָ��
void ExecRIns(unsigned instruction)
{
	unsigned opcode=(instruction>>24)&0xFF;
	unsigned imm5=(instruction>>9)&0x1F;
	if(imm5!=0)
	{
		alu.srcA=0;
		alu.srcB[0]=1;
		alu.srcB[1]=0;
		shifter.right=0;
		shifter.in=regf.regB;
		shifter.shift(imm5);
		if(opcode==0x04||opcode==0x15)
		{
			shifter.out=(~shifter.out)+1;
		}
	}
	else
	{
		alu.srcA=0;
		alu.srcB[0]=alu.srcB[1]=0;
		if(opcode==0x04||opcode==0x15)
		{
			regf.regB=(~regf.regB)+1;
		}
	}
	if(opcode==0x08||opcode==0x04||opcode==0x15||opcode==0x1A)
	{
		alu.op[0]=alu.op[1]=0;
	}
	else if(opcode==0&&((instruction>>5)&1)==1)
	{
		alu.op[0]=1;
		alu.op[1]=0;
	}
	else if(opcode==0)
	{
		alu.op[0]=0;
		alu.op[1]=1;
	}
	else
	{
		alu.op[0]=alu.op[1]=1;
	}
	if(opcode==0x15)
	{
		alu.setflag=1;
		regwritetemp[clock%5][0]=0;
	}
	else
	{
		alu.setflag=0;
		regwritetemp[clock%5][0]=1;
		regwritetemp[clock%5][1]=regf.writereg;
		regf.src=0;
		regf.write=1;
	}
	alu.calculate(regf,pc,shifter,extender);
	regwritetemp[clock%5][2]=alu.out;
}

// ִ��I��ָ��
void ExecIIns(unsigned instruction)
{
	unsigned opcode=(instruction>>24)&0xFF;
	unsigned imm5=(instruction>>9)&0x1F;
	unsigned imm9=instruction&0x1FF;
	extender.in=imm9;
	extender.sign=0;
	shifter.in=extender.extend(9);
	shifter.right=1;
	shifter.shift(imm5);
	if(opcode==0x24||opcode==0x35)
	{
		shifter.out=~shifter.out+1;
	}
	alu.srcA=0;
	alu.srcB[0]=1;
	alu.srcB[1]=0;
	if(opcode==0x28||opcode==0x24||opcode==0x35||opcode==0x3A)
	{
		alu.op[0]=alu.op[1]=0;
	}
	else if(opcode==0x20)
	{
		alu.op[0]=0;
		alu.op[1]=1;
	}
	else
	{
		alu.op[0]=alu.op[1]=1;
	}
	if(opcode==0x35)
	{
		alu.setflag=1;
		regwritetemp[clock%5][0]=0;
	}
	else
	{
		alu.setflag=0;
		regwritetemp[clock%5][0]=1;
		regwritetemp[clock%5][1]=regf.writereg;
		regf.src=0;
		regf.write=1;		
	}
	alu.calculate(regf,pc,shifter,extender);
	regwritetemp[clock%5][2]=alu.out;
}

// ִ�д�ȡָ��
void ExecSL(unsigned instruction)
{
	unsigned opcode=(instruction>>24)&0xFF;
	unsigned imm5=(instruction>>9)&0x1F;
	unsigned imm14=instruction&0x3FFF;
	alu.setflag=0;
	alu.srcA=0;
	alu.op[0]=alu.op[1]=0;
	if((opcode&0x70)==0x50)
	{
		alu.srcB[0]=1;
		alu.srcB[1]=0;
		shifter.right=0;
		shifter.in=regf.regB;
		shifter.shift(imm5);
	}
	else
	{
		alu.srcB[0]=0;
		alu.srcB[1]=1;
		extender.sign=0;
		extender.in=imm14;
		extender.extend(14);
	}	
	cachetemp[clock%5][0]=alu.calculate(regf,pc,shifter,extender);
	if(!(opcode&1))
	{
		cachetemp[clock%5][1]=regf.regC;
		regf.write=0;
		regwritetemp[clock%5][0]=0;
	}
	else
	{
		regf.write=1;
		regwritetemp[clock%5][0]=2;
		regwritetemp[clock%5][1]=regf.writereg;
	}
}

// ִ��BEQָ��
void ExecBeq(unsigned instruction)
{
	if(regf.flag.Z)
	{
		WaitForSingleObject(mutex_pc,INFINITE);
		pc.pcsrc[0]=1;
		pc.pcsrc[1]=0;
		pc.next(regf,adder,alu);
		isjumpins=true;
		ReleaseSemaphore(mutex_pc,1,NULL);
	}
	regwritetemp[clock%5][0]=0;
}

// ִ��Bָ��
void ExecB(unsigned instruction)
{
	WaitForSingleObject(mutex_pc,INFINITE);
	pc.pcsrc[0]=1;
	pc.pcsrc[1]=0;
	pc.next(regf,adder,alu);
	isjumpins=true;
	ReleaseSemaphore(mutex_pc,1,NULL);
	regwritetemp[clock%5][0]=0;
}

// ִ��JUMPָ��
void ExecJump(unsigned instruction)
{
	WaitForSingleObject(mutex_pc,INFINITE);	
	pc.pcsrc[0]=0;
	pc.pcsrc[1]=1;
	pc.next(regf,adder,alu);
	isjumpins=true;
	ReleaseSemaphore(mutex_pc,1,NULL);
	regwritetemp[clock%5][0]=0;
}

// �ô��߳�
DWORD WINAPI VisitCache(LPVOID lpParam)
{
	if(state[clock%5][3]==-1)
	{
		return 0;
	}
	WaitForSingleObject(mutex_output,INFINITE);
	cout<<"�ô� - "<<vasm[pctemp[(clock+4)%5]/4]<<endl;
	ReleaseSemaphore(mutex_output,1,NULL);
	WaitForSingleObject(mutex_cpi,INFINITE);
	cpiwithoutcache+=99;
	ReleaseSemaphore(mutex_cpi,1,NULL);
	unsigned instruction=instructions[(clock+2)%5];
	unsigned opcode=(instruction>>24)&0xFF;
	if(opcode&1)
	{
		cache.read=1;
		cache.write=0;
	} // opcode���λΪ1����洢��������д�洢��
	else
	{
		cache.read=0;
		cache.write=1;
	}
	WaitForSingleObject(mutex_cpi,INFINITE);
	unsigned ret=cache.rw(1+3*(((instruction>>26)&1)==0),clock,cachetemp[(clock+4)%5][0],cachetemp[(clock+4)%5][1],cpiwithcache); // ����дCache
	ReleaseSemaphore(mutex_cpi,1,NULL);
	if(opcode&1)
	{
		regwritetemp[(clock+4)%5][2]=ret;
		regwritetemp[(clock+4)%5][0]=1;
	}
	return 0;
}

// д���߳�
DWORD WINAPI WriteBack(LPVOID lpParam)
{	
	if(state[clock%5][4]==-1||!wbtemp[(clock+3)%5])
	{
		return 0;
	}
	WaitForSingleObject(mutex_output,INFINITE);
	cout<<"д�� - "<<vasm[pctemp[(clock+3)%5]/4]<<endl;
	ReleaseSemaphore(mutex_output,1,NULL);
	regf.regs[regwritetemp[(clock+3)%5][1]]=regwritetemp[(clock+3)%5][2];
	return 0;
}

int main()
{
	FILE *fout=fopen("output.txt","w");
	*stdout=*fout;
	mutex_output=CreateSemaphore(NULL,1,1,NULL);
	InputInstructions();
	ParseBInstructions();
	LoadInstructions();
	vasm.push_back("FFFFFFFF");
	
	/*
	________________		________________		________________		________________		________________
	|Fetchins      |		|Decode        |		|Execute       |		|VisitMemory   |		|WriteBack     |		________________
	----------------		|Fetchins      |		|Decode        |		|Execute       |		|VisitMemory   |		|WriteBack     |		________________
	                		----------------		|Fetchins      |		|Decode        |		|Execute       |		|VisitMemory   |		|WriteBack     |		________________
	                		                		----------------		|Fetchins      |		|Decode        |		|Execute       |		|VisitMemory   |		|WriteBack     |		________________
	                		                		                		----------------		|Fetchins      |		|Decode        |		|Execute       |		|VisitMemory   |		|WriteBack     |		________________
	                		                		                		                		----------------		|Fetchins      |		|Decode        |		|Execute       |		|VisitMemory   |		|WriteBack     |
	                		                		                		                								----------------		----------------		----------------		----------------		----------------
	
	whileѭ����ÿ�ε�������ִ�е��൱����ͬһ�����еļ����̣߳�whileѭ��������Ǵ���������ִ�и�����
	*/ 
	while(state[clock%5][0]!=-1||state[clock%5][1]!=-1||state[clock%5][2]!=-1||state[clock%5][3]!=-1||state[clock%5][4]!=-1)
	{
		cout<<"\n\n=========================================================================\n";
		cout<<"ʱ������ : "<<clock<<endl;
		isjumpins=false;
		
		// ��������̣߳��ٵȴ�����̶߳�������Ž�����һ����
		HANDLE handle_getins=CreateThread(NULL,0,FetchInstructions,NULL,0,NULL);
		HANDLE handle_decode=CreateThread(NULL,0,Decode,NULL,0,NULL);
		HANDLE handle_exec=CreateThread(NULL,0,Execute,NULL,0,NULL);
		HANDLE handle_visitcache=CreateThread(NULL,0,VisitCache,NULL,0,NULL);
		HANDLE handle_wb=CreateThread(NULL,0,WriteBack,NULL,0,NULL);
		WaitForSingleObject(handle_getins,INFINITE);
		WaitForSingleObject(handle_decode,INFINITE);
		WaitForSingleObject(handle_exec,INFINITE);
		WaitForSingleObject(handle_visitcache,INFINITE);
		WaitForSingleObject(handle_wb,INFINITE);
		
		if(isjumpins)
		{
			state[(clock+1)%5][1]=state[(clock+1)%5][2]=-1; // ������תָ���һ����ֹͣ�����ִ�� 
			cout<<"��ǰ����ִ�е�����תָ�\n";
		}
		cout<<"-------------------------------------------------------------------------\n";
		regf.Print();
		cache.Print();
		datamemory.Print();
		clock++;			
	}
	cache.Buf2Mem();
	cout<<"================��=========��=========��===========��====================\n";
	regf.Print();
	cache.Print();
	datamemory.Print();
	cout<<"CPI with Cache = "<<cpiwithcache/double(execins)<<endl;
	cout<<"CPI without Cache = "<<cpiwithoutcache/double(execins)<<endl;
	return 0;
}

/*
��������: 
MOV r0,21
MOV r2,2
LOOP: STW r0,[r2]
ADD r2,r2,4
SUB r0,r0,1
CMPSUB.A r0,1
BEQ OUT
B LOOP
OUT:
MOV r8,12
MOV r9,10
OR r10,r8,r9
AND r11,r8,r9
MUL r12,r10,r11
MOV r5,4
MOV r5,r5<<4
ADD r5,r5,8
JUMP r5
B LOOP
ADD r0,r0,2
LDB r13,[r0]
*/
