// Sorts.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "assert.h"
#include "time.h"
#include "Heap.h"
#include <vector>
#include <iostream>
#include <sys/timeb.h>
using namespace std;

const int SAMPLENUM = 15;
const int SHOWNUM = 15;

//����Ԫ��
//void myswap(vector<int>::iterator iter1,vector<int>::iterator iter2){
//	int temp = *iter1;
//	*iter1 = *iter2;
//	*iter2 = temp;
//}

//ð������
void sort_bubble(vector<int> &data){
	for(int i = 0;i<data.size();i++){
		for(int j = 0;j<data.size()-i-1;j++){
			if(data[j]>data[j+1])swap(data[j],data[j+1]);
		}
	}
}
//=============================================================================

//��������_����
int partition(vector<int> &data,int left,int right){
	assert(right>left);
	int data1 = data[left];
	int data2 = data[left+(right-left)/2];
	int data3 = data[right];
	//ѡ��һ���м�ֵ��Ϊ��׼ֵ
	if(data1<data2){
		if(data2<data3)swap(data[left],data[left+(right-left)/2]);
		else if(data1<data3)swap(data[left],data[right]);
	}
	else{
		if(data2>data3)swap(data[left],data[left+(right-left)/2]);
		else if(data1>data3)swap(data[left],data[right]);
	}

	int i=left+1;
	int j=right;

	do{
		while(data[i]<=data[left]){
			i++;
			if(!(i>=left&&i<=right))break;
		}
		while(data[j]>data[left]){
			j--;
			if(!(j>=left&&i<=right))break;
		}
		if(i<j)swap(data[i],data[j]);
	}while(i<j);
	swap(data[j],data[left]);
	return j;
}

//��������_�ݹ��ӹ���
void quicksort(vector<int> &data,int left,int right){
	if(right<=left)return;
	int sppos = partition(data,left,right);
	quicksort(data,left,sppos-1);
	quicksort(data,sppos+1,right);
}
//��������
void sort_quick(vector<int> &data){
	quicksort(data,0,data.size()-1);
}
//================================================================================

//ֱ��ѡ������
void sort_dirctchoose(vector<int> &data){
	for(int i=0;i<data.size();++i){
		int minIndex = i;
		for(int j=i+1;j<data.size();++j){
			if (data[j]<data[minIndex])minIndex = j;
		}
		swap(data[i],data[minIndex]);
	}
}
//================================================================================

//������
void sort_heap(vector<int> &data){
	Heap minHeap;
	for(int i=0;i<data.size();++i){
		minHeap.add(data[i]);
	}
	int index = 0;
	while(minHeap.isEmpty() == false){
		int num = minHeap.removeRoot();
		data[index++] = num;
	}
}
//==================================================================================
//ֱ�Ӳ�������
void sort_directinsert(vector<int> &data){
	for(int i=0;i<data.size()-1;i++){
		int insertdata = data[i+1];
		int j=i;
		while(j>=0){
			if(data[j]<=insertdata){
				break;
			}
			else{
				data[j+1] = data[j];
				j--;
			}
		}
		data[j+1] = insertdata;
	}
}
//==================================================================================
//ϣ������
void sort_shell(vector<int> &data){
	int gap = data.size()/3+1;
	while(gap>0){
		for(int index=gap;index<data.size();index++){
			int indexfind = index;
			int datainsert = data[index];
			while(indexfind>=gap && datainsert<data[indexfind-gap]){
				data[indexfind] = data[indexfind-gap];
				indexfind -= gap;
			}
			data[indexfind] = datainsert;
		}
		if(gap>1)gap = gap/3+1;
		else gap = 0;
	}
}

//==================================================================================

