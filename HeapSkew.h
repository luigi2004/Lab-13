#if !defined (HEAPSKEW_H)
#define HEAPSKEW_H

#include "BinaryTree.h"

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
      virtual ~HeapSkew();

      bool heapIsEmpty();
      void heapInsert(T* item);
      T* heapRemove();

      void draw(Cairo::RefPtr<Cairo::Context> cr, int width, int height);
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

	if(left->isEmpty()) return right;
	if(right->isEmpty()) return left;
	
	int comp = (compare_items) (left->getItem(), right->getItem);
	if(comp < 0) merge(right, left);
	
	BinaryTree<T>* ll = left->detatchLeftSubtree();
	BinaryTree<T>* lr = left->detatchRightSubtree();
	
	left->attachRightSubtree(ll);
	if(lr->isEmpty()) 
	{
		ll->attachLeftSubtree(right);
	}
	else
	{
		BinaryTree<T>* new_tree = merge(lr, right);
		ll->attachLeftSubtree(new_tree);
	}
	
	return left;


}

template < class T >
void HeapSkew<T>::heapInsert(T* item)
{
   //DO THIS (calls merge, should be short)
	BinaryTree<T>* left = bt;
	BinaryTree<T>* right = new BinaryTree<T>(item);
	bt = merge(left,right);

   sze++;
}

template < class T >
T* HeapSkew<T>::heapRemove()
{
   //DO THIS (calls merge, should be short)
	BinaryTree<T>* left = bt->detatchLeftSubtree();
	BinaryTree<T>* right = bt->detatchRightSubtree();




   sze--;
   return result;
}

template < class T >
void HeapSkew<T>::draw(Cairo::RefPtr<Cairo::Context> cr, int width, int height)
{
   bt->draw(cr, width, height);
}

template < class T >
void HeapSkew<T>::mouseClicked(int x, int y) {bt->mouseClicked(x, y);}

#endif
