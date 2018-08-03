#pragma once

template <typename K>
class DataStructure;

template <class K>
class push
{
public:
	virtual bool Push(DataStructure<K> *, const K&) = 0;
	virtual bool operator()(DataStructure<K> *, const K&) = 0;
};
template <class K>
class pop
{
public:
	virtual K Pop(DataStructure<K>*) = 0;
	virtual K operator()(DataStructure<K> *) = 0;
};
template <class K>
class empty
{
public:
	virtual bool Empty(DataStructure<K> *) = 0;
	virtual bool operator()(DataStructure<K> *) = 0;
};
template <class K>
class print
{
public:
	virtual void Print(DataStructure<K> *) = 0;
	virtual void operator()(DataStructure<K> *) = 0;
};

template <class K>
class stackpush : public push<K>
{
	bool Push(DataStructure<K> *, const K&);
	bool operator()(DataStructure<K> *, const K&);
};
template <class K>
class stackpop : public pop<K>
{
	K Pop(DataStructure<K> *);
	K operator()(DataStructure<K> *);
};
template <class K>
class stackempty : public empty<K>
{
	bool Empty(DataStructure<K> *);
	bool operator()(DataStructure<K> *);
};
template <class K>
class stackprint : public print<K>
{
	void Print(DataStructure<K> *);
	void operator()(DataStructure<K> *);
};

template <class K>
class queuepush : public push<K>
{
	bool Push(DataStructure<K> *, const K&);
	bool operator()(DataStructure<K> *, const K&);
};
template <class K>
class queuepop : public pop<K>
{
	K Pop(DataStructure<K> *);
	K operator()(DataStructure<K> *);
};
template <class K>
class queueempty : public empty<K>
{
	bool Empty(DataStructure<K> *);
	bool operator()(DataStructure<K> *);
};
template <class K>
class queueprint : public print<K>
{
	void Print(DataStructure<K> *);
	void operator()(DataStructure<K> *);
};