//�鲢����_�ϲ�����
void sm_merge(vector<int> &data,int left,int count){
	if(left+count>data.size()-1)return;
	vector<int> datatemp;
	int i = left;
	int j = left+count;
	
	while(i<left+count || (j<left+2*count && j<data.size())){
		if(i>=left+count){
			for (int k = j; k<left + 2 * count&&k<data.size(); ++k)datatemp.push_back(data[k]);
			break;
		}
		if(j>=left+2*count || j>=data.size()){
			for (int k = i; k<left + count; ++k)datatemp.push_back(data[k]);
			break;
		}
		if(data[i]<data[j]){
			datatemp.push_back(data[i]);
			++i;
		}
		else{
			datatemp.push_back(data[j]);
			++j;
		}
	}
	i=0;
	for(int index=left;index<left+2*count&&index<data.size();index++){
		data[index] = datatemp[i++];
	}
}
//�鲢����
void sort_merge(vector<int> &data){
	int zhi = 1;
	do{
		for(int i=0;i<data.size()-zhi;i+=(2*zhi))
			sm_merge(data,i,zhi);
		zhi *= 2;
	}while(zhi < data.size());
}
//==================================================================================
//MSD��������_�ݹ麯��
void recursive_MSD(vector<int> &data,int left, int right, int tag){
	if (tag == 0)return;
	if (left >= right)return;
	vector<int> count(10,0);
	vector<vector<int>> bucket(10);
	int div = pow(10,tag-1);
	for (int i = left; i <= right; ++i){
		int pos = (data[i] / div) % 10;
		++count[pos];
		bucket[pos].push_back(data[i]);
	}
	int countit = 0;
	for (int i = 0; i < 10; ++i){
		int cc = 0;
		for (int j = 0; j < bucket[i].size(); ++j){
			data[left + countit+cc] = bucket[i][j];
			++cc;
		}
		recursive_MSD(data,left+countit,left+countit+cc-1,tag-1);
		countit += cc;
	}
}
//MSD�������� (���������֣�1-999)
void sort_MSD(vector<int> &data){
	recursive_MSD(data, 0, data.size() - 1, 3);
}
//==================================================================================
//LSD��������(���������֣�1-999)
void sort_LSD(vector<int> &data){
	for (int tag = 1; tag <= 3; ++tag){
		int div = pow(10,tag-1);
		vector<vector<int>> bucket(10);
		//����
		for (int i = 0; i < data.size(); ++i){
			int pos = (data[i] / div) % 10;
			bucket[pos].push_back(data[i]);
		}
		//�ռ�
		int index = 0;
		for (int i = 0; i < 10; ++i){
			for (int j = 0; j < bucket[i].size(); ++j){
				data[index++] = bucket[i][j];
			}
		}
	}
}

//==================================================================================




//==================================================================================
//==================================================================================
//ʸ���������(ǰSHOWNUM)
void outputVector(vector<int> data){
	int shownum = SAMPLENUM>SHOWNUM?SHOWNUM:SAMPLENUM;
	for(vector<int>::iterator iter = data.begin();iter != data.begin()+shownum;iter++){
		cout<<*iter<<"  ";
	}
	cout<<endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	vector<int> data;
	timeb start, finish;
	srand(time(NULL));
	for(int i=0;i<SAMPLENUM;i++){
		int num = rand()%1000;
		data.push_back(num);
	}
	cout << "δ�������飺" << endl;
	outputVector(data);
	cout << "---------" << endl;
	
	////ð������
	/*ftime(&start);
	sort_bubble(data);
	outputVector(data);
	ftime(&finish);
	cout << "ð������ִ��ʱ�䣺" << (finish.time - start.time)*1000+(finish.millitm-start.millitm)<< "ms" << endl;
	*/

	//��������
	/*ftime(&start);
	sort_quick(data);
	outputVector(data);
	ftime(&finish);
	cout << "��������ִ��ʱ�䣺" << (finish.time - start.time) * 1000 + (finish.millitm - start.millitm) << "ms" << endl;
	*/

	//ֱ��ѡ������
	//ftime(&start);
	//sort_dirctchoose(data);
	//outputVector(data);
	//ftime(&finish);
	//cout << "ֱ��ѡ������ִ��ʱ�䣺" << (finish.time - start.time) * 1000 + (finish.millitm - start.millitm) << "ms" << endl;



	//������
	//ftime(&start);
	//sort_heap(data);
	//outputVector(data);
	//ftime(&finish);
	//cout << "������ִ��ʱ�䣺" << (finish.time - start.time) * 1000 + (finish.millitm - start.millitm) << "ms" << endl;

	//ֱ�Ӳ�������
	/*ftime(&start);
	sort_directinsert(data);
	outputVector(data);
	ftime(&finish);
	cout << "ֱ�Ӳ�������ִ��ʱ�䣺" << (finish.time - start.time) * 1000 + (finish.millitm - start.millitm) << "ms" << endl;
*/

	//shell����
	/*ftime(&start);
	sort_shell(data);
	outputVector(data);
	ftime(&finish);
	cout << "shell����ִ��ʱ�䣺" << (finish.time - start.time) * 1000 + (finish.millitm - start.millitm) << "ms" << endl;
*/

	//�鲢����
	ftime(&start);
	sort_merge(data);
	outputVector(data);
	ftime(&finish);
	cout << "�鲢����ִ��ʱ�䣺" << (finish.time - start.time) * 1000 + (finish.millitm - start.millitm) << "ms" << endl;



	//MSD��������
	/*ftime(&start);
	sort_MSD(data);
	outputVector(data);
	ftime(&finish);
	cout << "MSD��������ִ��ʱ�䣺" << (finish.time - start.time) * 1000 + (finish.millitm - start.millitm) << "ms" << endl; 
*/

	//LSD��������
	/*ftime(&start);
	sort_LSD(data);
	outputVector(data);
	ftime(&finish);
	cout << "LSD��������ִ��ʱ�䣺" << (finish.time - start.time) * 1000 + (finish.millitm - start.millitm) << "ms" << endl;
*/
	char result;
	cin>>result;
	return 0;
}

