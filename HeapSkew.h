#if !defined HEAPSKEW_H
#define HEAPSKEW_H

#include "BinaryTree.h"
#include "wx/wx.h"
#include <iostream>
using namespace std;

template < class T >
class HeapSkew : public Drawable
{

   private:
      BinaryTree<T>* bt;
      int sze;
      BinaryTree<T>* merge(BinaryTree<T>* left, BinaryTree<T>* right);

      int (*compare_items) (T* item_1, T* item_2);

   public:
      HeapSkew(int (*comp_items) (T* item_1, T* item_2));
      ~HeapSkew();

      bool heapIsEmpty();
      void heapInsert(T* item);
      T* heapRemove();

      void draw(wxDC& dc, int width, int height);
      void mouseClicked(int x, int y);

};

// this is a MAXHEAP (largest items to top alphabetical order)
template < class T >
HeapSkew<T>::HeapSkew(int (*comp_items) (T* item_1, T* item_2)) : Drawable()
{ 
   bt = new BinaryTree<T>();
   sze = 0;

   compare_items = comp_items;
}

template < class T >
HeapSkew<T>::~HeapSkew() 
{ 
   delete bt;
}  

template < class T >
bool HeapSkew<T>::heapIsEmpty()
{
   return sze == 0;
}

template < class T >
BinaryTree<T>* HeapSkew<T>::merge(BinaryTree<T>* left, BinaryTree<T>* right)
{
  //DO THIS
	if(left == NULL)
	{
		return right;
	}
	cout << "1\n";
	if(right == NULL)
	{
		return left;
	}
	cout << "Pre Comp\n";
	T* left_root = left->getRootItem();
	T* right_root = right->getRootItem();
	cout << "Got Subs..." << endl;
	int comp = (*compare_items) (left_root, right_root);
	cout << "Comp = " << comp << endl;
	if(comp == -1) //Left less than right
	{
		cout << "3\n";
		return merge(right, left);
	}
	BinaryTree<T>* LL = left->detachLeftSubtree();
	cout << "4\n";
	BinaryTree<T>* LR = left->detachRightSubtree();
	cout << "5\n";
	left->attachRightSubtree(LL);
	cout << "6\n";
	if(LR == NULL)
	{
		cout << "7\n";
		left->attachLeftSubtree(right);
	}
	else
	{
		cout << "8\n";
		left->attachLeftSubtree(merge(LR, right));
	}
	cout << "9\n";
	delete LL;
	delete LR;
	cout << "10\n";
	return left;
}

template < class T >
void HeapSkew<T>::heapInsert(T* item)
{
   //DO THIS (calls merge, should be short)
   BinaryTree<T>* right = new BinaryTree<T> (item);
   bt = merge(bt, right);
   delete right;
}

template < class T >
T* HeapSkew<T>::heapRemove()
{
   //DO THIS (calls merge, should be short)
    T* item = bt->getRootItem();
	BinaryTree<T>* left = bt->detachLeftSubtree();
	BinaryTree<T>* right = bt->detachRightSubtree();
	bt = merge(left, right);
	delete left;
	delete right;
	return item;



}

template < class T >
void HeapSkew<T>::draw(wxDC& dc, int width, int height)
{
   bt->draw(dc, width, height);
}

template < class T >
void HeapSkew<T>::mouseClicked(int x, int y) {bt->mouseClicked(x, y);}

#endif
