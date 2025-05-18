#include <iostream>
#include <cstring>
using namespace std;

struct student {
    long no; /*学号*/
    char name[10]; /*姓名*/
    char sex; /*性别*/
    int age; /*年龄*/
    float score; /*平均成绩*/
};
struct node {
    student data;
    node *next;
};
node *head = NULL;
// 建立链表
void createList() {
    int n;
    cout << "请输入学生人数：";
    cin >> n;
    for (int i = 0; i < n; i++) {
        node *p = new node;
        cout << "请输入第" << i+1 << "个学生的信息：" << endl;
        cout << "学号：";
        cin >> p->data.no;
        cout << "姓名：";
        cin >> p->data.name;
        cout << "性别：";
        cin >> p->data.sex;
        cout << "年龄：";
        cin >> p->data.age;
        cout << "平均成绩：";
        cin >> p->data.score;
        p->next = head;
        head = p;
    }
}
// 遍历链表
void traverseList() {
    node *p = head;
    while (p != NULL) {
        cout << "学号:" << p->data.no ;
        cout << "姓名:" << p->data.name ;
        cout << "性别:" << p->data.sex ;
        cout << "年龄:" << p->data.age ;
        cout << "平均成绩:" << p->data.score <<endl;
        p = p->next;
    }
}
// 插入结点
void insertNode() {
    node *p = new node;
    cout << "请输入要插入的学生的信息：" << endl;
    cout << "学号：";
    cin >> p->data.no;
    cout << "姓名：";
    cin >> p->data.name;
    cout << "性别：";
    cin >> p->data.sex;
    cout << "年龄：";
    cin >> p->data.age;
    cout << "平均成绩：";
    cin >> p->data.score;
    p->next = head;
    head = p;
}

// 删除结点
void deleteNode() {
    long no;
    cout << "请输入要删除的学生的学号：";
    cin >> no;
    node *p = head;
    node *pre = NULL;
    while (p != NULL) {
        if (p->data.no == no) {
            if (pre == NULL) {
                head = p->next;
            } else {
                pre->next = p->next;
            }
            delete p;
            cout << "删除成功！" << endl;
            return;
        }
        pre = p;
        p = p->next;
    }
    cout << "未找到该学生！" << endl;
}
int main() {
    int c;
    while (true) {
        cout << "请选择要进行的操作：" << endl;
        cout << "1.建立链表2.遍历链表3.插入结点4.删除结点5.退出程序"<<endl ;
        cin >> c;
        switch (c) {
            case 1:
                createList();break;
            case 2:
                traverseList(); break;
            case 3:
                insertNode();break;
            case 4:
                deleteNode(); break;
            case 5: return 0;
            default: cout << "输入有误，请重新输入！" << endl;
        }
    }
    return 0;
}
