#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <Windows.h>

//1、给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点。
//示例：
//给定一个链表: 1->2->3->4->5, 和 n = 2.
//当删除了倒数第二个节点后，链表变为 1->2->3->5.
//说明：
//给定的 n 保证是有效的。
//尝试使用一趟扫描实现

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



//2、将两个有序链表合并为一个新的有序链表并返回。
//新链表是通过拼接给定的两个链表的所有节点组成的。
//示例：
//输入：1->2->4, 1->3->4
//输出：1->1->2->3->4->4
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


//给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。
//示例:
//给定 1->2->3->4, 你应该返回 2->1->4->3.
//说明:
//你的算法只能使用常数的额外空间。
//你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
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



//给出一个链表，每 k 个节点一组进行翻转，并返回翻转后的链表。
//k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k 的整数倍，那么将最后剩余节点保持原有顺序。
//示例 :
//给定这个链表：1->2->3->4->5
//当 k = 2 时，应当返回: 2->1->4->3->5
//当 k = 3 时，应当返回: 3->2->1->4->5
//说明 :
//你的算法只能使用常数的额外空间。
//你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
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




//给定一个链表，旋转链表，将链表每个节点向右移动 k 个位置，其中 k 是非负数。
//
//示例 1:
//
//输入: 1->2->3->4->5->NULL, k = 2
//输出: 4->5->1->2->3->NULL
//解释:
//向右旋转 1 步: 5->1->2->3->4->NULL
//向右旋转 2 步: 4->5->1->2->3->NULL
//示例 2:
//
//输入: 0->1->2->NULL, k = 4
//输出: 2->0->1->NULL
//解释:
//向右旋转 1 步: 2->0->1->NULL
//向右旋转 2 步: 1->2->0->NULL
//向右旋转 3 步: 0->1->2->NULL
//向右旋转 4 步: 2->0->1->NULL
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





