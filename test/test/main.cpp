#include <iostream>
using namespace std;
struct kdNode {
    int key[2];
    kdNode* left, * right;
    kdNode() {
        left = right = NULL;
    }
    kdNode(int in[]) {
        left = right = NULL;
        key[0] = in[0];
        key[1] = in[1];
    }
};
int main(){
	kdNode** a;
	kdNode* b;
	b = new kdNode;
	a = &b;
	delete(*a);
	*a = NULL;
	if (b == NULL)cout << "yes";
	return 0;
}
