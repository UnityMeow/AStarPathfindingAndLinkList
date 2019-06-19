#pragma once

template <typename T>
class CLinkList
{
	struct _NODE		//节点
	{
		T _data;		//节点数据 也就是 表要存储的数据
		_NODE* _next;	//节点的后续 下一个节点的地址
		_NODE* _pre;	//节点的前驱 上一个节点的地址
	};
						//因为链表是无限 生成 和 删除节点的
						//所以理论上 没有容量限制
	//int m_Size;		//容量	表现在的总长
	int m_Length;	//长度	表现在的数据个数
	_NODE* m_Head;	//节点头

	//得到节点 地址
	void* GetPoint(int pos) const;

public:
	CLinkList();
	CLinkList(const CLinkList& that);
	CLinkList& operator =(const CLinkList& that);
	~CLinkList();

	//插入数据
	bool Insert(T data, int pos);
	//推入数据（一般就是往最后放数据）
	void Push(T data);
	//删除节点	(-1 默认删除最后一个节点)
	bool Erase(int pos = -1);
	//清空链表
	void Clear();
	//获取表长
	int Length()const;
	//获取数据
	T* Get(int pos)const;
	//定位 （就是获取数据 在表中的位置）
	int Locate(T data, int begin = 0);
	//排序
	void Sort(int begin, int end, bool increase);
};

template <typename T>
void* CLinkList<T>::GetPoint(int pos) const
{
	if(pos < 0 || pos >= m_Length)
		return 0;

	_NODE* p = m_Head;
	//得到新节点的 后续 (后遍历)
	for(int i = 0; i <= pos; ++i)
		p = p->_next;
	return p;
}

template <typename T>
CLinkList<T>::CLinkList()
{
	// 开堆 生成 头节点
	 m_Head = new _NODE;
	 m_Head->_next = m_Head;
	 m_Head->_pre = m_Head;
	 m_Length = 0;
}

template <typename T>
CLinkList<T>::CLinkList(const CLinkList& that)
{
	// 开堆 生成 头节点
	m_Head = new _NODE;
	m_Head->_next = m_Head;
	m_Head->_pre = m_Head;
	m_Length = 0;
	int iTmp = that.Length();
	for(int i = 0; i < iTmp; ++i)
		Push(*(that.Get(i)));
}

template <typename T>
CLinkList<T>& CLinkList<T>::operator =(const CLinkList& that)
{
	//清空链表
	Clear();
	int iTmp = that.Length();
	for(int i = 0; i < iTmp; ++i)
		Push(*(that.Get(i)));
	return *this;
}

template <typename T>
CLinkList<T>::~CLinkList()
{
	Clear();
	delete m_Head;
}

//插入数据
template <typename T>
bool CLinkList<T>::Insert(T data, int pos)
{
	//合法检测
	if(pos < 0 || pos > m_Length)
		return 0;
	//新建节点 
	_NODE* p = new _NODE;
	//用新的节点存储数据
	p->_data = data;

	_NODE* hou = m_Head;

	//得到新节点的 后续 (后遍历)
	for(int i = 0; i <= pos; ++i)
		hou = hou->_next;

	//得到新节点的 前驱
	_NODE* qian = hou->_pre;

	//进行链接
	p->_pre = qian;
	p->_next = hou;
	qian->_next = p;
	hou->_pre = p;

	m_Length += 1;
	return 1;
}

//推入数据（一般就是往最后放数据）
template <typename T>
void CLinkList<T>::Push(T data)
{
	//新建节点 
	_NODE* p = new _NODE;
	//用新的节点存储数据
	p->_data = data;
	
	//得到新节点的 前驱
	_NODE* qian = m_Head->_pre;
	//得到新节点的 后续
	_NODE* hou = m_Head;

	//进行链接
	p->_pre = qian;
	p->_next = hou;
	qian->_next = p;
	hou->_pre = p;

	m_Length += 1;
}

//删除节点	(-1 默认删除最后一个节点)
template <typename T>
bool CLinkList<T>::Erase(int pos)
{
	_NODE* p = (_NODE*)GetPoint(pos);

	if(p != 0)
	{
		_NODE* qian = p->_pre;
		_NODE* hou = p->_next;
		delete p;
		qian->_next = hou;
		hou->_pre = qian;
		m_Length -= 1;
		return 1;
	}
	else
		return 0;
}

//清空链表
template <typename T>
void CLinkList<T>::Clear()
{
	while(m_Length)
	{
		Erase(0);
	}
	m_Head->_next = m_Head;
	m_Head->_pre = m_Head;
}

//获取表长
template <typename T>
int CLinkList<T>::Length()const
{
	return m_Length;
}

//获取数据
template <typename T>
T* CLinkList<T>::Get(int pos)const
{
	_NODE* p = (_NODE*)(GetPoint(pos));
	if(p == 0)
		return 0;
	return &(p->_data);
}

//定位 （就是获取数据 在表中的位置）
template <typename T>
int CLinkList<T>::Locate(T data, int begin)
{
	return 0;
}

//排序
template <typename T>
void CLinkList<T>::Sort(int begin, int end, bool increase)
{
	
}