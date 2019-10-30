#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack
{
protected:
  T *pMem;
  int size;
  int top;
public:
  TStack(int _size)
  {
    size = _size;
    top = -1;
    if ((size < 1) || (size > MaxStackSize))
      throw size;
    pMem = new T[size];
  }
  TStack()
  {
  }
  ~TStack()
  {
    delete [] pMem;
  }

  virtual bool empty() {
	  return top == -1;
  }

  virtual void push(T object) {
	  pMem[++top] = object;
  }

  virtual void pop(){
	  pMem[top--] = T();
  }

  virtual T front(){
	  return pMem[0];
  }

  virtual T back(){
	  return pMem[top];
  }

  virtual T& operator[](int i) {
	  if (i>-1 && i < top)
		  return pMem[i];
	  throw 0;
  }
};

#endif
