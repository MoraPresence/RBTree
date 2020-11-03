#include "RBTree.h"

int main() {
    int way = 0;
    int actionData = 0;
    bool v0 = IsDebuggerPresent();
    if (IsDebuggerPresent())
        return 0;
    rbtree TestTree;
    TestTree.show(&TestTree._root, 0);
    if (!IsDebuggerPresent()) {
        do {
            printf("\nWhat do you want to do?\n");
            printf("1.Insert\n");
            printf("2.Delete\n");
            printf("3.Show\n");
            printf("4.Inorder\n");
            printf("5.Preorder\n");
            printf("6.Postorder\n");
            printf("7.Exit\n");
            printf("Enter your choice:");
            scanf("%d", &way);
            switch (way) {
                case 1:
                    printf("\nEnter The Data for Inserting:");
                    scanf("%d", &actionData);
                    printf("\nInserting!\n\n");
                    TestTree.insert(actionData);
                    break;
                case 2:
                    printf("\nEnter The Data for Deleting:");
                    scanf("%d", &actionData);
                    TestTree.searchUnit(actionData, TestTree._root);
                    break;
                case 3:
                    TestTree.show(&TestTree._root, 0);
                    break;
                case 4:
                    printf("\n");
                    TestTree.inorder(TestTree._root);
                    printf("\n");
                    break;
                case 5:
                    printf("\n");
                    TestTree.preorder(TestTree._root);
                    printf("\n");
                    break;
                case 6:
                    printf("\n");
                    if (TestTree._root) {
                        TestTree.postorder(TestTree._root->left);
                        TestTree.postorder(TestTree._root->right);
                        printf("%d -> ", TestTree._root->data);
                    }

                    printf("\n");
                    v0 = IsDebuggerPresent();
                    break;
                case 7:
                    printf("\nExiting......");
                    return 0;
                default:
                    printf("Please Enter a valid number!!\n");
                    break;
            }
        } while (!v0);
    }
    return 0;
}
