//基于链表的书籍管理系统
#include<stdio.h>
#include <stdlib.h>

//定义一个结点，包含书籍信息
typedef struct BookInformation{
    char ISBN_Number[100];//书籍的ISBN号码
    char Title[100];//书籍标题
    double Price;//书籍价格
    BookInformation *next;//下一本书的地址
}BookInformation;

//定义一个头结点
BookInformation *head = NULL;

//新建一个结点,返回新结点的地址
BookInformation* NewNode(){
    BookInformation *newbook = (BookInformation *)malloc(sizeof(BookInformation));
    //用malloc分配内存给newbook，分配失败会返回null，成功返回地址
    //malloc返回的地址是“void*”类型，它不限定指针指向的数据的类型，因此这里强制转换类型
    return newbook;
}

//初始化表
void InitList(){
    head = NULL;
    printf("初始化完毕\n");
}

//读取新书籍
void AddBook(BookInformation *NewBook){
    //这里用尾插将新书加入列表
    NewBook->next = NULL;
    if(head == NULL){
        head = NewBook;
        return;
        //head==NULL表明是空表
        //head直接指向新书
    }
    else{
        BookInformation *current = head;
        while (current->next != NULL) {
            //用遍历去寻找尾节点，将尾节点的信息存在current里
            current = current->next;
        }
        current->next = NewBook;
    }
}

//显示所有书籍信息
void Display(){
    BookInformation *current = head;
    while(current != NULL){
        printf("%s %s %.2f\n",current->ISBN_Number,current->Title,current->Price);
        current = current->next;
    }
    printf("显示完毕\n");
}

//统计书籍数量
int Count(){
    BookInformation *current = head;
    int count = 0;
    while(current != NULL){
        count++;
        current = current->next;
    }
    return count;
}

//计算平均价格
double Average(){
    double sum = 0,ave;
    BookInformation *current = head;
    while(current != NULL){
        sum += current->Price;
        current = current->next;
    }
    ave = sum / Count();
    return ave;
}

//根据平均价格修改书籍信息
void ChangePrice(){
    double ave = Average();
    BookInformation *current = head;
    while(current != NULL){
        if(current->Price >= ave)
            current->Price = current->Price * 1.1;
        else
            current->Price = current->Price * 1.2;
        current = current->next;
    }
}

//查询最高价格
double SearchHighest(){
    double max = 0;
    BookInformation *current = head;
    while (current != NULL){
        if(max < current->Price)
            max = current->Price;
        current = current->next;
    }
    return max;
}

//逆序输出表格
//recursiveReverseDisplay和reverseDisplayBooks两个函数来自ChatGPT
//用以实现链表的逆序输出，且不改变链表本身
//函数用递归实现了功能
void recursiveReverseDisplay(BookInformation *current){
    if (current == NULL) {
        return;
    }
    recursiveReverseDisplay(current->next);
    printf("%s ",current->ISBN_Number);
    printf("%s ", current->Title);
    printf("%.2f\n", current->Price);
}

void reverseDisplay(){
    if (head == NULL) {
        printf("书库为空\n");
        return;
    }
    printf("书籍如下：\n");
    recursiveReverseDisplay(head);
}

//新图书的入库
void NewBook(){
    int newnumber;
    BookInformation *newbook = NewNode();
    BookInformation *current = head, *next = current->next;
    printf("请输入新书的序号：\n");
    scanf("%d",&newnumber);
    int count = Count();
    if(newnumber <= 0 || newnumber > count + 1){
        //newnumber的数值有限制
        //例如：原先由6本，newnumber就要大于等于0、小于等于7，7表示在最后添加
        printf("入库位置非法\n");
        return;
    }
    printf("请输入新书的ISBN号码：\n");
    scanf("%s",newbook->ISBN_Number);
    printf("请输入新书的书名：\n");
    scanf("%s",newbook->Title);
    printf("请输入新书的价格：\n");
    scanf("%lf",&newbook->Price);
    int flag = 0;
    //需要遍历链表才能找到目标位置
    //用flag记录实时位置
    //与newnumber比较来确认是否到达目标位置
    //flag代表current当前位置，next代表修改前current的下一位置
    while(current != NULL){
        if(flag + 1 == newnumber){
            newbook->next = next;
            current->next = newbook;
            break;
        }
        flag++;
        if(current->next != NULL){
            current = current->next;
            next = next->next;
        }
        else
            break;
    }
}

