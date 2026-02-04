// Definition for singly-linked list.
class ListNode {
    int val;
    ListNode next;
    ListNode(int val) { this.val = val; }
}

@SuppressWarnings("unused")
class Solution {
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        int partSum = l1.val + l2.val;
        int carry = partSum / 10; partSum %= 10;

        ListNode sum = new ListNode(partSum);
        l1 = l1.next; l2 = l2.next;

        ListNode temp = sum;
        while(l1 != null && l2 != null) {
            partSum = l1.val + l2.val + carry;
            carry = partSum / 10; partSum %= 10;

            temp.next = new ListNode(partSum);
            l1 = l1.next; l2 = l2.next;
            temp = temp.next;
        }
        while(l1 != null) {
            partSum = l1.val + carry;
            carry = partSum / 10; partSum %= 10;

            temp.next = new ListNode(partSum);
            temp = temp.next; l1 = l1.next;
        }
        while(l2 != null) {
            partSum = l2.val + carry;
            carry = partSum / 10; partSum %= 10;
            
            temp.next = new ListNode(partSum);
            temp = temp.next; l2 = l2.next;
        }
        if(carry != 0) temp.next = new ListNode(carry);
        return sum;
    }
}

/* old version with broken integer overflows
class Solution {
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        int num1 = 0, num2 = 0;

        ListNode temp = l1; int pow = 0;
        while(temp != null) {
            num1 += temp.val * (int)Math.pow(10, pow++);
            temp = temp.next;
        }
        temp = l2; pow = 0;
        while(temp != null) {
            num2 += temp.val * (int)Math.pow(10, pow++);
            temp = temp.next;
        }
        int sum = num1 + num2;
        ListNode lsum = new ListNode(sum % 10);
        sum /= 10; temp = lsum;
        while(sum > 0) {
            temp.next = new ListNode(sum % 10);
            sum /= 10; temp = temp.next;
        }
        return lsum;
    }
}
*/