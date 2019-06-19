#pragma once

template <typename T>
class CLinkList
{
	struct _NODE		//�ڵ�
	{
		T _data;		//�ڵ����� Ҳ���� ��Ҫ�洢������
		_NODE* _next;	//�ڵ�ĺ��� ��һ���ڵ�ĵ�ַ
		_NODE* _pre;	//�ڵ��ǰ�� ��һ���ڵ�ĵ�ַ
	};
						//��Ϊ���������� ���� �� ɾ���ڵ��
						//���������� û����������
	//int m_Size;		//����	�����ڵ��ܳ�
	int m_Length;	//����	�����ڵ����ݸ���
	_NODE* m_Head;	//�ڵ�ͷ

	//�õ��ڵ� ��ַ
	void* GetPoint(int pos) const;

public:
	CLinkList();
	CLinkList(const CLinkList& that);
	CLinkList& operator =(const CLinkList& that);
	~CLinkList();

	//��������
	bool Insert(T data, int pos);
	//�������ݣ�һ��������������ݣ�
	void Push(T data);
	//ɾ���ڵ�	(-1 Ĭ��ɾ�����һ���ڵ�)
	bool Erase(int pos = -1);
	//�������
	void Clear();
	//��ȡ��
	int Length()const;
	//��ȡ����
	T* Get(int pos)const;
	//��λ �����ǻ�ȡ���� �ڱ��е�λ�ã�
	int Locate(T data, int begin = 0);
	//����
	void Sort(int begin, int end, bool increase);
};

template <typename T>
void* CLinkList<T>::GetPoint(int pos) const
{
	if(pos < 0 || pos >= m_Length)
		return 0;

	_NODE* p = m_Head;
	//�õ��½ڵ�� ���� (�����)
	for(int i = 0; i <= pos; ++i)
		p = p->_next;
	return p;
}

template <typename T>
CLinkList<T>::CLinkList()
{
	// ���� ���� ͷ�ڵ�
	 m_Head = new _NODE;
	 m_Head->_next = m_Head;
	 m_Head->_pre = m_Head;
	 m_Length = 0;
}

template <typename T>
CLinkList<T>::CLinkList(const CLinkList& that)
{
	// ���� ���� ͷ�ڵ�
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
	//�������
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

//��������
template <typename T>
bool CLinkList<T>::Insert(T data, int pos)
{
	//�Ϸ����
	if(pos < 0 || pos > m_Length)
		return 0;
	//�½��ڵ� 
	_NODE* p = new _NODE;
	//���µĽڵ�洢����
	p->_data = data;

	_NODE* hou = m_Head;

	//�õ��½ڵ�� ���� (�����)
	for(int i = 0; i <= pos; ++i)
		hou = hou->_next;

	//�õ��½ڵ�� ǰ��
	_NODE* qian = hou->_pre;

	//��������
	p->_pre = qian;
	p->_next = hou;
	qian->_next = p;
	hou->_pre = p;

	m_Length += 1;
	return 1;
}

//�������ݣ�һ��������������ݣ�
template <typename T>
void CLinkList<T>::Push(T data)
{
	//�½��ڵ� 
	_NODE* p = new _NODE;
	//���µĽڵ�洢����
	p->_data = data;
	
	//�õ��½ڵ�� ǰ��
	_NODE* qian = m_Head->_pre;
	//�õ��½ڵ�� ����
	_NODE* hou = m_Head;

	//��������
	p->_pre = qian;
	p->_next = hou;
	qian->_next = p;
	hou->_pre = p;

	m_Length += 1;
}

//ɾ���ڵ�	(-1 Ĭ��ɾ�����һ���ڵ�)
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

//�������
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

//��ȡ��
template <typename T>
int CLinkList<T>::Length()const
{
	return m_Length;
}

//��ȡ����
template <typename T>
T* CLinkList<T>::Get(int pos)const
{
	_NODE* p = (_NODE*)(GetPoint(pos));
	if(p == 0)
		return 0;
	return &(p->_data);
}

//��λ �����ǻ�ȡ���� �ڱ��е�λ�ã�
template <typename T>
int CLinkList<T>::Locate(T data, int begin)
{
	return 0;
}

//����
template <typename T>
void CLinkList<T>::Sort(int begin, int end, bool increase)
{
	
}