//旧图书出库
void OldBook(){
    int oldnumber;
    printf("请输入目标图书的序号：\n");
    scanf("%d",&oldnumber);
    if(oldnumber <= 0 || oldnumber > Count()){
        printf("出库位置非法\n");
        return;
    }
    int flag = 0;
    BookInformation *current = head;//用flag来记录current位置
    BookInformation *nextbook = current->next;//current的后一本书
    BookInformation *previous = NULL;//current的前一本书
   while(current != NULL){
    if(flag == oldnumber){
        if(previous == NULL){
            head = current->next;
        } else {
            previous->next = current->next;
        }
        free(current);
        break;
    }
    flag++;
    if(current->next != NULL){
        previous = current;
        current = current->next;
        nextbook = nextbook->next;
    } else {
        break;
    }
}

}

//所有可选项
void ChoicesDisplay(){
    printf("请选择你要进行的操作：\n");
    printf("【1】、创建一个图书表；\n");
    printf("【2】、初始化图书表；\n");
    printf("【3】、输入图书信息；\n");
    printf("【4】、显示所有图书信息；\n");
    printf("【5】、逆序显示所有图书信息；\n");
    printf("【6】、根据平均价格修改书籍信息；\n");
    printf("【7】、查询最高价格的图书；\n");
    printf("【8】、新图书入库；\n");
    printf("【9】、旧图书出库；\n");
    printf("【10】、退出。\n");
}

//主函数
int main(){
    

    int choice;
    ChoicesDisplay();
    printf("请输入：");
    scanf("%d",&choice);
    int flag = 0;
    //用flag判断用户是否选择创建表
    while(1){
        switch(choice){
            case 1 :{//创建
                flag = 1;
                printf("创建成功\n");
                break;
            }

            case 2 :{//初始化
                InitList();
                break;
            }

            case 3 :{//输入信息
                printf("请输入图书信息\n");
                printf("输入“0 0 0 ”表示输入结束\n");
                BookInformation *newbook = NewNode();
                while(1){
                    newbook = NewNode();
                    scanf("\n%s %s %lf",newbook->ISBN_Number,newbook->Title,&newbook->Price);
                    if(newbook->Price == 0.00)
                        break;
                    AddBook(newbook);
                }
                break;
            }
            
            case 4 :{//显示所有书籍
                Display();
                break;
            }

            case 5 :{//逆序输出所有书籍
                reverseDisplay();
                break;
            }

            case 6 :{//根据平均数修改价格并输出
                ChangePrice();
                printf("平均价格：");
                printf("%.2f\n",Average());
                printf("修改后如下：\n");
                Display();
                break;
            }

            case 7 :{//查询并输出最高价图书
                BookInformation *current = head;
                double max = SearchHighest();
                while(current != NULL){
                    if(max == current->Price){
                        printf("%s %s %.2f\n",current->ISBN_Number,current->Title,current->Price);
                        break;
                    }
                    current = current->next;
                }
                printf("查询完毕\n");
                break;
            }
            
            case 8 :{//新书籍入库
                NewBook();
                printf("新书库如下：\n");
                Display();
                break;
            }

            case 9 :{//旧图书出库
                OldBook();
                printf("修改后书库如下：\n");
                Display();
                break;
            }

            case 10 :{//退出
                exit(0);
            }
            
            default :{
                printf("选项输入有误，请重新输入\n");
                break;
            }
        }
        ChoicesDisplay();
        printf("请输入选项：\n");
        scanf("%d",&choice);
    }
    return 0;
}