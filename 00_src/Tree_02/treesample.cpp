#include "TreeClass.cpp"


int main(void)
{
	TreeClass<int> * tree = new TreeClass<int>;
	tree->BuildTree(tree);
	tree->PRINT(tree);
	tree->Delete(tree);
	return 0;
}