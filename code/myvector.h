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
	//构造
	MyVector();
	//初始化构造
	MyVector(std::initializer_list<T> li);
	//拷贝
	MyVector(const MyVector& v1);
	//赋值运算符
	MyVector<T>& operator=(const MyVector& v1);
	//长度
	int size();
	//[]重载
	T& operator[](int index);
	//返回底元素
	T& front();
	//返回顶元素
	T& back();
	//压入新元素
	void push_back(const T& t1);
	//弹出新元素
	void  pop_back();
	//插入元素
	void insert(int index, const T& t1);
	//删除元素
	void erase(int index);
    void eraseT(const T &t);
	//清空
	void clear();
	//排序
	void sort();
	//二分查找
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
