#ifndef MYVECTOR_H
#define MYVECTOR_H

#include<initializer_list>

template<typename T>
class MyVector
{
	T array[200];
	T* ps = array;
	T* p = array;
public:
	//����
	MyVector();
	//��ʼ������
	MyVector(std::initializer_list<T> li);
	//����
	MyVector(const MyVector& v1);
	//��ֵ�����
	MyVector<T>& operator=(const MyVector& v1);
	//����
	int size();
	//[]����
	T& operator[](int index);
	//���ص�Ԫ��
	T& front();
	//���ض�Ԫ��
	T& back();
	//ѹ����Ԫ��
	void push_back(const T& t1);
	//������Ԫ��
	void  pop_back();
	//����Ԫ��
	void insert(int index, const T& t1);
	//ɾ��Ԫ��
	void erase(int index);
    void eraseT(const T &t);
	//���
	void clear();
	//����
	void sort();
	//���ֲ���
	//int binary_search(const T& v1);
}; 

template<typename T>
MyVector<T>::MyVector() {};

template<typename T>
MyVector<T>::MyVector(std::initializer_list<T> li)
{
	for (auto ptr = li.begin(); ptr != li.end(); ptr++)
	{
		*(p++) = *ptr;
	}
};

template<typename T>
MyVector<T>::MyVector(const MyVector& v1)
{
	while (p - ps != v1.p - v1.ps)
		*(p++) = *(v1.ps);
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& v1)
{
	p = ps;
	while (p - ps != v1.p - v1.ps)
		*(p++) = *(v1.ps);
	return (*this);
}

template<typename T>
int MyVector<T>::size()
{
	return p - ps;
}

template<typename T>
T& MyVector<T>::operator[](int index)
{
	return (*(ps + index));
}

template<typename T>
T& MyVector<T>::front()
{
	return (*ps);
}

template<typename T>
T& MyVector<T>::back()
{
	return *(p-1);
}

template<typename T>
void MyVector<T>::push_back(const T& t1)
{
	*(p++) = t1;
}

template<typename T>
void  MyVector<T>::pop_back()
{
	p--;
}

template<typename T>
void MyVector<T>::insert(int index, const T& t1)
{
	for (T* ptr = p; ptr != ps + index; ptr--)
		*ptr = *(ptr - 1);
	*(ps + index) = t1;
	p++;
}

template<typename T>
void MyVector<T>::erase(int index)
{
	for (T* ptr = ps + index; ptr != p - 1; ptr++)
		*ptr = *(ptr + 1);
	p--;
}

template<typename T>

void MyVector<T>::eraseT(const T &t)
{
    for (int i = 0; i != size(); i++)
        {
            if (*(ps + i) == t)
            {
                erase(i);
                break;
            }
        }
}

template<typename T>
void MyVector<T>::clear()
{
	p = ps;
}

template<typename T>
void MyVector<T>::sort()
{
	for (MyVector<T>* ptr = ps; ptr != p - 1; ptr++)
	{
		for (MyVector<T>* ptr1 = ptr + 1; ptr1 != p; ptr1++)
		{
			if (*ptr > * ptr1)
			{
				T temp = *ptr;
				*ptr = *ptr1;
				*ptr1 = temp;
			}
		}
	}
}

#endif //MYVECTOR_H
