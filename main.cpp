#include "main.h"
//__stdcall — оно же PASCAL — противоположный C-шному договор
// о передаче параметров в функцию и о том, кто после выполнения
// функции чистит стек. Применяется в Win API.
int main() {
    struct node *BinWood = nullptr;
    insert(2, &BinWood);
    insert(1, &BinWood);
    insert(3, &BinWood);
    insert(5, &BinWood);
    insert(7, &BinWood);
    insert(4, &BinWood);
    insert(-1, &BinWood);
    //BinWood = deleteUnit(2, BinWood);

    show(&BinWood, 0);
    inorder(BinWood);
    std::cout << std::endl;
    preorder(BinWood);
    std::cout << std::endl;
    postorder(BinWood->left);
    postorder(BinWood->right);

    return 0;
}
