//基于顺序表实现的图书管理系统
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXSIZE 100

//定义一个BookInformation的结构体,储存单本书籍的信息
typedef struct{
    char ISBN_Number[100];   //图书的ISBN号码
    char NameOfBook[100];   //书籍的名称
    double price = NULL;           //图书的价格
}BookInformation;

BookInformation book[MAXSIZE];

//初始化表
void InitList(BookInformation *book){
    //for(int i = 0; i < MAXSIZE; i++)
        //book[i].price = NULL;
}

//统计整个表中有多少本图书
int CountList(BookInformation *book){
    int count = 0;
    while(book[count].price != NULL){
        count++;
    }
    return count;
}

//读取新书籍
void AddBook(BookInformation *book){
    int i = 0;
    printf("请输入图书信息\n");
    printf("输入“0 0 0 ”表示输入结束\n");
    while(1){
        scanf("\n%s %s %lf",book[i].ISBN_Number,book[i].NameOfBook,&book[i].price);
        if(book[i].price == 0){
            break;
        }
        i++;
    }
}

//打印整个表，显示其中的信息
void DisplayList(BookInformation *book){
    if(book[0].price == NULL){
        printf("表中无图书\n");
        return;
    }
    for(int i = 0;book[i].price != NULL; i++)
        printf("%s %s %.2f\n",book[i].ISBN_Number,book[i].NameOfBook,book[i].price);
}

//计算平均价格
double AverageOfBook(BookInformation *book){
    double sum = 0,average;
    for(int i = 0;book[i].price != NULL; i++){
        sum += book[i].price;
    }
    average = sum/CountList(book);
    return average;
}

//根据平均价格修改图书价格
void ChangePrice(BookInformation *book){
    double average = AverageOfBook(book);
    for(int i = 0;book[i].price != NULL; i++){
        if(book[i].price < average){
            //这里是永久修改书籍价格的代码
            book[i].price = book[i].price * 1.2;
            printf("%s %s %.2f\n",book[i].ISBN_Number,book[i].NameOfBook,book[i].price);
            //未修改书籍价格的代码在下面一行的注释中
            //else的内容同此，不再额外注释
            //printf("%s %s %.2f\n",book->ISBN_Number,book->NameOfBook,book->price * 1.2);
        }
        else{
            book[i].price = book[i].price * 1.1;
            printf("%s %s %.2f\n",book[i].ISBN_Number,book[i].NameOfBook,book[i].price);
            //printf("%s %s %.2f\n",book->ISBN_Number,book->NameOfBook,book->price * 1.1);
        }
    }
    printf("修改完毕\n");
}

//逆序输出图书表
void ReserveOutput(BookInformation *book){
    int count = CountList(book);
    for(int i = count -1 ; i >= 0 ; i--){
        printf("%s %s %.2f\n",book[i].ISBN_Number,book[i].NameOfBook,book[i].price);
    }
}

//查询最高价格
double SearchHighestPrice(BookInformation *book){
    double max = 0;
    for(int i = 0;i < CountList(book);i++){
        if(max <= book[i].price)
            max = book[i].price;
    }
    return max;
}

//输出最高价图书
void MaxPeiceBook(BookInformation *book){
    double MaxPrice = SearchHighestPrice(book);
    for(int i = 0;i < CountList(book);i++)
        if(book[i].price == MaxPrice)
            printf("%s %s %.2f",book[i].ISBN_Number,book[i].NameOfBook,book[i].price);
}

//新图书入库
void NewBook(BookInformation *book,int newnumber,BookInformation newbook){
    int i = 0,count = CountList(book);
    if(newnumber > count + 1 || newnumber <= 0){
        //newnumber的值有限制，例如原有6本书，newnumber最大为7，最小为1
        printf("无法插入，请重新输入\n");
        return;
    }
    for(i = count;i>=newnumber;i--)
        book[i] = book[i-1];
    book[newnumber-1] = newbook;
    printf("新表格如下：\n");
    DisplayList(book);
}

//旧图书出库
void OldBook(BookInformation *book,int oldnumber){
    int i = 0,count = CountList(book);
    if(oldnumber <= 0 || oldnumber > count){
        //oldnumber的值有限制，要大于0，小于等于总数
        printf("无法出库，请重新输入\n");
        return;
    }
    for(i=oldnumber-1;i<count;i++)
        book[i] = book[i+1];
    printf("新表格如下：\n");
    DisplayList(book);
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
    printf("这是一个图书管理系统\n");
    int flag = 0;
    //用flag判断用户是否选择了创建一个表
    while(1){
        ChoicesDisplay();
        printf("请输入选项：\n");
        scanf("%d",&choice);
        switch(choice){
            case 1 :
                flag = 1;
                printf("创建完成\n");
                break;
            
            case 2 :
                if(flag == 0){
                    printf("未创建表，无法操作\n");
                    break;
                }
                InitList(book);
                printf("初始化成功\n");
                break;
            
            case 3 :{
                if(flag == 0){
                    printf("未创建表，无法操作\n");
                    break;
                }
                AddBook(book);
                break;
            }
            
            case 4 :{
                if(flag == 0){
                    printf("未创建表，无法操作\n");
                    break;
                }
                DisplayList(book);
                break;
            }

            case 5 :{
                if(flag == 0){
                    printf("未创建表，无法操作\n");
                    break;
                }
                ReserveOutput(book);
                printf("输出完毕\n");
                break;
            }
            
            case 6 :{
                if(flag == 0){
                    printf("未创建表，无法操作\n");
                    break;
                }
                ChangePrice(book);
                break;
            }

            case 7 :{
                if(flag == 0){
                    printf("未创建表，无法操作\n");
                    break;
                }
                MaxPeiceBook(book);
                printf("查询成功\n");
                break;
            }

            case 8 :{
                if(flag == 0){
                    printf("未创建表，无法操作\n");
                    break;
                }
                BookInformation newbook;
                InitList(&newbook);
                int newnumber;
                printf("请输入新书的序号：\n");
                scanf("%d",&newnumber);
                printf("请输入新书的信息：\n");
                printf("(格式：ISBN号 书名 价格)\n");
                scanf("%s %s %lf",&newbook.ISBN_Number,&newbook.NameOfBook,&newbook.price);
                NewBook(book,newnumber,newbook);
                printf("入库完毕\n");
                break;
            }

            case 9 :{
                if(flag == 0){
                    printf("未创建表，无法操作\n");
                    break;
                }
                int oldnumber;
                printf("请输入要出库的书籍序号：\n");
                scanf("%d",&oldnumber);
                OldBook(book,oldnumber);
                printf("出库完毕\n");
                break;
            }      
            
            case 10 :
                exit(0);
            
            default :
                printf("输入有误，请重新输入\n");
                break;
        }
    }
    return 0;
}