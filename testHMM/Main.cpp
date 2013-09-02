#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;
//Hello, this is whj's testing.
int SwapInt32(int p);
float SwapFloat(float p);
int IsVAXOrder(void);
short SwapShort(short p);

template<class T>
T SwapData(T p)
{
	int len = sizeof(T);
	char tmp;
	char *ptr = (char*)&p;
	for(int i=0; i<len/2; i++)
	{
		tmp = ptr[i];
		ptr[i] = ptr[len-1-i];
		ptr[len-1-i] = tmp;
	}
	return p;
}

int main()
{
	int vax = IsVAXOrder();
	ifstream fReader;
	fReader.open("P50_0000_1_0_20121002_ske.dat.ext",ios::binary);
	fstream fw("P50_0000_1_0_20121002_ske.dat.txt",ios::out);
	int count, samPeriod;
	short size, type;
	if(fReader == NULL)
		return -1;
	fReader.read((char*)&count,sizeof(int));
	fw<<count<<"("<<SwapInt32(count)<<")"<<endl;
	cout<<count<<"("<<SwapInt32(count)<<")"<<endl;
	cout << SwapData<int>(count) << endl;
	fReader.read((char*)&samPeriod,sizeof(int));
	fw << samPeriod << " " << SwapInt32(samPeriod) << endl;
	cout << samPeriod << " " << SwapInt32(samPeriod) << endl;

	fReader.read((char*)&size,2);
	fw << size << " " << SwapShort(size) << endl;
	cout << size << " " << SwapShort(size) << endl;
	cout << SwapData<short>(size) << endl;

	fReader.read((char*)&type,2);
	fw << type << " " << SwapShort(type) << endl;
	cout << type << " " << SwapShort(type) << endl;
	cout << SwapData<short>(type) << endl;

	int num_points = SwapShort(size)/sizeof(float);
	fw << num_points << endl;
	cout << num_points << endl;

	for(int i=0; i<SwapInt32(count); i++)
	{
		for(int j=0; j<num_points; j++)
		{
			float tmp;
			fReader.read((char*)&tmp,sizeof(float));
			fw << SwapFloat(tmp) << " ";
			cout << SwapFloat(tmp) << " ";
		}
		fw << endl;
		cout << endl;
	}
	fw.close();
	system("pause");
	return 0;
}

int IsVAXOrder(void)
{
	short x, *px;
	unsigned char *pc;

	px = &x;
	pc = (unsigned char *) px;
	*pc = 1; 
	*(pc+1) = 0;         /* store bytes 1 0 */
	if (x == 1) 
		return 1;           /* does it read back as 1? */
	else 
		return 0;
}

int SwapInt32(int p)
{
	char temp;
	char *q = (char*) &p;

	temp = *q; 
	*q = *(q+3); 
	*(q+3) = temp;

	temp = *(q+1); 
	*(q+1) = *(q+2); 
	*(q+2) = temp;

	return p;
}

float SwapFloat(float p)
{
	char tmp;
	char *ptr = (char *)&p;

	tmp = ptr[0];
	ptr[0] = ptr[3];
	ptr[3] = tmp;

	tmp = ptr[1];
	ptr[1] = ptr[2];
	ptr[2] = tmp;

	return p;
}

/* SwapShort: swap byte order of short data value p */
short SwapShort(short p)
{
	char temp, *q;

	q = (char*) &p;
	temp = *q; 
	*q = *(q+1); 
	*(q+1) = temp;

	return p;
}