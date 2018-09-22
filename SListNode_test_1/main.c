#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <Windows.h>

//1������һ������ɾ������ĵ����� n ���ڵ㣬���ҷ��������ͷ��㡣
//ʾ����
//����һ������: 1->2->3->4->5, �� n = 2.
//��ɾ���˵����ڶ����ڵ�������Ϊ 1->2->3->5.
//˵����
//������ n ��֤����Ч�ġ�
//����ʹ��һ��ɨ��ʵ��

 //Definition for singly-linked list.
 struct ListNode {
     int val;
     struct ListNode *next;
 };

struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    struct ListNode *fast = head;
    struct ListNode *slow = head;
    struct ListNode *prv = fast;
    while(n){
        slow = slow->next;
        n--;
    }
    if(slow != NULL){
        while(slow != NULL){
            prv = fast;
            fast = fast->next;
            slow = slow->next;
        }
        prv->next = fast->next;
        free(fast);
    }
    else{
        head = head->next;
        free(fast);
    }
    
    return head;
}



//2����������������ϲ�Ϊһ���µ������������ء�
//��������ͨ��ƴ�Ӹ�����������������нڵ���ɵġ�
//ʾ����
//���룺1->2->4, 1->3->4
//�����1->1->2->3->4->4
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    if(l1 == NULL){
        return l2;
    }
    if(l2 == NULL){
        return l1;
    }
    struct ListNode *head = NULL;
    if(l1->val >= l2->val){
        head = l2;
        head->next = mergeTwoLists(l1, l2->next);
    }
    if(l1->val < l2->val){
        head = l1;
        head->next = mergeTwoLists(l1->next, l2);
    }
    
    return head;
}


//����һ���������������������ڵĽڵ㣬�����ؽ����������
//ʾ��:
//���� 1->2->3->4, ��Ӧ�÷��� 2->1->4->3.
//˵��:
//����㷨ֻ��ʹ�ó����Ķ���ռ䡣
//�㲻��ֻ�ǵ����ĸı�ڵ��ڲ���ֵ��������Ҫʵ�ʵĽ��нڵ㽻����
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* swapPairs(struct ListNode* head) {
    if(head == NULL){
        return;
    }
    struct ListNode* left = head;
    struct ListNode* right = head->next;
    struct ListNode* prv = left;
    int flag = 1;
    while(left != NULL && right != NULL){
        left->next = right->next;
        right->next = left;
        if(flag){
            head = right;
            flag--;
        }
        else{
            prv->next = right;
        }
        prv = left;
        left = left->next;
        if(left != NULL){
            right = left->next;
        }
    }
    
    return head;
}



//����һ������ÿ k ���ڵ�һ����з�ת�������ط�ת�������
//k ��һ��������������ֵС�ڻ��������ĳ��ȡ�����ڵ��������� k ������������ô�����ʣ��ڵ㱣��ԭ��˳��
//ʾ�� :
//�����������1->2->3->4->5
//�� k = 2 ʱ��Ӧ������: 2->1->4->3->5
//�� k = 3 ʱ��Ӧ������: 3->2->1->4->5
//˵�� :
//����㷨ֻ��ʹ�ó����Ķ���ռ䡣
//�㲻��ֻ�ǵ����ĸı�ڵ��ڲ���ֵ��������Ҫʵ�ʵĽ��нڵ㽻����
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
typedef struct ListNode ListNode;
struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    if(head == NULL){
        return NULL;
    }
    if(k == 1){
        return head;
    }
    int n = 0;
    ListNode* node = head;
    while(node != NULL){
        node = node->next;
        n++;
    }
    if(n < k){
        return head;
    }
    int m = n/k;
    ListNode* tail = head->next;
    ListNode* newhead = head;
    ListNode* prv = head;
    node = prv->next;
    int flag = 1;
    int i = 0;
    while(m){
        i = k;
        while(i-2 > 0){
            tail = tail->next;
            i--;
        }
        i = k;
        while(i-1){
            prv->next = tail->next;
            tail->next = prv;
            prv = node;
            node = node->next;
            i--;
        }
        if(flag)
        {
            head = prv;
            flag--;
        }
        else{
            newhead->next = prv;
        }
        
        i = k;
        while(i-1){
            prv = prv->next;
            i--;
        }
        newhead = prv;
        if(prv->next != NULL){
            prv = prv->next;
            tail = prv->next;
            node = prv->next;
        }
            
        m--;
    }
    
    return head;
}




//����һ��������ת����������ÿ���ڵ������ƶ� k ��λ�ã����� k �ǷǸ�����
//
//ʾ�� 1:
//
//����: 1->2->3->4->5->NULL, k = 2
//���: 4->5->1->2->3->NULL
//����:
//������ת 1 ��: 5->1->2->3->4->NULL
//������ת 2 ��: 4->5->1->2->3->NULL
//ʾ�� 2:
//
//����: 0->1->2->NULL, k = 4
//���: 2->0->1->NULL
//����:
//������ת 1 ��: 2->0->1->NULL
//������ת 2 ��: 1->2->0->NULL
//������ת 3 ��: 0->1->2->NULL
//������ת 4 ��: 2->0->1->NULL
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
typedef struct ListNode ListNode;
struct ListNode* rotateRight(struct ListNode* head, int k) {
    if(head == NULL){
        return NULL;
    }
    if(head->next == NULL){
        return head;
    }
    int n;
    ListNode* node = head;
    while(node != NULL){
        node = node->next;
        n++;
    }
    k = k % n;
    while(k){
        struct ListNode* tile = head;
        node = head->next;
        while(node->next != NULL){
            tile = tile->next;
            node = node->next;
        }
        tile->next = node->next;
        node->next = head;
        head = node;
        k--;
    }
    
    return head;
}





